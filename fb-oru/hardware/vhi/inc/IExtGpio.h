/*
 * \file      IRef.h
 * \brief     Virtual interface to external GPIO
 *
 *
 * \details   The 10MHz ref board consists both of an internal GPIO device and this external GPIO device
 */

#ifndef IEXTGPIO_H_
#define IEXTGPIO_H_

#include <memory>
#include <bitset>
#include "GlobalTypeDefs.h"

namespace Mplane
{

/*! \brief  Generic IExtGpio interface
 *
 *  The 10MHz ref board consists both of an internal GPIO device and this external GPIO device
 */
class IExtGpio
{
public:
    IExtGpio() { };

    /*! \brief Destructor
     *
     */
    virtual ~IExtGpio() { };

    /**
     * Singleton
     */
    static std::shared_ptr<IExtGpio> getInterface();

	/**
	 * Activate/deactivate GPIO output
	 */
    virtual bool setGpio(unsigned gpio, bool enable) =0 ;

	/**
	 * Read GPIO input
	 */
    virtual bool getGpio(unsigned gpio) =0 ;

	/**
	 * Activate/deactivate GPIO output. Uses bitset 0:7 to set/clear GPIO 0:7. Mask bits
	 * are used to allow the change of specific output bits. If the mask bit is true then
	 * the output will be changed; if mask bit is false then it will not
	 */
    virtual bool setGpio(const std::bitset<8>& outBits, const std::bitset<8>& outMask) =0 ;

	/**
	 * Read GPIO input. Reads GPIO 4:7 and maps them to bitset 0:3
	 */
    virtual bool getGpio(std::bitset<4>& inBits) =0 ;



    /*! \brief  The initialise method
     *
     *  Method called during system startup.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise() =0 ;


};

} /* namespace Mplane */




#endif /* IEXTGPIO_H_ */
