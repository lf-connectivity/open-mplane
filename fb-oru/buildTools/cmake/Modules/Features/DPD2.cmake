##======================================================================================================================
## CMake for DPD2 feature
##
##======================================================================================================================

# Include guard
if (_INCLUDED_DPD2_FEATURE)
	return ()
endif (_INCLUDED_DPD2_FEATURE)
set (_INCLUDED_DPD2_FEATURE 1)

##======================================================================================================================
## SETTINGS

message(STATUS "DPD2 : DPD2=$ENV{FEAT_DPD2}")

## Since PIM and DPD2 builds are effectively the same, we need to ensure we don't "disable" embedded build if one
## of the features is set. So we need to set a combined variabled to determine if it's ok to disable embedded builds
if ("$ENV{FEAT_DPD2}" STREQUAL "NONE")
    # DPD2 feature not enabled

elseif ("$ENV{FEAT_DPD2}" STREQUAL "APP")
    # DPD2 built into main code

else()
    # Embedded
    set (EMBEDDED_BUILD 1)

endif()

    

##======================================================================================================================
## MACROS/FUNCTIONS

##----------------------------------------------------------------------------------------------------------------------
## DPD2_appStart()
##
## Hook: Macro called during appStart()
##
macro (DPD2_appStart)

    message(STATUS "DPD2_appStart : DPD2=$ENV{FEAT_DPD2} (EMBEDDED_BUILD=${EMBEDDED_BUILD})")
    
    # Build in DPD2 if feature enabled
    if (NOT "$ENV{FEAT_DPD2}" STREQUAL "NONE")
    
        addRepoLib( libs  dpd2 common )
        addRepoLib( libs  dpd2 ${BUILD_BOARD} )
    
    endif()
    
    # Set up application build for either embedded (microblaze etc) or not
    if ("$ENV{FEAT_DPD2}" STREQUAL "NONE")
        # DPD2 feature not enabled
        message(STATUS "FEAT_DPD2 : set to NONE")
        if (NOT EMBEDDED_BUILD)
            delEmbeddedBuild(dpd2)
        endif()
            
    elseif ("$ENV{FEAT_DPD2}" STREQUAL "APP")
        # DPD2 built into main code
        message(STATUS "FEAT_DPD2 : set to APP")
        if (NOT EMBEDDED_BUILD)
            delEmbeddedBuild(dpd2)
        endif()
        
    else()
        message(STATUS "FEAT_DPD2 : set to embedded")
        # DPD2 Embedded in fpga
        addEmbeddedBuild(dpd2)
    
    endif()
    
    
    
endmacro (DPD2_appStart)


