/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioControlTestFactorys.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "CommonRadio.h"


#include "ITxPort.h"
#include "IRxPort.h"
#include "IRadioInfo.h"

#include "CommonRxPort.h"
#include "CommonTxPort.h"
#include "CommonAdc.h"
#include "CommonAttenuator.h"
#include "CommonDac.h"
#include "CommonSynth.h"

#include <vector>

#include "IAppControl.h"

#include "EgAppControl.h"

#include "CommonRadio.h"
#include "CommonServices.h"

#include "RadioControlTestCase.h"

#include "TestCommonRadio.h"

using namespace Mplane;
using namespace std;

std::shared_ptr<IAppControl> IAppControlFactory::getInterface()
{
    static std::shared_ptr<IAppControl> radioControl(new TestRadioControl());
    return radioControl;
}

std::shared_ptr<IServicesCtl> IServicesFactory::create()
{
    static std::shared_ptr<IServicesCtl> iServicesCtl(new CommonServices());

    return iServicesCtl;
}
