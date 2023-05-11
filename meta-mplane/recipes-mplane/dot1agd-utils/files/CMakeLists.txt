# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(dot1agd-utils C)

include(GNUInstallDirs)

add_compile_definitions(HAVE_NET_ETHERNET_H)

include_directories(inc)

set(COMMON_SRC
  src/dot1ag_eth.c
  src/ieee8021ag.c
)

# dot1agd
add_executable(dot1agd
  bin-src/dot1agd.c
  ${COMMON_SRC}
)

target_link_libraries(dot1agd
  -lpcap
)

# ethping
add_executable(ethping
  bin-src/ethping.c
  ${COMMON_SRC}
)

target_link_libraries(ethping
  -lpcap
)

# ethtrace
add_executable(ethtrace
  bin-src/ethtrace.c
  ${COMMON_SRC}
)

target_link_libraries(ethtrace
  -lpcap
)

install(TARGETS dot1agd ethping ethtrace DESTINATION ${CMAKE_INSTALL_BINDIR})
