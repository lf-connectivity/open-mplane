/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Process.h
 * \brief     Application process utilities
 *
 *
 * \details
 *
 */


#ifndef PROCESS_H_
#define PROCESS_H_


namespace Mplane {

class Process {
public:

	/**
	 * Get the processes memory resident set size
	 * @return resident set size (in kilobytes)
	 */
	static long int getResidentSetSize() ;

	/**
	 * Use Linux sysinfo() to get system memory statistics in bytes
	 * @param total
	 * @param free
	 * @param used
	 * @param shared
	 * @param buffer
	 * @return true if able to read system info
	 */
	static bool getSystemMemory(unsigned long& total, unsigned long& free, unsigned long& used,
			unsigned long& shared, unsigned long& buffer);
} ;

}

#endif /* PROCESS_H_ */
