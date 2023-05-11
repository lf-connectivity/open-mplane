
#include <unistd.h>
#include "gtest/gtest.h"

int main( int argc, char* argv[] )
{
	::testing::InitGoogleTest(&argc, argv);
	::chdir("serial") ;
	return RUN_ALL_TESTS();
}

