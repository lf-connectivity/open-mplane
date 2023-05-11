/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AppTrace.hpp
 * \brief     Create an application method "tracing" object
 *
 *
 * \details   This object is used to "trace" the application program's execution
 *to narrow down the location of failures/exits/aborts The object is created at
 *the start of a method, where it prints out the file / method / line. When the
 *method is exited the object is destroyed and prints the "method exit" message.
 *
 *                 message method on this object can be used to
 *print additional messages during the method's execution
 *
 */

#ifndef INC_APPTRACE_HPP_
#define INC_APPTRACE_HPP_

#include <iostream>

// uncomment this to trace app execution
#define TRACE_APP

#ifdef TRACE_APP
#define APP_TRACE(msg...) AppTrace __tracer(__FILE__, __func__, __LINE__, msg)
#define APP_TRACE_MSG(msg) __tracer.message(__LINE__, msg)
#else
#define APP_TRACE(msg...) \
  {}
#define APP_TRACE_MSG(msg) \
  {}
#endif

namespace Mplane {

/*!
 * \class  AppTrace
 * \brief
 * \details
 *
 */
class AppTrace {
 public:
  AppTrace(
      const std::string& file,
      const std::string& function,
      unsigned line,
      const std::string& msg = "")
      : mFile(file), mFunction(function) {
    std::cerr << "START " << mFile << "::" << mFunction << "():" << line;
    if (!msg.empty())
      std::cerr << "[" << msg << "]";
    std::cerr << std::endl;
  }

  virtual ~AppTrace() {
    std::cerr << "END " << mFile << "::" << mFunction << "()" << std::endl;
  }

  void
  message(unsigned line, const std::string& msg = "") {
    std::cerr << "MSG " << mFile << "::" << mFunction << "():" << line;
    if (!msg.empty())
      std::cerr << " [" << msg << "]";
    std::cerr << std::endl;
  }

 private:
  std::string mFile;
  std::string mFunction;
};

} // namespace Mplane

#endif /* INC_APPTRACE_HPP_ */
