##======================================================================================================================
## CMake for PIM feature
##
##======================================================================================================================

# Include guard
if (_INCLUDED_PIM_FEATURE)
	return ()
endif (_INCLUDED_PIM_FEATURE)
set (_INCLUDED_PIM_FEATURE 1)

##======================================================================================================================
## SETTINGS

message(STATUS "PIM : PIM=$ENV{FEAT_PIM}")
    

## Since PIM and DPD builds are effectively the same, we need to ensure we don't "disable" embedded build if one
## of the features is set. So we need to set a combined variabled to determine if it's ok to disable embedded builds
if ("$ENV{FEAT_DPD}" STREQUAL "NONE")
    # DPD feature not enabled

#elseif ("$ENV{FEAT_DPD}" STREQUAL "APP")
    # DPD built into main code

else()
    # Embedded
    set (EMBEDDED_BUILD 1)

endif()



##======================================================================================================================
## MACROS/FUNCTIONS

##----------------------------------------------------------------------------------------------------------------------
## PIM_appStart()
##
## Hook: Macro called during appStart()
##
macro (PIM_appStart)

    message(STATUS "PIM_appStart : PIM=$ENV{FEAT_PIM} (EMBEDDED_BUILD=${EMBEDDED_BUILD})")
    
    # Build in PIM if feature enabled
    if (NOT "$ENV{FEAT_PIM}" STREQUAL "NONE")
    
        addRepoLib( libs  pim common )
#        addRepoLib( libs  pim ${BUILD_BOARD} )
    
    endif()
    
    # Set up application build for either embedded (microblaze etc) or not
    if ("$ENV{FEAT_PIM}" STREQUAL "NONE")
        # PIM feature not enabled
        message(STATUS "FEAT_PIM : set to NONE")
        if (NOT EMBEDDED_BUILD)
            delEmbeddedBuild(pim)
        endif()
    
#    elseif ("$ENV{FEAT_PIM}" STREQUAL "APP")
        # PIM built into main code
#        message(STATUS "FEAT_PIM : set to APP")
#        delEmbeddedBuild(pim)
    
    else()
        message(STATUS "FEAT_PIM : set to embedded")
        # PIM Embedded in fpga
        addEmbeddedFpgaBuild(pim)
    
    endif()
    
    
    
endmacro (PIM_appStart)


