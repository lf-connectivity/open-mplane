/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformMem.h
 * \brief     Class to contain waveform memory details
 *
 *
 * \details   Contains the waveform memory block start and end address. Used in allocating memory blocks
 *
 */


#ifndef WAVEFORMMEM_H_
#define WAVEFORMMEM_H_

#include <iostream>
#include <memory>
#include "IWaveformMem.h"

namespace Mplane {

/**
 * WaveformMem class
 */
class WaveformMem : public virtual IWaveformMem {
public:
	WaveformMem(unsigned startAddress, unsigned size) :
		mStart(startAddress),
		mSize(size)
	{}
	virtual ~WaveformMem() {}

	// Accessors
	virtual unsigned start() const { return mStart; }
	virtual unsigned end() const { return mStart + mSize - 1 ; }
	virtual unsigned size() const { return mSize ; }

	// display
	virtual void show(std::ostream& os) const
	{
		os << std::hex <<
			"0x" << start() <<
			" .. " <<
			"0x" << end() <<
			std::dec ;
	}


	// Comparators
	virtual bool operator==(const IWaveformMem& rhs) {
		if (mStart==rhs.start() && mSize==rhs.size())
			return true ;
		return false ;
	}

	virtual bool operator!=(const IWaveformMem& rhs) { return !operator==(rhs); }


private:
	unsigned mStart ;
	unsigned mSize ;
} ;


/**
 * Helper class used with find_if
 */
class WaveformMemPtrFind {
public:
	explicit WaveformMemPtrFind(const std::shared_ptr<IWaveformMem>& lhs) :
		mToFind(lhs)
	{}

	bool operator()(const std::shared_ptr<IWaveformMem>& rhs) const
	{
		return mToFind->operator==(*rhs) ;
	}

private:
	const std::shared_ptr<IWaveformMem>& mToFind ;
};


} // namespace Mplane


inline std::ostream& operator<<(std::ostream& os, const Mplane::IWaveformMem& rhs)
{
	rhs.show(os) ;
	return os ;
}

inline std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Mplane::IWaveformMem>& rhs)
{
	if (rhs.get() == 0)
	{
		os << "(null)" ;
	}
	else
	{
		os << *rhs ;
	}
	return os ;
}


#endif /* WAVEFORMMEM_H_ */
