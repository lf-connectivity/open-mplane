/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISystemSynth.h
 * \brief     Virtual interface to system synth
 *
 *
 * \details   NOTE: The ISynth class isn't actual virtual because it's derived from a concrete class Device (which is
 * 				really annoying but there's not much we can do at the moment unless we untangle the whole mess)
 *
 */


#ifndef VHI_INC_ISYSTEMSYNTH_H_
#define VHI_INC_ISYSTEMSYNTH_H_

#include <memory>
#include "ISynth.h"

namespace Mplane {

/*!
 * \class  ISystemSynth
 * \brief
 * \details
 *
 */
class ISystemSynth : public virtual ISynth {
public:
	ISystemSynth() {}
	virtual ~ISystemSynth() {}

	/**
	 * Create the instance
	 */
	static std::shared_ptr<ISystemSynth> makeInstance(unsigned deviceIndex, const std::string& name = "SystemSynth") ;


    /*! \brief  The doInit method
     *
     *  Method called by the initialise() method in Initialise.
     *  This is pure virtual and MUST be implemented by inheritors.
     *
     *  Means that this CommonSynth class does not provide any synth-type specific
     *  initialisation. That is left to the inheritors who know what
     *  device they are.
     *
     *  The implementation is expected to set the following before returning:
     *  mInitResult - eg. to ReturnType::RT_OK if all is ok
     *  mInitResultString - eg. to "SYNTH INITIALISED OK" if all is ok
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State doInit() =0;

    /*! \brief  Program the synthesiser
     *
     *  Method to program the synthesiser, either to its fixed default frequency,
     *  or the frequency specified.
     *
     *  Pure virtual because programming a synth is not a common
     *  procedure and is board and synth type specific, but we know we need
     *  to program it to set the frequency, so this forces the
     *  implementation to provide the program procedure.
     *
     *  \return state of RT_OK if synthesiser is locked OK, RT_other if not.
     */
    virtual ReturnType::State program() =0;


} ;

}

#endif /* VHI_INC_ISYSTEMSYNTH_H_ */
