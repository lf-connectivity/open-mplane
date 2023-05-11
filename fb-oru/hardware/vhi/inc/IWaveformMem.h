/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IWaveformMem.h
 * \brief     Virtual interface to waveform memory
 *
 *
 * \details
 *
 */


#ifndef IWAVEFORMMEM_H_
#define IWAVEFORMMEM_H_


namespace Mplane {

class IWaveformMem {
public:
	IWaveformMem() {}
	virtual ~IWaveformMem() {}

	// Accessors
	virtual unsigned start() const =0 ;
	virtual unsigned end() const =0 ;
	virtual unsigned size() const =0 ;

	// display
	virtual void show(std::ostream& os) const =0 ;

	// Comparators
	virtual bool operator==(const IWaveformMem& rhs) =0 ;
	virtual bool operator!=(const IWaveformMem& rhs) =0 ;

} ;

}

#endif /* IWAVEFORMMEM_H_ */
