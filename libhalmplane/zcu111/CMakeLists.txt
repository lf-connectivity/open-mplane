string(CONCAT SRC
  "src/MplaneEcpri.cpp;"
  "src/MplaneAlarms.cpp;"
  "src/MplanePerformanceMgmt.cpp;"
  "src/MplaneExternalio.cpp;"
  "src/MplaneFan.cpp;"
  "src/MplaneHardware.cpp;"
)
include_directories(inc)

if( "${CONTEXT}" STREQUAL "YOCTO")
  list(TRANSFORM SRC PREPEND "zcu111/")
  target_sources(halmplane PUBLIC ${SRC})
else()
  add_sources(SOURCES ${SRC})
endif()

target_link_libraries( halmplane
  -lxcommon
  -lcommon
  -lsmbus
)
