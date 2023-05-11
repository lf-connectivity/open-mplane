/*
 * CommonRadioInfo.h
 *
 *  Created on: 15 Jun 2013
 *      Author: gdurban
 */

#ifndef COMMONRADIOINFO_H_
#define COMMONRADIOINFO_H_

#include "IRadioInfo.h"

namespace Mplane
{

/**
 * Class used to obtain basic radio information such as hardware identifier,
 * serial number etc.
 *
 * This class may be extended by a radio specific implementation.
 *
 * @note it should only be created through the appropriate implementation
 * of the IRadioInofFactory::create() method.
 *
 */
class CommonRadioInfo: public IRadioInfo
{

public:

    /**
     * Return the hardware ID read from the radio.
     * @return
     */
	virtual unsigned int getHardwareID();

	CommonRadioInfo();

	virtual ~CommonRadioInfo();

};

} /* namespace Mplane */

#endif /* COMMONRADIOINFO_H_ */
