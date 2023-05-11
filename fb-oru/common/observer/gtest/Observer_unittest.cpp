/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Observer_unittest.cpp
 * \brief     Google Test of Observer
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the Observer class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>

#include <map>
#include <memory>
#include "Observer.hpp"

using namespace Mplane;

using namespace std;

//-----------------------------------------------
class IClassSubject
{
public:
	IClassSubject() {}
	virtual ~IClassSubject() {}
	virtual void doSomething() =0 ;

};

class ClassSubject : public Subject<IClassSubject>, public IClassSubject
{
public:
	ClassSubject(){}
	virtual ~ClassSubject() {}
	virtual void doSomething() override {
		std::cerr << "ClassSubject" << std::endl ;
	}

	virtual void runIt() {
		notify() ;
	}
};

class ClassSubjectX : public ClassSubject
{
public:
	ClassSubjectX(){}
	virtual ~ClassSubjectX() {}
	virtual void doSomething() override {
		std::cerr << "ClassSubjectX" << std::endl ;
	}
};

class ClassSubjectY : public ClassSubject
{
public:
	ClassSubjectY(){}
	virtual ~ClassSubjectY() {}
	virtual void doSomething() override {
		std::cerr << "ClassSubjectY" << std::endl ;
	}
};




class ClassSubjectData : public Subject<IClassSubject, const std::map<std::string, unsigned>&>, public IClassSubject
{
public:
	ClassSubjectData(const std::map<std::string, unsigned>& data) : mData(data) {}
	virtual ~ClassSubjectData() {}
	virtual void doSomething() override {
		std::cerr << "ClassSubject" << std::endl ;
	}

	virtual void runIt() {
		notify(mData) ;
	}

	std::map<std::string, unsigned> mData ;
};

class ClassSubjectDataX : public ClassSubjectData
{
public:
	ClassSubjectDataX(const std::map<std::string, unsigned>& data) : ClassSubjectData(data) {}
	virtual ~ClassSubjectDataX() {}
	virtual void doSomething() override {
		std::cerr << "ClassSubjectDataX" << std::endl ;
	}
};

class ClassSubjectDataY : public ClassSubjectData
{
public:
	ClassSubjectDataY(const std::map<std::string, unsigned>& data) : ClassSubjectData(data) {}
	virtual ~ClassSubjectDataY() {}
	virtual void doSomething() override {
		std::cerr << "ClassSubjectDataY" << std::endl ;
	}
};



//-----------------------------------------------
class IClassObs
{
public:
	IClassObs() {}
	virtual ~IClassObs() {}
	virtual void doSomething() =0 ;
    virtual void update(IClassSubject& subject) =0 ;
};

class ClassObs : public Observer<IClassSubject>, public IClassObs
{
public:
	ClassObs() {}
	virtual ~ClassObs() {}
	virtual void doSomething() override {
		std::cerr << "ClassObs" << std::endl ;
	}

    virtual void update(IClassSubject& subject) {
    	std::cerr << "ClassObs: " ;
    	subject.doSomething() ;
    }
    virtual const char* name() const {return "ClassObs";};

};

class ClassObsWrap : public Observer<IClassSubject> {
public:
	ClassObsWrap(IClassObs* parent, const std::string& name) : mParent(parent), mName(name) {
		std::cerr << "ClassObsWrap new " << mName << std::endl ;
	}
	virtual ~ClassObsWrap()  {
		std::cerr << "ClassObsWrap destroy " << mName << std::endl ;
	}

    virtual void update(IClassSubject& subject) {
    	std::cerr << mName << ": " ;
    	mParent->update(subject) ;
    }
    virtual const char* name() const {return "ClassObsWrap";};
private:
    IClassObs* mParent;
    std::string mName ;
};


class ClassObsData : public Observer<IClassSubject, const std::map<std::string, unsigned>&>, public IClassObs
{
public:
	ClassObsData() {}
	virtual ~ClassObsData() {}
	virtual void doSomething() override {
		std::cerr << "ClassObsData" << std::endl ;
	}

    virtual void update(IClassSubject& subject) {}

    virtual void update(IClassSubject& subject, const std::map<std::string, unsigned>& data) {
    	std::cerr << "ClassObsData: " ;
    	subject.doSomething() ;
    	for (auto entry : data)
    	{
    		std::cerr << entry.first << "=" << entry.second << std::endl ;
    	}
    }
    virtual const char* name() const {return "ClassObsData";};

};


//---------------------------------------------------------------------------------------------------------
//class ClassObsWrap : public Observer<IClassSubject> {
//public:
//	ClassObsWrap(IClassObs* parent, const std::string& name) : mParent(parent), mName(name) {
//		std::cerr << "ClassObsWrap new " << mName << std::endl ;
//	}
//	virtual ~ClassObsWrap()  {
//		std::cerr << "ClassObsWrap destroy " << mName << std::endl ;
//	}
//
//    virtual void update(IClassSubject& subject) {
//    	std::cerr << mName << ": " ;
//    	mParent->update(subject) ;
//    }
//    virtual const char* name() const {return "ClassObsWrap";};
//private:
//    IClassObs* mParent;
//    std::string mName ;
//};




template<typename Tparent, typename Tsubject>
class ClassObsWrapTemplate : public Observer<Tsubject> {
public:
	ClassObsWrapTemplate(Tparent* parent, const std::string& name, std::shared_ptr<Tsubject> subject) :
		mParent(parent), mName(name), mSubject(subject)
	{
		std::cerr << "ClassObsWrapTemplate new " << mName << std::endl ;
	}
	virtual ~ClassObsWrapTemplate()  {
		std::cerr << "ClassObsWrapTemplate destroy " << mName << std::endl ;
	}

    virtual void update(Tsubject& subject) {
    	std::cerr << mName << ": " ;
    	mParent->update(subject) ;
    }
    virtual const char* name() const {return mName.c_str();};

    virtual std::shared_ptr<Tsubject> getSubject() {
    	return mSubject ;
    }

private:
    Tparent* mParent;
    std::string mName ;
    std::shared_ptr<Tsubject> mSubject ;
};

template<typename Tparent, typename Tsubject>
inline std::shared_ptr<ClassObsWrapTemplate<Tparent, Tsubject>>
make_observerWrapper(Tparent* parent, const std::string& name, std::shared_ptr<Tsubject> subject)
{
	std::shared_ptr<ClassObsWrapTemplate<Tparent, Tsubject>> observer(
		new ClassObsWrapTemplate<Tparent, Tsubject>(parent, name, subject)
	) ;
	return observer ;
}


class ClassObsArray :public IClassObs
{
public:
	ClassObsArray() {}
	virtual ~ClassObsArray() {
		for (auto obs : mObservers)
		{
		}
	}
	virtual void doSomething() override {
		std::cerr << "ClassObsArray" << std::endl ;
	}

    virtual void update(IClassSubject& subject) {
    	std::cerr << "== ClassObsArray ==" << std::endl ;
    	subject.doSomething() ;
    }
    virtual const char* name() const {return "ClassObsArray";};

    virtual void addSubject(std::shared_ptr<IClassSubject> subject) {
    	std::shared_ptr<ClassObsWrap> observer(new ClassObsWrap(this, "ClassObsArray wrapper" + std::to_string(mObservers.size())) ) ;
    	mObservers.push_back(observer) ;

    	std::shared_ptr<Subject<IClassSubject>> ss( std::dynamic_pointer_cast<Subject<IClassSubject>>(subject) ) ;
    	ss->attach(*observer) ;
    }

    std::vector< std::shared_ptr<ClassObsWrap> > mObservers ;
};


class ClassObsArrayTemplated :public IClassObs
{
public:
	ClassObsArrayTemplated() {}
	virtual ~ClassObsArrayTemplated() {
		for (auto obs : mObservers)
		{
	    	std::shared_ptr<Subject<IClassSubject>> ss( std::dynamic_pointer_cast<Subject<IClassSubject>>(obs->getSubject()) ) ;
			ss->detach(*obs) ;
		}
	}
	virtual void doSomething() override {
		std::cerr << "ClassObsArrayTemplated" << std::endl ;
	}

    virtual void update(IClassSubject& subject) {
    	std::cerr << "== ClassObsArrayTemplated ==" << std::endl ;
    	subject.doSomething() ;
    }
    virtual const char* name() const {return "ClassObsArrayTemplated";};

    virtual void addSubject(std::shared_ptr<IClassSubject> subject) {

    	std::string name("ClassObsArrayTemplated wrapper" + std::to_string(mObservers.size())) ;

    	std::shared_ptr<ClassObsWrapTemplate<IClassObs, IClassSubject>> observer(
    		new ClassObsWrapTemplate<IClassObs, IClassSubject>(this, name, subject)
    	) ;
    	mObservers.push_back(observer) ;

//    	mObservers.push_back(make_observerWrapper(dynamic_cast<IClassObs*>(this), name, subject)) ;

//    	std::shared_ptr<ClassObsWrapTemplate<IClassObs, IClassSubject>> observer(
//    			make_observerWrapper( dynamic_cast<IClassObs*>(this), name, subject)
//    	) ;
//    	mObservers.push_back(observer) ;

    	std::shared_ptr<Subject<IClassSubject>> ss( std::dynamic_pointer_cast<Subject<IClassSubject>>(subject) ) ;
    	ss->attach(*observer) ;
    }

    std::vector< std::shared_ptr<ClassObsWrapTemplate<IClassObs, IClassSubject>> > mObservers ;
};



//-------------------------------------------------------------------------------------------------------------
TEST(Observer, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	ClassSubject subject ;
	ClassObs observer ;

	subject.attach(observer) ;

	subject.runIt() ;
	subject.runIt() ;

	subject.detachAll() ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(Observer, Pointers)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IClassSubject> subject(new ClassSubjectX) ;
	ClassObs observer ;

	std::shared_ptr<Subject<IClassSubject>> ss( std::dynamic_pointer_cast<Subject<IClassSubject>>(subject) ) ;
	ss->attach(observer) ;

	std::shared_ptr<ClassSubjectX> s(std::dynamic_pointer_cast<ClassSubjectX>(subject)) ;
	s->runIt() ;
	s->runIt() ;

	ss->detachAll() ;
}



//-------------------------------------------------------------------------------------------------------------
TEST(Observer, Array)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::shared_ptr<IClassSubject> subject1(new ClassSubjectX) ;
	std::shared_ptr<IClassSubject> subject2(new ClassSubjectY) ;
	ClassObsArray observer ;

	observer.addSubject(subject1) ;
	observer.addSubject(subject2) ;

	std::shared_ptr<ClassSubjectX> s1(std::dynamic_pointer_cast<ClassSubjectX>(subject1)) ;
	s1->runIt() ;
	s1->runIt() ;
	std::shared_ptr<ClassSubjectY> s2(std::dynamic_pointer_cast<ClassSubjectY>(subject2)) ;
	s2->runIt() ;
	s2->runIt() ;

//	ss->detachAll() ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(Observer, ArrayTemplated)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::shared_ptr<IClassSubject> subject1(new ClassSubjectX) ;
	std::shared_ptr<IClassSubject> subject2(new ClassSubjectY) ;
	ClassObsArrayTemplated observer ;

	observer.addSubject(subject1) ;
	observer.addSubject(subject2) ;

	std::shared_ptr<ClassSubjectX> s1(std::dynamic_pointer_cast<ClassSubjectX>(subject1)) ;
	s1->runIt() ;
	s1->runIt() ;
	std::shared_ptr<ClassSubjectY> s2(std::dynamic_pointer_cast<ClassSubjectY>(subject2)) ;
	s2->runIt() ;
	s2->runIt() ;

//	ss->detachAll() ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(Observer, BasicData)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	ClassSubjectData subject(std::map<std::string, unsigned>{
		{"one", 1},
		{"two", 2},
	}) ;
	ClassObsData observer ;

	subject.attach(observer) ;

	subject.runIt() ;
	subject.runIt() ;

	subject.detachAll() ;
}
