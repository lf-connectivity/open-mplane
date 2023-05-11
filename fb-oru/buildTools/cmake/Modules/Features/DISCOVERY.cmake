##======================================================================================================================
## CMake for DISCOVERY feature
##
##======================================================================================================================

# Include guard
if (_INCLUDED_DISCOVERY_FEATURE)
	return ()
endif (_INCLUDED_DISCOVERY_FEATURE)
set (_INCLUDED_DISCOVERY_FEATURE 1)

    message(STATUS "DISCOVERY : DISCOVERY=$ENV{FEAT_DISCOVERY}")

##======================================================================================================================
## MACROS/FUNCTIONS

##----------------------------------------------------------------------------------------------------------------------
## DISCOVERY_appStart()
##
## Hook: Macro called during appStart()
##
macro (DISCOVERY_appStart)

    message(STATUS "DISCOVERY_appStart : DISCOVERY=$ENV{FEAT_DISCOVERY}")

endmacro (DISCOVERY_appStart)


