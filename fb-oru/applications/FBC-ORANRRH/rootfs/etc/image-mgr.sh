#!/bin/sh
#
# Image management functions.
#
# We implement a very simple approach of trying the current image N times and if that doesn't work we try rolling back
# to the "previous" link. If all fails we stop
#

#===================================================================================================================
# CONSTANTS
#===================================================================================================================

# u-boot env var used to keep track of the number of retries
BOOT_RETRIES_COUNT_VAR=bootRetries

# Maximum number of retries
BOOT_RETRIES=1

#===================================================================================================================
# OBJECT DATA
#===================================================================================================================
IMAGE_DIR=/nandflash
TMP_DIR=/tmp
DEBUG_PRINT=$(i2cenv DEBUG_PRINT | sed -e 's/^.*=//')
DEBUG_SYSLOG=$(i2cenv DEBUG_SYSLOG | sed -e 's/^.*=//')
APPSTATE_FILE=/var/log/app-state.txt

#===================================================================================================================
# PRIVATE
#===================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
# log a message
##----------------------------------------------------------------------------------------------------------------------
logMsg()
{
	msg="[$(date +%T)] $*"
	>&2 echo "$msg"
	
	logger -t image-mgr $*
}


#-------------------------------------------------------------------------------------------------------------------
# debugPrint(...)
#
# Print args if debug is enabled
#
debugPrint()
{
	if [ "flag$DEBUG_PRINT" == "flag1" ]
	then
		logMsg $*
	fi

	if [ "flag$DEBUG_SYSLOG" == "flag1" ]
	then
		logger -t image-mgr-debug $*
	fi
}

#-------------------------------------------------------------------------------------------------------------------
# followLink(link)
#
# Recursively reads the link until we find the base file linked to
#
followLink()
{
	local link=$1

	while [ -h $link ]
	do
		link=$(readlink $link)
	done

	if [ -f $link ]
	then
		echo $link
	fi
}


#-------------------------------------------------------------------------------------------------------------------
# processLink(linkName)
#
# Processes the current / previous links in application images area. Gets the current setting and:
# 1. Removes both if either are missing
# 2. Removes both if either point to missing file
# 3. Removes both if they point to different packages
# 4. Returns the package name if they both exist AND point to the same package
#
processLink()
{
	local imageDir=$IMAGE_DIR
	local tmpDir=$TMP_DIR

	local linkName=$1

	# Check app  dirs
	for dir in app  ; do
		set ${dir}Link=
		set ${dir}Pkg=

		# does this name link exist
		if [ -h $imageDir/$dir-images/$linkName ]
		then
			# find tgz pointed at
			link=$(readlink $imageDir/$dir-images/$linkName)

			# bore down to actual file
			file=$(followLink $imageDir/$dir-images/$linkName)

			# does it exist
			if [ -n "$file" -a -f "$file" ]
			then
				# Save the link
				eval ${dir}Link=$link
			fi
		fi

	done

#	echo processLink $linkName
#	echo   APP LINK: ${appLink}

	# check that links were found
	remove=0
	if [ ! -n "$appLink" ]
	then
		return
	fi

	# All's well so return the link
	echo $appLink
}

#===================================================================================================================
# PUBLIC
#===================================================================================================================


#-------------------------------------------------------------------------------------------------------------------
# imageMgr(imageDir, tmpDir, debugEnable, debugSyslog)
#
# "Initialises" the image manager "object" by saving the directories used for the images and temporary files
#
imageMgr()
{
	IMAGE_DIR=$1
	TMP_DIR=$2
	DEBUG_PRINT=$3
	DEBUG_SYSLOG=$4
}

#-------------------------------------------------------------------------------------------------------------------
# runRetry()
#
# Uses the u-boot environment variable to determine how many retries we've already run and when to move on to the "previous"
# image or stop
#
runRetry()
{
	local imageDir=$IMAGE_DIR
	local tmpDir=$TMP_DIR

	current=$(processLink current)
	previous=$(processLink previous)

	# If previous = current then there's no point reverting back to it
	if [ "$current" == "$previous" ]
	then
		rm -f $imageDir/app-images/previous
		previous=
	fi

	if [ -n "$current" ]
	then
		echo "$current" > $tmpDir/tmp.$$
		IFS=':' read appCurrent < $tmpDir/tmp.$$
		rm -f $tmpDir/tmp.$$ 2>/dev/null
	fi

	if [ -n "$previous" ]
	then
		echo "$previous" > $tmpDir/tmp.$$
		IFS=':' read appPrevious < $tmpDir/tmp.$$
		rm -f $tmpDir/tmp.$$ 2>/dev/null
	fi

	# Where are we with the retries
	retries=$(i2cenv $BOOT_RETRIES_COUNT_VAR | sed -e 's/^.*=//')
	retries=${retries:-1}

	#logMsg "runRetry retries=$retries current=$current previous=$previous"
	#logMsg "runRetry appCurrent=$appCurrent "
	#logMsg "runRetry appPrevious=$appPrevious "

	retriesNext=$(( retries + 1 ))
	i2cenv -W $BOOT_RETRIES_COUNT_VAR=$retriesNext >/dev/null 2>&1

	# retry count to use to switch over to previous
	prevTry=$(( BOOT_RETRIES + 1 ))

	# see if we still need to retry
	if [ $retries -le $BOOT_RETRIES ]
	then
		# Only do this if we have a current link - highly unlikely we'd get here without one but possibly there's no code loaded
		if [ -n "$current" ]
		then
			# try again with current
			logMsg "runRetry : retry current"
			echo current
			return
		fi

		# Change to using previous immediately
		retries=$prevTry
		retriesNext=$(( retries + 1 ))
		i2cenv -W $BOOT_RETRIES_COUNT_VAR=$retriesNext >/dev/null 2>&1
	fi

	# Do we try previous
	if [ $retries -eq $prevTry ]
	then
		# Do we have a previous to try?
		if [ -n "$previous" ]
		then
			# try with previous
			rm -f $imageDir/app-images/current
			rm -f $imageDir/app-images/previous

			ln -sf $appPrevious $imageDir/app-images/current

			logMsg "runRetry : try previous"
			echo previous
			return
		fi
	fi

	logMsg "runRetry : all attempts failed"

}

#-------------------------------------------------------------------------------------------------------------------
# clearRetry()
#
# Stops any retries (clears the retry counter)
#
clearRetry()
{
	debugPrint clearRetry
	i2cenv -W $BOOT_RETRIES_COUNT_VAR=   >/dev/null 2>&1
}

#-------------------------------------------------------------------------------------------------------------------
# appStable(timeoutTime)
#
# Keep attempting to read that the application has reached the stable state. Times out if not stable after timeoutTime
#
appStable()
{
	local timeoutTime=$1

    local t=$timeoutTime

    while [ $t -gt 0 ]; do

    	state=$(tail -n 1 $APPSTATE_FILE 2>&1 | grep appState=)
    	if [ -n "$state" ]
    	then
    		stable=$(echo "$state" | grep appState=STABLE)
    		if [ -n "$stable" ]
    		then
	    		# Reached stable state so stop
	    		echo "STABLE"
	    		return
	    	fi

    		fail=$(echo "$state" | grep appState=FAIL)
    		if [ -n "$fail" ]
    		then
	    		# Already failed, so stop now
	    		echo "TIMEOUT"
	    		return
	    	fi


    	fi

        t=$((t -= 1))
        if [ $t -eq 0 ]; then
		    # Timed out
		    echo "TIMEOUT"
        	return
        fi

        sleep 1
    done

	echo "TIMEOUT"
}


#-------------------------------------------------------------------------------------------------------------------
# stableOrReboot(timeoutTime)
#
# Get the application state. If not stable then try rolling back to a previous version. While it can rollback, this function
# will not exit (it calls reboot directly).
#
# If the app is stable this returns "STABLE"; otherwise it returns "FAILED"
#
stableOrReboot()
{
	local timeout=$1

	# First try getting the app state
	state=$(appStable $timeout)

	if [ "$state" == "STABLE" ]
	then
		# If this is the result of a rollback then log that fact
		retries=$(i2cenv $BOOT_RETRIES_COUNT_VAR | sed -e 's/^.*=//')
		if [ -n "$retries" ]
		then
			logMsg "** Application has rolled back to previous version **"
		fi
	
		clearRetry
		echo "STABLE"
		return
	fi

	# Bad things happened. See if we can retry/rollback
	version=$(runRetry)

	# If we have a version to try, then reboot
	if [ -n "$version" ]
	then
		# reboot
		logMsg "Application failed, rebooting to use $version image"
		echo "REBOOT"

		return ;
	fi

	# Having got here we have nothing left to try
	echo "FAILED"
}
