/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __HAL_MPLANE_H__
#define __HAL_MPLANE_H__

/**
 * @brief HAl init function, to be called before YANG handlers initialization.
 *
 * @return 0 if successful, 1 otherwise
 */
int halmplane_init();

/**
 * @brief HAl exit function, to be called when application exits.
 *
 * @return 0 if successful, 1 otherwise
 */
int halmplane_exit();

#endif // __HAL_MPLANE_H__
