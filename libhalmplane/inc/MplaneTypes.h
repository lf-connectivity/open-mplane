/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_TYPES_H__
#define __MPLANE_TYPES_H__

typedef enum halmplane_error_e {
  NONE = 0,
  UNIMPLEMENTED,
  UNAVAILABLE,
  FILE_OPEN_ERROR,
  FILE_READ_ERROR,
  FILE_WRITE_ERROR,
  INVALID_ARG,
  DEVICE_ERROR,

} halmplane_error_t;

typedef double decimal64_t;
typedef char* date_time_t;

#endif
