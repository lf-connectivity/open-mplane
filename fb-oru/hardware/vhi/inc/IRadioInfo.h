/*
 * RadioInfo.h
 *
 *  Created on: 15 Jun 2013
 *      Author: gdurban
 */

#ifndef VRH_RADIOINFO_H_
#define VRH_RADIOINFO_H_
#include <memory>

namespace Mplane
{

/**
 * The board information interface returns data commonly associated with
 * all radio stype, for example, its unique ID, its serial number etc.
 */
class IRadioInfo
{
public:

    /**
     * Method used to return the unit hardware ID of the radio board.
     * @return
     */
	virtual unsigned int getHardwareID() = 0;

	virtual ~IRadioInfo() {};

};

/**
 * Factory used to create the polymorphic radio information interface.
 */
class IRadioInfoFactory
{
public:
    /**
     * Method used to create the board information interface for a specific
     * radio type.
     * @return a pointer to the board information interface.
     */
    static std::shared_ptr<IRadioInfo> create();
};

} /* namespace Mplane */

#endif /* VRH_RADIOINFO_H_ */
