#!/bin/bash

function usage() {
	echo "Usage: o-ran-user-config.sh [OPTIONS]"
	echo ""
	echo "The o-ran-usermgmt.yang module cannot be loaded without at least one"
	echo "enabled user. This script configures default users for the"
	echo "o-ran-usermgmt module."
	echo ""
	echo "OPTIONS:"
	echo "    -u | --userlist <filepath>, Path to user list input where each"
	echo "        line is of the form user:group:password. If no user list is"
	echo "        present, installs a default root user."
	echo "        (default: /usr/share/mplane-server/userlist)"
	echo "    -m | --modules <dirpath>, YANG module directory."
	echo "        (default: /usr/share/mplane-server/modules)"
	echo "    -s | --sysrepo-path <dirpath>, Sysrepo applications path."
	echo "        (default: /usr/local/bin)"
	echo "    -h | --help, Print this help message and exit."
	echo
}

##----------------------------------------------------------------------------------------------------------------------
# Globals
##----------------------------------------------------------------------------------------------------------------------
USERLIST=/usr/share/mplane-server/userlist
MODDIR=/usr/share/mplane-server/modules
SYSREPOCTL=/usr/local/bin/sysrepoctl
SYSREPOCFG=/usr/local/bin/sysrepocfg

OWNER=$USER
GROUP=$USER

ROOT_USER=root

USER_GROUPS="SUDO NMS FM-PM SWM SMO HYBRID-ODU"

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
# readUserList()
# Read user list file if present
##----------------------------------------------------------------------------------------------------------------------
readUserList()
{
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

			var=${group^^}
			var=${var//[-]/_}

			eval ${var}_USER=$user
			eval ${var}_GROUP=$group
			eval ${var}_PASSWD=$passwd

		done < "$USERLIST"
	fi
}


##----------------------------------------------------------------------------------------------------------------------
# startAcm()
# Set ietf-netconf-acm groups/users
##----------------------------------------------------------------------------------------------------------------------
startAcm()
{
	# import default config
	CONFIG="<nacm xmlns=\"urn:ietf:params:xml:ns:yang:ietf-netconf-acm\">
  <enable-nacm>true</enable-nacm>
  <read-default>permit</read-default>
  <write-default>deny</write-default>
  <exec-default>permit</exec-default>
  <groups>
    <group>
      <name>root</name>
      <user-name>$ROOT_USER</user-name>
    </group>"

	for group in $USER_GROUPS
	do
		group_name_var=${group//[-]/_}_GROUP
		group_user_var=${group//[-]/_}_USER
		if [ ! -z "${!group_name_var}" ]; then
			CONFIG+="
    <group>
      <name>${!group_name_var}</name>
      <user-name>${!group_user_var}</user-name>
    </group>"
		fi
	done

	CONFIG+="
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

	# import default config
	CONFIG="<users xmlns=\"urn:o-ran:user-mgmt:1.0\">
    <user>
        <name>$ROOT_USER</name>
        <account-type>PASSWORD</account-type>
        <enabled>true</enabled>
    </user>"

	for group in $USER_GROUPS
	do
		group_user_var=${group//[-]/_}_USER
		if [ ! -z "${!group_user_var}" ]; then
			CONFIG+="
    <user>
        <name>${!group_user_var}</name>
        <account-type>PASSWORD</account-type>
        <enabled>true</enabled>
    </user>"
		fi
	done

	CONFIG+="
</users>"

	TMPFILE=`mktemp -u`
	printf -- "$CONFIG" > $TMPFILE
	# apply it to startup and running
	$SYSREPOCFG -W $TMPFILE -d startup -f xml -m o-ran-usermgmt -v2
	$SYSREPOCFG -C startup -m o-ran-usermgmt -v2
	# remove the tmp file
	rm $TMPFILE
}

##=== MAIN =============================================================================================================

# Parse options
while [[ $# -gt 0 ]]; do
	case $1 in
		-u|--userlist)
			USERLIST="${2}"
			shift
			;;
		-m|--modules)
			MODDIR="${2}"
			shift
			;;
		-s|--sysrepo-path)
			sysrepodir="${2}"
			SYSREPOCTL="${sysrepodir}/sysrepoctl"
			SYSREPOCFG="${sysrepodir}/sysrepocfg"
			shift
			;;
		-h|--help)
			usage
			exit 0
			;;
		*) echo "Unknown option: ${1}"
			exit 1
			;;
	esac
	shift
done

echo "Reading user list"
readUserList

echo "Starting ACM"
startAcm

echo "Starting user management"
startUsermgmt

echo "Done."
