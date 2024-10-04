cmake_minimum_required(VERSION 3.12)

if("${CONTEXT}" STREQUAL "STANDALONE")

  include(GNUInstallDirs)

  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

  # the -I flag in gcc
  include_directories(
    ${PROJECT_SOURCE_DIR}/inc/
    )

  set(LIB_SOURCES
      ${BUILD}/src/MplaneEcpri.c
      ${BUILD}/src/MplaneAlarms.c
      ${BUILD}/src/MplanePerformanceMgmt.c
  )

  # Library
  set(LIBRARY_NAME halmplane)
  add_library(${LIBRARY_NAME} STATIC ${LIB_SOURCES})
  install(TARGETS halmplane
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
      )

elseif( "${CONTEXT}" STREQUAL "YOCTO")
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

  if (ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
  endif()

  set(LIBRARY_NAME halmplane)
  set(version "1.1")
  project (halmplane VERSION 1.1.0 LANGUAGES CXX)
  add_library(${LIBRARY_NAME} SHARED)
  set_target_properties(${LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
  set_target_properties(${LIBRARY_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

  include(GNUInstallDirs)

  # Build context
  if(${BUILD_BOARD} STREQUAL "ZCU111")
     set(BOARD "zcu111")
  else()
     set(BOARD "${BUILD_BOARD}")
  endif()

  if (NOT GITDIR)
    get_filename_component (GITDIR ${PROJECT_SOURCE_DIR} DIRECTORY)
    list(APPEND CMAKE_MODULE_PATH ${GITDIR}/buildTools/cmake/Modules)
  endif()

  include_directories(
    ${PROJECT_SOURCE_DIR}/inc/
    ${PROJECT_SOURCE_DIR}/hal-common/inc/
  )

  add_subdirectory(hal-common)
  include(${BOARD}/CMakeLists.txt)
  target_include_directories(halmplane PUBLIC hal-common/inc)
  target_include_directories(halmplane PUBLIC inc)

  if(${BUILD_BOARD_STYLE} STREQUAL "MODULE")
    set_target_properties(${LIBRARY_NAME} PROPERTIES OUTPUT_NAME ${LIBRARY_NAME}-mod-${BOARD})
  else()
    install(
      FILES
      inc/MplaneAlarms.h
      inc/MplaneAntennaCalibration.h
      inc/MplaneBeamforming.h
      inc/MplaneCompression.h
      inc/MplaneDelayMgmt.h
      inc/MplaneDhcp.h
      inc/MplaneEcpri.h
      inc/MplaneFaultMgmt.h
      inc/MplaneHardware.h
      inc/MplaneInterfaces.h
      inc/MplaneModuleCapability.h
      inc/MplanePerformanceMgmt.h
      inc/MplaneProcessingElements.h
      inc/MplaneSupervision.h
      inc/MplaneTransceiver.h
      inc/MplaneUplaneConf.h
      inc/MplaneExternalio.h
      inc/MplaneTypes.h
      inc/MplaneFan.h
      inc/MplaneSync.h
      inc/HalMplane.h
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
  endif()

  install(TARGETS halmplane
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

else() # fb-oru app build
  set(version "0.1")
  project (halmplane VERSION 0.1 LANGUAGES CXX)

  # Build context
  if(${BUILD_BOARD} STREQUAL "ZCU111")
     set(BOARD "zcu111")
  elseif(${BUILD_BOARD} STREQUAL "ATLAS")
     set(BOARD "atlas")
  elseif(${BUILD_BOARD} STREQUAL "FBZCU27")
     set(BOARD "fbzcu27")
  else()
     set(BOARD "zcu111")
  endif()

  if (NOT GITDIR)

    get_filename_component (GITDIR ${PROJECT_SOURCE_DIR} DIRECTORY)
    list(APPEND CMAKE_MODULE_PATH ${GITDIR}/buildTools/cmake/Modules)

  endif()

  include(rse)
  addIncludes ()
  addInterfaceIncludes(hardware)
  useRepoLib (common)
  add_subdirectory(hal-common)
  add_subdirectory(${BOARD})
  include(libraryCommonTasks)
  target_include_directories(halmplane PUBLIC inc)

endif()
