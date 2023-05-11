#!/bin/sh

#set -x 

echo ==== 23_yang-user_config.sh ===
echo REPO_PATH=$REPO_PATH

action="${1:-start}"

##----------------------------------------------------------------------------------------------------------------------
# Constants
##----------------------------------------------------------------------------------------------------------------------
SYSREPOCTL=/usr/local/bin/sysrepoctl
SYSREPOCFG=/usr/local/bin/sysrepocfg
USERLIST=/nandflash/.settings/users

MODDIR=/nandflash/yangfiles
OWNER=$USER
GROUP=$USER

# if running under sim
if [ ! -z "$REPO_PATH" ]; then
	MODDIR=$REPO_PATH/../../yangfiles
	SYSREPOCTL=$REPO_PATH/../../bin/sysrepoctl
	SYSREPOCFG=$REPO_PATH/../../bin/sysrepocfg
fi

if [ ! -z "$SCRIPTS_PATH" ]; then
	USERLIST=$SCRIPTS_PATH/../cmake/rootfs/settings/users
fi

ROOT_USER=axis
SUDO_USER=oran
NMS_USER=nmsuser
SWM_USER=swmuser
FM_PM_USER=fmpmuser

##----------------------------------------------------------------------------------------------------------------------
# handle error
##----------------------------------------------------------------------------------------------------------------------
errorMsg()
{
    echo >&2 "******* $@ *******"
}

##----------------------------------------------------------------------------------------------------------------------
# log a message
##----------------------------------------------------------------------------------------------------------------------
logMsg()
{
	msg="[$(date +%T)]: $*"
	echo "$msg"
}


##----------------------------------------------------------------------------------------------------------------------
# Read user list file if present
##----------------------------------------------------------------------------------------------------------------------
if [ -f $USERLIST ]; then

	echo Read user file list...
	while IFS= read line
	do
		if [ -z "$line" ]; then
			continue
		fi
		if [[ "$line" == "#"* ]]; then
			continue
		fi

		IFS=':' read -a strarr <<< "$line"
		
		user=${strarr[0]}
		group=${strarr[1]}
		passwd=${strarr[2]}
		home=${strarr[3]}
		
		var=${group^^}
		var=${var//[-]/_}
		
		eval ${var}_USER=$user
		eval ${var}_GROUP=$group
		eval ${var}_PASSWD=$passwd
		eval ${var}_HOME=$home
		
	done < "$USERLIST"
fi


#echo SUDO_USER=$SUDO_USER
#echo SUDO_GROUP=$SUDO_GROUP
#
#echo SWM_USER=$SWM_USER
#echo SWM_GROUP=$SWM_GROUP
#
#echo NMS_USER=$NMS_USER
#echo NMS_GROUP=$NMS_GROUP
#
#echo FM_PM_USER=$FM_PM_USER
#echo FM_PM_GROUP=$FM_PM_GROUP

##----------------------------------------------------------------------------------------------------------------------
# startAcm()
# Set ietf-netconf-acm groups/users
##----------------------------------------------------------------------------------------------------------------------
startAcm()
{
	# check that there is no listen/Call Home configuration yet
	SERVER_CONFIG=`$SYSREPOCFG -X -x "/ietf-netconf-acm:nacm/groups/group[name='sudo']/name"`
	if [ ! -z "$SERVER_CONFIG" ]; then
	    return
	fi
	
	# import default config
	CONFIG="<nacm xmlns=\"urn:ietf:params:xml:ns:yang:ietf-netconf-acm\">
  <enable-nacm>true</enable-nacm>
  <read-default>permit</read-default>
  <write-default>deny</write-default>
  <exec-default>permit</exec-default>
  <groups>
    <group>
      <name>$SUDO_GROUP</name>
      <user-name>$SUDO_USER</user-name>
    </group>
    <group>
      <name>$SWM_GROUP</name>
      <user-name>$SWM_USER</user-name>
    </group>
    <group>
      <name>$NMS_GROUP</name>
      <user-name>$NMS_USER</user-name>
    </group>
    <group>
      <name>$FM_PM_GROUP</name>
      <user-name>$FM_PM_USER</user-name>
    </group>
    <group>
      <name>root</name>
      <user-name>$ROOT_USER</user-name>
    </group>
  </groups>
</nacm>"
	TMPFILE=`mktemp -u`
	printf -- "$CONFIG" > $TMPFILE
	# apply it to startup and running
	$SYSREPOCFG --edit=$TMPFILE -d startup -f xml -m ietf-netconf-acm -v2
	$SYSREPOCFG -C startup -m ietf-netconf-acm -v2
	# remove the tmp file
	rm $TMPFILE
}


##----------------------------------------------------------------------------------------------------------------------
# install_module()
##----------------------------------------------------------------------------------------------------------------------
install_module() 
{
    $SYSREPOCTL -a -i $MODDIR/$1 -s $MODDIR -o $OWNER -g $GROUP -v2
    local rc=$?
    if [ $rc -ne 0 ]; then
        exit $rc
    fi
}

##----------------------------------------------------------------------------------------------------------------------
# update_module()
##----------------------------------------------------------------------------------------------------------------------
update_module() 
{
    $SYSREPOCTL -a -U $MODDIR/$1 -s $MODDIR -o $OWNER -g $GROUP -v2
    local rc=$?
    if [ $rc -ne 0 ]; then
        exit $rc
    fi
}

##----------------------------------------------------------------------------------------------------------------------
# startUsermgmt()
# Set startup data for o-ran-usermgmt
##----------------------------------------------------------------------------------------------------------------------
startUsermgmt()
{
	name=o-ran-usermgmt
	
	# get current modules
	SCTL_MODULES=`$SYSREPOCTL -l`
	
	# install module if not installed yet
    SCTL_MODULE=`echo "$SCTL_MODULES" | grep "^$name \+|[^|]*| I"`
    if [ -z "$SCTL_MODULE" ]; then
        # install module with all its features
        $SYSREPOCTL -i $MODDIR/$name.yang -s $MODDIR -v2 
    fi
    
    # For debug
    # $SYSREPOCTL -l
	
	# check that there is no user configuration yet
	SERVER_CONFIG=`$SYSREPOCFG -X -x "/o-ran-usermgmt:users/user[name='$ORAN_USER']/name"`
	if [ ! -z "$SERVER_CONFIG" ]; then
	    return
	fi
	
	# import default config
	CONFIG="<users xmlns=\"urn:o-ran:user-mgmt:1.0\">
    <user>
        <name>$SUDO_USER</name>
        <account-type>PASSWORD</account-type>
        <enabled>true</enabled>
    </user>
    <user>
        <name>$NMS_USER</name>
        <account-type>PASSWORD</account-type>
        <enabled>true</enabled>
    </user>
    <user>
        <name>$SWM_USER</name>
        <account-type>PASSWORD</account-type>
        <enabled>true</enabled>
    </user>
    <user>
        <name>$FM_PM_USER</name>
        <account-type>PASSWORD</account-type>
        <enabled>true</enabled>
    </user>
    <user>
        <name>$ROOT_USER</name>
        <account-type>PASSWORD</account-type>
        <enabled>true</enabled>
    </user>
    
</users>
	"
	TMPFILE=`mktemp -u`
	printf -- "$CONFIG" > $TMPFILE
	# apply it to startup and running
	$SYSREPOCFG -W $TMPFILE -d startup -f xml -m o-ran-usermgmt -v2
	$SYSREPOCFG -C startup -m o-ran-usermgmt -v2
	# remove the tmp file
	rm $TMPFILE
	
	
	# For debug
    # $SYSREPOCTL -l
}


##----------------------------------------------------------------------------------------------------------------------
# start()
##----------------------------------------------------------------------------------------------------------------------
start()
{
	echo Start ACM...
	startAcm
	
	echo Start user management...
	startUsermgmt
}

##----------------------------------------------------------------------------------------------------------------------
# stop()
##----------------------------------------------------------------------------------------------------------------------
stop()
{
	:
}


##=== MAIN =============================================================================================================

case $action in
    start)
		start
	;;
    stop)
    	stop
	;;
    restart)
    	stop
    	sleep 1
		start
	;;
    *)
    	echo >&2 "$0 - '$1' invalid action"
	exit 2
	;;
esac

echo YANG user config complete
exit 0

