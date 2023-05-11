#!/bin/sh
#
# Image management functions. Some of which may be used or not. These functions were written to implement
# image checking (for valid packages - i.e. ones that have the package file and it's corresponding app and lib
# files).
#

#===================================================================================================================
# CONSTANTS
#===================================================================================================================

# Filename of list of found packages
# Format is
# name:package file:app tgz:lib tgz
PACKAGES=rc-pkgs.txt

# Filename of list of validated packages
# Format is
# name:package file:app tgz:lib tgz:[current]:[previous]
#
VALID_PACKAGES=rc-vpkgs.txt

#===================================================================================================================
# OBJECT DATA
#===================================================================================================================
IMAGE_DIR=/nandflash
TMP_DIR=/tmp
DEBUG_PRINT=

#===================================================================================================================
# PRIVATE
#===================================================================================================================

#-------------------------------------------------------------------------------------------------------------------
# debugPrint(...)
#
# Print args if debug is enabled
#
debugPrint()
{
	if [ -n "$DEBUG_PRINT" ]
	then
		echo $*
	fi
}

#-------------------------------------------------------------------------------------------------------------------
# findPkg(findName)
#
# Searches the valid packages list to find the entry. Returns the package name
#
findPkg()
{
	local imageDir=$IMAGE_DIR
	local tmpDir=$TMP_DIR

	local findName=$1
	found=$(grep $findName $tmpDir/$VALID_PACKAGES)
	if [ -n "$found" ]
	then
		IFS=':' read name pkg app lib <<< "$found"
		echo $name
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
# Processes the current / previous links in application and lib images areas. Gets the current setting and:
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

	# Check app and lib dirs
	for dir in app lib ; do
		set ${dir}Link=
		set ${dir}Pkg=

		# does this name link exist
		if [ -h $imageDir/$dir-images/$linkName ]
		then
			# find tgz pointed at
			link=$(basename $(readlink $imageDir/$dir-images/$linkName))
			eval ${dir}Link=$link

			# bore down to actual file
			file=$(followLink $imageDir/$dir-images/$linkName)

			# does it exist
			if [ -n "$file" -a -f "$file" ]
			then
				# Now get the package name
				eval ${dir}Pkg=$(findPkg ${link})
			fi
		fi

	done

#	echo processLink $linkName
#	echo   APP LINK: ${appLink}
#	echo   APP PKG : ${appPkg}
#	echo   LIB LINK: ${libLink}
#	echo   LIB PKG : ${libPkg}

	# check that packages were found
	remove=0
	if [ ! -n "$appPkg" -o ! -n "$libPkg" ]
	then
		remove=1
	fi

	# See if they match
	if [ "$appPkg" != "$libPkg" ]
	then
		remove=1
	fi

	if [ "$remove" == "1" ]
	then
	echo REMOVING LINKS

		# Mismatch, so remove all existing
		for dir in app lib ; do

			if [ -e $imageDir/$dir-images/$linkName ]
			then
				rm -f $imageDir/$dir-images/$linkName
			fi
		done

		return
	fi

	# All's well so return the package name
	echo $appPkg
}


#===================================================================================================================
# PUBLIC
#===================================================================================================================


#-------------------------------------------------------------------------------------------------------------------
# imageMgr(imageDir, tmpDir, debugEnable)
#
# "Initialises" the image manager "object" by saving the directories used for the images and temporary files
#
imageMgr()
{
	IMAGE_DIR=$1
	TMP_DIR=$2
	DEBUG_PRINT=$3
}


#-------------------------------------------------------------------------------------------------------------------
# readPkgs()
#
# Gets the list of package files, reads each file to get that package's application and library files and creates a
# list (in a temp file) of all the packages found
#
readPkgs()
{
	local imageDir=$IMAGE_DIR
	local tmpDir=$TMP_DIR

	rm -f $tmpDir/$PACKAGES

	for filename in $imageDir/pkg-images/*.pkg; do
		if [ -f $filename ]; then
			debugPrint $filename

			base=$(basename $filename .pkg)
			app=$(grep app $filename | sed -e 's/app[ \t]*//' -e 's/tgz.*/tgz/')
			lib=$(grep lib $filename | sed -e 's/lib[ \t]*//' -e 's/tgz.*/tgz/')
			debugPrint $app
			debugPrint $lib

			echo "$base:$filename:$imageDir/app-images/$app:$imageDir/lib-images/$lib" >> $tmpDir/$PACKAGES
		fi
	done
}

#-------------------------------------------------------------------------------------------------------------------
# validatePkgs()
#
# Processes the information gathered by readPkgs() but here it validates that the specified application and library
# files exist
#
validatePkgs()
{
	local imageDir=$IMAGE_DIR
	local tmpDir=$TMP_DIR

	rm -f $tmpDir/$VALID_PACKAGES

	while IFS=':' read name pkg app lib; do

		debugPrint $name : $pkg : $app : $lib

		if [ -f $app ]; then
			if [ -e $lib ]; then

				# at this point $lib is either a file or could be a link to a file (or another link!)
				# Get the actual file
				libActual=$lib
				if [ -h $lib ]
				then
					libActual=$(followLink $lib)
				fi

				if [ -n "$libActual" -a -f "$libActual" ]
				then
					echo "$name:$pkg:$app:$lib::" >> $tmpDir/$VALID_PACKAGES
					debugPrint Added valid package
				fi
			fi
		fi
	done < "$tmpDir/$PACKAGES"

	# Now check for current/previous
#processLink current
#processLink previous
#return

	current=$(processLink current)
	previous=$(processLink previous)

echo CURRENT=$current
echo PREVIOUS=$previous

	if [ "$current" == "$previous" ]
	then
		rm -f $imageDir/app-images/previous
		rm -f $imageDir/lib-images/previous
		previous=
	fi

	# Edit file to insert current and previous links
	if [ -n "$current" ]
	then
		sed -i "/$current/ s/::/:$current:/" $tmpDir/$VALID_PACKAGES
	fi
	if [ -n "$previous" ]
	then
		sed -i "/$previous/ s/::/::$previous/" $tmpDir/$VALID_PACKAGES
	fi
}


#-------------------------------------------------------------------------------------------------------------------
# cleanPkgs()
#
# Uses the valid packages list. Deletes all package files not in the list
#
cleanPkgs()
{
	local imageDir=$IMAGE_DIR
	local tmpDir=$TMP_DIR

	local imageDir=$IMAGE_DIR
	local tmpDir=$TMP_DIR

	local linkName=$1

	# Clean out the pkg and app dirs first because they are straight forward
	for filename in $imageDir/pkg-images/*.pkg; do

		pkg=$(findPkg $filename)
		if [ ! -n "$pkg" ]
		then
			echo Cleaning out invalid package $filename
			rm -f $filename*
		fi
	done
	for filename in $imageDir/app-images/*.tgz; do

		pkg=$(findPkg $filename)
		if [ ! -n "$pkg" ]
		then
			echo Cleaning out invalid application $filename
			rm -f $filename*
		fi
	done

	# now look at the lib files - need to keep any base files that are linked by valid lib links

	# start by creating a list of real files that are linked to by valid packages
	rm -f $tmpDir/rc-validLibs.txt
	while IFS=':' read name pkg app lib; do

		debugPrint $name : $pkg : $app : $lib
		libActual=$(followLink $lib)
		echo $libActual >> $tmpDir/rc-validLibs.txt

	done < "$tmpDir/$PACKAGES"

	# now process the lib files
	for filename in $imageDir/lib-images/*.tgz; do

		pkg=$(findPkg $filename)
		if [ ! -n "$pkg" ]
		then
			# If it's a link then we can just remove it
			if [ -h $filename ]
			then
				echo Cleaning out invalid lib link $filename
				rm -f $filename*
			else
				# Can only clean out real files if they aren't used by valid packages
				if ! grep -q $filename $tmpDir/rc-validLibs.txt
				then
					echo Cleaning out invalid lib $filename
					rm -f $filename*
				fi
			fi
		fi
	done

}

