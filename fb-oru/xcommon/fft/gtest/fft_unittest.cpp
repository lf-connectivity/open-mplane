/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Crc_unittest.cpp
 * \brief     Google Test of Crc
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the Crc class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include <memory>

#include "FftCalc.hpp"

using namespace Mplane ;

//-------------------------------------------------------------------------------------------------------------
TEST(fft, testFloat)
{
	std::shared_ptr<IFftCalc<float> > fft(FftCalcBuilder<float>::factory(8)) ;

	float input[] = {
			1.0, 0.0,
			1.0, 0.0,
			1.0, 0.0,
			1.0, 0.0,
			0.0, 0.0,
			0.0, 0.0,
			0.0, 0.0,
			0.0, 0.0 } ;

	float data[16] ;
	for (int i = 0; i < 16; ++i)
	{
		data[i] = input[i] ;
	}

	// forward fft
	fft->fft(data) ;

	float expected[] = {

	4, 0,
	1, -2.414213562373095f,
	0, 0,
	1, -0.414213418960571f,
	0, 0,
	1, 0.414213657379150f,
	0, 0,
	1, 2.414213418960571f,

	} ;

	std::cout << "fft" << std::endl;
	for (int i = 0; i < 16; i+=2)
	{
		std::cout << std::fixed << std::setprecision(15) << "(" << data[i] << ", " << data[i+1] << ")" << std::endl;
		EXPECT_NEAR(expected[i], data[i], 0.01) ;
		EXPECT_NEAR(expected[i+1], data[i+1], 0.01) ;
	}


	// INVERSE
	std::shared_ptr<IFftCalc<float> > ifft(InverseFftCalcBuilder<float>::factory(8)) ;

	// inverse fft
	ifft->fft(data) ;

	std::cout << "inv fft" << std::endl;
	for (int i = 0; i < 16; i+=2)
	{
		std::cout << std::fixed << std::setprecision(15) << "(" << data[i] << ", " << data[i+1] << ")" << std::endl;
		EXPECT_NEAR(input[i], data[i], 0.01) ;
		EXPECT_NEAR(input[i+1], data[i+1], 0.01) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
TEST(fft, testDouble)
{
	std::shared_ptr<IFftCalc<double> > fft(FftCalcBuilder<double>::factory(8)) ;

	double input[] = {
			1.0, 0.0,
			1.0, 0.0,
			1.0, 0.0,
			1.0, 0.0,
			0.0, 0.0,
			0.0, 0.0,
			0.0, 0.0,
			0.0, 0.0 } ;

	double data[16] ;
	for (int i = 0; i < 16; ++i)
	{
		data[i] = input[i] ;
	}

	// forward fft
	fft->fft(data) ;

	double expected[] = {

		4, 0,
		1, -2.414213562373095,
		0, 0,
		1, -0.414213562373094,
		0, 0,
		1, 0.414213562373095,
		0, 0,
		1, 2.414213562373094,

	} ;

	std::cout << "fft" << std::endl;
	for (int i = 0; i < 16; i+=2)
	{
		std::cout << std::fixed << std::setprecision(15) << "(" << data[i] << ", " << data[i+1] << ")" << std::endl;
		EXPECT_NEAR(expected[i], data[i], 0.01) ;
		EXPECT_NEAR(expected[i+1], data[i+1], 0.01) ;
	}


	// INVERSE
	std::shared_ptr<IFftCalc<double> > ifft(InverseFftCalcBuilder<double>::factory(8)) ;

	// inverse fft
	ifft->fft(data) ;

	std::cout << "inv fft" << std::endl;
	for (int i = 0; i < 16; i+=2)
	{
		std::cout << std::fixed << std::setprecision(15) << "(" << data[i] << ", " << data[i+1] << ")" << std::endl;
		EXPECT_NEAR(input[i], data[i], 0.01) ;
		EXPECT_NEAR(input[i+1], data[i+1], 0.01) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
TEST(fft, testComplexFloat)
{
	std::shared_ptr<IFftCalc<std::complex<float>> > fft(FftCalcBuilder<std::complex<float>>::factory(8)) ;

	std::complex<float> cx[] = {
			{ 1.0, 0.0},
			{ 1.0, 0.0},
			{ 1.0, 0.0},
			{ 1.0, 0.0},
			{ 0.0, 0.0},
			{ 0.0, 0.0},
			{ 0.0, 0.0},
			{ 0.0, 0.0}, } ;

	std::complex<float> data[8] ;
	for (int i = 0; i < 8; ++i)
	{
		data[i] = cx[i] ;
	}

	// forward fft
	fft->fft(cx) ;

	std::complex<float> expected[] = {
	{4, 0},
	{1, -2.4142142f},
	{0, 0},
	{1, -0.41421342f},
	{0, 0},
	{1, 0.41421366f},
	{0, 0},
	{1, 2.4142142f},

	} ;
	(void)expected ;

	std::cout << "fft" << std::endl;
	for (int i = 0; i < 8; ++i)
	{
		std::cout << std::fixed << std::setprecision(15) << "(" << cx[i].real() << ", " << cx[i].imag() << ")" << std::endl;
		EXPECT_NEAR(expected[i].real(), cx[i].real(), 0.01) ;
		EXPECT_NEAR(expected[i].imag(), cx[i].imag(), 0.01) ;
	}

	// INVERSE
	std::shared_ptr<IFftCalc<std::complex<float>> > ifft(InverseFftCalcBuilder<std::complex<float>>::factory(8)) ;

	// inverse fft
	ifft->fft(cx) ;

	std::cout << "inv fft" << std::endl;
	for (int i = 0; i < 8; ++i)
	{
		std::cout << std::fixed << std::setprecision(15) << "(" << cx[i].real() << ", " << cx[i].imag() << ")" << std::endl;
		EXPECT_NEAR(data[i].real(), cx[i].real(), 0.01) ;
		EXPECT_NEAR(data[i].imag(), cx[i].imag(), 0.01) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
TEST(fft, testComplexDouble)
{
	std::shared_ptr<IFftCalc<std::complex<double>> > fft(FftCalcBuilder<std::complex<double>>::factory(8)) ;

	std::complex<double> cx[] = {
			{ 1.0, 0.0},
			{ 1.0, 0.0},
			{ 1.0, 0.0},
			{ 1.0, 0.0},
			{ 0.0, 0.0},
			{ 0.0, 0.0},
			{ 0.0, 0.0},
			{ 0.0, 0.0}, } ;

	std::complex<double> data[8] ;
	for (int i = 0; i < 8; ++i)
	{
		data[i] = cx[i] ;
	}

	// forward fft
	fft->fft(cx) ;

	std::complex<double> expected[] = {

	{4, 0},
	{1, -2.414213562373095},
	{0, 0},
	{1, -0.414213562373094},
	{0, 0},
	{1, 0.414213562373095},
	{0, 0},
	{1, 2.414213562373094},

	} ;
	(void)expected ;

	std::cout << "fft" << std::endl;
	for (int i = 0; i < 8; ++i)
	{
		std::cout << std::fixed << std::setprecision(15) << "(" << cx[i].real() << ", " << cx[i].imag() << ")" << std::endl;
		EXPECT_NEAR(expected[i].real(), cx[i].real(), 0.01) ;
		EXPECT_NEAR(expected[i].imag(), cx[i].imag(), 0.01) ;
	}

	// INVERSE
	std::shared_ptr<IFftCalc<std::complex<double>> > ifft(InverseFftCalcBuilder<std::complex<double>>::factory(8)) ;

	// inverse fft
	ifft->fft(cx) ;

	std::cout << "inv fft" << std::endl;
	for (int i = 0; i < 8; ++i)
	{
		std::cout << std::fixed << std::setprecision(15) << "(" << cx[i].real() << ", " << cx[i].imag() << ")" << std::endl;
		EXPECT_NEAR(data[i].real(), cx[i].real(), 0.01) ;
		EXPECT_NEAR(data[i].imag(), cx[i].imag(), 0.01) ;
	}
}
