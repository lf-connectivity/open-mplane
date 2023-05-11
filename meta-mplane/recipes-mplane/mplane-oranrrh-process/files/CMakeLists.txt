# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(MplaneOranrrhProcess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

add_executable(MplaneOranrrhProcess
  bin-src/MplaneOranrrhProcess.cpp
  src/NetStatusFactory.cpp
)

string(CONCAT LINK_LIBS
  "-lapplications-common-specific;"
  "-lapplications-common;"
  "-lyang-manager-server;"
  "-ltif-zcu111-mplane-oranrrh;"
  "-ltif-zcu111-oranrrh;"
  "-ltif-zcu111;"
  "-ltif-common-model;"
  "-ltif-common;"
  "-lswtools-shared;"
  "-lservices-zcu111-oranrrh;"
  "-lservices-zcu111;"
  "-lservices-oranrrh;"
  "-lservices-shared;"
  "-lservices-common;"
  "-lhalmplane;"
  "-lhardware-zcu111-oranrrh;"
  "-lhardware-zcu111;"
  "-lhardware-shared;"
  "-lfpga-zcu111;"
  "-lhardware-common;"
  "-lcommon;"
  "-lxcommon;"
  "-ltinyxml2;"
  "-lsysrepo-cpp;"
  "-lsysrepo;"
  "-lnetconf2;"
  "-lyang-cpp;"
  "-lyang;"
  "-lssh;"
  "-lpcap;"
  "-lpthread"
)


# TODO: Link these in the correct order so we don't need to list them thrice.
target_link_libraries(MplaneOranrrhProcess
  ${LINK_LIBS}
  ${LINK_LIBS}
  ${LINK_LIBS}
)

install(TARGETS MplaneOranrrhProcess DESTINATION ${CMAKE_INSTALL_BINDIR})
