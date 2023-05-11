#ifndef _ETNA_FTU_CALDATA_H_
#define _ETNA_FTU_CALDATA_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CalData.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */
#include <memory>

#include "ICalData.h"

#include "IRxAgcCalData.h"
#include "IRxCalData.h"
#include "IRxIfCalData.h"
#include "ISRxCalData.h"
#include "ISwrCalData.h"
#include "IPamCalData.h"
#include "ITxIfCalData.h"
#include "ITxIfCal.h"
#include "ITxCalData.h"
#include "ITxCal.h"

#include "TxCalData.h"
#include "RxCalData.h"
#include "RxIfCalData.h"
#include "TxIfCalData.h"
#include "RxAgcCalData.h"
#include "SRxCalData.h"
#include "SwrCalData.h"
#include "TxDCOffsetCal.h"
#include "TxQuadCal.h"
#include "RxCalDownload.h"
#include "RxIfCalDownload.h"
#include "SRxCalDownload.h"
#include "SwrCalDownload.h"
#include "TxCalDownload.h"
#include "TxIfCalDownload.h"
#include "TxDCOffsetCalDownload.h"
#include "TxQuadCalDownload.h"
#include "TxVVACal.h"
#include "TxVVACalDownload.h"
#include "PaDetCal.h"
#include "PaDetCalDownload.h"
#include "PamCalData.h"
#include "PamCalDownload.h"


namespace Mplane
{


class CalData: public ICalData,
	public IRxCalDataContainer,
	public IRxIfCalDataContainer,
	public ISRxCalDataContainer,
    public ISwrCalDataContainer,
	public IRxAgcCalDataContainer,
	public ITxIfCalDataContainer,
	public ITxCalDataContainer
{
public:

    /**
     * Simple constructor
     */
    CalData();

    /**
     * Method called during radio initialisation to load the various calibration
     * data files used by the various calibration data interfaces and populate the
     * ITxCal and IRxCal interface implementations.
     * @return
     */
    virtual ReturnType::State load();

    /**
     * Method used to indicate that the application has loaded its calibration data
     * @return
     */
    virtual bool isLoaded();

    /**
     * Method used to return an interface to calibration data interface associated with
     * the Tx path.
     * @return reference to the Tx path calibration data interface
     */
    virtual std::shared_ptr<ITxCalData> getTxCal();

    /**
     * Method used to return an interface to calibration data interface associated with
     * the Rx path.
     * @return reference to the Rx path calibration data interface
     */
    virtual std::shared_ptr<IRxCalData> getRxCal();

    /**
     * Method used to return an interface to calibration data interface associated with
     * the PAM.
     * @return reference to the PAM calibration data interface
     */
    virtual std::shared_ptr<IPamCalData> getPamCal();

    /**
     * Method used to return an interface to calibration data interface associated with
     * the Rx path.
     * @return reference to the Rx path calibration data interface
     */
    virtual std::shared_ptr<IRxIfCalData> getRxIfCal();

    /**
     * Method used to return an interface to calibration data interface associated with
     * the Tx path.
     * @return reference to the Tx path calibration data interface
     */
    virtual std::shared_ptr<ITxIfCalData> getTxIfCal();

     /**
      * Method used to return an interface to calibration data interface associated with
      * the SRx path.
      * @return reference to the SRx path calibration data interface
      */
     std::shared_ptr<ISRxCalData> getSRxCal();

     /**
       * Get the ISwrCalData object instance
       */
      virtual std::shared_ptr<ISwrCalData> getSwrCal();

     /**
      * Method used to return an interface to the TX port DAC DC Offset calibrationdata
      *
      * @return
      */
      std::shared_ptr<TxDCOffsetCalData> getTxDCOffsetCal();

     /**
      * Method used to return an interface to the TX port DAC Quadrature phase and magnitude
      * offset calibration data
      *
      * @return
      */
     std::shared_ptr<TxQuadOffsetCalData> getTxQuadOffsetCal();


     /**
      * Method used
      * @return
      */
     std::shared_ptr<TxVVACalData> getTxVVACal();


     /**
      * Method used
      * @return
      */
     std::shared_ptr<PaDetCalData> getPaDetCal();


     /**
      * Method used to return an interface to calibration data interface associated with
      * the Rx AGC path.
      * @return reference to the Rx path calibration data interface
      */
     virtual std::shared_ptr<IRxAgcCalData> getRxAgcCal() override ;

    /**
     * Method used to return an interface to calibration data interface associated with
     * the Front End Module.
     * @return reference to the FEM calibration data interface
     * @throws exception if not supported by the hardware
     */
//    virtual ICalBase& getFemCal( ) throw ( std::logic_error);

    /**
     * Method used to return an interface to calibration data interface associated with
     * the sampling path.
     * @return reference to the sampler path calibration data interface
     * @throws exception if not supported by the hardware
     */
//    virtual ICalBase& getSamplerCal( ) throw ( std::logic_error);

    /**
     * Simple destructor
     */
    virtual ~CalData();

public:
    std::shared_ptr<RxCalDownload> mRxCalDownload;
    std::shared_ptr<RxIfCalDownload> mRxIfCalDownload;
    std::shared_ptr<SRxCalDownload> mSRxCalDownload;
    std::shared_ptr<SwrCalDownload> mSwrCalDownload;
    std::shared_ptr<TxCalDownload> mTxCalDownload;
    std::shared_ptr<TxIfCalDownload> mTxIfCalDownload;
    std::shared_ptr<TxDCOffsetCalDownload> mTxDCOffsetCalDownload;
    std::shared_ptr<TxQuadOffsetCalDownload> mTxQuadOffsetCalDownload;
    std::shared_ptr<TxVVACalDownload> mTxVVACalDownload;
    std::shared_ptr<PaDetCalDownload> mPaDetCalDownload;
    std::shared_ptr<PamCalDownload> mPamCalDownload;


    std::shared_ptr<TxCalData> mTxcal;
    std::shared_ptr<RxCalData> mRxcal;
    std::shared_ptr<RxIfCalData> mRxIfcal;
    std::shared_ptr<TxIfCalData> mTxIfcal;
    std::shared_ptr<SRxCalData> mSRxcal;
    std::shared_ptr<SwrCalData> mSwrcal;
    std::shared_ptr<TxDCOffsetCalData> mTxDCOffsetCal;
    std::shared_ptr<TxQuadOffsetCalData> mTxQuadOffsetCal;
    std::shared_ptr<TxVVACalData> mTxVVACal;
    std::shared_ptr<PaDetCalData> mPaDetCal;
    std::shared_ptr<RxAgcCalData> mRxAgccal;
    std::shared_ptr<PamCalData> mPamCal;

protected:
    bool mIsLoaded;
};

}


#endif /* _ETNA_FTU_CALDATA_H_ */
