/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DirNode_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */
#include "gtest/gtest.h"

#include "DirNode.h"

using namespace Mplane ;

//===================================================================================================================
class DirNodeTest : public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp()
    {
    	const ::testing::TestInfo* const test_info =
    	  ::testing::UnitTest::GetInstance()->current_test_info();

    	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    	std::cout << test_info->name() << " - START" <<  std::endl;

    }

    /*! @brief Tear down the test
     */
    virtual void TearDown()
    {

    }

    //-------------------------------------------------------------------------------------------------------------
    std::vector<std::string> getDirPaths(const DirNodePtr& dirNode)
    {
    	std::vector<std::string> paths ;

    	std::vector< DirNodePtr > dirContents( dirNode->getDir() ) ;
    	for (std::vector< DirNodePtr >::const_iterator iter(dirContents.begin()); iter != dirContents.end(); ++iter)
    	{
    		paths.push_back((*iter)->getFullPath()) ;
    	}
    	for (std::vector< DirNodePtr >::const_iterator iter(dirContents.begin()); iter != dirContents.end(); ++iter)
    	{
    		if ((*iter)->isDir())
    		{
    			std::vector<std::string> subPaths(getDirPaths(*iter)) ;
    			paths.insert(paths.end(), subPaths.begin(), subPaths.end()) ;
    		}
    	}

    	return paths ;
    }


};




//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(DirNodeTest, Root)
{
	// Create root node
	DirNodePtr root = new DirNode("/", DirNode::DN_DIRECTORY) ;
	EXPECT_TRUE(root->isDir()) ;
	EXPECT_EQ(root->getPath(), "/") ;
	EXPECT_EQ(root->getName(), "") ;

	root->showDetails() ;

	delete root ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(DirNodeTest, Root_A_B)
{
	// Create root node
	DirNodePtr root = new DirNode("/", DirNode::DN_DIRECTORY) ;
	EXPECT_TRUE(root->isDir()) ;
	EXPECT_EQ(root->getPath(), "/") ;
	EXPECT_EQ(root->getName(), "") ;

	DirNodePtr dirA = new DirNode("/A", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirB = new DirNode("/B", DirNode::DN_DIRECTORY) ;

	EXPECT_TRUE(dirA->isDir()) ;
	EXPECT_EQ(dirA->getPath(), "/") ;
	EXPECT_EQ(dirA->getName(), "A") ;
	EXPECT_TRUE(dirA->isDir()) ;
	EXPECT_EQ(dirB->getPath(), "/") ;
	EXPECT_EQ(dirB->getName(), "B") ;

	EXPECT_TRUE(root->add(dirA)) ;
	EXPECT_TRUE(root->add(dirB)) ;

	root->showDetails() ;

	delete root ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(DirNodeTest, Root_A_A_B)
{
	// Create root node
	DirNodePtr root = new DirNode("/", DirNode::DN_DIRECTORY) ;
	EXPECT_TRUE(root->isDir()) ;
	EXPECT_EQ(root->getPath(), "/") ;
	EXPECT_EQ(root->getName(), "") ;

	DirNodePtr dirA = new DirNode("/A", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirB = new DirNode("/B", DirNode::DN_DIRECTORY) ;

	EXPECT_TRUE(dirA->isDir()) ;
	EXPECT_EQ(dirA->getPath(), "/") ;
	EXPECT_EQ(dirA->getName(), "A") ;
	EXPECT_TRUE(dirA->isDir()) ;
	EXPECT_EQ(dirB->getPath(), "/") ;
	EXPECT_EQ(dirB->getName(), "B") ;

	EXPECT_TRUE(root->add(dirA)) ;
	EXPECT_TRUE(root->add(dirB)) ;

	DirNodePtr dirAA = new DirNode("/A/A", DirNode::DN_DIRECTORY) ;

	EXPECT_TRUE(dirAA->isDir()) ;
	EXPECT_EQ(dirAA->getPath(), "/A/") ;
	EXPECT_EQ(dirAA->getName(), "A") ;

	EXPECT_TRUE(root->add(dirAA)) ;


	root->showDetails() ;

	delete root ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(DirNodeTest, Basic)
{
	// Create root node
	DirNodePtr root = new DirNode("/", DirNode::DN_DIRECTORY) ;
	EXPECT_TRUE(root->isDir()) ;
	EXPECT_EQ(root->getPath(), "/") ;
	EXPECT_EQ(root->getName(), "") ;

	DirNodePtr dirA = new DirNode("/A", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirB = new DirNode("/B", DirNode::DN_DIRECTORY) ;

	EXPECT_TRUE(dirA->isDir()) ;
	EXPECT_EQ(dirA->getPath(), "/") ;
	EXPECT_EQ(dirA->getName(), "A") ;
	EXPECT_TRUE(dirA->isDir()) ;
	EXPECT_EQ(dirB->getPath(), "/") ;
	EXPECT_EQ(dirB->getName(), "B") ;

	EXPECT_TRUE(root->add(dirA)) ;
	EXPECT_TRUE(root->add(dirB)) ;

	std::string error = root->getError() ;
	EXPECT_EQ(error, "") ;
	std::cout << "DirNode error=" << error << std::endl ;

	std::vector< DirNodePtr > dirContents = root->getDir() ;
	EXPECT_EQ(dirContents.size(), 2u) ;

	DirNodePtr dirAA = new DirNode("/A/A", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirBA = new DirNode("/B/A", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirCA = new DirNode("/C/A", DirNode::DN_DIRECTORY) ;

	EXPECT_TRUE(dirAA->isDir()) ;
	EXPECT_EQ(dirAA->getPath(), "/A/") ;
	EXPECT_EQ(dirAA->getName(), "A") ;
	EXPECT_TRUE(dirBA->isDir()) ;
	EXPECT_EQ(dirBA->getPath(), "/B/") ;
	EXPECT_EQ(dirBA->getName(), "A") ;
	EXPECT_TRUE(dirCA->isDir()) ;
	EXPECT_EQ(dirCA->getPath(), "/C/") ;
	EXPECT_EQ(dirCA->getName(), "A") ;

	EXPECT_TRUE(root->add(dirAA)) ;
	EXPECT_TRUE(root->add(dirBA)) ;

	error = root->getError() ;
	EXPECT_EQ(error, "") ;
	std::cout << "DirNode error=" << error << std::endl ;

	dirContents = dirA->getDir() ;
	EXPECT_EQ(dirContents.size(), 1u) ;


	// This should cause an error because /C does not exist
	EXPECT_FALSE(root->add(dirCA)) ;
	error = root->getError() ;
	EXPECT_FALSE(error.empty()) ;
	std::cout << "DirNode error=" << error << std::endl ;


	delete root ;
	delete dirCA ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(DirNodeTest, Navigation)
{
	std::string error ;

	//	/
	//		A/
	//			AA/
	//				AAA/
	//				AAB/
	//			AB/
	//		B/
	//			BB/
	//
	DirNodePtr root = new DirNode("/", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirA = new DirNode("/A", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirB = new DirNode("/B", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAA = new DirNode("/A/AA", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAAA = new DirNode("/A/AA/AAA", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAAB = new DirNode("/A/AA/AAB", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAB = new DirNode("/A/AB", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirBB = new DirNode("/B/BB", DirNode::DN_DIRECTORY) ;
	EXPECT_TRUE(root->add(dirA)) ;
	EXPECT_TRUE(root->add(dirB)) ;
	EXPECT_TRUE(root->add(dirAA)) ;

	std::cout << "============================" << std::endl ;
	root->show() ;
	std::cout << "============================" << std::endl ;

	EXPECT_TRUE(root->add(dirAAA)) ;
	EXPECT_TRUE(root->add(dirAAB)) ;
	EXPECT_TRUE(root->add(dirAB)) ;
	EXPECT_TRUE(root->add(dirBB)) ;

	EXPECT_EQ(dirAAA->getFullPath(), "/A/AA/AAA") ;

	error = root->getError() ;
	EXPECT_EQ(error, "") ;
	std::cout << "DirNode error=" << error << std::endl ;

	std::cout << "============================" << std::endl ;
	root->show() ;
	std::cout << "============================" << std::endl ;

	DirNodePtr dir ;

	dir = root->findDir("/A/AA/AAB") ;
	EXPECT_TRUE(dir != 0) ;
	EXPECT_EQ(dir->getPath(), "/A/AA/") ;
	EXPECT_EQ(dir->getName(), "AAB") ;
	EXPECT_FALSE(dir->isHidden()) ;

	// .. on '/' is always '/'
	dir = root->findDir("../../../../B/BB") ;
	EXPECT_TRUE(dir != 0) ;
	EXPECT_EQ(dir->getPath(), "/B/") ;
	EXPECT_EQ(dir->getName(), "BB") ;

	// relative to '/A/AA/AAB'
	dir = dirAAB->findDir("../../../../B/BB") ;
	EXPECT_TRUE(dir != 0) ;
	EXPECT_EQ(dir->getPath(), "/B/") ;
	EXPECT_EQ(dir->getName(), "BB") ;

	// relative to '/A/AA/AAB'
	dir = dirAAB->findDir("../AAA") ;
	EXPECT_TRUE(dir != 0) ;
	EXPECT_EQ(dir->getPath(), "/A/AA/") ;
	EXPECT_EQ(dir->getName(), "AAA") ;

	dir = root->findDir("../AAA") ;
	EXPECT_TRUE(dir == 0) ;

	delete root ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(DirNodeTest, DirDelete)
{
	std::string error ;

	//	/
	//		A/
	//			AA/
	//				AAA/
	//				AAB/
	//			AB/
	//		B/
	//			BB/
	//
	DirNodePtr root = new DirNode("/", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirA = new DirNode("/A", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirB = new DirNode("/B", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAA = new DirNode("/A/AA", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAAA = new DirNode("/A/AA/AAA", DirNode::DN_DIRECTORY) ;
	DirNodePtr fileAAA1 = new DirNode("/A/AA/AAA/file1", DirNode::DN_FILE) ;
	DirNodePtr fileAAA2 = new DirNode("/A/AA/AAA/file2", DirNode::DN_FILE) ;
	DirNodePtr dirAAB = new DirNode("/A/AA/AAB", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAB = new DirNode("/A/AB", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirBB = new DirNode("/B/BB", DirNode::DN_DIRECTORY) ;
	EXPECT_TRUE(root->add(dirA)) ;
	EXPECT_TRUE(root->add(dirB)) ;
	EXPECT_TRUE(root->add(dirAA)) ;
	EXPECT_TRUE(root->add(dirAAA)) ;
	EXPECT_TRUE(root->add(fileAAA1)) ;
	EXPECT_TRUE(root->add(fileAAA2)) ;
	EXPECT_TRUE(root->add(dirAAB)) ;
	EXPECT_TRUE(root->add(dirAB)) ;
	EXPECT_TRUE(root->add(dirBB)) ;

	std::cout << "============================" << std::endl ;
	root->show() ;
	std::cout << "============================" << std::endl ;


	DirNodePtr file ;
	file = root->findFile("/A/AA/AAA/file1") ;
	EXPECT_TRUE(file != 0) ;


	EXPECT_FALSE(fileAAA1->deleteDirContents()) ;

	// Delete /A/AA contents
	EXPECT_TRUE(dirAA->deleteDirContents()) ;
	std::cout << "============================" << std::endl ;
	root->show() ;
	std::cout << "============================" << std::endl ;

	DirNodePtr dir ;
	dir = root->findDir("/A/AA") ;
	EXPECT_TRUE(dir != 0) ;
	EXPECT_EQ(dir->getPath(), "/A/") ;
	EXPECT_EQ(dir->getName(), "AA") ;

	dir = root->findDir("/A/AA/AAA") ;
	EXPECT_TRUE(dir == 0) ;
	file = root->findFile("/A/AA/AAA/file1") ;
	EXPECT_TRUE(file == 0) ;

	// .. on '/' is always '/'
	dir = root->findDir("../../../../B/BB") ;
	EXPECT_TRUE(dir != 0) ;
	EXPECT_EQ(dir->getPath(), "/B/") ;
	EXPECT_EQ(dir->getName(), "BB") ;

	dir = root->findDir("../AAA") ;
	EXPECT_TRUE(dir == 0) ;

	delete root ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(DirNodeTest, Hidden)
{
	std::string error ;

	DirNode::setShowHidden(false) ;

	//	/
	//		A/
	//			AA/
	//				AAA/
	//				AAB/
	//			AB/
	//		B/
	//			BB/
	//		.C/
	//			CC/
	//		D/
	//			.DA/
	//				DAA/
	//				DAB/
	//			DB/
	//
	DirNodePtr root = new DirNode("/", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirA = new DirNode("/A", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAB = new DirNode("/A/AB", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirB = new DirNode("/B", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirBB = new DirNode("/B/BB", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirC = new DirNode("/.C", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirCC = new DirNode("/.C/CC", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAA = new DirNode("/A/AA", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAAA = new DirNode("/A/AA/AAA", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAAB = new DirNode("/A/AA/AAB", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirD = new DirNode("/D", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirDA = new DirNode("/D/.DA", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirDAA = new DirNode("/D/.DA/AAA", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirDAB = new DirNode("/D/.DA/AAB", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirDB = new DirNode("/D/DB", DirNode::DN_DIRECTORY) ;
	EXPECT_TRUE(root->add(dirA)) ;
	EXPECT_TRUE(root->add(dirAA)) ;
	EXPECT_TRUE(root->add(dirAAA)) ;
	EXPECT_TRUE(root->add(dirAAB)) ;
	EXPECT_TRUE(root->add(dirAB)) ;
	EXPECT_TRUE(root->add(dirB)) ;
	EXPECT_TRUE(root->add(dirBB)) ;
	EXPECT_TRUE(root->add(dirC)) ;
	EXPECT_TRUE(root->add(dirCC)) ;
	EXPECT_TRUE(root->add(dirD)) ;
	EXPECT_TRUE(root->add(dirDA)) ;
	EXPECT_TRUE(root->add(dirDAA)) ;
	EXPECT_TRUE(root->add(dirDAB)) ;
	EXPECT_TRUE(root->add(dirDB)) ;

	EXPECT_EQ(dirAAA->getFullPath(), "/A/AA/AAA") ;

	error = root->getError() ;
	EXPECT_EQ(error, "") ;
	std::cout << "DirNode error=" << error << std::endl ;

	std::cout << "============================" << std::endl ;
	root->show() ;
	std::cout << "============================" << std::endl ;
	std::cout << "============================" << std::endl ;
	root->showDetails() ;
	std::cout << "============================" << std::endl ;

	DirNodePtr dir ;

	dir = root->findDir("/A/AA/AAB") ;
	EXPECT_TRUE(dir != 0) ;
	EXPECT_EQ(dir->getPath(), "/A/AA/") ;
	EXPECT_EQ(dir->getName(), "AAB") ;

	// .. on '/' is always '/'
	dir = root->findDir("../../../../B/BB") ;
	EXPECT_TRUE(dir != 0) ;
	EXPECT_EQ(dir->getPath(), "/B/") ;
	EXPECT_EQ(dir->getName(), "BB") ;

	// relative to '/A/AA/AAB'
	dir = dirAAB->findDir("../../../../B/BB") ;
	EXPECT_TRUE(dir != 0) ;
	EXPECT_EQ(dir->getPath(), "/B/") ;
	EXPECT_EQ(dir->getName(), "BB") ;

	// relative to '/A/AA/AAB'
	dir = dirAAB->findDir("../AAA") ;
	EXPECT_TRUE(dir != 0) ;
	EXPECT_EQ(dir->getPath(), "/A/AA/") ;
	EXPECT_EQ(dir->getName(), "AAA") ;

	dir = root->findDir("../AAA") ;
	EXPECT_TRUE(dir == 0) ;

	dir = root->findDir("/C/CC") ;
	EXPECT_TRUE(dir != 0) ;
	EXPECT_EQ(dir->getPath(), "/C/") ;
	EXPECT_EQ(dir->getName(), "CC") ;

	// Normal view
	std::cerr << "CONTENTS:" << std::endl ;
	std::string contentsStr ;
	std::vector<std::string> contents(getDirPaths(root)) ;
	for (auto entry : contents)
	{
		std::cerr << entry << std::endl ;
		contentsStr += entry + "\n" ;
	}
	std::cerr << std::endl ;

	EXPECT_TRUE(contentsStr.find("/A\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AA\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AB\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AA/AAA\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AA/AAB\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/B\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/B/BB\n") != std::string::npos) ;
	EXPECT_FALSE(contentsStr.find("/C\n") != std::string::npos) ;
	EXPECT_FALSE(contentsStr.find("/C/CC\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/D\n") != std::string::npos) ;
	EXPECT_FALSE(contentsStr.find("/D/DA\n") != std::string::npos) ;
	EXPECT_FALSE(contentsStr.find("/D/DA/AAA\n") != std::string::npos) ;
	EXPECT_FALSE(contentsStr.find("/D/DA/AAB\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/D/DB\n") != std::string::npos) ;


	// Show hidden view
	DirNode::setShowHidden(true) ;
	std::cerr << "CONTENTS:" << std::endl ;
	contentsStr = "" ;
	contents = getDirPaths(root) ;
	for (auto entry : contents)
	{
		std::cerr << entry << std::endl ;
		contentsStr += entry + "\n" ;
	}
	std::cerr << std::endl ;

	EXPECT_TRUE(contentsStr.find("/A\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AA\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AB\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AA/AAA\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AA/AAB\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/B\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/B/BB\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/C\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/C/CC\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/D\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/D/DA\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/D/DA/AAA\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/D/DA/AAB\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/D/DB\n") != std::string::npos) ;

	DirNode::setShowHidden(false) ;

	delete root ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(DirNodeTest, Change)
{
	std::string error ;

	//	/
	//		A/
	//			AA/
	//				AAA/
	//				AAB/
	//			AB/
	//		B/
	//			BB/
	//
	DirNodePtr root = new DirNode("/", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirA = new DirNode("/A", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirB = new DirNode("/B", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAA = new DirNode("/A/AA", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAAA = new DirNode("/A/AA/AAA", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAAB = new DirNode("/A/AA/AAB", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAB = new DirNode("/A/AB", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirBB = new DirNode("/B/BB", DirNode::DN_DIRECTORY) ;
	EXPECT_TRUE(root->add(dirA)) ;
	EXPECT_TRUE(root->add(dirB)) ;
	EXPECT_TRUE(root->add(dirAA)) ;

	EXPECT_TRUE(root->add(dirAAA)) ;
	EXPECT_TRUE(root->add(dirAAB)) ;
	EXPECT_TRUE(root->add(dirAB)) ;
	EXPECT_TRUE(root->add(dirBB)) ;

	EXPECT_EQ(dirAAA->getFullPath(), "/A/AA/AAA") ;

	error = root->getError() ;
	EXPECT_EQ(error, "") ;
	std::cout << "DirNode error=" << error << std::endl ;

	DirNodePtr dir ;

	dir = root->findDir("/A/AA/AAB") ;
	EXPECT_TRUE(dir != 0) ;
	EXPECT_EQ(dir->getPath(), "/A/AA/") ;
	EXPECT_EQ(dir->getName(), "AAB") ;
	EXPECT_FALSE(dir->isHidden()) ;

	std::cout << "============================" << std::endl ;
	root->showDetails() ;
	std::cout << "============================" << std::endl ;


	dir = root->findDir("/A/AA/") ;

	std::cerr << "HIDE AA...." << std::endl ;
	dir->setHidden(true) ;
	std::cout << "============================" << std::endl ;
	root->showDetails() ;
	std::cout << "============================" << std::endl ;

	// Normal view
	{
	std::cerr << "CONTENTS:" << std::endl ;
	std::string contentsStr ;
	std::vector<std::string> contents(getDirPaths(root)) ;
	for (auto entry : contents)
	{
		std::cerr << entry << std::endl ;
		contentsStr += entry + "\n" ;
	}
	std::cerr << std::endl ;

	//	/A
	//	/B
	//	/A/AB
	//	/B/BB
	EXPECT_TRUE(contentsStr.find("/A\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AB\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/B\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/B/BB\n") != std::string::npos) ;

	}

	std::cerr << "UN-HIDE AA...." << std::endl ;
	dir->setHidden(false) ;
	std::cout << "============================" << std::endl ;
	root->showDetails() ;
	std::cout << "============================" << std::endl ;

	// Normal view
	{
	std::cerr << "CONTENTS:" << std::endl ;
	std::string contentsStr ;
	std::vector<std::string> contents(getDirPaths(root)) ;
	for (auto entry : contents)
	{
		std::cerr << entry << std::endl ;
		contentsStr += entry + "\n" ;
	}
	std::cerr << std::endl ;

	//	/A
	//	/B
	//	/A/AB
	//	/A/AA
	//	/A/AA/AAA
	//	/A/AA/AAB
	//	/B/BB
	EXPECT_TRUE(contentsStr.find("/A\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AA\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AB\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AA/AAA\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AA/AAB\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/B\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/B/BB\n") != std::string::npos) ;
	}

	std::cerr << "Rename AA->XX...." << std::endl ;
	dir->rename("XX") ;
	std::cout << "============================" << std::endl ;
	root->showDetails() ;
	std::cout << "============================" << std::endl ;

	// Normal view
	{
	std::cerr << "CONTENTS:" << std::endl ;
	std::string contentsStr ;
	std::vector<std::string> contents(getDirPaths(root)) ;
	for (auto entry : contents)
	{
		std::cerr << entry << std::endl ;
		contentsStr += entry + "\n" ;
	}
	std::cerr << std::endl ;

	//	/A
	//	/B
	//	/A/AB
	//	/A/XX
	//	/A/XX/AAA
	//	/A/XX/AAB
	//	/B/BB
	EXPECT_TRUE(contentsStr.find("/A\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/XX\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AB\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/XX/AAA\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/XX/AAB\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/B\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/B/BB\n") != std::string::npos) ;

	}


	delete root ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(DirNodeTest, Change2)
{
	std::string error ;

	//	/
	//		A/
	//			AA/
	//				AAA/
	//				AAB/
	//			AB/
	//		B/
	//			BB/
	//
	DirNodePtr root = new DirNode("/", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirA = new DirNode("/A", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirB = new DirNode("/B", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAA = new DirNode("/A/AA", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAAA = new DirNode("/A/AA/AAA", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAAB = new DirNode("/A/AA/AAB", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirAB = new DirNode("/A/AB", DirNode::DN_DIRECTORY) ;
	DirNodePtr dirBB = new DirNode("/B/BB", DirNode::DN_DIRECTORY) ;
	EXPECT_TRUE(root->add(dirA)) ;
	EXPECT_TRUE(root->add(dirB)) ;
	EXPECT_TRUE(root->add(dirAA)) ;

	EXPECT_TRUE(root->add(dirAAA)) ;
	EXPECT_TRUE(root->add(dirAAB)) ;
	EXPECT_TRUE(root->add(dirAB)) ;
	EXPECT_TRUE(root->add(dirBB)) ;

	EXPECT_EQ(dirAAA->getFullPath(), "/A/AA/AAA") ;

	error = root->getError() ;
	EXPECT_EQ(error, "") ;
	std::cout << "DirNode error=" << error << std::endl ;

	DirNodePtr dir ;

	dir = root->findDir("/A/AA/AAB") ;
	EXPECT_TRUE(dir != 0) ;
	EXPECT_EQ(dir->getPath(), "/A/AA/") ;
	EXPECT_EQ(dir->getName(), "AAB") ;
	EXPECT_FALSE(dir->isHidden()) ;

	std::cout << "============================" << std::endl ;
	root->showDetails() ;
	std::cout << "============================" << std::endl ;

	// Normal view
	{
	std::cerr << "CONTENTS:" << std::endl ;
	std::string contentsStr ;
	std::vector<std::string> contents(getDirPaths(root)) ;
	for (auto entry : contents)
	{
		std::cerr << entry << std::endl ;
		contentsStr += entry + "\n" ;
	}
	std::cerr << std::endl ;

	//	/A
	//	/B
	//	/A/AB
	//	/A/AA
	//	/A/AA/AAA
	//	/A/AA/AAB
	//	/B/BB
	EXPECT_TRUE(contentsStr.find("/A\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AA\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AB\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AA/AAA\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/A/AA/AAB\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/B\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/B/BB\n") != std::string::npos) ;
	}


	dir = root->findDir("/A/") ;
	std::cout << "----------------------------" << std::endl ;
	dir->showDetails() ;
	std::cout << "----------------------------" << std::endl ;

	std::cerr << "Rename A->X...." << std::endl ;
	dir->rename("X") ;
	std::cout << "============================" << std::endl ;
	root->showDetails() ;
	std::cout << "============================" << std::endl ;

	// Normal view
	{
	std::cerr << "CONTENTS:" << std::endl ;
	std::string contentsStr ;
	std::vector<std::string> contents(getDirPaths(root)) ;
	for (auto entry : contents)
	{
		std::cerr << entry << std::endl ;
		contentsStr += entry + "\n" ;
	}
	std::cerr << std::endl ;

	//	/X
	//	/B
	//	/X/AB
	//	/X/AA
	//	/X/AA/AAA
	//	/X/AA/AAB
	//	/B/BB
	EXPECT_TRUE(contentsStr.find("/X\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/X/AA\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/X/AB\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/X/AA/AAA\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/X/AA/AAB\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/B\n") != std::string::npos) ;
	EXPECT_TRUE(contentsStr.find("/B/BB\n") != std::string::npos) ;
	}



	delete root ;
}


//===================================================================================================================
