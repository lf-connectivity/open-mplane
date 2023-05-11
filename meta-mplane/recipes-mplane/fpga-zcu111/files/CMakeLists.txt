# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(fpga-zcu111)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(inc)

add_library(fpga-zcu111
  src/Zcu111SystemFpga.cpp
  src/Zcu111SystemFpgaFactory.cpp
)

install(TARGETS fpga-zcu111 DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  inc/Zcu111SystemFpga.h
  inc/regs/CommonFpgaAntennaRegs.h
  inc/regs/CommonFpgaChainRegs.h
  inc/regs/CommonFpgaFibreRegs.h
  inc/regs/CommonFpgaIqRegs.h
  inc/regs/CommonFpgaOranRegs.h
  inc/regs/CommonFpgaSystemRegs.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  DIRECTORY
  inc/regs

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
