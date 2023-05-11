/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SharedCounter.hpp
 * \brief     Non-thread counter for SharedPtr
 *
 *
 * \details   A reference counter for SharedPtr that is *not* thread safe (and therefore more efficient)
 *
 */


#ifndef SHAREDCOUNTER_HPP_
#define SHAREDCOUNTER_HPP_

class SharedCounter
{
public:
    SharedCounter () :
    	counter(NULL)
    {
    }

    // default copy constructor and copy-assignment operator
    // are fine in that they just copy the shared counter

public:
    //initialize its value to one:
    void init ()
    {
    	if (counter)
    		delete counter ;
    	counter = new unsigned(1) ;
    }

    // dispose of the counter:
    void dispose ()
    {
    	delete counter ;
    	counter = NULL ;
    }

    // increment by one:
    void increment ()
    {
        ++*counter;
    }

    // decrement by one:
    void decrement ()
    {
        --*counter;
    }

    // test for zero:
    bool is_zero ()
    {
        return *counter == 0;
    }

    // testing
    const unsigned _get_count () const
    {
    	if (!counter)
    		return 0 ;
        return *counter ;
    }

private:
    unsigned *counter;

};



#endif /* SHAREDCOUNTER_HPP_ */
