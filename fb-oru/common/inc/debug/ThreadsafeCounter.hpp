/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ThreadsafeCounter.hpp
 * \brief     Non-thread counter for SharedPtr
 *
 *
 * \details   A reference counter for SharedPtr that is thread safe.
 *
 * The counter relies on the SharedPtr to manage whether it needs to create a counter (and mutex) on the heap
 * or delete the counter when everything has finished. It's important that the counter and mutex are heap based
 * so that multiple instances of this object can all point to the same entities.
 *
 */


#ifndef THREADSAFECOUNTER_HPP_
#define THREADSAFECOUNTER_HPP_

class ThreadsafeCounter
{
public:
    ThreadsafeCounter () :
    	counter(NULL),
    	mutex(NULL)
    {
    }

    // default copy constructor and copy-assignment operator
    // are fine in that they just copy the shared counter

public:
    //initialize its value to one:
    void init ()
    {
    	if (mutex)
    		delete mutex ;
   		mutex = new Mutex() ;

   		if (counter)
    		delete counter ;
    	counter = new unsigned(1) ;
    }

    // dispose of the counter:
    void dispose ()
    {
    	{
			Mutex::Lock lock( *mutex ) ;
			delete counter ;
			counter = NULL ;
    	}

    	delete mutex ;
    	mutex = NULL ;
    }

    // increment by one:
    void increment ()
    {
    	Mutex::Lock lock( *mutex ) ;
        ++*counter;
    }

    // decrement by one:
    void decrement ()
    {
    	Mutex::Lock lock( *mutex ) ;
        --*counter;
    }

    // test for zero:
    bool is_zero ()
    {
    	Mutex::Lock lock( *mutex ) ;
        return *counter == 0;
    }

    // testing
    const unsigned _get_count () const
    {
    	Mutex::Lock lock( *mutex ) ;
    	if (!counter)
    		return 0 ;
        return *counter ;
    }

private:
    unsigned *counter;
    Mutex *mutex;

};



#endif /* THREADSAFECOUNTER_HPP_ */
