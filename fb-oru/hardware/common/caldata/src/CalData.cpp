/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CalData.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

//#include "Benchmark.h"
#include "ICalData.h"
#include "CalData.h"
#include "ICalDownloadManagement.h"
#include <memory>
using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CalData::CalData():
	mRxCalDownload( new RxCalDownload() ),
	mRxIfCalDownload( new RxIfCalDownload() ),
	mSRxCalDownload( new SRxCalDownload() ),
    mSwrCalDownload( new SwrCalDownload() ),
	mTxCalDownload( new TxCalDownload() ),
	mTxIfCalDownload( new TxIfCalDownload()),
	mTxDCOffsetCalDownload( new TxDCOffsetCalDownload() ),
	mTxQuadOffsetCalDownload( new TxQuadOffsetCalDownload() ),
	mTxVVACalDownload( new TxVVACalDownload() ),
	mPaDetCalDownload( new PaDetCalDownload() ),
	mPamCalDownload( new PamCalDownload() ),
	mTxcal(),
	mRxcal(),
	mRxIfcal(),
	mTxIfcal(),
	mSRxcal(),
	mTxDCOffsetCal(),
	mTxQuadOffsetCal(),
	mTxVVACal(),
	mPaDetCal(),
	mRxAgccal(),
	mPamCal(),
	mIsLoaded( false )
{
    /**
     * Tell the calibration data download manager about the three extended calibration
     * download tasks that we support. This will initialise the paths supported by each type
     */

    ICalDownloadManagement::getInstance()->addCalDownloadType( mRxCalDownload );
    ICalDownloadManagement::getInstance()->addCalDownloadType( mRxIfCalDownload );
    ICalDownloadManagement::getInstance()->addCalDownloadType( mSRxCalDownload );
    ICalDownloadManagement::getInstance()->addCalDownloadType( mSwrCalDownload );
    ICalDownloadManagement::getInstance()->addCalDownloadType( mTxCalDownload );
    ICalDownloadManagement::getInstance()->addCalDownloadType( mTxIfCalDownload );
    ICalDownloadManagement::getInstance()->addCalDownloadType( mTxDCOffsetCalDownload );
    ICalDownloadManagement::getInstance()->addCalDownloadType( mTxQuadOffsetCalDownload );
    ICalDownloadManagement::getInstance()->addCalDownloadType( mTxVVACalDownload );
    ICalDownloadManagement::getInstance()->addCalDownloadType( mPaDetCalDownload );
    ICalDownloadManagement::getInstance()->addCalDownloadType( mPamCalDownload );


    /**
     * Now that we have the download objects and their paths are set, pass them into the
     * calibration data handler objects so that they can supply the correct path to the
     * calibration data files.
     */

    mTxcal = std::make_shared<TxCalData>(mTxCalDownload) ;
    mRxcal = std::make_shared<RxCalData>(mRxCalDownload) ;
    mRxIfcal = std::make_shared<RxIfCalData>(mRxIfCalDownload) ;
    mTxIfcal = std::make_shared<TxIfCalData>(mTxIfCalDownload) ;
    mSRxcal = std::make_shared<SRxCalData>(mSRxCalDownload) ;
    mSwrcal = std::make_shared<SwrCalData>(mSwrCalDownload) ;
    mTxDCOffsetCal = std::make_shared<TxDCOffsetCalData>( mTxDCOffsetCalDownload );
    mTxQuadOffsetCal = std::make_shared<TxQuadOffsetCalData>( mTxQuadOffsetCalDownload );
    mTxVVACal = std::make_shared<TxVVACalData>( mTxVVACalDownload );
    mPaDetCal = std::make_shared<PaDetCalData>( mPaDetCalDownload );
    mPamCal = std::make_shared<PamCalData>( mPamCalDownload );

    // RX AGC uses the rxcal file
    mRxAgccal = std::make_shared<RxAgcCalData>(mRxCalDownload) ;
}


//-------------------------------------------------------------------------------------------------------------
ReturnType::State CalData::load()
{
//    std::shared_ptr<Benchmark> bench(Benchmark::getInstance()) ;
//    bench->start("cal-load") ;

//    bench->start("txcal-load") ;
    mTxcal->load();
//    std::cerr << "CAL Load txcal : " << bench->stop("txcal-load") << std::endl ;

//    bench->start("rxcal-load") ;
    mRxcal->load();
//    std::cerr << "CAL Load rxcal : " << bench->stop("rxcal-load") << std::endl ;

//    bench->start("rxifcal-load") ;
    mRxIfcal->load();
//    std::cerr << "CAL Load rxifcal : " << bench->stop("rxifcal-load") << std::endl ;

//    bench->start("txifcal-load") ;
	mTxIfcal->load();
//    std::cerr << "CAL Load txifcal : " << bench->stop("txifcal-load") << std::endl ;

//    bench->start("srxcal-load") ;
    mSRxcal->load();
//    std::cerr << "CAL Load srxcal : " << bench->stop("srxcal-load") << std::endl ;

//    bench->start("swcal-load") ;
    mSwrcal->load();
//    std::cerr << "CAL Load swcal : " << bench->stop("swcal-load") << std::endl ;

//    bench->start("txdccal-load") ;
    mTxDCOffsetCal->load();
//    std::cerr << "CAL Load txdccal : " << bench->stop("txdccal-load") << std::endl ;

//    bench->start("txquadcal-load") ;
    mTxQuadOffsetCal->load();
//    std::cerr << "CAL Load txquadcal : " << bench->stop("txquadcal-load") << std::endl ;

//    bench->start("txvvacal-load") ;
    mTxVVACal->load();
//    std::cerr << "CAL Load txvvacal : " << bench->stop("txvvacal-load") << std::endl ;

//    bench->start("pamdetcal-load") ;
    mPaDetCal->load();
//    std::cerr << "CAL Load pamdetcal : " << bench->stop("pamdetcal-load") << std::endl ;

//    bench->start("agccal-load") ;
    mRxAgccal->load();
//    std::cerr << "CAL Load agccal : " << bench->stop("agccal-load") << std::endl ;

//    bench->start("pamcal-load") ;
    mPamCal->load();
//    std::cerr << "CAL Load pamcal : " << bench->stop("pamcal-load") << std::endl ;

//    std::cerr << "CAL Load Total : " << bench->stop("cal-load") << std::endl ;

    mIsLoaded = true;

    return ReturnType::RT_OK;   // ignore errors for now as unit may or maynot have cal data.
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ITxCalData> CalData::getTxCal()
{
    return mTxcal;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRxCalData> CalData::getRxCal()
{
    return mRxcal;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IPamCalData> CalData::getPamCal()
{
    return mPamCal;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRxIfCalData> CalData::getRxIfCal()
{
    return mRxIfcal;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ITxIfCalData> CalData::getTxIfCal()
{
	return mTxIfcal;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISRxCalData> CalData::getSRxCal()
{
    return mSRxcal;
}

std::shared_ptr<ISwrCalData> Mplane::CalData::getSwrCal()
{
    return mSwrcal;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<TxDCOffsetCalData> CalData::getTxDCOffsetCal()
{
    return mTxDCOffsetCal;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<TxQuadOffsetCalData> CalData::getTxQuadOffsetCal()
{
    return mTxQuadOffsetCal;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<TxVVACalData> CalData::getTxVVACal()
{
    return mTxVVACal;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<PaDetCalData> CalData::getPaDetCal()
{
    return mPaDetCal;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRxAgcCalData> CalData::getRxAgcCal()
{
    return mRxAgccal;
}



//-------------------------------------------------------------------------------------------------------------
CalData::~CalData()
{
}

//-------------------------------------------------------------------------------------------------------------
bool CalData::isLoaded()
{
    return mIsLoaded;
}
