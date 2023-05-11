#include "TestingTestMethods.h"

#include "TestingTestInterface.h"

using namespace Mplane ;

//TestingTestInterface::TestingTestInterface():
//	TestInterface(),
//    test( new testHandler(*this, *this) )
//{
//    add( test );
//}
//
//TestingTestInterface::~TestingTestInterface()
//{
//    delete test;
//}

TestingTestInterface::TestingTestInterface():
	TestInterfaceBase()
{
	testHandler::registerMethods( *this, *this );
}

TestingTestInterface::~TestingTestInterface()
{
}
