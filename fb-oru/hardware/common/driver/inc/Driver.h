/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Driver.h
 * \brief     Common implementation of a driver
 *
 *
 * \details   Common implementation of a driver
 *
 */


#ifndef COMMON_DRIVER_H_
#define COMMON_DRIVER_H_

#include <vector>
#include <string>
#include <memory>

#include "GlobalTypeDefs.h"
#include "IDriver.h"
#include "IRegData.h"

namespace Mplane {

/*!
 * \class  Driver
 * \brief
 * \details
 *
 */
class Driver : public virtual IDriver
{
public:
	virtual ~Driver();

    /**
     * Get driver name
     *
     * @return Name of the driver instance.
     */
    virtual std::string getName() const override;

protected:

    Driver(const std::string& name);

	// Allow derived class access to register init data
	std::shared_ptr<IRegData> regData() ;

private:
    /**
     * the sub class driver name.
     */
    std::string mName;

    /**
     * Pointer to register init data
     */
    std::shared_ptr<IRegData> mRegData;

} ;

}

#endif /* COMMON_DRIVER_H_ */
