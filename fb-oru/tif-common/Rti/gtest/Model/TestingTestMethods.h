#ifndef __TESTING_TEST_METHODS__H_
#define __TESTING_TEST_METHODS__H_

#include "DataVariant.h"
#include "IRtiMsgParser.h"
#include "IRtiSettings.h"
#include "Nodes/EntryFunc.h"

namespace Mplane {

class testHandler: public EntryFunc
{
public:
	testHandler(const std::string& pathname, const std::string& callFields,
			const std::string& returnFields, const std::string& comment,
			IRtiMsgParser& msgParser, IRtiSettings& settings);

    virtual ~testHandler();

    static void registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings) ;

protected:
    virtual std::string operator()(const std::string& functionName) ;

    void getVersion( DataVariantList *callList, DataVariantList *returnList );

    void getName( DataVariantList *callList, DataVariantList *returnList );

    void read(  DataVariantList *callList,DataVariantList *returnList );

    void write(  DataVariantList *callList,DataVariantList *returnList );

    void test10args(  DataVariantList *callList,DataVariantList *returnList );

};

}
#endif /* __TESTING_TEST_METHODS__H_ */
