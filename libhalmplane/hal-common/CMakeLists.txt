include_directories(inc)

if(("${CONTEXT}" STREQUAL "YOCTO") OR ("${CONTEXT}" STREQUAL "MODULE"))
  if( "${BOARD}" STREQUAL "zcu111")
    string(CONCAT SRC
      "hal-common/fb-oru/FbOruPerformanceMgmt.cpp;"
    )
    target_sources(halmplane PRIVATE ${SRC})
  endif()
else()
  if( "${BOARD}" STREQUAL "zcu111")
    string(CONCAT SRC
      "fb-oru/FbOruPerformanceMgmt.cpp;"
    )
    add_sources(SOURCES ${SRC})
  endif()
endif()
