#ifndef _GLOBALTYPEDEFS_H_
#define _GLOBALTYPEDEFS_H_

#include <cstdint>

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      GlobalTypeDefs.h
 * \brief     A file that defines common data types and classes.
 *
 *
 * \details   This file defines various common data types and classes for use
 *            by all radio software modules.
 *            These include platform independent integer and real types,
 *            which should be used by all subsystems.
 *            It contains definitions that would ordinarily be provided by
 *            the OS platform provider.
 *
 */

namespace Mplane {

// Data Type definitions

#ifndef UCHAR
typedef unsigned char UCHAR;
#endif

#ifndef UCHAR8
typedef unsigned char UCHAR8;
#endif

#ifndef USHORT
typedef unsigned short USHORT;
#endif

#ifndef UINT
typedef unsigned int UINT;
#endif

#ifndef ULONG
typedef unsigned long ULONG;
#endif

#ifndef INT8
typedef char INT8;
#endif

#ifndef UINT8
typedef unsigned char UINT8;
#endif

#ifndef INT16
typedef short INT16;
#endif

#ifndef UINT16
typedef unsigned short UINT16;
#endif

#ifndef INT32
typedef int INT32;
#endif

#ifndef UINT32
typedef unsigned int UINT32;
#endif

#ifndef INT64
typedef long long INT64;
#endif

#ifndef UINT64
typedef unsigned long long UINT64;
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(A) (sizeof(A) / sizeof(A[0]))
#endif

// FPGA read/write value type is largest available on this cpu
// NOTE: For now just hardcode to 32bits
using FpgaVal = uint32_t;

// ENDIAN
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define IS_LITTLE_ENDIAN
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define IS_BIG_ENDIAN
#endif

// General Class definitions

/*! \brief A generic return type enumerator class
 *
 * This class defines a generic return type enumerator, to allow users to
 * clearly understand the result of calling the method, in all implementations
 * of the interface.
 *
 * For example:
 * \code
 * MyDoSomethingClass
 * {
 *     ReturnType::State doAnAction();
 * }
 *
 * MyClass
 * {
 *    ReturnType::State retState = MyDoSomethingClass::doAnAction();
 *    if ( retState == ReturnType::RT_OK )
 *    {
 * \endcode
 *
 */

class ReturnType {
 public:
  enum State {
    /*!
     * Used to indicate success.
     */
    RT_OK,

    /*!
     * Used to indicate a non-specific error condition.
     */
    RT_ERROR,

    /*!
     * Used to indicate a busy condition, the caller should re-try or
     * abort its action.
     */
    RT_BUSY,

    /*!
     * Used to indicate that the action has resulted in a process being
     * started that will asynchronously reply with a result at some point
     * in the future which the caller must be prepared to receive.
     */
    RT_INPROGRESS,

    /*!
     * Used to indicate to the caller that the method called is not
     * supported by the particular implementation currently in use.
     */
    RT_NOT_SUPPORTED,

    /*!
     * Used to indicate that an initialise method has already been called.
     */
    RT_ALREADY_INITIALISED,

    /*!
     * Used to indicate that an initialise method has not been called.
     */
    RT_NOT_INITIALISED,

    /*!
     * Used to indicate that a requested function or action is already
     * in use and the attempt to reserve the resource has failed.
     */
    RT_INUSE,

    /*!
     * Used to indicate that an attempt to create or add something could
     * not be executed because it already exists.
     */
    RT_ALREADY_EXISTS,

    /*!
     * Used to indicate that a search for a resource resulted in it
     * not being found.
     */
    RT_NOT_FOUND,

    /*!
     * Used to indicate an operation on data or resource is out of range.
     */
    RT_OUT_OF_RANGE,

    /*!
     * Used to indicate a requested action that is not allowed, as distinct
     * from not-supported.
     */
    RT_NOT_ALLOWED,

    /*!
     * Used to indicate that some requested operation failed
     */
    RT_OPERATION_FAILED,

    /*!
     * Used to indicate that the supplied data could not be parsed as there
     * is something fundamentally wrong with the format of the data
     */
    RT_SYNTAX_ERROR,

    /**
     * Operation failed because it wasn't completed within the specified time
     */
    RT_TIMED_OUT
  };

  static const char*
  getState(ReturnType::State state) {
    switch (state) {
      case RT_OK:
        return "_OK";
        break;

      case RT_ERROR:
        return "_ERROR";
        break;

      case RT_BUSY:
        return "_BUSY";
        break;

      case RT_INPROGRESS:
        return "_INPROGRESS";
        break;

      case RT_NOT_SUPPORTED:
        return "_NOT_SUPPORTED";
        break;

      case RT_ALREADY_INITIALISED:
        return "_ALREADY_INITIALISED";
        break;

      case RT_NOT_INITIALISED:
        return "_NOT_INITIALISED";
        break;

      case RT_INUSE:
        return "_INUSE";
        break;

      case RT_ALREADY_EXISTS:
        return "_ALREADY_EXISTS";
        break;

      case RT_NOT_FOUND:
        return "_NOT_FOUND";
        break;

      case RT_OUT_OF_RANGE:
        return "_OUT_OF_RANGE";
        break;

      case RT_NOT_ALLOWED:
        return "_NOT_ALLOWED";
        break;

      case RT_OPERATION_FAILED:
        return "_OPERATION_FAILED";
        break;

      case RT_SYNTAX_ERROR:
        return "_SYNTAX_ERROR";
        break;

      case RT_TIMED_OUT:
        return "_TIMED_OUT";
        break;
    };

    return "_UNKNOWN_STATE";
  }
};

/**
 * Create an attribute for any variable created for RAII. Add this attribute to
stop compiler "unused" warnings
 *
@code
    Mplane::IPeripheralBus* RAII_VAR peripheral_bus(
Mplane::IPeripheralBus::getInstance() ) ;
@endcode
 */
#define RAII_VAR __attribute__((unused))

} /* namespace Mplane */

#endif /* _GLOBALTYPEDEFS_H_ */
