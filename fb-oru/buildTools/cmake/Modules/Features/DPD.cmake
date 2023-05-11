##======================================================================================================================
## CMake for DPD feature
##
##======================================================================================================================

# Include guard
if (_INCLUDED_DPD_FEATURE)
	return ()
endif (_INCLUDED_DPD_FEATURE)
set (_INCLUDED_DPD_FEATURE 1)

##======================================================================================================================
## SETTINGS

message(STATUS "DPD : DPD=$ENV{FEAT_DPD}")

## Since PIM and DPD builds are effectively the same, we need to ensure we don't "disable" embedded build if one
## of the features is set. So we need to set a combined variabled to determine if it's ok to disable embedded builds
if ("$ENV{FEAT_DPD}" STREQUAL "NONE")
    # DPD feature not enabled

elseif ("$ENV{FEAT_DPD}" STREQUAL "APP")
    # DPD built into main code

else()
    # Embedded
    set (EMBEDDED_BUILD 1)

endif()

    

##======================================================================================================================
## MACROS/FUNCTIONS

##----------------------------------------------------------------------------------------------------------------------
## DPD_appStart()
##
## Hook: Macro called during appStart()
##
macro (DPD_appStart)

    message(STATUS "DPD_appStart : DPD=$ENV{FEAT_DPD} (EMBEDDED_BUILD=${EMBEDDED_BUILD})")
    
    # Build in DPD if feature enabled
    if (NOT "$ENV{FEAT_DPD}" STREQUAL "NONE")
    
        addRepoLib( libs  dpd common )
        addRepoLib( libs  dpd ${BUILD_BOARD} )
    
    endif()
    
    # Set up application build for either embedded (microblaze etc) or not
    if ("$ENV{FEAT_DPD}" STREQUAL "NONE")
        # DPD feature not enabled
        message(STATUS "FEAT_DPD : set to NONE")
        if (NOT EMBEDDED_BUILD)
            delEmbeddedBuild(dpd)
        endif()
            
    elseif ("$ENV{FEAT_DPD}" STREQUAL "APP")
        # DPD built into main code
        message(STATUS "FEAT_DPD : set to APP")
        if (NOT EMBEDDED_BUILD)
            delEmbeddedBuild(dpd)
        endif()
        
    else()
        message(STATUS "FEAT_DPD : set to embedded")
        # DPD Embedded in fpga
        addEmbeddedFpgaBuild(dpd)
    
    endif()
    
    
    
endmacro (DPD_appStart)


