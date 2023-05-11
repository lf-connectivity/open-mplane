
#ifndef _RADIO_HARDWARE_COMMONEQUALISER_H_
#define _RADIO_HARDWARE_COMMONEQUALISER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonEqualiser.h
 * \brief     A file to define the interface to a common equaliser
 *
 *
 * \details   A file to define the interface to a common equaliser
 *
 */

#include "IEqualiser.h"
#include "IFrequencyChange.h"
#include "Frequency.h"
#include "FrequencyOffset.h"
#include "Conditional.h"
#include "Task.h"
#include "Temperature.h"
#include "Power.h"
#include "Observer.hpp"
#include "FftCalc.hpp"
#include "ICalModeChange.h"

namespace Mplane
{

struct EqPoint
{
	EqPoint() : freq(0.0), gain(0.0) {}
	EqPoint(const FrequencyOffset& _freq, const Power& _gain) :
		freq(_freq),
		gain(_gain)
	{}

	FrequencyOffset   freq;
    Power 		      gain;
};

class CommonEqualiser : public IEqualiser, public Observer<IFrequencyChange>, public Observer<ICalModeChange>
{
	//For unit testing purpose
	friend class TestRxEqTestCases;
	//For unit testing purpose
	friend class TestTxEqTestCases;

public:

    /**
     * Get the zero based index that can be used to reference the port from
     * a list of ports.
     * @return zero base index of the port
     */
    virtual int getIndex() const;

    /**
     * A string name associated with the port type used in logging and debugging.
     * @return port name
     */
    virtual std::string getName() const;

	/*!
     * \brief CommonEqualiser constructor
     */
	CommonEqualiser(int index, const char* name, FrequencyOffset minFreq,
			FrequencyOffset maxFreq, unsigned int numPoints);

    /*!
     * \brief CommonEqualiser destructor
     */
    virtual ~CommonEqualiser();

    /*! \brief virtual method to calculate equaliser coefficients
     *
     * \param  path
     * \return Return state of the set calculation is successful or not
     */
    virtual ReturnType::State calculateEqualiser(void) override;

    /*! \brief Pure virtual method to read whether equaliser is in
     * passthrough mode
     *
     * \return true/false
     */
    virtual bool getPassthroughMode( void ) override;

    /*! \brief Pure virtual method to enable/disable equaliser
     * passthrough mode
     *
     * \param enable - to turn ON/OFF the passthrough mode
     * \return None
     */
    virtual void setPassthroughMode( bool enable ) override;

    /**
     * @brief Print out contents of equaliser to stdout
     * Used for debug only
     */
    virtual void show(std::ostream& os = std::cout) const override;

private:

    // Methods supporting the subject/observer inheritance
    // ---------------------------------------------------
    /*!
     *
     * \brief update method to allow Rx/Tx frequency changes to be notified to us.
     *
     * \return none
     * \param IFrequencyChange &subject
     */
    virtual void update( IFrequencyChange &subject );

    virtual const char* name() const ;

    /*!
     *
     * \brief update method to allow cal mode changes to be notified to us.
     *
     * \return none
     * \param ICalModeChange &subject
     */
    virtual void update(ICalModeChange& subject);

protected:

    /*! \brief Given the spline object, interpolate and write the values in freqGainTable.
     *
     * \return none
     * \param ipFreqGainTable input frequency gain table
     * \param opFreqGainTable reference to the frequency response table in which the interpolated values
     * would be written
     */
    virtual bool interpolateFreqResp(std::vector<EqPoint> ipFreqGainTable, std::vector<EqPoint> &opFreqGainTable);

    /*! \brief Add the frequency responses freqGainTable1 and freqGainTable2 into freqGainTable1
     *
     * \return none
     * \param freqGainTable1 Frequency response 1 (Combined response goes into this)
     * \param freqGainTable2 Frequency response 2
     */
    virtual void combineFreqResp(std::vector<EqPoint> &freqGainTable1, std::vector<EqPoint> &freqGainTable2);

    /*! \brief Calculate IFFT on the frequency response
     *
     * \return none
     * \param freqGainTable Frequency response
     * \param timeDomainValues Reference to array that will get written with the output of IFFT
     */
    virtual void performIfft(std::vector<EqPoint> freqGainTable, std::complex<float> timeDomainValues[]);

    /*! \brief Calculate tukey window function of a specific size
     *
     * \return none
     * \param window_function Reference to vector that will get written with the window values
     */
    virtual void calculateTukeyWindow(std::vector<float> &window_function);

public:

    static const float SAMPLE_RATE_MHZ;

private:

    int mIndex;
    std::string mName;

protected:

    virtual void attachToFreqChange(void);

    Frequency mFrequencyChangeValue;           //!> Subject/Observer update changes due to frequency change
    Frequency mCurrentFrequency;               //!> Cache of current frequency to prevent cyclic frequency change
    FrequencyOffset mInterpolationMinFreq;     //!> Start frequency for interpolation of frequency response
    FrequencyOffset mInterpolationMaxFreq;     //!> End frequency for interpolation of frequency response
    unsigned int mInterpolationPoints;         //!> Number of points to interpolate in the frequency response
    bool mPassThroughMode;                     //!> Bypass equaliser so that it passes the input signal without any frequency domain correction
    bool mCalMode;                             //!> Cache of cal mode
};

}

#endif /* _RADIO_HARDWARE_COMMONEQUALISER_H_ */
