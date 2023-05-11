#include <sstream>
#include "Nodes/RtiDirEntry.h"
#include "Nodes/DirClass.h"
#include "RtiKeyword.h"
#include "TestingTestMethods.h"

using namespace Mplane ;

void testHandler::registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings)
{
	// Create a directory to store the data in
	msgParser.add( static_cast<RtiDirEntry *>(new DirClass("/tif:testing", "Testing area", msgParser, settings)) ) ;

	msgParser.add( static_cast<RtiDirEntry *>(new testHandler("/tif:testing/getVersion",
			"",
			"INT Status,INT Version",
			"get fpga version",
			msgParser, settings))
	);

	msgParser.add(
		static_cast<RtiDirEntry *>(new testHandler("/tif:testing/read", "INT Offset",
			"INT Status,INT Value,STRING Info",
			"read an fpga register",
			msgParser, settings))
	);

	msgParser.add(
		static_cast<RtiDirEntry *>(new testHandler("/tif:testing/write",
				"INT Offset,INT Value",
				"INT Status,STRING Info",
				"write an fpga register",
				msgParser, settings))
	) ;

	msgParser.add(
		static_cast<RtiDirEntry *>(new testHandler("/tif:testing/test10args",
			/* args */ 	"INT ARG1,INT aRg2,STRING arg3,STRING ARG4,FLOAT arg5,FLOAT ARG6,HEXINT arg7,"
						"HEXINT arg8, INT arg9,INT arg10",
			/* return */ "INT Status,STRING Info",
			/* comment */ "test command with 10 args to check arg parsing",
			msgParser, settings ))
	) ;

}


testHandler::testHandler(const std::string& pathname, const std::string& callFields,
		const std::string& returnFields, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryFunc(pathname, comment, callFields, returnFields, msgParser, settings)
{
}

testHandler::~testHandler()
{
}


void testHandler::getVersion(  DataVariantList *callList, DataVariantList *returnList )
{

    returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusOK );
    returnList->find("Version")->set( 0 );
}

void testHandler::getName(  DataVariantList *callList, DataVariantList *returnList )
{

    returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusOK );
    returnList->find("Name")->set( "string" );
}

void testHandler::read(  DataVariantList *callList, DataVariantList *returnList )
{
    int offset= callList->find("Offset")->toInt();
    int value= callList->find("Value")->toInt();

    std::stringstream ss ;
    ss << std::hex ;
    ss << 	"Offset=0x" << offset <<
    		" Value=0x" << value ;
    returnList->find(RtiKeyword::INFO_VAR)->set( ss.str() );

    returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusOK );
    returnList->find("Value")->set( 0 );
}

void testHandler::write(  DataVariantList *callList, DataVariantList *returnList )
{
    int offset= callList->find("Offset")->toInt();
    int value= callList->find("Value")->toInt();

    std::stringstream ss ;
    ss << std::hex ;
    ss << 	"Offset=0x" << offset <<
    		" Value=0x" << value ;
    returnList->find(RtiKeyword::INFO_VAR)->set( ss.str() );
    returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusOK );
}

void testHandler::test10args(  DataVariantList *callList, DataVariantList *returnList )
{
//    int offset= callList->find("Offset")->toInt();
//    int value= callList->find("Value")->toInt();

    returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusOK );
}

std::string testHandler::operator()(const std::string& functionName)
{
    if( functionName == "getVersion")
    {
        getVersion( callVarList, returnVarList  );
    }
    else if( functionName == "getName")
    {
        getName( callVarList, returnVarList  );
    }
    else if( functionName == "read")
    {
        read( callVarList, returnVarList  );
    }
    else if( functionName == "write")
    {
        write( callVarList, returnVarList  );
    }
    return returnVarList->toString();
}
