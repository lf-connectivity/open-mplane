##======================================================================================================================
## Cmake file for microblaze
##
## Expects the following variables to have been set:
##
## SOURCES              List of source files
## libs                 List of libraries used
##
## EMBEDDED_MAKEFILE    Makefile name (e.g. dpd_processor_k7.make)
## APP_NAME             Application name (e.g. dpd)
## MBLAZE_TAG           Microblaze processor tag (e.g. microblaze_0)
##
## EDK_DIR              From embedded/cmake/${TARGET}/build_settings.cmake - used for ISE toolset
## XILINX_TOOLCHAIN     From Toolchains/xilinx.cmake - path to microblaze compile executables - used for ISE toolset
## XILINX_SDK_DIR       If set, means we are using a Vivado toolset so ignore EDK_DIR and XILINX_TOOLCHAIN
##
##
##
##======================================================================================================================

message (microblaze.cmake: _INCLUDED_MICROBLAZE=${_INCLUDED_MICROBLAZE})

## Guard from multiple includes
if (_INCLUDED_MICROBLAZE)
	return ()
endif ()
set (_INCLUDED_MICROBLAZE 1)

##----------------------------------------------------------------------------------------------------------------------
## getMicroblazeVersion(filename varname)
## Reads the given filename to extract the version number for a string of the form:
##   $Rev: 31358 $
## stores the version number into the specified variable
function (getMicroblazeVersion filename varname)
    file (STRINGS ${filename} rev REGEX "Rev: ([0123456789]+) ")
    string (REGEX MATCH "([0123456789]+)" revNum ${rev})
#message(STATUS "varname=${varname} rev=${rev} revNum=${revNum}")

    set (${varname} ${revNum} PARENT_SCOPE)
endfunction (getMicroblazeVersion)

##----------------------------------------------------------------------------------------------------------------------
## readListFromFile(filename varname)
## Reads in a file and converts the lines into a list
function (readListFromFile filename varname)
    file (READ ${filename} contentStr)
    string (REPLACE "\n" " ;" contentList ${contentStr})

#message(STATUS "readListFromFile(${filename}) contentStr=${contentStr}")
#message(STATUS "LIST=${contentList}")
#list (LENGTH contentList len)
#message(STATUS "len=${len}")

    set (${varname} ${contentList} PARENT_SCOPE)
endfunction (readListFromFile)

##----------------------------------------------------------------------------------------------------------------------
## readSourceFileList(filename varname)
## Reads in a file and converts the lines into a list
function (readSourceFileList filename varname)

    # mangle source file to escape ';'
    execute_process(COMMAND sed -e "s/;/@semi@/g" ${filename}
        OUTPUT_VARIABLE src)
    string (REPLACE "\n" " ;" contentList ${src})

#message(STATUS "readSourceFileList(${filename}) contentStr=${src}")
#message(STATUS "LIST=${contentList}")
#list (LENGTH contentList len)
#message(STATUS "len=${len}")

    set (${varname} ${contentList} PARENT_SCOPE)
endfunction (readSourceFileList)

##----------------------------------------------------------------------------------------------------------------------
## writeFileList(filename list)
## Writes the list into a file
function (writeFileList filename list)

    string (REPLACE " ;" "\n" content "${list}")
    string (REPLACE "@semi@" ";" content "${content}")
    file (WRITE ${filename} "${content}")

endfunction (writeFileList)


##----------------------------------------------------------------------------------------------------------------------
## Show the settings
logMessage (
"==========================================================="
"BUILD SETTINGS"
"   "
"Target.............: ${TARGET}"
"FPGA...............: ${fpgaDevice}"
"Application........: ${BUILD_APPLICATION}"
"Customer...........: ${BUILD_CUSTOMER}"
"Board..............: ${BUILD_BOARD}"
"Duplex.............: ${BUILD_DUPLEX}"
"Fibre I/F..........: ${BUILD_FIBRE_INTERFACE}"
"Build..............: ${BUILD_NUMBER}"
"Version............: ${BUILD_VERSION}"
"   "
"-----------------------------------------------------------"
"PROJECT ${PROJECT_NAME} v${version}"
"   "
"Source Dir.........: ${CMAKE_CURRENT_SOURCE_DIR}"
"Build Dir..........: ${CMAKE_BINARY_DIR}"
"C++ Compiler.......: ${CMAKE_C_COMPILER}"
"Compile flags......: ${CMAKE_C_FLAGS}"
"Link flags.........: ${CMAKE_EXE_LINKER_FLAGS}"
"GITDIR.............: ${GITDIR}"
"ISE Version........: ${iseVersion}"
"==========================================================="
)


##----------------------------------------------------------------------------------------------------------------------
set (XILINX_SDK_BIN $ENV{XILINX_SDK_BIN})
#set (XILINX_SDK_BIN "/opt/Xilinx/SDK/2016.4/bin")
message("MICROBLAZE: XILINX_SDK_BIN=${XILINX_SDK_BIN}")

set (XILINX_BIT2BIN ${GITDIR}/tools/xilinx-bit2bin.pl)

if (XILINX_SDK_BIN)
    set (EDK_DIR "")
    set (XILINX_TOOLCHAIN ${XILINX_SDK_BIN}/../gnu/microblaze/lin/bin)
endif()

##----------------------------------------------------------------------------------------------------------------------
## Full microblaze compile

## ELF
set (ELF_FILE ${APP_NAME}.elf)
add_executable(${ELF_FILE} EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(${ELF_FILE} ${libs})

add_custom_command(TARGET ${ELF_FILE} POST_BUILD
    COMMAND ${XILINX_TOOLCHAIN}/mb-objdump -h ${ELF_FILE}
    COMMAND ${XILINX_TOOLCHAIN}/mb-size -x ${ELF_FILE}
    COMMENT Post-processing ELF
)
list (APPEND CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/${ELF_FILE})

if (NOT XILINX_SDK_BIN)

    ## Platform
    add_custom_target(mblaze_platform
        PATH=${PATH}:$ENV{PATH} ${CMAKE_MAKE_PROGRAM} -C ${EDK_DIR} -f ${EMBEDDED_MAKEFILE} -e DEVICE=${fpgaDevice} -e ISEVER=${iseVersion} libs
    )
    add_dependencies(${ELF_FILE} mblaze_platform)

endif()

## lib - alias to building ELF
add_custom_target(lib ALL DEPENDS ${ELF_FILE})

## FPGA
findFpga(fpgaTgz)
get_filename_component(fpgaTgzDir ${fpgaTgz} DIRECTORY)

message (STATUS "Fpga chosen: ${fpgaTgz}")

# extract tar into temp dir
set (fpgaTempDir ${CMAKE_CURRENT_BINARY_DIR}/fpgaTgz)
message (STATUS "fpgaTempDir=${fpgaTempDir}")
execute_process(
    COMMAND rm -rf "${fpgaTempDir}"
)
file (MAKE_DIRECTORY ${fpgaTempDir})
execute_process(
    COMMAND tar "xf" "${fpgaTgz}"
    WORKING_DIRECTORY ${fpgaTempDir}
)

# Look for either .bit file (stored by new fpga build system)
set (mmiFile "")
set (foundFpgaBuild 0)
file (GLOB fpgaBitList "${fpgaTempDir}/*.bit")
list (LENGTH fpgaBitList len)
if (${len} EQUAL 1)

    set (foundFpgaBuild 1)
    list (GET fpgaBitList -1 fpgaBit)
    message(STATUS "** Using NEW fpga build system results **")
    message(STATUS "FPGA bit: ${fpgaBit}")

    get_filename_component(fpgaBitDir ${fpgaBit} DIRECTORY)
    get_filename_component(fpgaBitName ${fpgaBit} NAME)
    string(REPLACE ".bit" "" fpgaName ${fpgaBitName})

    message(STATUS "FPGA: ${fpgaName}")
    message(STATUS "FPGA bit dir: ${fpgaBitDir}")

    # bmm file
    set (bmmFile ${fpgaTempDir}/${fpgaName}_bd.bmm)

    # bit file
    set (bitFile ${fpgaTempDir}/${fpgaName}.bit)

    # mmi file
    set (mmiFile ${fpgaTempDir}/${fpgaName}.mmi)


else ()

    # or the .bin file (stored by old fpga build system)
    file (GLOB fpgaBinList "${fpgaTempDir}/*.bin")
    list (LENGTH fpgaBinList len)
    if (${len} EQUAL 1)
        set (foundFpgaBuild 1)
        list (GET fpgaBinList -1 fpgaBin)
        message(STATUS "** Using OLD fpga build system results **")

        message(STATUS "FPGA bin: ${fpgaBin}")

        get_filename_component(fpgaBinDir ${fpgaBin} DIRECTORY)
        get_filename_component(fpgaBinName ${fpgaBin} NAME)
        string(REPLACE ".bin" "" fpgaName ${fpgaBinName})

        message(STATUS "FPGA: ${fpgaName}")
        message(STATUS "FPGA bin dir: ${fpgaBinDir}")

        # bmm file
        set (bmmFile ${fpgaTgzDir}/${fpgaName}_bd.bmm)

        # bit file
        set (bitFile ${fpgaTgzDir}/${fpgaName}.bit)

    endif ()

endif ()

if (${foundFpgaBuild} EQUAL 0)
    message(FATAL_ERROR "Unable to find any fpga images in ${fpgaTgz}")
endif ()

## Check the md5 signature
execute_process(
    COMMAND md5sum "-c" "${fpgaTgz}.md5"
    WORKING_DIRECTORY ${fpgaTgzDir}
    RESULT_VARIABLE md5state
)

message(status "md5 result=${md5state}")
if (NOT ${md5state} EQUAL 0)
    message(FATAL_ERROR "MD5 does not match for ${fpgaTgz}")
endif ()

if (XILINX_SDK_BIN)

    ### VIVADO

    ## Process the MMI file to get the processor path
    file(STRINGS ${mmiFile} processor REGEX "<Processor")
#    message("PIM(XILINX): processor=${processor}")
    foreach (proc ${processor})
#        message("PIM(XILINX): * proc=${proc}")
        string (REGEX REPLACE ".*InstPath=\"([^\"]*)\".*" "\\1" MB_PROC_INST ${proc})
#        message("PIM(XILINX): * * path=${MB_PROC_INST}")
        
        if (MB_PROC_INST)
#            message("PIM(XILINX): GOT MB_PROC_INST")
            break()
        endif()
    
    endforeach()

    message("PIM(XILINX): MB_PROC_INST=${MB_PROC_INST}")

    # get the bit file
    add_custom_target(bitFile
        cp ${bitFile} ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT Copy bit file
    )
    list (APPEND CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/${fpgaName}.bit)
    
    # get the mmi file
    add_custom_target(mmiFile
        cp ${mmiFile} ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT Copy mmi file
    )
    list (APPEND CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/${fpgaName}.mmi)

    ## updatemem
    set (memFile ${fpgaName}_data.bit)
    add_custom_target(${memFile}
        ${XILINX_SDK_BIN}/updatemem -force -meminfo ${fpgaName}.mmi -data ${ELF_FILE} -bit ${fpgaName}.bit -proc ${MB_PROC_INST} -out ${memFile}
        DEPENDS ${ELF_FILE} bitFile mmiFile
        COMMENT updatemem
    )
    list (APPEND CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/${memFile})
    
    # Vivado is available on this machine
    add_custom_target(${binFile}
        perl ${XILINX_BIT2BIN} -i ${memFile} -o ${binFile}
        DEPENDS ${memFile}
        COMMENT bit2bin
    )

else()

    ### ISE 
    
    # get the bmm file
    add_custom_target(bmmFile
        cp ${bmmFile} ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT Copy bmm file
    )
    list (APPEND CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/${fpgaName}_bd.bmm)
    
    # get the bit file
    add_custom_target(bitFile
        cp ${bitFile} ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT Copy bit file
    )
    list (APPEND CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/${fpgaName}.bit)
    
    ## Data2mem
    set (memFile ${fpgaName}_data.bit)
    add_custom_target(${memFile}
        ${XILINX_BIN}/data2mem -bm ${fpgaName}_bd -bt ${fpgaName} -bd ${ELF_FILE} tag ${MBLAZE_TAG} -o b ${memFile}
        DEPENDS ${ELF_FILE} bitFile bmmFile
        COMMENT data2mem
    )
    list (APPEND CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/${memFile})
    
    ## Promgen
    set (binFile ${fpgaName}.bin)
    add_custom_target(${binFile}
        ${XILINX_BIN}/promgen -b -p bin -u 0 ${memFile} -w -o ${binFile}
        DEPENDS ${memFile}
        COMMENT promgen
    )
    list (APPEND CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/${binFile})

endif()


## New tarball
set (embeddedFpgaDir ${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}FpgaTgz)
add_custom_target(embeddedFpgaClean
    rm -rf "${embeddedFpgaDir}"
    COMMENT Clean tar dir
)
add_custom_target(embeddedFpga
    cp -r  ${fpgaTempDir} ${embeddedFpgaDir}
    COMMAND cp ${fpgaName}.bin ${embeddedFpgaDir}
    DEPENDS ${binFile} embeddedFpgaClean
    COMMENT tar source
)

## Final target is new fpga tarball
set (embeddedFpgaTgz ${CMAKE_BINARY_DIR}/fpga-${APP_NAME}.tgz)
add_custom_target(microblazeClean
    rm -f "${embeddedFpgaTgz}"
    COMMENT Clean tar
)
add_custom_target(embedded
    tar czf ${embeddedFpgaTgz} *
    DEPENDS embeddedFpga microblazeClean
    WORKING_DIRECTORY ${embeddedFpgaDir}
    COMMENT tarball
)

## Clean
add_custom_target(tempClean
    rm -rf "${fpgaTempDir}"
    COMMENT Clean temp
)

add_custom_target(full-clean
    rm -f ${CLEAN_FILES}
    DEPENDS microblazeClean
    DEPENDS embeddedFpgaClean
    DEPENDS tempClean
    COMMENT Clean all
)

