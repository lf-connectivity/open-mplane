/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IOranDelays.h
 * \brief     Oran Delays virtual interface
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef _VYMS_INC_IORANDELAYS_H_
#define _VYMS_INC_IORANDELAYS_H_

#include <memory>
#include <vector>

#include "Frequency.h"
#include "Zcu111Delay.h"
#include "GlobalTypeDefs.h"

namespace Mplane
{
class IOranDelays {
 public:
  typedef enum {
    _25G_CLOCK,
    _10G_CLOCK,
  } DelayClock_T;

  static std::shared_ptr<IOranDelays> getOranDelaysSingleton(
      IOranDelays::DelayClock_T delayClock);

  virtual Zcu111Delay CalcT2aMinUp(Frequency bandwidth) = 0; //!> Calculate T2a
                                                             //! Min Uplink (ns)
  virtual Zcu111Delay CalcT2aMaxUp(Frequency bandwidth) = 0; //!> Calculate T2a
                                                             //! Max Uplink (ns)
  virtual Zcu111Delay CalcTcpAdvDl(Frequency bandwidth) = 0; //!> Calculate TCP
                                                             //! advance
                                                             //! Downlink (ns)
  virtual Zcu111Delay CalcT2aMinCpDl(Frequency bandwidth) = 0; //!> Calculate
                                                               //! T2a Min CP
                                                               //! Downlink (ns)
  virtual Zcu111Delay CalcT2aMaxCpDl(Frequency bandwidth) = 0; //!> Calculate
                                                               //! T2a Max CP
                                                               //! Downlink (ns)
  virtual Zcu111Delay CalcTa3Min(Frequency bandwidth) = 0; //!> Calculate Ta3
                                                           //! Min (ns)
  virtual Zcu111Delay CalcTa3Max(Frequency bandwidth) = 0; //!> Calculate Ta3
                                                           //! Max (ns)
  virtual Zcu111Delay CalcT2aMinCpUl(Frequency bandwidth) = 0; //!> Calculate
                                                               //! T2a Min CP
                                                               //! Uplink (ns)
  virtual Zcu111Delay CalcT2aMaxCpUl(
      Frequency bandwidth, //!> Calculate T2a Min CP Uplink (ns)
      Frequency subCarrierSpacing) = 0;

  virtual UINT32 getNumSupportedAirStdBw(void) = 0;
  virtual UINT32 getNumSupportedScsSpacing(void) = 0;

  virtual void getSupportedAirStdBw(
      std::vector<Frequency>& supportedAirStdBw) = 0;
  virtual void getSupportedScsSpacing(
      std::vector<Frequency>& supportedScsSpacing) = 0;

  virtual ~IOranDelays() {}
};
}

#endif /* _VYMS_INC_IORANDELAYS_H_ */
