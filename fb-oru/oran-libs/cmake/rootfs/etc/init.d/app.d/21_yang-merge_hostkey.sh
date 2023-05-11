#!/bin/sh 

#set -e

SYSREPOCFG=/usr/local/bin/sysrepocfg
OPENSSL=/usr/local/bin/openssl

start()
{

# check that there is no SSH key with this name yet
KEYSTORE_KEY=`$SYSREPOCFG -X -x "/ietf-keystore:keystore/asymmetric-keys/asymmetric-key[name='genkey']/name"`
if [ ! -z "$KEYSTORE_KEY" ]; then
    exit
fi

# generate a new key
PRIVPEM=`$OPENSSL genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 -outform PEM 2>/dev/null`
# remove header/footer
PRIVKEY=`grep -v -- "-----" - <<STDIN
$PRIVPEM
STDIN`
# get public key
PUBPEM=`$OPENSSL rsa -pubout 2>/dev/null <<STDIN
$PRIVPEM
STDIN`
# remove header/footer
PUBKEY=`grep -v -- "-----" - <<STDIN
$PUBPEM
STDIN`

# generate edit config
CONFIG="<keystore xmlns=\"urn:ietf:params:xml:ns:yang:ietf-keystore\">
    <asymmetric-keys>
        <asymmetric-key>
            <name>genkey</name>
            <algorithm>rsa2048</algorithm>
            <public-key>$PUBKEY</public-key>
            <private-key>$PRIVKEY</private-key>
        </asymmetric-key>
    </asymmetric-keys>
</keystore>"
TMPFILE=`mktemp -u`
printf -- "$CONFIG" > $TMPFILE
# apply it to startup and running
$SYSREPOCFG --edit=$TMPFILE -d startup -f xml -m ietf-keystore -v2
$SYSREPOCFG -C startup -m ietf-keystore -v2
# remove the tmp file
rm $TMPFILE

}

stop()
{
	:
}


case $1 in
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


