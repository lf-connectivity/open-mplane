##======================================================================================================================
## RSE Shared CMake functions, Macros
##
##======================================================================================================================

# Include guard
if (_INCLUDED_RSE_FUNCTIONS)
	return ()
endif (_INCLUDED_RSE_FUNCTIONS)
set (_INCLUDED_RSE_FUNCTIONS 1)

##======================================================================================================================
## MACROS/FUNCTIONS

##----------------------------------------------------------------------------------------------------------------------
## logMessage( <message> ... )
##
## Function that displays the message(s)
##
function (logMessage)

	foreach (msg ${ARGV})
		message (STATUS "${msg}")
	endforeach ()

endfunction (logMessage)


##----------------------------------------------------------------------------------------------------------------------
## initialCapital( <var> <name> )
##
## Function that converts the first char of a name to upper case and the rest to lower case
##
function (initialCapital var name)

logDebug("initialCapital(var=${var} name=${name})")

	# capitalise the first letter of the name
	string (SUBSTRING ${name} 0 1 firstChar)
	string (SUBSTRING ${name} 1 -1 body)
	string (TOUPPER ${firstChar} firstChar)
	string (TOLOWER ${body} body)
	string (CONCAT name ${firstChar} ${body})

logDebug("initialCapital() name=${name}")

    # return
    set(${var} ${name} PARENT_SCOPE)

endfunction(initialCapital)

##----------------------------------------------------------------------------------------------------------------------
## getAlias( <var> <name> )
##
## Function that takes a repo name and returns it's alias (if any)
##
## NOTE: In order for make to pass the aliases down to cmake as encironment variables of the format ALIAS_xxx=yyy
## all '-' chars have to be replaced with '__' (otherwise the shell tries to execute the variable!)
##
function (getAlias var name)

	set(${var} "" PARENT_SCOPE)

	## start be escaping the name
	string(REPLACE "-" "__" escaped ${name})
	
	## Look up alias
	set(aliasName $ENV{ALIAS_${escaped}})
	if (NOT aliasName)
		return() 
	endif()
	
	## Unescape
	string(REPLACE "__" "-" unescaped ${aliasName})
	set(${var} ${unescaped} PARENT_SCOPE)

logDebug("alias(${name}) -> ALIAS=${unescaped}")

endfunction(getAlias)


##----------------------------------------------------------------------------------------------------------------------
## findIncludes( <dir> <var>)
##
## Macro that finds header files in a variety of subdirectories under <dir>. Sets <var> with the results
##
function (findIncludes dir var)

	file(GLOB_RECURSE ${var}
	    "${dir}/inc/*.h*"
	    "${dir}/*/inc/*.h*"
	    "${dir}/*/*/inc/*.h*"
	    "${dir}/*/*/*/inc/*.h*"
	    "${dir}/inc/*/*.h*"
	    "${dir}/*/inc/*/*.h*"
	    "${dir}/*/*/inc/*/*.h*"
	    "${dir}/*/*/*/inc/*/*.h*"
	)

#logDebug(STATUS "findIncludes: ${${var}}")

	# exclude dirs XXX.old - i.e. old/obsolete code not yet removed from the repo
	list(FILTER ${var} EXCLUDE REGEX ".*\\.old.*")
	
	# exclude dirs XXX.bak - i.e. backupds of code not yet removed from the repo
	list(FILTER ${var} EXCLUDE REGEX ".*\\.bak.*")

logDebug(STATUS "findIncludes[FILTER]: ${${var}}")

    # return
    set(${var} ${${var}} PARENT_SCOPE)

endfunction (findIncludes)

##----------------------------------------------------------------------------------------------------------------------
## addIncludes()
##
## Macro that adds the include path(s) to ${PROJECT_NAME}_INCLUDE_DIRS variable and also adds the paths to the included
## directories list. Searches in this subdirectory for any header files stored under 'inc' directory
##
macro (addIncludes)

	set(incDir "inc")
	string(LENGTH ${incDir} incLen) 
	
    findIncludes(${CMAKE_CURRENT_SOURCE_DIR} _HEADERS ${incDir} )

logDebug("addIncludes(${PROJECT_NAME}): CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR} HEADERS=${_HEADERS}")

	foreach (_headerFile ${_HEADERS})

	    # skip directories under build areas
		string (FIND ${_headerFile} "/build/" pos)
		if (${pos} EQUAL -1)
    	    get_filename_component(_dir ${_headerFile} PATH)

            list (APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${_dir})
			logDebug("addIncludes(${PROJECT_NAME}): ADD ${_dir}")
            
            ########
			# If this is under an 'inc' directory then point at the 'inc' path
			string (FIND ${_dir} "/${incDir}/" _pos)
			if (${_pos} GREATER -1)
	#logDebug("_addDirIncludes(${PROJECT_NAME}): _dir=${_dir} found /${inDir} at ${_pos} : removing after ${_pos}+${incLen}+1")
				# strip off after '/inc'
				math(EXPR _pos "${_pos}+${incLen}+1")
				string (SUBSTRING ${_dir} 0 ${_pos} _dir)

				logDebug("addIncludes(${PROJECT_NAME}): inc ADD ${_dir}")
		    
	        	list (APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${_dir})
			endif()
	
            
	    endif()

   	endforeach()

	list(LENGTH ${PROJECT_NAME}_INCLUDE_DIRS _numIncDirs)
	if (${_numIncDirs})

    	list(REMOVE_DUPLICATES ${PROJECT_NAME}_INCLUDE_DIRS)
    	includeDirectories(${${PROJECT_NAME}_INCLUDE_DIRS})

	endif()

	logDebug("addIncludes(${PROJECT_NAME}): ${PROJECT_NAME}_INCLUDE_DIRS=${${PROJECT_NAME}_INCLUDE_DIRS}")

endmacro (addIncludes)

##----------------------------------------------------------------------------------------------------------------------
## _addInterfaceIncludes(name)
##
## Macro that adds the include path(s) to the included directories list for interface headers in the named
## repository. Searches in this repository for any header files stored under an 'inc' directory under 'v*i' dir
##
macro (_addInterfaceIncludes name)

    set (path ${GITDIR}/${name})

	file(GLOB_RECURSE _HEADERS
	    "${path}/v*i/*.h*"
	    "${path}/v*i/inc/*.h*"

	    "${path}/*/v*i/*.h*"
	    "${path}/*/v*i/inc/*.h*"

	    "${path}/*/*/v*i/*.h*"
	    "${path}/*/*/v*i/inc/*.h*"

	    "${path}/*/*/*/v*i/*.h*"
	    "${path}/*/*/*/v*i/inc/*.h*"
	)
logDebug("addInterfaceIncludes(${name}): HEADERS=${_HEADERS}")

	foreach (_headerFile ${_HEADERS})

	    # skip directories under build areas
		string (FIND ${_headerFile} "/build/" pos)
logDebug("addInterfaceIncludes(${name}): header=${_headerFile} pos=${pos}")

		if (${pos} EQUAL -1)
    	    get_filename_component(_dir ${_headerFile} PATH)

            list (APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${_dir})
        endif()

	endforeach()

	list(LENGTH ${PROJECT_NAME}_INCLUDE_DIRS _numIncDirs)
	if (${_numIncDirs})

    	list(REMOVE_DUPLICATES ${PROJECT_NAME}_INCLUDE_DIRS)
    	includeDirectories(${${PROJECT_NAME}_INCLUDE_DIRS})

	endif()

endmacro (_addInterfaceIncludes)


##----------------------------------------------------------------------------------------------------------------------
## addInterfaceIncludes(name)
##
## Macro that adds the include path(s) to the included directories list for interface headers in the named
## repository. Searches in this repository for any header files stored under an 'inc' directory under 'v*i' dir
##
macro (addInterfaceIncludes name)

	_addInterfaceIncludes(${name})

	getAlias(aliasName ${name})
	if (aliasName)
		_addInterfaceIncludes(${aliasName})
	endif()

endmacro (addInterfaceIncludes)

##----------------------------------------------------------------------------------------------------------------------
## includeDirectories(dir1 [dir2 ..])
##
## Macro wrapper to include_directories that first checks to see if the directory is already in the list. Will only
## add directory if not already preset
##
macro (includeDirectories)

#logDebug("includeDirectories ${ARGV}")

	get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
#logDebug("includeDirectories INCLUDE_DIRECTORIES=${dirs}")
	foreach(dir ${ARGV})
#logDebug("includeDirectories checking ${dir}...")
		list(FIND dirs ${dir} index)
		if (${index} EQUAL -1)
			include_directories(${dir})
#logDebug("includeDirectroies: ADD ${dir}")
			list(APPEND dirs ${dir})
		endif()
	endforeach()

endmacro (includeDirectories)


##----------------------------------------------------------------------------------------------------------------------
## DOXYGEN-START _addDirIncludes
## _addDirIncludes(dir includeDirectoryName)
##
## Low-level macro that adds the include path(s) to ${PROJECT_NAME}_INCLUDE_DIRS variable and also adds the paths to the included
## directories list. Searches in the specified subdirectory for any header files stored under 'includeDirectoryName' directory
##
## DOXYGEN-END
##
##
macro (_addDirIncludes dir incDir)

logDebug("_addDirIncludes(${PROJECT_NAME}): dir=${dir} incDir=${incDir}")

    string(LENGTH ${incDir} incLen) 

    findIncludes(${dir} _HEADERS ${incDir})

logDebug("_addDirIncludes(${PROJECT_NAME}): CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR} HEADERS=${_HEADERS}")
logDebug("_addDirIncludes(${PROJECT_NAME}): dir=${dir} incDir=${incDir}")

	foreach (_headerFile ${_HEADERS})

	    get_filename_component(_dir ${_headerFile} PATH)

		# If this is under an 'inc' directory then point at the 'inc' path
		string (FIND ${_dir} "/${incDir}/" _pos)
		if (${_pos} GREATER -1)
#logDebug("_addDirIncludes(${PROJECT_NAME}): _dir=${_dir} found /${inDir} at ${_pos} : removing after ${_pos}+${incLen}+1")
			# strip off after '/inc'
			math(EXPR _pos "${_pos}+${incLen}+1")
			string (SUBSTRING ${_dir} 0 ${_pos} _dir)
		endif()

logDebug("_addDirIncludes(${PROJECT_NAME}): ADD ${_dir}")
	    
        list (APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${_dir})
	        
   	endforeach()
	
	list(LENGTH ${PROJECT_NAME}_INCLUDE_DIRS _numIncDirs)
	if (${_numIncDirs})
	
    	list(REMOVE_DUPLICATES ${PROJECT_NAME}_INCLUDE_DIRS)
    	includeDirectories(${${PROJECT_NAME}_INCLUDE_DIRS})

	endif()
	
logDebug("_addDirIncludes(${PROJECT_NAME}): ${PROJECT_NAME}_INCLUDE_DIRS=${${PROJECT_NAME}_INCLUDE_DIRS}")

endmacro (_addDirIncludes)

##----------------------------------------------------------------------------------------------------------------------
## DOXYGEN-START addDirIncludes
## addDirIncludes(dir [includeDirectoryName])
##
## Macro that adds the include path(s) to ${PROJECT_NAME}_INCLUDE_DIRS variable and also adds the paths to the included
## directories list. Searches in the specified subdirectory for any header files stored under 'includeDirectoryName' directory
##
## Scans the path and if any part is surrounded by {} then adds that path AND the path with this name replced by it's alias (if it has one)
##
## DOXYGEN-END
##
##
macro (addDirIncludes dir)

logDebug("addDirIncludes(${PROJECT_NAME}): dir=${dir} ARGC=${ARGC} ARGV0=${ARGV0} ARGV1=${ARGV1} ARGV2=${ARGV2}")

    set (incDir "inc")
    if ( ${ARGC} GREATER_EQUAL "2" )
        set (incDir "${ARGV1}")
    endif()
    string(LENGTH ${incDir} incLen) 

    # Process the dir looking for {name} type entries
    string (FIND ${dir} "{" pos)
    string (FIND ${dir} "}" epos)
    if ( (${pos} LESS 0) OR (${epos} LESS ${pos}) )
    
        # No special entries so use dir as-is
	    _addDirIncludes(${dir} ${incDir})
	
	else()
	
	    # Special entry, use name and alias if set
	    string(SUBSTRING ${dir} 0 ${pos} prefix)
	    
	    math (EXPR namestart "${pos} + 1")
	    math (EXPR namelen "${epos} - ${pos} - 1")
	    string(SUBSTRING ${dir} ${namestart} ${namelen} name)
        
	    math (EXPR suffixstart "${epos} + 1")
	    string(SUBSTRING ${dir} ${suffixstart} -1 suffix)
        
logDebug("addDirIncludes: prefix=${prefix} name=${name} suffix=${suffix}")

        ## as-is        
logDebug("addDirIncludes: PATH=${prefix}${name}${suffix}")
	    _addDirIncludes(${prefix}${name}${suffix} ${incDir})
	    
	    ## check for alias
	    getAlias(aliasName ${name})
    	if (aliasName)
logDebug("addDirIncludes: ALIAS PATH=${prefix}${aliasName}${suffix}")
    	    _addDirIncludes(${prefix}${aliasName}${suffix} ${incDir})
    	endif()
	    
	
	endif()
	
logDebug("addDirIncludes(${PROJECT_NAME}): ${PROJECT_NAME}_INCLUDE_DIRS=${${PROJECT_NAME}_INCLUDE_DIRS}")

endmacro (addDirIncludes)


##----------------------------------------------------------------------------------------------------------------------
## pushSrcDir( <dir> )
##
## Function which adds a sub-directory name to the list of sub-directory prefixes that will be used by add_sources
##
function (pushSrcDir dir)

logDebug ("pushSrcDir(${dir}) PROJECT_NAME=${PROJECT_NAME} CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR} CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")

    get_property( src_dirs GLOBAL PROPERTY SRC_DIRS_PREFIX )

    list (APPEND src_dirs ${dir})

logDebug("pushSrcDir(${dir}) - src_dirs=${src_dirs}")

    set_property( GLOBAL PROPERTY SRC_DIRS_PREFIX ${src_dirs} )

endfunction(pushSrcDir)

##----------------------------------------------------------------------------------------------------------------------
## popSrcDir( )
##
## Function which removes a sub-directory name from the list of sub-directory prefixes that will be used by add_sources
##
function (popSrcDir)
    get_property( src_dirs GLOBAL PROPERTY SRC_DIRS_PREFIX )

logDebug("popSrcDir() - src_dirs=${src_dirs}")

    list (LENGTH src_dirs len)
    if (${len} EQUAL 0)
        message(FATAL_ERROR "Attempting to pop source directory from empty list")
    endif ()

    list (REMOVE_AT src_dirs -1)

logDebug("popSrcDir() - now src_dirs=${src_dirs}")

    set_property( GLOBAL PROPERTY SRC_DIRS_PREFIX ${src_dirs} )

endfunction(popSrcDir)

##----------------------------------------------------------------------------------------------------------------------
## addSrcDirPrefix( <path> )
##
## Function which adds the list of sub-directory prefixes to the path stored in variable named <path>
##
function (addSrcDirPrefix path)
    get_property( src_dirs GLOBAL PROPERTY SRC_DIRS_PREFIX )

    list (LENGTH src_dirs len)
    if (${len} EQUAL 0)
        return ()
    endif ()

    # Prefix the path
    set (prefix "")
    foreach (dir ${src_dirs})
        set (prefix "${prefix}${dir}/")
    endforeach ()

logDebug("addSrcDirPrefix(${${path}}) - src_dirs=${src_dirs} prefix=${prefix}")

    # return the new path
    set (${path} ${prefix}${${path}} PARENT_SCOPE)

endfunction(addSrcDirPrefix)

##----------------------------------------------------------------------------------------------------------------------
## usingSrcDirPrefix( <flag> )
##
## Sets <flag> if we are using a source path directory prefix. This means that we're under some sub-directory and don't
## want to add these directory names to the top-level repository library name
##
function (usingSrcDirPrefix flag)
    get_property( src_dirs GLOBAL PROPERTY SRC_DIRS_PREFIX )

    list (LENGTH src_dirs len)

    # return flag
    set (${flag} ${len} PARENT_SCOPE)

endfunction(usingSrcDirPrefix)



##----------------------------------------------------------------------------------------------------------------------
## add_sources( <var> ... )
##
## Macro that adds the source files to the named variable
##
macro (add_sources var)
    file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")

logDebug ("add_sources(${var}) PROJECT_NAME=${PROJECT_NAME} CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR} CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR} relPath=${_relPath} ARGN=${ARGN}")

    if (NOT _relPath)
        set(_relPath ".")
    endif()

	if (_relPath MATCHES "^\\.\\./.*")

	    # relative (external) path - use as-is

	elseif(_relPath MATCHES "^/.*")

	    # absolute path - use as-is

	else()

    	# strip off any prefix directories (library may be in a sub-directory under the main repository (e.g. hardware/common)
    	get_filename_component(_relPath ${_relPath} NAME)

    endif()

    # Now add any directory prefix values
    addSrcDirPrefix(_relPath)

logDebug ("add_sources(${var}) relPath=${_relPath}")

    foreach (_src ${ARGN})
        if (_relPath)
            list (APPEND ${var} "${_relPath}/${_src}")
        else()
            list (APPEND ${var} "${_src}")
        endif()
    endforeach()

logDebug ("add_sources(${var}) _relPath=${_relPath} LIST: ${var}=${${var}}")

    if (_relPath)
        # propagate var to parent directory
        set (${var} ${${var}} PARENT_SCOPE)

logDebug ("add_sources(${var}) set ${var} in PARENT")

    endif()
endmacro(add_sources)

##----------------------------------------------------------------------------------------------------------------------
## add_dirs( <var> ... )
##
## Macro that adds the directories to the named variable (NOTE: This is just an alias to make it's function clear -
## actually just uses the "add_sources" macro)
##
macro (add_dirs var)
	add_sources (${var} ${ARGN})
endmacro(add_dirs)

##----------------------------------------------------------------------------------------------------------------------
## add_targets( <var> ... )
##
## Macro that adds the targets to the named variable
##
macro (add_targets var)
    file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach (_target ${ARGN})
        list (APPEND ${var} "${_target}")
    endforeach()
    if (_relPath)
        # propagate var to parent directory
        set (${var} ${${var}} PARENT_SCOPE)
    endif()
endmacro(add_targets)

##----------------------------------------------------------------------------------------------------------------------
## getBuildPath( <path> )
##
## Function that determines the current build path relative to the repository. For example, building in
## ~/git/common/build/x86_64-ETNA-FTU-AXIS will set $path to "build/x86_64-ETNA-FTU-AXIS"
##
function (getBuildPath path)

	string (REPLACE "${CMAKE_SOURCE_DIR}/" "" _path ${CMAKE_BINARY_DIR})
	set (${path} ${_path} PARENT_SCOPE)

	logDebug("CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR} CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR} build=${_path}")

endfunction(getBuildPath)

##----------------------------------------------------------------------------------------------------------------------
## getBuildPaths( <paths> )
##
## Function that determines the current build path relative to the repository, and creates a list of paths
## that should be searched in other repositories based on the customer/application/board settings.
##
## For example, if the build directory is build/x86_64-ETNA-AXIS-FTU then it returns the paths:
##
##    build/x86_64-ETNA-AXIS-FTU
##    build/x86_64-ETNA-AXIS
##    build/x86_64-ETNA
##    build/x86_64
##
function (getBuildPaths paths)

	# get main build path
	getBuildPath( buildPath )

	get_filename_component(dir ${buildPath} DIRECTORY)
	get_filename_component(name ${buildPath} NAME)

	set(_paths ${buildPath})
	string(FIND ${name} "-" pos REVERSE)
	while (${pos} GREATER 0)
	    string (SUBSTRING ${name} 0 ${pos} name)
	    list (APPEND _paths ${dir}/${name})
    	string(FIND ${name} "-" pos REVERSE)
	endwhile ()

	logDebug("getBuildPaths=${_paths}")
	set (${paths} ${_paths} PARENT_SCOPE)

endfunction(getBuildPaths)

##----------------------------------------------------------------------------------------------------------------------
## repoLibName( <lib> <repo> [ <sub-dir> ] )
##
## Function that sets $lib with the correct library name determined by the repository name and optionally a sub-directory.
## With no sub-directory specified $lib is just set to the repository name. With a sub-directory specified it concatentantes
## them to produce a combined library name
##
function (repoLibName lib repo subdir)

	logDebug("repoLibName(repo=${repo} subdir=${subdir})")

	# If subdir is of the form "../ETNA/waveform" then convert to just "waveform" i.e. strip off ../<dir>
	string (REGEX REPLACE "^\\.\\./[^/]+/" "/" subdir ${subdir})
	logDebug("repoLibName(now subdir=${subdir})")

	if (subdir)

	    ## Don't use sub-dirs if the directory prefix is set
	    usingSrcDirPrefix(usingPrefix)
	    if (${usingPrefix} GREATER 0)

    		# don't use subdir
    		set (subdir "")

	    else (${usingPrefix} GREATER 0)
    		# If sub-dir is something like ETNA/adc then we use the "ETNA" part, however if it's just something
    		# like fault (for example from the common repository) then we don't use that. So, we only use the first
    		# dir of a directory path if that path contains multiple dirs; otherwise we don't use it at all
    		#
    		string (FIND ${subdir} "/" pos)
    		if (${pos} GREATER 0)
    			# strip off any subdirectories
    			string (SUBSTRING ${subdir} 0 ${pos} subdir)

    			# capitalise the first letter of the sub-directory (leave rest in same case)
    			string (SUBSTRING ${subdir} 0 1 firstChar)
    			string (SUBSTRING ${subdir} 1 -1 body)
    			string (TOUPPER ${firstChar} firstChar)
    			string (CONCAT subdir ${firstChar} ${body})

    		logDebug("stripping trailing dirs...")

    		else(${pos} GREATER 0)
    			# don't use subdir
    			set (subdir "")
    		endif(${pos} GREATER 0)

	    endif (${usingPrefix} GREATER 0)

		# create the combined name
		set (${lib} "${repo}${subdir}" PARENT_SCOPE)

		logDebug("repoLibName = lib=${repo}${subdir} (pos=${pos})")

	else ()

		set (${lib} "${repo}" PARENT_SCOPE)

	endif ()

endfunction(repoLibName)

##----------------------------------------------------------------------------------------------------------------------
## getCurrentLib( <lib> )
##
## Function that determines the current library. For example, building the common lib of hardware will set $lib
## to hardwareCommon
##
function (getCurrentLib lib)

    file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    repoLibName(libname ${PROJECT_NAME} ${_relPath})

    logDebug("getCurrentLib() PROJECT_NAME=${PROJECT_NAME} relpath=${_relPath} lib=${libname}")

	set( ${lib} ${libname} PARENT_SCOPE)

endfunction(getCurrentLib)


##----------------------------------------------------------------------------------------------------------------------
## _findRepoLib(<name> [ <subdir> [test]] )
##
## Function that adds any includes/targets defined by the repository $name as a cmake package. If subdir is specified then
## loads in the package from that sub directory of the repository (e.g. hardware/common). If the 3rd argument is specified
## then the test library for this subdirectory will be loaded
##
## Adds the <name>_package_source file to the parent scope variable PACKAGE_SOURCE_LIST
##
function (_findRepoLib name)

logDebug("_findRepoLib(${name} ARGV1=${ARGV1} test=${ARGV2}) : ARGC=${ARGC}")
#	logDebug("PROJECT_NAME=${PROJECT_NAME} (SRC=${CMAKE_CURRENT_SOURCE_DIR}): useRepoLib(name=${name} subdir=${ARGV1})")

    # get repository name
    set (repoName ${name})
	if (${ARGC} GREATER 1)

	    # subdir may be of the form "embedded/lib"
	    string(REPLACE "/" "" subname ${ARGV1})

		# also need to get the library name we're looking for
		repoLibName(repoName ${name} "${subname}/dummy")

		# If 3rd argument is specified then append it to the package name
		if (${ARGC} GREATER 2)
			set (repoName ${repoName}${ARGV2})
		endif()
	endif()

    # Handle feature names (which are of the form <featue>@<value>
    # Replace @ with _
    string (REPLACE "@" "_" repoName ${repoName})

	# convert path names to just a name
    string (REPLACE "/" "" repoName ${repoName})

logDebug("_findRepoLib(${name} subdir=${ARGV1} repoName=${repoName})")


    # get the list of build paths to try
	set (paths "")

	getAlias(aliasName ${name})

	getBuildPaths( buildPaths )
	foreach (buildPath ${buildPaths})

    	if (${ARGC} GREATER 1)

    		# subdir
    		list (APPEND paths ${GITDIR}/${name}/${ARGV1}/${buildPath})
    		if (aliasName)
	    		list (APPEND paths ${GITDIR}/${aliasName}/${ARGV1}/${buildPath})
    		endif()
    		
    		# alternatively, may be a "submodule" in an adjacent repo
    		list (APPEND paths ${GITDIR}/${name}-${ARGV1}/${buildPath})
    		if (aliasName)
	    		list (APPEND paths ${GITDIR}/${aliasName}-${ARGV1}/${buildPath})
    		endif()
    		
    		# may be a subdirectory under this repo build
    		list (APPEND paths ${GITDIR}/${name}/${buildPath}/${ARGV1})
    		if (aliasName)
	    		list (APPEND paths ${GITDIR}/${aliasName}/${buildPath}/${ARGV1})
    		endif()
    		
    		# special case for features - look in <name>-common/<lib>
    		string (FIND ${ARGV1} ".feature" pos)
        	if (${pos} GREATER 0)
        		list (APPEND paths ${GITDIR}/${name}-common/${ARGV1}/${buildPath})
        		if (aliasName)
    	    		list (APPEND paths ${GITDIR}/${aliasName}-common/${ARGV1}/${buildPath})
        		endif()
            endif()
    		
    		# another special case where "subdir" is complete path from repo and name is a lib under this build path
    		list (APPEND paths ${GITDIR}/${ARGV1}/${buildPath})

    		# special case: "sysroot" directory under repo
    		list (APPEND paths ${GITDIR}/${name}/${buildPath}/sysroot)
    		if (aliasName)
	    		list (APPEND paths ${GITDIR}/${aliasName}/${buildPath}/sysroot)
    		endif()
    		

    	else ()

    	    # top
    	    list (APPEND paths ${GITDIR}/${name}/${buildPath})
    		if (aliasName)
	    		list (APPEND paths ${GITDIR}/${aliasName}/${buildPath})
    		endif()

    	endif()
	endforeach()

	logDebug("_findRepoLib(${repoName}) search paths=${paths}")
   	set(pkgPaths ${paths} PARENT_SCOPE)

	# Find the package
	set (quiet "QUIET")
	if (DEBUG_CMAKELIST)
	    set (quiet "")
	endif()
	find_package (${repoName} ${quiet} PATHS ${paths} NO_DEFAULT_PATH)
	if (NOT ${repoName}_VERSION)
		find_package (${name} ${quiet} PATHS ${paths} NO_DEFAULT_PATH)
		if (NOT ${name}_VERSION)
			return()
		endif ()
	endif ()


	# Package will set pkgName to the real name
	set(pkgName ${pkgName} PARENT_SCOPE)

	# Pass settings up
	set (REPO_INCLUDE_DIRS ${${pkgName}_INCLUDE_DIRS} PARENT_SCOPE)

	## Get the name of the source package (tarball of source files)
	set (REPO_PACKAGE_SOURCE_LIST ${${pkgName}_package_source} PARENT_SCOPE)
	
	## Get the list of C++ files for this lib
	set (REPO_SOURCE_FILES ${${pkgName}_source} PARENT_SCOPE)

#logDebug("PROJECT_NAME=${PROJECT_NAME} LIB_SOURCE_FILES: ${pkgName} = ${${pkgName}_source} : ${LIB_SOURCE_FILES}")

endfunction(_findRepoLib)

##----------------------------------------------------------------------------------------------------------------------
## useRepoLib( <name> [ <subdir> [test]] )
##
## Function that adds any includes/targets defined by the repository $name as a cmake package. If subdir is specified then
## loads in the package from that sub directory of the repository (e.g. hardware/common). If the 3rd argument is specified
## then the test library for this subdirectory will be loaded
##
## Adds the <name>_package_source file to the parent scope variable PACKAGE_SOURCE_LIST
##
function (useRepoLib name)

	## set alias
	getAlias(aliasName ${name})

logDebug("useRepoLib(${name} [${ARGN}]) - ALIAS=${aliasName}")

	## try the given name first
	set(pkgName "")
	_findRepoLib(${name} ${ARGN})

	## retry if not found
	if (NOT pkgName)
	
		# Not found, try an ALIAS if possible
		if (aliasName)
logDebug("useRepoLib(${name}) - failed, trying ${aliasName}")
			_findRepoLib(${aliasName} ${ARGN})
		endif()
	endif()
	
	## should have found it by now
	if (NOT pkgName)
    	if (${ARGC} GREATER 1)
    	    set (fullname ${name}/${ARGV1})
    	endif()
		message (FATAL_ERROR "Unable to load repository ${name} (${fullname})- searched in ${pkgPaths} for build")
	endif()

#	logDebug("PROJECT_NAME=${PROJECT_NAME} (SRC=${CMAKE_CURRENT_SOURCE_DIR}): useRepoLib(name=${name} subdir=${ARGV1})")

	# Package will set pkgName to the real name

	# Add the include paths
	includeDirectories (${REPO_INCLUDE_DIRS})

logDebug("useRepoLib(${name}) Added includes for ${pkgName}=${REPO_INCLUDE_DIRS}")

	## Add the real name to the parent scope
	set (REPO_LIB_NAME ${pkgName} PARENT_SCOPE)

logDebug("useRepoLib(${name}) PACKAGE_SOURCE_LIST=${PACKAGE_SOURCE_LIST}")

	## Get the name of the source package (tarball of source files)
	list (APPEND PACKAGE_SOURCE_LIST ${REPO_PACKAGE_SOURCE_LIST})
	set (PACKAGE_SOURCE_LIST ${PACKAGE_SOURCE_LIST} PARENT_SCOPE)
	
	## Get the list of C++ files for this lib
	list (APPEND LIB_SOURCE_FILES ${REPO_SOURCE_FILES})
	set (LIB_SOURCE_FILES ${LIB_SOURCE_FILES} PARENT_SCOPE)
	set (THIS_LIB_SOURCE_FILES ${REPO_SOURCE_FILES} PARENT_SCOPE)

logDebug("useRepoLib(${name}) THIS_LIB_SOURCE_FILES=${THIS_LIB_SOURCE_FILES}")
logDebug("useRepoLib(${name}) LIB_SOURCE_FILES=${REPO_SOURCE_FILES}")

endfunction(useRepoLib)


##----------------------------------------------------------------------------------------------------------------------
## addRepoLib( <varname> <name> [ <subdir> [test]] )
##
## Function that first loads the specified repo lib ( via useRepoLib() ). It then appends the actual repo library name
## to the variable specified by <var>.
##
## For example, instead of using the sequence:
##
##   useRepoLib (hardware vhi test)  # adds the library hardwareVhiTest
##   ...
##   addGtest(some_TEST "...;hardwareVhiTest" ${test_src})
##
## You can use:
##
##   set (libs "...")
##   addRepoLib (libs hardware vhi test)
##   ...
##   addGtest(some_TEST "${libs}" ${test_src})
##
## Which means you don't need to know the actual library name
##
function (addRepoLib var name)

#	logDebug("addRepoLib(name=${name} subdir=${ARGV2})")

	set (REPO_LIB_NAME "")

	# load the package
	useRepoLib(${name} ${ARGN})

logDebug("addRepoLib(${name}) to var ${var} = ${${var}} : REPO_LIB_NAME=${REPO_LIB_NAME} CMAKE_CURRENT_LIST_DIR=${CMAKE_CURRENT_LIST_DIR}")

	## the real name is now in REPO_LIB_NAME, add it to the libraries variable
	list (APPEND ${var} ${REPO_LIB_NAME})
	set (${var} ${${var}} PARENT_SCOPE)

logDebug("addRepoLib(${name}) - now ${var} = ${${var}}")

	## Pass the source package list back up
	set (PACKAGE_SOURCE_LIST ${PACKAGE_SOURCE_LIST} PARENT_SCOPE)

    # Pass the list of source files back up
	set (LIB_SOURCE_FILES ${LIB_SOURCE_FILES} PARENT_SCOPE)

endfunction(addRepoLib)


##----------------------------------------------------------------------------------------------------------------------
## addRepoIncludes(repo [subdir])
##
## Macro that adds the include path(s) to ${PROJECT_NAME}_INCLUDE_DIRS variable and also adds the paths to the included
## directories list. Searches in this subdirectory for any header files stored under 'inc' directory
##
macro (addRepoIncludes repo)

    set (path ${GITDIR}/${repo})
    
    set (subdir "${ARGV1}")
    if (subdir)
        set (path ${path}/${subdir})
    endif()

    findIncludes(${path} _HEADERS)

logDebug("addRepoIncludes(${path}): HEADERS=${_HEADERS}")

	foreach (_headerFile ${_HEADERS})

	    # skip directories under build areas
		string (FIND ${_headerFile} "/build/" pos)
		if (${pos} EQUAL -1)
    	    get_filename_component(_dir ${_headerFile} PATH)

            list (APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${_dir})
        endif()

	endforeach()

	list(LENGTH ${PROJECT_NAME}_INCLUDE_DIRS _numIncDirs)
	if (${_numIncDirs})

    	list(REMOVE_DUPLICATES ${PROJECT_NAME}_INCLUDE_DIRS)
    	includeDirectories(${${PROJECT_NAME}_INCLUDE_DIRS})

	endif()

	logDebug("addRepoIncludes(${path}): ${PROJECT_NAME}_INCLUDE_DIRS=${${PROJECT_NAME}_INCLUDE_DIRS}")

endmacro (addRepoIncludes)





##----------------------------------------------------------------------------------------------------------------------
## addFeature( <varname> <feature-name> <feature-value> <name> <subdir> )
##
## Function that adds a feature library that has been built in <name>/<subdir>. The Feature dir will be
## <feature-name>@<feature-value> and the library will be <name><subdir>_<feature-name>_<feature-value>
##
function (addFeature var feature featValue name subdir)

	logDebug("addFeature(var=${var} name=${name} subdir=${subdir} feat=${feature} value=${featValue})")
	
	if ("${subdir}" STREQUAL "" )
	    set (subdir "${feature}@${featValue}")
	else()
	    set (subdir "${subdir}/${feature}@${featValue}")
	endif()
	
	logDebug("addFeature: addRepoLib(${var} ${name} ${subdir})")
	addRepoLib(${var} ${name} ${subdir})

	logDebug("addFeature: ${var} = ${${var}}")

	## the real name is now in var, pass back up to parent
	set (${var} ${${var}} PARENT_SCOPE)

endfunction(addFeature)


##----------------------------------------------------------------------------------------------------------------------
## addLibFeature( <varname> <path> )
##
## Macro that adds a feature library at <path>. Converts <path> into:
## <feature-name> <feature-value> <name> <subdir> and call addRepoLib()
##
## <path> is expected to of the form: hardware/common.features/DPD@APP i.e. <name>/<subdir>/<feature-name>@<feature-value>
##
macro (addLibFeature var path)

	logDebug("addLibFeature(var=${var} path=${path})")

	# remove GIT dir from start of path if present
	string(REPLACE "${GITDIR}/" "" path ${path})

    # Actually all we need do here is grab the first directory name as <name> and pass the rest down
	string (FIND ${path} "/" pos)
	if (${pos} LESS 0)
	    return()
    endif()
    
    string(SUBSTRING ${path} 0 ${pos} name)
    math(EXPR pos "${pos}+1")
    string(SUBSTRING ${path} ${pos} -1 subdir)
	logDebug("addLibFeature(var=${var} name=${name} subdir=${subdir})")

    # Special case where name is of the form <base>-common and is a common shared "submodule"
    # In this case just refer to the lib as <base> and it will be correctly found
##    string(REPLACE "-common" "" name ${name})
    
	logDebug("addLibFeature: addRepoLib(${var} ${name} ${subdir})")
	addRepoLib(${var} ${name} ${subdir})

	logDebug("addLibFeature: ${var} = ${${var}}")

endmacro(addLibFeature)


##----------------------------------------------------------------------------------------------------------------------
## addAppFeature( <path> )
##
## Function that adds an application feature library. This is a special case where the library source is added to the
## list of application source such that the feature lib is compiled into objects and linked direct, rather than
## linking in a lib. This ensures that any autoload classes get initialised properly
##
function (addAppFeature path)

	logDebug("addAppFeature(path=${path})")
	
	# remove GIT dir from start of path if present
	string(REPLACE "${GITDIR}/" "" path ${path})

	# remove "applications" from start of path if present
	string(REGEX MATCH "(applications[^/]*)/" applib ${path})
	string(REGEX REPLACE "applications[^/]*/" "" path ${path})

    # Load this lib	
	string(REPLACE "/" "" applib ${applib})
	logDebug("addAppFeature: useRepoLib(${applib} ${path})")
    useRepoLib(${applib} ${path})
    
    # Add any sources
	logDebug("addAppFeature: SOURCES=${SOURCES}")
	logDebug("addAppFeature: THIS_LIB_SOURCE_FILES=${THIS_LIB_SOURCE_FILES}")
	list (APPEND SOURCES ${THIS_LIB_SOURCE_FILES})
	set (SOURCES ${SOURCES} PARENT_SCOPE)
	logDebug("addAppFeature: now SOURCES=${SOURCES}")
    
endfunction(addAppFeature)


##----------------------------------------------------------------------------------------------------------------------
## addThisLib( <varname> )
##
## Function that works out the name of the current library. It then appends this repo library name
## to the variable specified by <var>.
##
##
function (addThisLib var)

   	getCurrentLib(lib)
	list (APPEND ${var} ${lib})
	set (${var} ${${var}} PARENT_SCOPE)

logDebug("addThisLib(lib=${lib})")

endfunction(addThisLib)


##----------------------------------------------------------------------------------------------------------------------
## addRosLib( <varname> <name> )
##
## Function that adds a ROS-built library and appends the full path to the list specified by <varname>.
##
##
function (addRosLib var name)

	logDebug("addRosLib(name=${name}) : ${var} = ${${var}}")

    find_library(${name}_libpath ${name} PATHS ${DEVTOOLS_INSTALLDIR}/lib)
	logDebug("find_library(libpath ${name} PATHS ${DEVTOOLS_INSTALLDIR}/lib) : result=${${name}_libpath}")

    list (APPEND ${var} ${${name}_libpath})
    set (${var} ${${var}} PARENT_SCOPE)

    logDebug("addRosLib(${name}) - now ${var} = ${${var}}")

endfunction(addRosLib)



##----------------------------------------------------------------------------------------------------------------------
## addLinkLibs(<target>)
##
## Function that adds link libraries to the target, including any libs defined in the toolchain. 
## Wraps the libraries in a start/end group
##
function (addLinkLibs target)

	logDebug("addLinkLibs(${target}) TOOLCHAIN_LINK_LIBS: --start<< ${TOOLCHAIN_LINK_LIBS} >>end--")
	target_link_libraries(${target} -Wl,--start-group ${ARGN} ${TOOLCHAIN_LINK_LIBS} -Wl,--end-group)
	logDebug("addLinkLibs(${target}) LIBS: --start<< ${ARGN} >>end--")

endfunction(addLinkLibs)


##----------------------------------------------------------------------------------------------------------------------
## addTestCommon( <varname> <name> )
##
## Function that adds a 'test-common' subdirectory for use with tests. The test-common directory must be of the form:
##
##  test-common/
##    inc/            # includes
##    src/            # source
##
## Adds the includes directory and sets <var> to the full path for the source
##
function (addTestCommon var name)

	logDebug("addTestCommon(name=${name})")

    includeDirectories(${GITDIR}/${name}/test-common/inc)
	set (${var} ${GITDIR}/${name}/test-common/src PARENT_SCOPE)

endfunction(addTestCommon)

##----------------------------------------------------------------------------------------------------------------------
## addShared( <varname> <name> )
##
## Function that adds a 'shared' subdirectory for use with tests. The shared directory must be of the form:
##
##  shared/
##    inc/            # includes
##    src/            # source
##
## Adds the includes directory and sets <var> to the full path for the source
##
function (addShared var name)

	logDebug("addShared(name=${name})")

    includeDirectories(${GITDIR}/${name}/shared/inc)
	set (${var} ${GITDIR}/${name}/shared/src PARENT_SCOPE)

endfunction(addShared)


##----------------------------------------------------------------------------------------------------------------------
## exportLib()
##
## Function that exports this library
##
function (exportLib)
	string (TOLOWER ${PROJECT_NAME} project_name)

	logDebug("exportLib(${PROJECT_NAME}) - exporting CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}")
	export (TARGETS ${PROJECT_NAME} FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-targets.cmake)

	# set up some variables used in the config files
	set (binary_dir ${${PROJECT_NAME}_BINARY_DIR})
	set (include_dirs ${${PROJECT_NAME}_INCLUDE_DIRS})
	
	# Process the SOURCES list
	set (SOURCE_FILES "")
	foreach (path ${SOURCES})
	
	    # Only store C++ source
	    get_filename_component(ext ${path} EXT)
	    if (${ext} STREQUAL ".cpp")
	    
	        # Ensure full source path
	        get_filename_component(fullpath ${path} ABSOLUTE ${CMAKE_SOURCE_DIR})
	        
	        list(APPEND SOURCE_FILES ${fullpath})
	    
	    endif()
	
	endforeach()

	configure_file(
		${GITDIR}/buildTools/cmake/inc/pkg-config.cmake.in
		${${PROJECT_NAME}_BINARY_DIR}/${project_name}-config.cmake @ONLY)

	configure_file(
		${GITDIR}/buildTools/cmake/inc/pkg-config-version.cmake.in
		${${PROJECT_NAME}_BINARY_DIR}/${project_name}-config-version.cmake @ONLY)

	## Also create an alias target so we can just run 'make lib'
	add_custom_target(lib DEPENDS ${PROJECT_NAME})

	logDebug("exportLib(${PROJECT_NAME}) - END")

endfunction(exportLib)

##----------------------------------------------------------------------------------------------------------------------
## findFpga( <variable name> )
##
## Function that finds a valid fpga tgz and sets the specified variable with the tgz full path
##
## NOTE: addEmbeddedFpgaBuild() function changes this function's behaviour
##
function (findFpga fpgaTgzVar)

    if (DEFINED FPGA_FIND_FILE AND NOT FPGA_FIND_FILE STREQUAL "")

		# Use this setting
		set (fpgaTgz ${FPGA_FIND_FILE})

	else()

        ## Relies on the make to pass in a build setting that specifies which fpga to use
        if (DEFINED BUILD_FPGA_TARBALL AND NOT BUILD_FPGA_TARBALL STREQUAL "")

    		# Use this setting
    		set (fpgaTgz ${BUILD_FPGA_TARBALL})

        else()

            set(FPGADIR ${GITDIR}/fpga/images/${BUILD_BOARDAPPNAME})

            ## find a valid fpga
            file (GLOB fpgaTgzList "${FPGADIR}/*.tgz")
            list (LENGTH fpgaTgzList len)
            if (${len} EQUAL 0)
                message(FATAL_ERROR "Unable to find any fpga images in ${FPGADIR}")
            endif ()
            list (GET fpgaTgzList -1 fpgaTgz)

        endif()

	endif()

    set (${fpgaTgzVar} ${fpgaTgz} PARENT_SCOPE)

endfunction (findFpga)

##----------------------------------------------------------------------------------------------------------------------
## _setEmbeddedBase( <name> )
## 
## Base macro for setting up embedded build - used internally by other macros
##
##
macro (_setEmbeddedBuild name)

	logDebug("_setEmbeddedBuild(name=${name})")
	
	set (embeddedPath ${GITDIR}/${name}/embedded)
	set (embeddedBuild ${embeddedPath}/build/${EMBEDDED_TARGET}-${BUILD_BOARD}-${BUILD_CUSTOMER}-${BUILD_APPLICATION})

	logDebug("_setEmbeddedBuild(name=${name}) embeddedPath=${embeddedPath}")
	logDebug("_setEmbeddedBuild(name=${name}) embeddedBuild=${embeddedBuild}")

    # Includes embedded headers - common
    includeDirectories(${embeddedPath}/inc)
    includeDirectories(${embeddedPath}/vapi/inc)
    
    # Include target-specific headers
    includeDirectories(${embeddedPath}/${EMBEDDED_TARGET}/inc)
    includeDirectories(${embeddedPath}/${BUILD_FPGA_VENDOR}/inc)

    # Export
    set (${name}EmbeddedPath ${embeddedPath} PARENT_SCOPE)
    set (${name}EmbeddedBuild ${embeddedBuild} PARENT_SCOPE)
    
	logDebug("_setEmbeddedBuild(name=${name}) END")

endmacro(_setEmbeddedBuild)

##----------------------------------------------------------------------------------------------------------------------
## setEmbeddedFpga( <name> )
##
## Macro that modifies the behaviour of findFpga() function such that it will use this fpga tarball rather than the
## stored (raw) fpga. Does this through a cache variable.
##
##
macro (setEmbeddedFpga name)

	logDebug("setEmbeddedFpga(name=${name})")

	set (fpgaTgz ${embeddedBuild}/fpga-${name}.tgz)

    # Export
    set (${name}FpgaTgz ${fpgaTgz} PARENT_SCOPE)

    # Make findFpga use this fpga rather than the raw fpga stored in the 'fpga' repo
    set (FPGA_FIND_FILE ${fpgaTgz} CACHE STRING "FPGA to use in the application" FORCE)

	logDebug("setEmbeddedFpga(name=${name}) END")

endmacro(setEmbeddedFpga)

##----------------------------------------------------------------------------------------------------------------------
## setEmbeddedBuild( <name> )
##
## Macro that sets up the embedded build variables
##
##
macro (setEmbeddedBuild name)

	logDebug("setEmbeddedBuild(name=${name})")

	# For x86_64 builds, set the embedded build target to x86_64; otherwise use the fpga vendor as target
	set (EMBEDDED_TARGET ${BUILD_FPGA_VENDOR})
    if (${TARGET} STREQUAL "x86_64")
    	set (EMBEDDED_TARGET ${TARGET})
	endif()

	logDebug("setEmbeddedBuild(name=${name}) - EMBEDDED_TARGET=${EMBEDDED_TARGET} BUILD_FPGA_VENDOR=${BUILD_FPGA_VENDOR}")
	
	_setEmbeddedBuild(${name})

	logDebug("setEmbeddedBuild(name=${name}) embeddedPath=${embeddedPath}")
	logDebug("setEmbeddedBuild(name=${name}) embeddedBuild=${embeddedBuild}")

	logDebug("setEmbeddedBuild(name=${name}) END")

endmacro(setEmbeddedBuild)


##----------------------------------------------------------------------------------------------------------------------
## setEmbeddedBuild( <name> )
##
## Macro that that sets up the embedded build variables AND modifies the behaviour of findFpga() function such that it will use this fpga tarball rather than the
## stored (raw) fpga. Does this through a cache variable.
##
##
macro (setEmbeddedFpgaBuild name)

	logDebug("setEmbeddedFpgaBuild(name=${name})")

	setEmbeddedBuild(${name})

	# Change FPGA to embed the app
	setEmbdeddedFpga(${name})

	logDebug("setEmbeddedFpgaBuild(name=${name}) END")

endmacro(setEmbeddedFpgaBuild)




##----------------------------------------------------------------------------------------------------------------------
## unsetEmbeddedBuild( <name> )
##
## Macro that clears any cache variables related to embedded builds
##
##
macro (unsetEmbeddedBuild name)

	logDebug("unsetEmbeddedBuild(name=${name})")

    # Make findFpga use this fpga rather than the raw fpga stored in the 'fpga' repo
    set (FPGA_FIND_FILE "" CACHE STRING "FPGA to use in the application" FORCE)

	logDebug("unsetEmbeddedBuild(name=${name}) END")

endmacro(unsetEmbeddedBuild)


##----------------------------------------------------------------------------------------------------------------------
## useEmbeddedBuild( <name> )
##
## Macro that modifies the behaviour of findFpga() function such that it will use this fpga tarball rather than the
## stored (raw) fpga. Does this through a cache variable.
##
##
function (useEmbeddedBuild name)

	logDebug("useEmbeddedBuild(name=${name})")

    setEmbeddedBuild(${name})

	logDebug("useEmbeddedBuild(name=${name}) END")

endfunction(useEmbeddedBuild)


##----------------------------------------------------------------------------------------------------------------------
## addEmbeddedBuild( <name> )
##
## Function that adds a Embedded design to the build. You specify the repo name and the function
## assumes there is a <name>/embedded directory in which a CMakeLists.txt file lives. It ensures
## the embedded directory CMakeLists.txt is included.
##
## Also modifies the behaviour of findFpga() function such that it will use this fpga tarball rather than the
## stored (raw) fpga. Does this through a cache variable.
##
##
function (addEmbeddedBuild name)

	logDebug("addEmbeddedBuild(name=${name})")

	setEmbeddedBuild(${name})

logDebug("Added embedded project ${EMBEDDED_PROJECT}")

    # Save the name of the embedded project being used (causes embedded code to be built as part of packaging)
    set (EMBEDDED_PROJECT ${embeddedBuild} CACHE STRING "Embedded project used in the application" FORCE)
    logDebug("embeddedBuild=${embeddedBuild}")
    logDebug("EMBEDDED_PROJECT=${EMBEDDED_PROJECT}")

endfunction(addEmbeddedBuild)


##----------------------------------------------------------------------------------------------------------------------
## useEmbeddedFpgaBuild( <name> )
##
## Macro that modifies the behaviour of findFpga() function such that it will use this fpga tarball rather than the
## stored (raw) fpga. Does this through a cache variable.
##
##
function (useEmbeddedFpgaBuild name)

	logDebug("useEmbeddedFpgaBuild(name=${name})")

    setEmbeddedFpgaBuild(${name})

	logDebug("useEmbeddedFpgaBuild(name=${name}) END")

endfunction(useEmbeddedFpgaBuild)


##----------------------------------------------------------------------------------------------------------------------
## addEmbeddedFpgaBuild( <name> )
##
## Function that adds a Embedded design to the build. You specify the repo name and the function
## assumes there is a <name>/embedded directory in which a CMakeLists.txt file lives. It ensures
## the embedded directory CMakeLists.txt is included.
##
## Also modifies the behaviour of findFpga() function such that it will use this fpga tarball rather than the
## stored (raw) fpga. Does this through a cache variable.
##
##
function (addEmbeddedFpgaBuild name)

	logDebug("addEmbeddedBuild(name=${name})")

	setEmbeddedFpgaBuild(${name})

logDebug("Added embedded project ${EMBEDDED_PROJECT}")

    # Save the name of the embedded project being used (causes embedded code to be built as part of packaging)
    set (EMBEDDED_PROJECT ${embeddedBuild} CACHE STRING "Embedded project used in the application" FORCE)
    logDebug("embeddedBuild=${embeddedBuild}")
    logDebug("EMBEDDED_PROJECT=${EMBEDDED_PROJECT}")

endfunction(addEmbeddedFpgaBuild)


##----------------------------------------------------------------------------------------------------------------------
## delEmbeddedBuild( <name> )
##
## Function that deletes a Embedded design to the build. This clears out the cache variables from any previous settings
##
##
function (delEmbeddedBuild name)

	logDebug("delEmbeddedBuild(name=${name})")

	unsetEmbeddedBuild(${name})

logDebug("Deleted embedded project ${EMBEDDED_PROJECT}")

    # Save the name of the embedded project being used (causes embedded code to be built as part of packaging)
    set (EMBEDDED_PROJECT "" CACHE STRING "Embedded project used in the application" FORCE)
    logDebug("EMBEDDED_PROJECT=${EMBEDDED_PROJECT}")

endfunction(delEmbeddedBuild)


##----------------------------------------------------------------------------------------------------------------------
## setEmbeddedProcess( <name> )
## 
## Macro that sets up a build for a standalone process running on the target (running code that was originally
## written to run on an embedded processor (in the fpga))
##
##
macro (setEmbeddedProcess name)

	logDebug("setEmbeddedProcess(name=${name})")
	
	# Set target
	set (EMBEDDED_TARGET ${TARGET})

	logDebug("setEmbeddedProcess(name=${name}) - EMBEDDED_TARGET=${EMBEDDED_TARGET} BUILD_FPGA_VENDOR=${BUILD_FPGA_VENDOR}")
	
	_setEmbeddedBuild(${name})

	logDebug("setEmbeddedProcess(name=${name}) END")

endmacro(setEmbeddedProcess)


##----------------------------------------------------------------------------------------------------------------------
## useEmbeddedProcess( <name> )
## 
## Macro that sets up a build for a standalone process running on the target (running code that was originally
## written to run on an embedded processor (in the fpga))
##
##
function (useEmbeddedProcess name)

	logDebug("useEmbeddedProcess(name=${name})")
	
    setEmbeddedProcess(${name})

	logDebug("useEmbeddedProcess(name=${name}) END")

endfunction(useEmbeddedProcess)


##----------------------------------------------------------------------------------------------------------------------
## addEmbeddedProcess( <name> )
## 
## Function that adds a Embedded design to the build. You specify the repo name and the function
## assumes there is a <name>/embedded directory in which a CMakeLists.txt file lives. It ensures 
## the embedded directory CMakeLists.txt is included.
##
##
function (addEmbeddedProcess name)

	logDebug("addEmbeddedProcess(name=${name})")
	
	setEmbeddedProcess(${name})
	
logDebug("Added embedded process project ${EMBEDDED_PROJECT}")

    # Save the name of the embedded project being used (causes embedded code to be built as part of packaging)
    set (EMBEDDED_PROJECT ${embeddedBuild} CACHE STRING "Embedded project used in the application")
    logDebug("embeddedBuild=${embeddedBuild}")
    logDebug("EMBEDDED_PROJECT=${EMBEDDED_PROJECT}")
    
endfunction(addEmbeddedProcess)


##----------------------------------------------------------------------------------------------------------------------
## addEmbeddedExecutable(  <exe> <source list> <libs list> )
##
## Macro that adds an embedded executable build target
##
##
##
##
macro (addEmbeddedExecutable exe sourceList libs)

add_executable(${exe} ${sourceList})
addLinkLibs(${exe} ${libs})

set(appBuilddir ${GITDIR}/$ENV{BUILD_APP_REPO}/${BUILD_CUSTOMER}-${BUILD_APPLICATION}/build/$ENV{BUILD_APP_TARGET}-${BUILD_BOARD}-${BUILD_CUSTOMER}-${BUILD_APPLICATION})

add_custom_target(${exe}-clean ALL
	COMMAND rm -f ${appBuilddir}/extras/embedded-firmware/${exe}
	COMMENT Clean out extras/embedded-firmware)

install(
	TARGETS ${exe}
	DESTINATION ${appBuilddir}/extras/embedded-firmware
)

endmacro (addEmbeddedExecutable)

##----------------------------------------------------------------------------------------------------------------------
## addLinkerScript(  <link script path> )
##
## Macro that adds a linker script
##
macro (addLinkerScript linkScript)

set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-T -Wl,${CMAKE_CURRENT_SOURCE_DIR}/${linkScript}")

endmacro (addLinkerScript)


##----------------------------------------------------------------------------------------------------------------------
## addExternalDirectory(  <relPath>  )
##
## Macro that adds a directory that is not a subdirectory of the main project. Uses <relPath> as the relative path to the
## directory.
##
## Example: addExternalDirectory( ../ETNA_ART/caldata )
##
##
##
macro (addExternalDirectory relPath)

logDebug("addExternalDirectory(${PROJECT_NAME}): START path=${relPath}")

    ## Add includes
    get_filename_component(dir ${relPath} DIRECTORY)
    findIncludes(${dir} _HEADERS)

logDebug("addExternalDirectory(${PROJECT_NAME}): CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR} HEADERS=${_HEADERS}")

	foreach (_headerFile ${_HEADERS})
	    get_filename_component(_dir ${_headerFile} PATH)

        list (APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${_dir})

	endforeach()

	list(LENGTH ${PROJECT_NAME}_INCLUDE_DIRS _numIncDirs)
	if (${_numIncDirs})

    	list(REMOVE_DUPLICATES ${PROJECT_NAME}_INCLUDE_DIRS)
    	includeDirectories(${${PROJECT_NAME}_INCLUDE_DIRS})

	endif()

logDebug("addExternalDirectory(${PROJECT_NAME}): ${PROJECT_NAME}_INCLUDE_DIRS=${${PROJECT_NAME}_INCLUDE_DIRS}")


    ## Process the source
    get_filename_component(name ${relPath} NAME)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${relPath} ${CMAKE_CURRENT_BINARY_DIR}/${name})

logDebug("addExternalDirectory(${PROJECT_NAME}): END add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${relPath} ${CMAKE_CURRENT_BINARY_DIR}/${name})")

endmacro(addExternalDirectory)

##----------------------------------------------------------------------------------------------------------------------
## addExternalIncludeDirectory(  <relPath>  )
##
## Macro that adds an include directory that is not a subdirectory of the main project. Uses <relPath> as the relative path to the
## directory.
##
## Example: addExternalIncludeDirectory( ../ETNA_ART/caldata )
##
##
##
macro (addExternalIncludeDirectory relPath)

    ## Add includes
    get_filename_component(dir ${relPath} DIRECTORY)
    findIncludes(${dir} _HEADERS)

    logDebug("addExternalIncludeDirectory(${PROJECT_NAME}): CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR} HEADERS=${_HEADERS}")

	foreach (_headerFile ${_HEADERS})
	    get_filename_component(_dir ${_headerFile} PATH)

        list (APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${_dir})

	endforeach()

	list(LENGTH ${PROJECT_NAME}_INCLUDE_DIRS _numIncDirs)
	if (${_numIncDirs})

    	list(REMOVE_DUPLICATES ${PROJECT_NAME}_INCLUDE_DIRS)
    	includeDirectories(${${PROJECT_NAME}_INCLUDE_DIRS})

	endif()

logDebug("addExternalIncludeDirectory(${PROJECT_NAME}): ${PROJECT_NAME}_INCLUDE_DIRS=${${PROJECT_NAME}_INCLUDE_DIRS}")

endmacro(addExternalIncludeDirectory)


##----------------------------------------------------------------------------------------------------------------------
## addExecutable(  <name> <source list> <libraries list>  )
##
## Macro that adds an executable built from the source list and linked with the libraries list.
##
##
macro (addExecutable name source libs)

    add_executable(${name} ${source})
    addLinkLibs(${name} ${libs})

    # Now also need to link against real-time library
    target_link_libraries(${name} rt rt rt)

endmacro(addExecutable)

##----------------------------------------------------------------------------------------------------------------------
## addVersionConfig()
##
## Macro that adds a config.h file containing version information.
##
##
macro (addVersionConfig)

    set (CFG_FILE ${PROJECT_BINARY_DIR}/config.h)

logDebug("addVersionConfig: CFG_FILE=${CFG_FILE}")

    ## NOTE: Use the target name "config_h" rather than a real file. This ensures the generate command is forced to always
    ## re-run every build

    # Some values are read direct from the current environment
    set (genConfigCommand ${CMAKE_COMMAND}
                -D GITDIR=${GITDIR}
                -D PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}
                -D BUILD_APPLICATION=${BUILD_APPLICATION}
                -D BUILD_APPNAME=${BUILD_APPNAME}
                -D BUILD_BOARD=${BUILD_BOARD}
                -D BUILD_BOARDAPPNAME=${BUILD_BOARDAPPNAME}
                -D BUILD_CUSTOMER=${BUILD_CUSTOMER}
                -D BUILD_DUPLEX=${BUILD_DUPLEX}
                -D BUILD_FIBRE_INTERFACE=${BUILD_FIBRE_INTERFACE}
                -D BUILD_NUMBER=${BUILD_NUMBER}
                -D BUILD_VERSION=${BUILD_VERSION}
                -D BUILD_FPGA_PART=${BUILD_FPGA_PART}
                -D BUILD_FPGA_BUILD=${BUILD_FPGA_BUILD}
                -D BUILD_FPGA_VENDOR=${BUILD_FPGA_VENDOR}
                -D PROJECT_NAME=${PROJECT_NAME}
                -D TARGET=${TARGET}
                -D BUILD_ENUM_APPLICATION=${BUILD_ENUM_APPLICATION}
                -D BUILD_ENUM_BOARD=${BUILD_ENUM_BOARD}
                -D BUILD_ENUM_CUSTOMER=${BUILD_ENUM_CUSTOMER}
                -D BUILD_ENUM_DUPLEX=${BUILD_ENUM_DUPLEX}
                -D BUILD_ENUM_FIBRE_INTERFACE=${BUILD_ENUM_FIBRE_INTERFACE}
                -P ${GITDIR}/buildTools/cmake/Modules/genConfig.cmake)

    # Force creation of a file now so that it's available for use in the source list
    execute_process(
        COMMAND ${genConfigCommand}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )

    # command to create the config file
    add_custom_command(
        OUTPUT config_h
        COMMAND ${genConfigCommand}
        COMMENT "genConfig: Creating version config ${CFG_FILE}"
    )


    add_custom_target(
           version ALL
           #DEPENDS ${CFG_FILE}
           DEPENDS config_h
           COMMENT "genConfig: Creating version ${CFG_FILE}"
    )

    # Add to include list
    includeDirectories(${PROJECT_BINARY_DIR})

    # Add to SOURCES list
    list (APPEND SOURCES ${CFG_FILE})

endmacro(addVersionConfig)

##----------------------------------------------------------------------------------------------------------------------
## call(name)
##
## Macro that "calls" a function via a variable. What it actually does is include the named macro. You then have to provide
## a cmake module of the same name and get that to do whatever you need to do
##
##
macro (call name)
    include(${feat}-appStart)
endmacro()

##----------------------------------------------------------------------------------------------------------------------
## appStart(name [srclist])
##
## Macro that perfoms some common setup for an application make
##
##
macro (appStart name)

    set (srclist ${ARGV1})
    set (libs "")

    set (app ${name})
    initialCapital(board ${BUILD_BOARD})
    set (boardApp ${board}${app})

    set (PACKAGE_SOURCE_LIST "")

    set (SOURCES
        bin-src/${app}.cpp
    )

    if (srclist)
        list(APPEND SOURCES "${srclist}")
    endif()
    
    ## "Call" feature hooks
    foreach (feat ${FEATURES})
        logDebug("appStart: feat ${feat} call appStart...")    
        call(${feat}-appStart)
    endforeach()
    
    logDebug("appStart: FEATURES=${FEATURES}")    
    logDebug("appStart: FEATURE_LIBS=${FEATURE_LIBS}")    

endmacro(appStart)

##----------------------------------------------------------------------------------------------------------------------
## appEnd()
##
## Macro that perfoms some common cleanup for an application make
##
##
macro (appEnd)

    ## Features
    
    logDebug("appEnd: libs=${libs}")
    
    foreach (featLib ${FEATURE_LIBS})

    	# remove GIT dir from start of path if present
    	string(REPLACE "${GITDIR}/" "" featLib ${featLib})
    	
        logDebug("appEnd: featLib=${featLib}")
    	
    	# check if this is an application lib
    	string (FIND ${featLib} "applications" pos)
    	if (${pos} EQUAL 0)
    	
            logDebug("appEnd: addAppFeature ${featLib}")
    	    # special application feature
            addAppFeature( ${featLib} )
    	else()
    	    
            logDebug("appEnd: addLibFeature ${featLib}")
    	    # feature in another repo - treat like any other lib
            addLibFeature( libs  ${featLib} )
        endif()

    endforeach()
    
    logDebug("appEnd: END libs=${libs}")
    
    ## "Call" feature hooks
#    foreach (feat ${FEATURES})
#        call(${feat}-appEnd)
#    endforeach()

    ## Executable
    addExecutable(${boardApp} "${SOURCES}" "${libs}")
    set (STARTUP_APP ${boardApp} PARENT_SCOPE)

    # Set the common install target
    install(TARGETS ${boardApp} RUNTIME DESTINATION ${APP_ROOTFS}/bin)

    ## Pass the source package list back up
    set (PACKAGE_SOURCE_LIST ${PACKAGE_SOURCE_LIST} PARENT_SCOPE)

    ## Pass the source list back up
    set (SOURCE_PATHS "")
    foreach (src ${SOURCES})
#    	logDebug("appEnd: ADD ${src}")
    	# Handle absolute paths
		string (FIND ${src} "/" abspos)
		if ( ${abspos} EQUAL 0 )
			# absolute
	        list (APPEND SOURCE_PATHS "${src}")
	    else()
	    	# relative
	        list (APPEND SOURCE_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/${src}")
	    endif()
    	
    endforeach()
    set (SOURCE_PATHS ${SOURCE_PATHS} PARENT_SCOPE)
    set (SOURCES ${SOURCES} PARENT_SCOPE)

endmacro(appEnd)

##----------------------------------------------------------------------------------------------------------------------
## setParentSources()
##
## Macro that pushes the current SOURCES list to the parent scope. Also ensures that the paths
## are corrected when going to the parent level
##
##
macro (setParentSources)

    # In local builds the variables are something like:
    #CMAKE_SOURCE_DIR=/data/git/rse/hardware/ECB_ART
    #CMAKE_CURRENT_SOURCE_DIR=/data/git/rse/hardware/ECB_ART/ArtHwFaults
    #SOURCES=Faults/src/ArtFaults.cpp;Faults/src/ArtFaultsSingleton.cpp
    #
    # we want: ArtHwFaults/Faults/src/ArtFaults.cpp etc -OR- /data/git/rse/hardware/ECB_ART/ArtHwFaults/Faults/src/ArtFaults.cpp


    # In builds that use this as an "external" directory:
    #CMAKE_SOURCE_DIR=/data/git/rse/hardware/ECB_CART
    #CMAKE_CURRENT_SOURCE_DIR=/data/git/rse/hardware/ECB_ART/ArtHwFaults
    #SOURCES=../ECB_ART/ArtHwFaults/Faults/src/ArtFaults.cpp;../ECB_ART/ArtHwFaults/Faults/src/ArtFaultsSingleton.cpp
    #
    # we want: ../ECB_ART/ArtHwFaults/Faults/src/ArtFaults.cpp etc (i.e. unchanged)

    set(src)
    foreach (path ${SOURCES})

        ## if path is relative then leave as-is; if path is absolute then leave as-is; otherwise prefix with the current source path
		string (FIND ${path} ".." relpos)
		string (FIND ${path} "/" abspos)
		if ( (${relpos} EQUAL -1) AND (NOT ${abspos} EQUAL 0) )
            set (path ${CMAKE_CURRENT_SOURCE_DIR}/${path})
	    endif()

        list(APPEND src ${path})
    endforeach()

    ## Now push the new list up to the parent
    set (SOURCES ${src} PARENT_SCOPE)

endmacro (setParentSources)


