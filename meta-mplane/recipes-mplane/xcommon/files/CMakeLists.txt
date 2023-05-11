# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(xcommon)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(Feature/inc)
include_directories(WaveFile/inc)
include_directories(cubicSpline/inc)
include_directories(fft/inc)
include_directories(inc)
include_directories(key/inc)
include_directories(lzo/inc)
include_directories(md5/inc)

add_library(xcommon
  Base64/src/Base64.cpp
  ByteTransfer/src/dummy.cpp
  Crc/src/Crc.cpp
  Feature/src/Feature.cpp
  Feature/src/GenericFeature.cpp
  PathUtils/src/PathUtils.cpp
  WaveFile/src/CaptureWave.cpp
  WaveFile/src/CaptureWaveData.cpp
  WaveFile/src/CaptureWaveHeader.cpp
  WaveFile/src/PlaybackWave.cpp
  WaveFile/src/PlaybackWaveHeader.cpp
  WaveFile/src/WaveFileHeader.cpp
  crypt/src/Crypt.cpp
  cubicSpline/src/cubicSpline.cpp
  cubicSpline/src/matlab_cubic_spline.cpp
  cubicSpline/src/matlab_cubic_spline_emxAPI.cpp
  cubicSpline/src/matlab_cubic_spline_emxutil.cpp
  cubicSpline/src/matlab_cubic_spline_initialize.cpp
  cubicSpline/src/matlab_cubic_spline_terminate.cpp
  cubicSpline/src/rtGetInf.cpp
  cubicSpline/src/rtGetNaN.cpp
  cubicSpline/src/rt_nonfinite.cpp
  cubicSpline/src/spline.cpp
  key/src/GlobalKey.cpp
  key/src/Key.cpp
  key/utils/convertTem.cpp
  lzo/src/Lzo.cpp
  lzo/src/minilzo.cpp
  md5/src/Md5Sum.cpp
  md5/src/md5.cpp
  sha1/src/Sha1.cpp
)

install(TARGETS xcommon DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  Feature/inc/Feature.h
  Feature/inc/GenericFeature.h
  WaveFile/inc/CaptureWaveData.h
  WaveFile/inc/WaveFileHeader.h
  cubicSpline/inc/cubicSpline.h
  cubicSpline/inc/matlab_cubic_spline.h
  cubicSpline/inc/matlab_cubic_spline_emxAPI.h
  cubicSpline/inc/matlab_cubic_spline_emxutil.h
  cubicSpline/inc/matlab_cubic_spline_initialize.h
  cubicSpline/inc/matlab_cubic_spline_terminate.h
  cubicSpline/inc/matlab_cubic_spline_types.h
  cubicSpline/inc/rtGetInf.h
  cubicSpline/inc/rtGetNaN.h
  cubicSpline/inc/rt_nonfinite.h
  cubicSpline/inc/rtwtypes.h
  cubicSpline/inc/spline.h
  fft/inc/IFftCalc.h
  fft/inc/FftBuilders.hpp
  fft/inc/FftCalc.hpp
  fft/inc/FftComplex.hpp
  fft/inc/FftStandard.hpp
  fft/inc/IFftCalc_impl.hpp
  fft/inc/SinCos.hpp
  inc/Base64.h
  inc/ByteTransfer.hpp
  inc/CaptureWave.h
  inc/CaptureWaveHeader.h
  inc/Crc.h
  inc/Crypt.h
  inc/ErrorStr.hpp
  inc/IDataType.h
  inc/IDomain.h
  inc/IFeature.h
  inc/IFeatureBase.h
  inc/IGenericFeature.h
  inc/IKey.h
  inc/IWaveFile.h
  inc/Lzo.h
  inc/PathUtils.h
  inc/PlaybackWave.h
  inc/PlaybackWaveHeader.h
  inc/Sha1.h
  inc/xstringfunc.hpp
  key/inc/GlobalKey.h
  key/inc/Key.h
  lzo/inc/lzoconf.h
  lzo/inc/lzodefs.h
  lzo/inc/minilzo.h
  md5/inc/Md5Sum.h
  md5/inc/md5.h
  visualstudio/XcommonTests/stdafx.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
