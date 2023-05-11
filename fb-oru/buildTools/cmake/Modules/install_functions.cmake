##======================================================================================================================
## RSE CMake functions/macros used for install
##
##======================================================================================================================

# Include guard
if (_INCLUDED_INSTALL_FUNCTIONS)
	return ()
endif (_INCLUDED_INSTALL_FUNCTIONS)
set (_INCLUDED_INSTALL_FUNCTIONS 1)

##======================================================================================================================
## MACROS/FUNCTIONS



##----------------------------------------------------------------------------------------------------------------------
## readFileList(filePath dirsVar filesVar modesVar copyVar)
##
## Function that reads in a file list (used to create a rootfs) and sets the lists referred to by dirsVar, and filesVar
## with entries for directory and file creation respectively. Also, the list modesVar will contain a list of entities that
## will have their mode/premissions set.
##
## File list will be of the form:
##
## # a comment line
## DIR <rootfs directory path> <owner>:<group> <permissions>
## DIRCOPY <rootfs directory path> <owner>:<group> <source directory>
## FILE <rootfs file path> <owner>:<group> <permissions> <source file location (relative to this list file)>
## INCLUDE <new list file path (relative to this list file)>
## MODE <rootfs file path> <owner>:<group> <permissions>
##
##
function (readFileList filePath dirsVar filesVar modesVar copyVar)

logMessage("READ FILELIST: ${filePath}")

    if (NOT EXISTS "${filePath}")
        return()
    endif()

    ## Read in the control file
    file(READ "${filePath}" contents)
    if (NOT contents)
        return()
    endif()

    get_filename_component(dir ${filePath} DIRECTORY)

    # Split lines
    STRING(REGEX REPLACE "\n" ";" contents "${contents}")
    set(linenum 0)
    foreach (line ${contents})
    
    	math(EXPR linenum "${linenum} + 1")
        logMessage(" * [${linenum}] ${line}")

        STRING(REGEX REPLACE "[\t ]+" ";" line "${line}")
        list (GET line 0 cmd)
        logMessage(" * * ${cmd}")

        if (cmd MATCHES "#")
			# skip comments
			continue()
        endif()

        if (cmd MATCHES "DIRCOPY")
            list (GET line 1 rootfs)
            list (GET line 2 owner)
            list (GET line 3 src)
	        logMessage(" * * * DIRCOPY '${rootfs}' '${owner}' '${src}'")
            
            if (rootfs AND owner AND src)
            	string(CONFIGURE ${rootfs} rootfs) 
            	string(CONFIGURE ${owner} owner) 
            	string(CONFIGURE ${src} src) 
            	string(SUBSTRING "${src}" 0 1 pathFirst)
            	if (NOT "${pathFirst}" STREQUAL "/")
            		set(src "${dir}/${src}")
            	endif()
		        logMessage(" * * * * ADD DIRCOPY '${rootfs}' '${owner}' '${src}'")
                list (APPEND ${copyVar} "${linenum}@${rootfs}@${owner}@${src}")
            endif()
            continue()
        endif()

        if (cmd MATCHES "DIR")
            list (GET line 1 rootfs)
            list (GET line 2 owner)
            list (GET line 3 perms)
            if (rootfs AND owner AND perms)
            	string(CONFIGURE ${rootfs} rootfs) 
            	string(CONFIGURE ${owner} owner) 
            	string(CONFIGURE ${perms} perms) 
                list (APPEND ${dirsVar} "${linenum}@${rootfs}@${owner}@${perms}")
            endif()
            continue()
        endif()

        if (cmd MATCHES "FILE")
            list (GET line 1 rootfs)
            list (GET line 2 owner)
            list (GET line 3 perms)
            list (GET line 4 path)
            if (rootfs AND owner AND perms)
            	string(CONFIGURE ${rootfs} rootfs) 
            	string(CONFIGURE ${owner} owner) 
            	string(CONFIGURE ${perms} perms) 
            	string(CONFIGURE ${path} path) 
            	string(SUBSTRING "${path}" 0 1 pathFirst)
            	if (NOT "${pathFirst}" STREQUAL "/")
            		set(path "${dir}/${path}")
            	endif()
            	
            	# Handle wildcards in path
            	string(FIND ${path} "*" pos)
            	if (pos GREATER -1)
            	
            		# found a wildcard - search for the first matching directory
            		file (GLOB pathList LIST_DIRECTORIES false "${path}")
			        logMessage(" * * pathList=${pathList}")
    				
    				foreach(path ${pathList})
    
    					# create an extry for each match
    					# For the destination we support using '%' as a placeholder for the expanded file name
    					get_filename_component(name ${path} NAME)
    					string(REPLACE "%" "${name}" expanded "${rootfs}")
	                    list (APPEND ${filesVar} "${linenum}@${expanded}@${owner}@${perms}@${path}")
            	
            		endforeach() 
            		
            	else()
            		# normal text
	                list (APPEND ${filesVar} "${linenum}@${rootfs}@${owner}@${perms}@${path}")
            	endif()
            	
            	
            endif()
            continue()
        endif()

        if (cmd MATCHES "INCLUDE")

            list (GET line 1 incfile)
            if (incfile)
            	string(CONFIGURE ${incfile} incfile) 
            	string(SUBSTRING "${incfile}" 0 1 pathFirst)
            	if (NOT "${pathFirst}" STREQUAL "/")
            		set(incfile "${dir}/${incfile}")
            	endif()
                readFileList(${incfile} ${dirsVar} ${filesVar} ${modesVar} ${copyVar})
            endif()

            continue()
        endif()

        if (cmd MATCHES "MODE")
            list (GET line 1 rootfs)
            list (GET line 2 owner)
            list (GET line 3 perms)
            if (rootfs AND owner AND perms)
            	string(CONFIGURE ${rootfs} rootfs) 
            	string(CONFIGURE ${owner} owner) 
            	string(CONFIGURE ${perms} perms) 
                list (APPEND ${modesVar} "${linenum}@${rootfs}@${owner}@${perms}")
            endif()
            continue()
        endif()

    endforeach()

    set (${dirsVar} ${${dirsVar}} PARENT_SCOPE)
    set (${filesVar} ${${filesVar}} PARENT_SCOPE)
    set (${modesVar} ${${modesVar}} PARENT_SCOPE)
    set (${copyVar} ${${copyVar}} PARENT_SCOPE)

endfunction (readFileList)

##----------------------------------------------------------------------------------------------------------------------
## fileListEntry(entry linenumVar rootfsVar ownerVar groupVar permsVar restListVar)
##
## Function that takes a entry from the fileLists list and splits it into it's common parts
##
function (fileListEntry entry linenumVar rootfsVar ownerVar groupVar permsVar restListVar)

    STRING(REGEX REPLACE "@" ";" contents "${entry}")

    list (LENGTH contents len)
    if (${len} LESS 3)
        return()
    endif()

    list (GET contents 0 ${linenumVar})
    list (GET contents 1 ${rootfsVar})
    list (GET contents 2 ownerGroup)
    list (GET contents 3 ${permsVar})

    list (REMOVE_AT contents 0)
    list (REMOVE_AT contents 0)
    list (REMOVE_AT contents 0)
    list (REMOVE_AT contents 0)

    STRING(REGEX REPLACE ":" ";" og "${ownerGroup}")
    list (LENGTH og len)
    if (${len} LESS 2)
        return()
    endif()
    list (GET og 0 ${ownerVar})
    list (GET og 1 ${groupVar})

    set (${rootfsVar} ${${rootfsVar}} PARENT_SCOPE)
    set (${ownerVar} ${${ownerVar}} PARENT_SCOPE)
    set (${groupVar} ${${groupVar}} PARENT_SCOPE)
    set (${permsVar} ${${permsVar}} PARENT_SCOPE)
    set (${restListVar} ${contents} PARENT_SCOPE)

endfunction (fileListEntry)

##----------------------------------------------------------------------------------------------------------------------
## fileListMode(modeEntry linenumVar rootfsVar ownerVar groupVar permsVar)
##
## Function that takes a entry from the fileLists list and splits it into it's common parts for MODE command
##
function (fileListMode modeEntry linenumVar rootfsVar ownerVar groupVar permsVar)

    set (rest)
    fileListEntry(${modeEntry} ${linenumVar} ${rootfsVar} ${ownerVar} ${groupVar} ${permsVar} rest)

    set (${linenumVar} ${${linenumVar}} PARENT_SCOPE)
    set (${rootfsVar} ${${rootfsVar}} PARENT_SCOPE)
    set (${ownerVar} ${${ownerVar}} PARENT_SCOPE)
    set (${groupVar} ${${groupVar}} PARENT_SCOPE)
    set (${permsVar} ${${permsVar}} PARENT_SCOPE)

endfunction (fileListMode)


##----------------------------------------------------------------------------------------------------------------------
## fileListDir(dirEntry linenumVar rootfsVar ownerVar groupVar permsVar)
##
## Function that takes a entry from the fileLists list and splits it into it's common parts for DIR command
##
function (fileListDir dirEntry linenumVar rootfsVar ownerVar groupVar permsVar)

    set (rest)
    fileListEntry(${dirEntry} ${linenumVar} ${rootfsVar} ${ownerVar} ${groupVar} ${permsVar} rest)

    set (${linenumVar} ${${linenumVar}} PARENT_SCOPE)
    set (${rootfsVar} ${${rootfsVar}} PARENT_SCOPE)
    set (${ownerVar} ${${ownerVar}} PARENT_SCOPE)
    set (${groupVar} ${${groupVar}} PARENT_SCOPE)
    set (${permsVar} ${${permsVar}} PARENT_SCOPE)

endfunction (fileListDir)

##----------------------------------------------------------------------------------------------------------------------
## fileListDirCopy(dirEntry linenumVar rootfsVar ownerVar groupVar permsVar)
##
## Function that takes a entry from the fileLists list and splits it into it's common parts for DIRCOPY command
##
function (fileListDirCopy dirEntry linenumVar rootfsVar ownerVar groupVar srcVar)

    set (rest)
    fileListEntry(${dirEntry} ${linenumVar} ${rootfsVar} ${ownerVar} ${groupVar} ${srcVar} rest)

    set (${linenumVar} ${${linenumVar}} PARENT_SCOPE)
    set (${rootfsVar} ${${rootfsVar}} PARENT_SCOPE)
    set (${ownerVar} ${${ownerVar}} PARENT_SCOPE)
    set (${groupVar} ${${groupVar}} PARENT_SCOPE)
    set (${srcVar} ${${srcVar}} PARENT_SCOPE)

endfunction (fileListDirCopy)

##----------------------------------------------------------------------------------------------------------------------
## fileListFile(dirEntry linenumVar rootfsVar ownerVar groupVar permsVar srcVar)
##
## Function that takes a entry from the fileLists list and splits it into it's common parts for FILE command
##
function (fileListFile fileEntry linenumVar rootfsVar ownerVar groupVar permsVar srcVar)

    set (rest)
    fileListEntry(${fileEntry} ${linenumVar} ${rootfsVar} ${ownerVar} ${groupVar} ${permsVar} rest)

    set (${linenumVar} ${${linenumVar}} PARENT_SCOPE)
    set (${rootfsVar} ${${rootfsVar}} PARENT_SCOPE)
    set (${ownerVar} ${${ownerVar}} PARENT_SCOPE)
    set (${groupVar} ${${groupVar}} PARENT_SCOPE)
    set (${permsVar} ${${permsVar}} PARENT_SCOPE)
    set (${srcVar} ${rest} PARENT_SCOPE)

endfunction (fileListFile)


##----------------------------------------------------------------------------------------------------------------------
## tarFromDir(TARFILE ROOTFS DIRMODE FILEMODE)
##
## Function which creates the TARFILE from the contents of a directory. Tars all the directories with mode DIRMODE
## first, then tars the files with mode FILEMODE
##
function (tarFromDir TARFILE ROOTFS DIRMODE FILEMODE)

    ## tar - from rootfs (make all files accessible to root only)

    # Create a list of dirs
    set (dirs "")

    file (GLOB_RECURSE filesDirs LIST_DIRECTORIES true RELATIVE ${ROOTFS} "${ROOTFS}/*")
    logMessage ("ROOTFS FILES/DIRS: ${filesDirs}")
    foreach (fd ${filesDirs})

        logMessage ("-- * fd: ${fd} --")

        if (NOT IS_DIRECTORY ${ROOTFS}/${fd})
            get_filename_component(fd ${fd} DIRECTORY)
            logMessage (" * * fd: ${fd}")
        endif ()

        if ("${fd}" STREQUAL "")
            continue()
        endif ()

        if (NOT IS_DIRECTORY ${ROOTFS}/${fd})
            continue()
        endif()

        logMessage (" * IS DIR")

        string(REPLACE "/" ";" dlist ${fd})
        list(GET dlist 0 dir)
        list(LENGTH dlist len)
        logMessage (" * [len:${len}] dir=${dir} dlist=${dlist}")

        while (len GREATER 0)
            list(APPEND dirs ${dir})
            list(REMOVE_AT dlist 0)
            list(LENGTH dlist len)
        logMessage (" * [len:${len}] dirs=${dirs} dir=${dir} dlist=${dlist}")

            if (len GREATER 0)
                list(GET dlist 0 nextdir)
                set (dir "${dir}/${nextdir}")
        logMessage (" * * [len:${len}] dirs=${dirs} dir=${dir} dlist=${dlist} nextdir=${nextdir}")
            endif()
        endwhile ()

    endforeach ()
    list(REMOVE_DUPLICATES dirs)
    list(SORT dirs)
    logMessage ("ROOTFS DIRS: ${dirs}")

   	logMessage(" * * tar cf ${TARFILE} --numeric-owner --owner=0 --group=0 --mode=${DIRMODE} --no-recursion ${dirs}")

    # tar dirs
    execute_process(
        WORKING_DIRECTORY ${ROOTFS}
        COMMAND tar "cf" "${TARFILE}" --numeric-owner --owner=0 --group=0 --mode=${DIRMODE} --no-recursion ${dirs}
    )

    # get list of files
    file (GLOB_RECURSE files LIST_DIRECTORIES false RELATIVE ${ROOTFS} "${ROOTFS}/*")
    logMessage ("ROOTFS FILES: ${files}")

   	logMessage(" * * tar rf ${TARFILE} --numeric-owner --owner=0 --group=0 --mode=${FILEMODE} ${files}")

    # tar files
    execute_process(
        WORKING_DIRECTORY ${ROOTFS}
        COMMAND tar "rf" "${TARFILE}" --numeric-owner --owner=0 --group=0 --mode=${FILEMODE} ${files}
    )

endfunction (tarFromDir)

##----------------------------------------------------------------------------------------------------------------------
## subdirlist(resultVar dir)
##
## Function which recursively finds all the directories under ${dir}
##
macro (subdirlist resultVar curdir)

logMessage(STATUS "subdirlist ${curdir} result=${resultVar} list=${${resultVar}}")

	set(dirlist "${${resultVar}}")
	FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  	FOREACH(child ${children})
   		IF(IS_DIRECTORY ${curdir}/${child})
logMessage(STATUS "subdirlist ADD ${curdir}/${child}")
			LIST(APPEND dirlist ${curdir}/${child})
      		# do the subdirs of this
      		subdirlist(${resultVar} ${curdir}/${child})
logMessage(STATUS "subdirlist list=${${resultVar}}")
    	ENDIF()
  	ENDFOREACH()
  
  	SET(${resultVar} ${dirlist})

logMessage(STATUS "subdirlist ${curdir} END list=${${resultVar}} dirlist=${dirlist}")

endmacro(subdirlist)

##----------------------------------------------------------------------------------------------------------------------
## tarRootfs(filelist ROOTFS TMP_ROOTFS TARFILE repoFiles)
##
## Macro which creates the TARFILE by reading the file list text file stored in ${filelist} combined with any files
## installed into the ROOTFS directory
##
macro (tarRootfs filelist ROOTFS TMP_ROOTFS TARFILE repoFiles)

logMessage("## TARGET=${TARGET} repoFiles=${repoFiles}") 

    # Read in the control file
    readFileList(${filelist} filelistDirs filelistFiles fileListModes fileListCopy)

#    logMessage ("# fileListDirs : ${filelistDirs}")
#    logMessage ("# fileListFiles: ${filelistFiles}")
#    logMessage ("# fileListModes: ${fileListModes}")
#    logMessage ("# fileListCopy : ${fileListCopy}")
    
    # Read in files from repos
    string(REPLACE ":" ";" fileLists "${repoFiles}")
    foreach(fl ${fileLists})
    	set(flDirs "")
    	set(flFiles "")
    	set(flModes "")
    	set(flCopy "")
    	
	    readFileList(${fl} flDirs flFiles flModes flCopy)

#    logMessage ("#SDP# ${fl}: flFiles: ${flFiles}")

	    list(APPEND filelistDirs ${flDirs})
	    list(APPEND filelistFiles ${flFiles})
	    list(APPEND fileListModes ${flModes})
	    list(APPEND fileListCopy ${flCopy})

    endforeach()
    
    logMessage ("## After loading repos' file lists:")
    logMessage ("# fileListDirs : ${filelistDirs}")
    logMessage ("# fileListFiles: ${filelistFiles}")
    logMessage ("# fileListModes: ${fileListModes}")
    logMessage ("# fileListCopy : ${fileListCopy}")
    


    # tar - from rootfs (make all files accessible to root only)
    tarFromDir("${TARFILE}" ${ROOTFS} 0755 0750)


    # [DIR] tar - add from dirs list
    foreach (entry ${filelistDirs})

        # get entry fields
        fileListDir(${entry} linenum rootpath owner group perms)

        logMessage(" * DIR ${rootpath}")

    	# create dir in rootfs area
    	# if rootpath=/nandflash then relRootfs=nandflash
    	string (SUBSTRING ${rootpath} 1 -1 relRootfs)

       	logMessage(" * * mkdir -p ${TMP_ROOTFS}/${relRootfs}")

    	execute_process(
    	    WORKING_DIRECTORY ${TMP_ROOTFS}
    	    COMMAND mkdir "-p" "${TMP_ROOTFS}/${relRootfs}"
    	    RESULT_VARIABLE rc
    	)
    	logMessage("# mkdir rc=${rc}")
    	if (NOT rc EQUAL 0)
    		message(FATAL_ERROR "Unable to create directory ${TMP_ROOTFS}/${relRootfs} [line number ${linenum}]")
    	endif()

       	logMessage(" * * tar rf ${TARFILE} --numeric-owner --owner=${owner} --group=${group} --mode=${perms} ${relRootfs}")

        # use the created dir (in rootfs area) to create the tar entry
    	execute_process(
    	    WORKING_DIRECTORY ${TMP_ROOTFS}
    	    COMMAND tar "rf" "${TARFILE}" --numeric-owner --owner=${owner} --group=${group} --mode=${perms} ${relRootfs}
    	    RESULT_VARIABLE rc
    	)
    	logMessage("# tar rc=${rc}")
    	if (NOT rc EQUAL 0)
    		message(FATAL_ERROR "TAR error with file ${TARFILE} [line number ${linenum}]")
    	endif()

       	logMessage(" * * rm -rf ${TMP_ROOTFS}/${relRootfs}")

		# clean up - remove the created directory
    	execute_process(
    	    WORKING_DIRECTORY ${TMP_ROOTFS}
    	    COMMAND rm "-rf" "${TMP_ROOTFS}/${relRootfs}"
    	)

    endforeach()

    # [DIRCOPY] Part 1 tar - add dirs from copy list
    foreach (entry ${fileListCopy})

        # get entry fields
        fileListDirCopy(${entry} linenum rootpath owner group src)
        set (perms "0755")

        logMessage(" * DIRCOPY ${rootpath}")
        
        # Get the list of directories under this source
        execute_process(
    	    COMMAND find ${src} -type d
			OUTPUT_VARIABLE subdirs
        )
    	STRING(REGEX REPLACE "\n" ";" subdirs "${subdirs}")
        logMessage(" * * SUBDIRS=${subdirs}")
        
#        execute_process(
#    	    COMMAND find ${src} -type f
#			OUTPUT_VARIABLE files
#        )
#        logMessage(" * * SUBFILES=${files}")
        
        # if rootpath=/nandflash then relRootfs=nandflash
    	string (SUBSTRING ${rootpath} 1 -1 relRootfs)
        
        set (srcroot ${src})
		foreach (subdir ${subdirs})

			string (REPLACE "${srcroot}/" "" relSubdir ${subdir})
			string (REPLACE "${srcroot}" "" relSubdir ${relSubdir})
			set (relSubdir "${relRootfs}/${relSubdir}")
			
	    	# create dir in rootfs area
	       	logMessage(" * * mkdir -p ${TMP_ROOTFS}/${relSubdir}")
	
	    	execute_process(
	    	    WORKING_DIRECTORY ${TMP_ROOTFS}
	    	    COMMAND mkdir "-p" "${TMP_ROOTFS}/${relSubdir}"
	    	    RESULT_VARIABLE rc
	    	)
	    	logMessage("# mkdir rc=${rc}")
	    	if (NOT rc EQUAL 0)
	    		message(FATAL_ERROR "Unable to create directory ${TMP_ROOTFS}/${relSubdir} [line number ${linenum}]")
	    	endif()
	
	       	logMessage(" * * tar rf ${TARFILE} --numeric-owner --owner=${owner} --group=${group} --mode=${perms} ${relSubdir}")
	
	        # use the created dir (in rootfs area) to create the tar entry
	    	execute_process(
	    	    WORKING_DIRECTORY ${TMP_ROOTFS}
	    	    COMMAND tar "rf" "${TARFILE}" --numeric-owner --owner=${owner} --group=${group} --mode=${perms} ${relSubdir}
	    	    RESULT_VARIABLE rc
	    	)
	    	logMessage("# tar rc=${rc}")
	    	if (NOT rc EQUAL 0)
	    		message(FATAL_ERROR "TAR error with file ${TARFILE} [line number ${linenum}]")
	    	endif()
	
	       	logMessage(" * * rm -rf ${TMP_ROOTFS}/${relSubdir}")
	
			# clean up - remove the created directory
	    	execute_process(
	    	    WORKING_DIRECTORY ${TMP_ROOTFS}
	    	    COMMAND rm "-rf" "${TMP_ROOTFS}/${relSubdir}"
	    	)
    	    	
    	    	
    	endforeach()
    	
    endforeach()



    # [FILE] tar - add from files list
    foreach (entry ${filelistFiles})

        # get entry fields
        fileListFile(${entry} linenum rootpath owner group perms src)

        logMessage(" * FILE ${rootpath}")

    	# copy file over to rootfs area
    	string (SUBSTRING ${rootpath} 1 -1 relRootfs)
    	get_filename_component(dir "${relRootfs}" DIRECTORY)
    	get_filename_component(file "${relRootfs}" NAME)
    	set (dest "${relRootfs}")

        # strip off any ".in" extension if present
        string (REGEX REPLACE "\\.in$" "" templateFile ${file})

        logMessage(" * * dir ${dir} file ${file} template ${templateFile}")

		# check for ".in" etension (i.e. see if this is a translate file)
    	if (NOT ${templateFile} STREQUAL ${file})

    	    # translate file first
    	    set (dest ${TMP_ROOTFS}/${templateFile})
    	    configure_file(${src} ${dest} @ONLY)
        	logMessage(" * * TRANSLATE src ${src} dest ${dest}")

    	    set (src ${dest})
    	    set (dest ${dir}/${templateFile})

    	endif()

       	logMessage(" * * src=${src} dir=${dir} dest=${TMP_ROOTFS}/${dest}")

       	logMessage(" * * mkdir -p ${dir}")
       	logMessage(" * * cp ${src} ${TMP_ROOTFS}/${dest}")

    	# copy the file
    	execute_process(
    	    WORKING_DIRECTORY ${TMP_ROOTFS}
    	    COMMAND mkdir "-p" "${dir}"
    	)
    	execute_process(
    	    WORKING_DIRECTORY ${TMP_ROOTFS}
    	    COMMAND cp "${src}" "${TMP_ROOTFS}/${dest}"
    	    RESULT_VARIABLE rc
    	)
    	logMessage("# cp rc=${rc}")
    	if (NOT rc EQUAL 0)
    		message(FATAL_ERROR "Unable to copy ${src} [line number ${linenum}]")
    	endif()

       	logMessage(" * * tar rf ${TARFILE} --numeric-owner --owner=${owner} --group=${group} --mode=${perms} ${dest}")

        # use the copy to create the tar entry
    	execute_process(
    	    WORKING_DIRECTORY ${TMP_ROOTFS}
    	    COMMAND tar "rf" "${TARFILE}" --numeric-owner --owner=${owner} --group=${group} --mode=${perms} ${dest}
    	    RESULT_VARIABLE rc
    	)
    	logMessage("# tar rc=${rc}")
    	if (NOT rc EQUAL 0)
    		message(FATAL_ERROR "TAR error with file ${TARFILE} [line number ${linenum}]")
    	endif()

        # Dump current contents
#    	execute_process(
#    	    WORKING_DIRECTORY ${TMP_ROOTFS}
#    	    COMMAND tar "tvf" "${TARFILE}"
#    	)

       	logMessage(" * * rm -rf ${TMP_ROOTFS}/${dest}")

    	execute_process(
    	    WORKING_DIRECTORY ${TMP_ROOTFS}
    	    COMMAND rm "-rf" "${TMP_ROOTFS}/${dest}"
    	)

    endforeach()

    # [DIRCOPY] Part 2 tar - add files from copy list
    foreach (entry ${fileListCopy})

        # get entry fields
        fileListDirCopy(${entry} linenum rootpath owner group src)

        logMessage(" * DIRCOPY ${rootpath}")
        
        # Get the list of files under this source
        execute_process(
    	    COMMAND find ${src} -type f
			OUTPUT_VARIABLE subfiles
        )
    	STRING(REGEX REPLACE "\n" ";" subfiles "${subfiles}")
        logMessage(" * * SUBFILES=${subfiles}")
        
        # if rootpath=/nandflash then relRootfs=nandflash
    	string (SUBSTRING ${rootpath} 1 -1 relRootfs)
        
        set (srcroot ${src})
		foreach (src ${subfiles})

			string (REPLACE "${srcroot}/" "" relSubfile ${src})
			string (REPLACE "${srcroot}" "" relSubfile ${relSubfile})
			set (relSubfile "${relRootfs}/${relSubfile}")
			
	    	# copy file over to rootfs area
	    	get_filename_component(dir "${relSubfile}" DIRECTORY)
	    	get_filename_component(file "${relSubfile}" NAME)
	    	set (dest "${relSubfile}")
	
	        # strip off any ".in" extension if present
	        string (REGEX REPLACE "\\.in$" "" templateFile ${file})
	
	        logMessage(" * * dir ${dir} file ${file} template ${templateFile}")
	
			# check for ".in" etension (i.e. see if this is a translate file)
	    	if (NOT ${templateFile} STREQUAL ${file})
	
	    	    # translate file first
	    	    set (dest ${TMP_ROOTFS}/${templateFile})
	    	    configure_file(${src} ${dest} @ONLY)
	        	logMessage(" * * TRANSLATE relSubfile ${relSubfile} dest ${dest}")
	
	    	    set (src ${dest})
	    	    set (dest ${dir}/${templateFile})
	
	    	endif()
	
	       	logMessage(" * * src=${src} dir=${dir} dest=${TMP_ROOTFS}/${dest}")
	
	       	logMessage(" * * mkdir -p ${dir}")
	       	logMessage(" * * cp ${src} ${TMP_ROOTFS}/${dest}")
	
	    	# copy the file
	    	execute_process(
	    	    WORKING_DIRECTORY ${TMP_ROOTFS}
	    	    COMMAND mkdir "-p" "${dir}"
	    	)
	    	execute_process(
	    	    WORKING_DIRECTORY ${TMP_ROOTFS}
	    	    COMMAND cp "${src}" "${TMP_ROOTFS}/${dest}"
	    	    RESULT_VARIABLE rc
	    	)
	    	logMessage("# cp rc=${rc}")
	    	if (NOT rc EQUAL 0)
	    		message(FATAL_ERROR "Unable to copy ${src} [line number ${linenum}]")
	    	endif()

			# get file perms
			execute_process(
	    	    WORKING_DIRECTORY ${TMP_ROOTFS}
	    	    COMMAND stat -c "%a" ${src}
	    	    RESULT_VARIABLE perms
	    	)
	       	logMessage(" * * tar rf ${TARFILE} --numeric-owner --owner=${owner} --group=${group} --mode=${perms} ${dest}")
	
	        # use the copy to create the tar entry
	    	execute_process(
	    	    WORKING_DIRECTORY ${TMP_ROOTFS}
	    	    COMMAND tar "rf" "${TARFILE}" --numeric-owner --owner=${owner} --group=${group} --mode=${perms} ${dest}
	    	    RESULT_VARIABLE rc
	    	)
	    	logMessage("# tar rc=${rc}")
	    	if (NOT rc EQUAL 0)
	    		message(FATAL_ERROR "TAR error with file ${TARFILE} [line number ${linenum}]")
	    	endif()
	
	        # Dump current contents
	#    	execute_process(
	#    	    WORKING_DIRECTORY ${TMP_ROOTFS}
	#    	    COMMAND tar "tvf" "${TARFILE}"
	#    	)
	
	       	logMessage(" * * rm -rf ${TMP_ROOTFS}/${dest}")
	
	    	execute_process(
	    	    WORKING_DIRECTORY ${TMP_ROOTFS}
	    	    COMMAND rm "-rf" "${TMP_ROOTFS}/${dest}"
	    	)

    	endforeach()
    	
    endforeach()


    # [MODE] tar - change any entries with new modes/permissions
    foreach (entry ${fileListModes})

        # get entry fields
        fileListDir(${entry} linenum rootpath owner group perms)

        logMessage(" * MODE ${rootpath}")

    	# extract entry into rootfs area
    	string (SUBSTRING ${rootpath} 1 -1 relRootfs)
    	execute_process(
    	    WORKING_DIRECTORY ${TMP_ROOTFS}
    	    COMMAND tar "xf" "${TARFILE}" --numeric-owner --owner=${owner} --group=${group} --mode=${perms} ${relRootfs}
    	    RESULT_VARIABLE rc
    	)
    	logMessage("# tar rc=${rc}")
    	if (NOT rc EQUAL 0)
    		message(FATAL_ERROR "TAR error with file ${TARFILE} [line number ${linenum}]")
    	endif()

        logMessage(" * *  relRootfs=${relRootfs}")

    	# remove existing entry
    	execute_process(
    	    WORKING_DIRECTORY ${TMP_ROOTFS}
    	    COMMAND tar "f" "${TARFILE}" --delete ${relRootfs}
    	    RESULT_VARIABLE rc
    	)
    	logMessage("# tar rc=${rc}")
    	if (NOT rc EQUAL 0)
    		message(FATAL_ERROR "TAR error with file ${TARFILE} [line number ${linenum}]")
    	endif()

        # use the copy to create the new tar entry with changed permissions
    	execute_process(
    	    WORKING_DIRECTORY ${TMP_ROOTFS}
    	    COMMAND tar "rf" "${TARFILE}" --numeric-owner --owner=${owner} --group=${group} --mode=${perms} ${relRootfs}
    	    RESULT_VARIABLE rc
    	)
    	logMessage("# tar rc=${rc}")
    	if (NOT rc EQUAL 0)
    		message(FATAL_ERROR "TAR error with file ${TARFILE} [line number ${linenum}]")
    	endif()

        # delete
#    	execute_process(
#    	    WORKING_DIRECTORY ${TMP_ROOTFS}
#    	    COMMAND rm "-rf" "${TMP_ROOTFS}/${relRootfs}"
#    	)

    endforeach()



    # tgz
    execute_process(
        WORKING_DIRECTORY ${ROOTFS}
        COMMAND gzip -f -S .tgz "${TARFILE}"
   	    RESULT_VARIABLE rc
    )
    logMessage("# gzip rc=${rc}")
   	if (NOT rc EQUAL 0)
   		nessage(FATAL_ERROR "Unable to gzip TAR ${TARFILE}")
   	endif()


endmacro (tarRootfs)
