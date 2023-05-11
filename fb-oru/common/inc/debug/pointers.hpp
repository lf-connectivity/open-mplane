/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Pointers.hpp
 * \brief     Shared pointer
 *
 *
 * \details   Templates for shared pointers
 *
 */

#ifndef POINTERS_HPP_
#define POINTERS_HPP_

#include <cassert>

#ifdef OFF_TARGET
/*!
 * In order to debug pointer problems, define the following:
 */
#define DEBUG_SHARED_PTR

/*!
 * Define this to print ALL pointer access rather than just watched pointers
 */
#define DEBUG_SHOW_ALL_SHARED_PTR

#ifdef DEBUG_SHARED_PTR
#include "debug/SharedPtrDebug.h"
#endif
#endif

// Use some other library parts
#include "Mutex.h"

namespace Mplane
{

// Load various implementation template files
#include "debug/SharedCounter.hpp"
#include "debug/ThreadsafeCounter.hpp"
#include "debug/SharedPtr.hpp"

}

#endif /* POINTERS_HPP_ */
