
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/TextTestProgressListener.h>

#include <cppunit/XmlOutputter.h>

int main( int argc, char* argv[] )
{
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

