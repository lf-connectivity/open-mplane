#!/bin/sh 
# Install fault config file

FAULT_INSTALLED=/usr/share/fault-config
FAULT_STORED=/nandflash/configdata


start()
{
	mkdir -p $FAULT_STORED

	# copy config
	echo Installing YANG configuration file...
	cp $FAULT_INSTALLED/*.xml $FAULT_INSTALLED/*.xsd $FAULT_STORED/
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

