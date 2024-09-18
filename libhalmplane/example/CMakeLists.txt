string(CONCAT SRC
  "src/MplaneInterfaces.cpp;"
  "src/MplaneProcessingElements.cpp;"
  "src/MplaneUplaneConf.cpp;"
  "src/HalMplane.cpp;"
)
include_directories(inc)

if(("${CONTEXT}" STREQUAL "YOCTO") OR ("${CONTEXT}" STREQUAL "MODULE"))
  list(TRANSFORM SRC PREPEND "example/")
  target_sources(halmplane PRIVATE ${SRC})
else()
  add_sources(SOURCES ${SRC})
endif()
