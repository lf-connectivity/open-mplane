#!/bin/sh 
# Install yang config file

YANG_INSTALLED=/usr/share/yang-config
YANG_STORED=/nandflash/configdata


start()
{
	mkdir -p $YANG_STORED

	# copy config
	echo Installing YANG configuration file...
	cp $YANG_INSTALLED/*.xml $YANG_INSTALLED/*.xsd $YANG_STORED/
}

stop()
{
    echo "  "
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
        start
    ;;
    *)
        echo >&2 "$0 - '$1' invalid action"
        exit 2
    ;;
esac

