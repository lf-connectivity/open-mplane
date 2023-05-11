/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestICpriPortHandler.cpp
 * \brief     Implementation of the CPRI port handler interface ICpriPortHandler class
 *
 *
 * \details   This file defines the stub implementation of the CPRI port handler
 *            interface ICpriPortHandler class.
 *
 */

#include "TestICpriPortHandler.h"

using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
// Factory for port handlers
std::shared_ptr<ICpriPortHandler> ICpriPortHandler::factory(unsigned port, std::shared_ptr<ICpriSfpControlLogic> sfpLogic)
{
	return std::shared_ptr<ICpriPortHandler>( new TestICpriPortHandler(port) ) ;
}

Mplane::TestICpriPortHandler::TestICpriPortHandler(UINT32 instance) :
	mPort ( instance ),
	mPortLogicallyEnabled(false),
	mCpriLinkState ( false ),
	mLastSmStateChanged ( false ),
	mCpriPmre ( 1 ),   // default to having 1 master port
	mCpriReId ( 0 ),
	mCpriLinkId ( 0 ),
	mMasterMode( mPort == 0 ? false : true )	// 0=slave; 1=master

{
    ICpriCore::CpriPortStatus portStatus;

    portStatus.logicallyEnabled = false;
    portStatus.active = false;
    portStatus.mgtPllLock = false;
    portStatus.mgtTxClockLock = false;
    portStatus.mgtRxClockLock = false;
    portStatus.lineRate = ICpriCore::RateUnknown;
    portStatus.ethernetMinCMBandwidth = ICpriCore::CMRateUnknown;
    portStatus.ethernetMaxCMBandwidth = ICpriCore::CMRateUnknown;
    portStatus.protocolVersion = 0;
    portStatus.remoteSapDefect = false;
    portStatus.remoteLossOfFrame = false;
    portStatus.remoteLossOfSync = false;
    portStatus.sfpLos = true;  // start with no fibre connected
    portStatus.localLossOfFrame = false;
    portStatus.localLossOfSync = false;

    mCurrentPortStatus = portStatus;
}

Mplane::TestICpriPortHandler::~TestICpriPortHandler() {
}


//==================================================================================================
// Test Interface

void Mplane::TestICpriPortHandler::testInjectPortStatus(
		const ICpriCore::CpriPortStatus portStatus) {

	mLastSmStateChanged = hasPortStatusChanged(portStatus) ;
	mCurrentPortStatus = portStatus ;
}

void Mplane::TestICpriPortHandler::testInjectLinkState(const bool linkState) {
	mCpriLinkState = linkState ;
}

void Mplane::TestICpriPortHandler::testInjectPmre(const UINT32 pmre) {
	mCpriPmre = pmre ;
}

void Mplane::TestICpriPortHandler::testInjectLinkId(const UINT32 linkId) {
	mCpriLinkId = linkId ;
}

void Mplane::TestICpriPortHandler::testInjectReId(const UINT32 reId) {
	mCpriReId = reId ;
}

void Mplane::TestICpriPortHandler::testInjectSetStateChange(bool state) {
    mLastSmStateChanged = state ;
}

void Mplane::TestICpriPortHandler::testInjectSetMasterMode(bool master) {
	mMasterMode = master ;
}


//==================================================================================================
// ICpriPortHandler Interface
void Mplane::TestICpriPortHandler::show(std::ostream& os)
{
    os << "TestICpriPortHandler show - Port " << mPort <<  std::endl;
}

bool Mplane::TestICpriPortHandler::isSlave() {
	// 0=slave; 1=master
	return !mMasterMode ;
}

bool Mplane::TestICpriPortHandler::isMaster() {
	// 0=slave; 1=master
	return mMasterMode ;
}

ICpriCore::CpriPortStatus Mplane::TestICpriPortHandler::getLinkStatus() {
    return mCurrentPortStatus;
}

bool Mplane::TestICpriPortHandler::isLinkUp() {
    return mCpriLinkState;
}

bool Mplane::TestICpriPortHandler::isLinkOK(
		ICpriCore::CpriPortStatus portStatus) {
    bool linkActive = true;  // be optimistic, the most likely outcome

    /* NOTE: SAP defect Indication (SDI) is not considered a fault that should
     * take down the slave link. The fault handling system will handle the response to all detected faults
     * and may decide to block the Tx as it is an indication that IQ data is potentially invalid.
     *
     * The Master link is considered up if SDI bit is set on master.
     */

    if ( !portStatus.logicallyEnabled ||
         !portStatus.active ||
         portStatus.remoteLossOfFrame ||
         portStatus.remoteLossOfSync  ||
         portStatus.localLossOfFrame  ||
         portStatus.localLossOfSync )
    {
        linkActive = false;
    }

    return linkActive;
}

UINT32 Mplane::TestICpriPortHandler::getPort() {
	return mPort ;
}

UINT32 Mplane::TestICpriPortHandler::getPmre() {
	return mCpriPmre ;
}

UINT32 Mplane::TestICpriPortHandler::getReId() {
	return mCpriReId ;
}

UINT32 Mplane::TestICpriPortHandler::getLinkId() {
	return mCpriLinkId ;
}

bool Mplane::TestICpriPortHandler::getSlaveOamLinkState() {
	return false ;
}

bool Mplane::TestICpriPortHandler::getSlaveLastOamLinkState() {
	return false ;
}


bool Mplane::TestICpriPortHandler::hasStateChanged() {
    return mLastSmStateChanged;
}


bool Mplane::TestICpriPortHandler::hasPortStatusChanged(ICpriCore::CpriPortStatus portStatus) {
    // Return true when any element of the port status has changed

    return (mCurrentPortStatus.logicallyEnabled       != portStatus.logicallyEnabled ||
            mCurrentPortStatus.active                 != portStatus.active ||
            mCurrentPortStatus.lineRate               != portStatus.lineRate ||
            mCurrentPortStatus.ethernetMinCMBandwidth != portStatus.ethernetMinCMBandwidth ||
            mCurrentPortStatus.ethernetMaxCMBandwidth != portStatus.ethernetMaxCMBandwidth ||
            mCurrentPortStatus.protocolVersion        != portStatus.protocolVersion   ||
            mCurrentPortStatus.remoteSapDefect        != portStatus.remoteSapDefect   ||
            mCurrentPortStatus.remoteLossOfFrame      != portStatus.remoteLossOfFrame ||
            mCurrentPortStatus.remoteLossOfSync       != portStatus.remoteLossOfSync  ||
            mCurrentPortStatus.mgtPllLock             != portStatus.mgtPllLock        ||
            mCurrentPortStatus.mgtTxClockLock         != portStatus.mgtTxClockLock    ||
            mCurrentPortStatus.mgtRxClockLock         != portStatus.mgtRxClockLock    ||
            mCurrentPortStatus.sfpLos                 != portStatus.sfpLos            ||
            mCurrentPortStatus.localLossOfFrame       != portStatus.localLossOfFrame  ||
            mCurrentPortStatus.localLossOfSync        != portStatus.localLossOfSync);

}

void Mplane::TestICpriPortHandler::show() {
}

void Mplane::TestICpriPortHandler::initialisePortStatus() {
}

bool Mplane::TestICpriPortHandler::stateMachine() {
	return true ;
}

void Mplane::TestICpriPortHandler::showSmState() {
}

void Mplane::TestICpriPortHandler::start() {
}

void Mplane::TestICpriPortHandler::resetPort() {
}

void Mplane::TestICpriPortHandler::setPortLineRateCapability(
		ICpriTypes::cpriRateCapabilityMask rateMask) {
}

void Mplane::TestICpriPortHandler::configSlavePort(
		ICpriCore::LineRate lineRate, ICpriCore::TxFormat txFormat) {
}

ICpriPortHandler::CpriSMStates Mplane::TestICpriPortHandler::getSmState() {
	return ICpriPortHandler::STATE_GOOD ;
}

void Mplane::TestICpriPortHandler::initPort() {
}

void Mplane::TestICpriPortHandler::setSlaveLastOamLinkState() {
}

void Mplane::TestICpriPortHandler::enableReset() {
}

void Mplane::TestICpriPortHandler::disableReset() {
}

void Mplane::TestICpriPortHandler::enableMasterPort(
		std::shared_ptr<ICpriCore> slaveCore) {
}

void Mplane::TestICpriPortHandler::disableMasterPort() {
}

bool Mplane::TestICpriPortHandler::changePortMode(
		ICpri::CpriPortType cpriPortType) {
	return true ;
}

bool Mplane::TestICpriPortHandler::setFixedLineRate(
		ICpriCore::LineRate lineRate) {
	return true ;
}
//==================================================================================================
