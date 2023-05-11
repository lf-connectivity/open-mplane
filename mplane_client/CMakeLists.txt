cmake_minimum_required (VERSION 3.16)

set (CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_STANDARD 17)

project (MPLANE_CLIENT CXX)

set (MPC_CLIENT mpc_client)
set (MPC_TESTER mpc_tester)
# set (Target_mpclient_demo mpclient-demo)

find_program (PROTOC protoc PATHS deps/install/bin)
find_program (GRPC_CPP_PLUGIN grpc_cpp_plugin PATHS deps/install/bin)

link_directories (deps/install/lib64 deps/install/lib)

find_library (PROTOBUF protobuf PATHS deps/install/lib64)
find_library (GRPC grpc PATHS deps/install/lib)
find_library (GRPC++ grpc++ PATHS deps/install/lib)

set (OUTPUT_DIR ${CMAKE_BINARY_DIR}/proto-gen)
file (MAKE_DIRECTORY ${OUTPUT_DIR})

add_custom_command (
  OUTPUT
    ${OUTPUT_DIR}/src/if/mpclient.pb.cc
    ${OUTPUT_DIR}/src/if/mpclient.pb.h
    ${OUTPUT_DIR}/src/if/mpclient.grpc.pb.cc
    ${OUTPUT_DIR}/src/if/mpclient.grpc.pb.h
  COMMAND
    ${PROTOC}
    --cpp_out=${OUTPUT_DIR}
    --proto_path=${PROJECT_SOURCE_DIR}
    --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
    --grpc_out=${OUTPUT_DIR}
    ${PROJECT_SOURCE_DIR}/src/if/mpclient.proto
)

include_directories (deps/install/include)
include_directories (${OUTPUT_DIR}/src/if/ ${OUTPUT_DIR})

set (
  MPC_IF_SRC
  ${OUTPUT_DIR}/src/if/mpclient.pb.cc ${OUTPUT_DIR}/src/if/mpclient.grpc.pb.cc)

set (
  MPC_LIBS
  netconf2 yang ssh gflags gtest ${GRPC++} ${GRPC} ${PROTOBUF} ssl crypto
  pthread glog z
)

file (GLOB MPC_CLIENT_SRC src/client/*.cpp)
add_executable (${MPC_CLIENT} ${MPC_CLIENT_SRC} ${MPC_IF_SRC})
target_link_libraries (${MPC_CLIENT} ${MPC_LIBS})

include_directories (test/rpc-client/)

file (GLOB_RECURSE MPC_TESTER_SRC test/*.cpp)
add_executable (${MPC_TESTER} ${MPC_TESTER_SRC} ${MPC_IF_SRC})
target_link_libraries (${MPC_TESTER} ${MPC_LIBS})

# file (GLOB MPCLIENT_DEMO_SOURCES src/demo/*.cpp)
# add_executable (${Target_mpclient_demo} ${MPCLIENT_DEMO_SOURCES} ${MPC_IF_SRC})
# target_link_libraries (${Target_mpclient_demo} ${Target_mpclient_client} ${MPC_LIBS})

# Copy test cases files when they are modified
file (GLOB MPC_TESTS_CASES test/tests/cases/*)
foreach (case ${MPC_TESTS_CASES})
  file (RELATIVE_PATH ending ${CMAKE_CURRENT_SOURCE_DIR}/test ${case})
  configure_file (${case} ${CMAKE_CURRENT_BINARY_DIR}/${ending} COPYONLY)
endforeach ()
