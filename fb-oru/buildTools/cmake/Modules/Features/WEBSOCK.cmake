## CMake for WEBSOCK feature
##
##======================================================================================================================

# Include guard
if (_INCLUDED_WEBSOCK_FEATURE)
	return ()
endif (_INCLUDED_WEBSOCK_FEATURE)
set (_INCLUDED_WEBSOCK_FEATURE 1)

    message(STATUS "WEBSOCK : WEBSOCK=$ENV{FEAT_WEBSOCK}")

##======================================================================================================================
## MACROS/FUNCTIONS

##----------------------------------------------------------------------------------------------------------------------
## WEBSOCK_appStart()
##
## Hook: Macro called during appStart()
##
macro (WEBSOCK_appStart)

    message(STATUS "WEBSOCK_appStart : WEBSOCK=$ENV{FEAT_WEBSOCK}")

endmacro (WEBSOCK_appStart)


