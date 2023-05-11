##======================================================================================================================
## Code Coverage CMake functions
##
##======================================================================================================================

## Guard from multiple includes
if (_INCLUDED_COVERAGE)
	return ()
endif ()
set (_INCLUDED_COVERAGE 1)

##----------------------------------------------------------------------------------------------------------------------
## Set up paths
if (${TARGET} STREQUAL "x86_64")
    set ( GCOV_PATH ${TOOLCHAIN_BIN}/${TOOLCHAIN_TARGET}-gcov )
    set ( LCOV_PATH ${TOOLCHAIN_BIN}/${TOOLCHAIN_TARGET}-lcov )
    set ( GCOVR_PATH ${GITDIR}/buildTools/coverage/gcovr )
    
    FIND_PROGRAM( PYTHON_EXECUTABLE python )
	IF(NOT PYTHON_EXECUTABLE)
		MESSAGE(FATAL_ERROR "Python not found! Aborting...")
	ENDIF() # NOT PYTHON_EXECUTABLE

	IF(NOT GCOVR_PATH)
		MESSAGE(FATAL_ERROR "gcovr not found! Aborting...")
	ENDIF() # NOT GCOVR_PATH
endif()

##----------------------------------------------------------------------------------------------------------------------
## addCoverage(<name>)
## 
## Macro that adds a GCOV coverage test. $name is the executable name and will be used to create the coverage target
##
macro (addCoverage name)

if (${TARGET} STREQUAL "x86_64")
	if (${BUILD_COVERAGE})
	
	    file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
	    set (executable ${name})
	    set (srcDir "${CMAKE_SOURCE_DIR}/src")
	    
#        if (_relPath)
#		    set (executable ${_relPath}/${name})
#		    set (srcDir "${CMAKE_SOURCE_DIR}/${_relPath}/src")
#        endif()

        if (_relPath)
        	if (_relPath MATCHES "^\\.\\./.*")
        	
        	    # relative (external) path - use as-is
        	    
        	elseif(_relPath MATCHES "^/.*")
        	
        	    # absolute path - use as-is
        	    
        	else()
        	
    		    set (executable ${_relPath}/${name})
    		    set (srcDir "${CMAKE_SOURCE_DIR}/${_relPath}/src")
        
            endif() 
        endif() 
        
        ## Need to first check to ensure we have some source
        if (IS_DIRECTORY ${srcDir})

			# Create Cobertura coverage target
			set (_targetname ${name}_coverage)
			set (_outputname coverage)

        	# Get directory in which to run the test
        	get_filename_component(_dir ${executable} DIRECTORY)
        	get_filename_component(_run ${executable} NAME)
        	
        	logDebug ("GCOV: _dir=${_dir} _run=${_run}")
        	logDebug ("GCOV: CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")
        	logDebug ("GCOV: CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
        	logDebug ("GCOV: CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}")
        	logDebug ("GCOV: CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")
        	
            if ( NOT _dir MATCHES "^test") 

logDebug("GCOV: Adding ${name} for coverage, exe=${executable} (rel=${_relPath} _dir=${_dir})...")

            	ADD_CUSTOM_TARGET(${_targetname}
            
            		# Running gcovr - text
            		GCOV=${GCOV_PATH} ${GCOVR_PATH} 
            			-e '/usr/include/*'  
            			-e '${LOCAL_INSTALL_DIR}/include/*'
            			-e '${CMAKE_SOURCE_DIR}/${_dir}/gtest/*'
            			-e '${CMAKE_SOURCE_DIR}/${_dir}/test/*'
            			-e '${GITDIR}/ros/*'
            			-o ${_outputname}.txt
            			-r ${CMAKE_SOURCE_DIR}
            			${CMAKE_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}.dir/${_dir}
            		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${_dir}
            		COMMENT "Running gcovr on ${executable} to produce Cobertura code coverage report."
            
            		# Running gcovr - xml
            		COMMAND GCOV=${GCOV_PATH} ${GCOVR_PATH} 
            			-e '/usr/include/*'  
            			-e '${LOCAL_INSTALL_DIR}/include/*'
            			-e '${CMAKE_SOURCE_DIR}/${_dir}/gtest/*'
            			-e '${CMAKE_SOURCE_DIR}/${_dir}/test/*'
            			-e '${GITDIR}/ros/*'
            			-x -o ${_outputname}.xml
            			-r ${CMAKE_SOURCE_DIR}
            			${CMAKE_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}.dir/${_dir}
            
            			DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${_run}
            	)
            
            	# Show info where to find the report
            	ADD_CUSTOM_COMMAND(TARGET ${_targetname} POST_BUILD
            		COMMAND ;
            		COMMENT "Cobertura code coverage report saved in ${_dir}/${_outputname}.xml."
            	)
    
    			
    			# Add this coverage target to the project coverage targets list
    			add_targets( ${PROJECT_NAME}_coverage ${name}_coverage )
		
            endif ( NOT _dir MATCHES "^test") 
            
		endif (IS_DIRECTORY ${srcDir})
		
	endif(${BUILD_COVERAGE})
endif()

endmacro (addCoverage)

##----------------------------------------------------------------------------------------------------------------------
## addCoverageTarget()
## 
## Function that adds a coverage target for this repository if we're building with settings that require coverage
## and there are some coverage results
##
function (addCoverageTarget)

if (${TARGET} STREQUAL "x86_64")
	if (${BUILD_COVERAGE})
		logDebug ("PROJECT_NAME=${PROJECT_NAME} coverage=${${PROJECT_NAME}_coverage}")
		if (${PROJECT_NAME}_coverage)
			add_custom_target (coverage DEPENDS ${${PROJECT_NAME}_coverage})
		else()
		    # Dummy target
			add_custom_target (coverage)
		endif()
	endif ()
endif ()

endfunction(addCoverageTarget)

