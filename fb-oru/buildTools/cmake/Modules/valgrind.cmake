##======================================================================================================================
## Valgrind CMake functions
##
##======================================================================================================================

## Guard from multiple includes
if (_INCLUDED_VALGRIND)
	return ()
endif ()
set (_INCLUDED_VALGRIND 1)



##----------------------------------------------------------------------------------------------------------------------
## Find executable
if (${TARGET} STREQUAL "x86_64")
    FIND_PROGRAM( VALGRIND_EXECUTABLE valgrind)
    logDebug("VALGRIND=${VALGRIND_EXECUTABLE}")
    if (NOT VALGRIND_EXECUTABLE)
    	message (FATAL_ERROR "Unable to locate valgrind")
    endif()
endif ()

##----------------------------------------------------------------------------------------------------------------------
## addMemcheck(<name>)
##
## Macro that adds a Valgrind memory leak test. $name is the executable name and will be used to create the coverage target
##
macro (addMemcheck name)

if (${TARGET} STREQUAL "x86_64")
	# Can't run valgrind when building for coverage
	if (NOT ${BUILD_COVERAGE})

	    file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
	    set (executable ${name})
	    set (srcDir "${CMAKE_SOURCE_DIR}/src")

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


logDebug("Adding ${name} for coverage, exe=${executable} (rel=${_relPath})...")

		set (_targetname ${name}_memcheck)
		set (suppress_file ${GITDIR}/buildTools/valgrind/suppress.txt)

		ADD_CUSTOM_TARGET(${_targetname}

			# run valgrind in memory leak check mode
			${VALGRIND_EXECUTABLE}
				-v --leak-check=full  --show-reachable=yes --track-origins=yes
				--undef-value-errors=yes
				--xml=yes --xml-file=${name}.memcheck
				--suppressions=${suppress_file}
				./${name}
				&> memcheck.log
	            || true

			COMMENT "Running valgrind memcheck on ${name}"
			DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${name}
		)

		# Add this coverage target to the project coverage targets list
		add_targets( ${PROJECT_NAME}_memcheck ${_targetname} )

logDebug("Memcheck:  add ${_targetname} to ${PROJECT_NAME}_memcheck=${${PROJECT_NAME}_memcheck}")

	endif(NOT ${BUILD_COVERAGE})
endif()

endmacro (addMemcheck)

##----------------------------------------------------------------------------------------------------------------------
## addMemcheckTarget()
##
## Function that adds a memory leak target for this repository if we're building with settings that do not require coverage
## and there are some memory test results
##
function (addMemcheckTarget)

logDebug("addMemcheckTarget BUILD_COVERAGE=${BUILD_COVERAGE}")

	if (NOT ${BUILD_COVERAGE})
		if (${PROJECT_NAME}_memcheck)
			add_custom_target (memcheck DEPENDS ${${PROJECT_NAME}_memcheck})
		else()
		    # Dummy target
			add_custom_target (memcheck)
		endif()
	endif ()

endfunction(addMemcheckTarget)

##----------------------------------------------------------------------------------------------------------------------
## addProfile(<name>)
##
## Macro that adds a Valgrind profiling test. $name is the executable name and will be used to create the profiling target
##
macro (addProfile name)

if (${TARGET} STREQUAL "x86_64")
	# Can't run valgrind when building for coverage
	if (NOT ${BUILD_COVERAGE})

	    file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
	    set (executable ${name})
	    set (srcDir "${CMAKE_SOURCE_DIR}/src")

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


logDebug("Adding ${name} for coverage, exe=${executable} (rel=${_relPath})...")

		set (_targetname ${name}_profile)

		ADD_CUSTOM_TARGET(${_targetname}

			# run valgrind in profiling mode
			${VALGRIND_EXECUTABLE}
				--tool=callgrind
				./${name}
	            || true

			COMMENT "Running valgrind callgrind on ${name}"
			DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${name}
		)

		# Add this coverage target to the project coverage targets list
		add_targets( ${PROJECT_NAME}_profile ${_targetname} )

logDebug("Profile:  add ${_targetname} to ${PROJECT_NAME}_profile=${${PROJECT_NAME}_profile}")

	endif(NOT ${BUILD_COVERAGE})
endif()

endmacro (addProfile)

##----------------------------------------------------------------------------------------------------------------------
## addProfileTarget()
##
## Function that adds a profiling target for this repository if we're building with settings that do not require coverage
##
function (addProfileTarget)

logDebug("addProfileTarget BUILD_COVERAGE=${BUILD_COVERAGE}")

	if (NOT ${BUILD_COVERAGE})
		if (${PROJECT_NAME}_profile)
			add_custom_target (profile DEPENDS ${${PROJECT_NAME}_profile})
		else()
		    # Dummy target
			add_custom_target (profile)
		endif()
	endif ()

endfunction(addProfileTarget)

