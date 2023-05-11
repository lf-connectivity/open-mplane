/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestArtUut.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#include "TestArtUut.h"
#include "ICpriController.h"
#include "ICpriCore.h"

Mplane::TestArtUut::TestArtUut()
{
}

bool Mplane::TestArtUut::isConnected()
{
    return false;
}

std::string Mplane::TestArtUut::getIpAddress()
{
    return "0.0.0.0";
}

Mplane::TestArtUut::~TestArtUut()
{
}

void Mplane::TestArtUut::update(ICpriPortHandler& subject)
{
}

std::string Mplane::TestArtUut::getCpriLineRate()
{
    return "";
}

const char* Mplane::TestArtUut::name() const
{
    return "ArtUut";
}

bool Mplane::TestArtUut::setCpriLineRate(int lineRate)
{
    return true;
}

void Mplane::TestArtUut::setIPAddress(std::string ipAddr)
{
}

void Mplane::TestArtUut::cpriL1Reset()
{
}
