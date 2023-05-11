/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TaskTests.cpp
 * \brief     Implementation of the main CppUnit test harness for common task
 *
 *
 * \details   This file contains the main CppUnit controlling function for the
 *            common task sources.
 *
 */

#ifndef _REENTRANT
#define _REENTRANT
#endif
#define _POSIX_SOURCE

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/TextTestProgressListener.h>

#include <cppunit/XmlOutputter.h>

#include "FileLockSockets.h"

using namespace Mplane ;


int main( int argc, char* argv[] )
{
	// stop any other socket tests from running at the same time
	FileLockSockets locker ;
	locker.lock() ;

  // Create the event manager and test controller
  CPPUNIT_NS::TestResult controller;

  // Add a listener that colllects test result
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener( &result );

  // Add a listener that print dots as test run.
  CPPUNIT_NS::TextTestProgressListener progress;
  controller.addListener( &progress );

  // Add the top suite to the test runner
  CppUnit::TextTestRunner runner;
  runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
  runner.run( controller );

  // Output result to XML format
  std::ofstream results ("cppunit.xml");
  CppUnit::XmlOutputter* x_outputter = new CppUnit::XmlOutputter( &result,
          results );
  x_outputter->write();

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, std::cerr );
  outputter.write();

    delete x_outputter ;

  return result.wasSuccessful() ? 0 : 1;
}
