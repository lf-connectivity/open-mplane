string(CONCAT SRC
  "src/MplaneInterfaces.cpp;"
  "src/MplaneProcessingElements.cpp;"
  "src/MplaneUplaneConf.cpp;"
  "src/HalMplane.cpp;"
)
include_directories(inc)

list(TRANSFORM SRC PREPEND "example/")
target_sources(halmplane PRIVATE ${SRC})
