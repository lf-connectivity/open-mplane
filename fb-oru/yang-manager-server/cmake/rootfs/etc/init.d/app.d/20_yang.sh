#!/bin/sh 
# Install yang model files

YANG_INSTALLED=/usr/share/yang-models
YANG_STORED=/nandflash/yangfiles
YANG_STAGING=/tmp/yang-models
YANG_TMP=/tmp/yang-tmp
YANG_DIFF=$YANG_TMP/yang.diff

start()
{
	mkdir -p $YANG_STORED
	mkdir -p $YANG_STAGING
	mkdir -p $YANG_TMP
	
	# copy files to temporary staging area
	cd $YANG_INSTALLED
	SAVEIFS=$IFS
	IFS=$(echo -en "\n\b")

	# copy yang	
	for yf in $(find . -name "*.yang")
	do
		base=$(basename "$yf")
		cp "$yf" $YANG_STAGING
	done
	IFS=$SAVEIFS
	
	# Create hash file for stored files                                                   
	cd $YANG_STORED
	md5sum *.yang > $YANG_TMP/existing.md5 2>/dev/null
	                                                

	# Create the hash file
	cd $YANG_STAGING
	md5sum *.yang > md5

	# Check against existing
	if [ -f $YANG_STORED/md5 ]; then
		diff --width 400 --side-by-side $YANG_TMP/existing.md5 $YANG_STAGING/md5 > $YANG_DIFF
		if [ $? -ne 0 ]; then		

			# copy differences...
			echo YANG models changed

			while read p; do

# Diff results are of the form:
#
# 9eba6713372375817755ded2785a7cab  o-ran-compression-factors.y   9eba6713372375817755ded2785a7cab  o-ran-compression-factors.y
#                                                               > de39a92c28c860e6aad1f89f4159a304  missing.yang
# 415e63825da7933958c4f3dec592f415  o-ran-trace.yang            | d7988fc22f9a89f178263544e5d46e0a  o-ran-trace.yang          
# f09f1259ba9b26de85b249c20563d256  o-ran-dhcp.yang               f09f1259ba9b26de85b249c20563d256  o-ran-dhcp.yang
# d41d8cd98f00b204e9800998ecf8427e  should-be-deleted.yang      <                                                         


				if grep -q '|' <<< "$p" ; then
					file=$(awk '{print $2;}' <<< "$p")
					echo "modified : $file"
					cp $YANG_STAGING/$file $YANG_STORED
				fi
				if grep -q '>' <<< "$p" ; then
					file=$(awk '{print $3;}' <<< "$p")
					echo "new : $file"
					cp $YANG_STAGING/$file $YANG_STORED
				fi
				if grep -q '<' <<< "$p" ; then
					file=$(awk '{print $2;}' <<< "$p")
					echo "deleted : $file"
					rm $YANG_STORED/$file
				fi
			
			done <$YANG_DIFF

			# now update the hash
			cp $YANG_STAGING/md5 $YANG_STORED

		else
			echo YANG models unchanged
		fi
	else
		# copy all
		echo Initial install of YANG models...
		cp $YANG_STAGING/* $YANG_STORED/
	fi

	# Clear out temp area
	rm -rf $YANG_STAGING
	rm -rf $YANG_TMP
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

