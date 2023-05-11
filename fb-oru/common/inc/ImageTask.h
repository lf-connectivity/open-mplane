/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ImageTask.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef IMAGETASK_H_
#define IMAGETASK_H_

#include "Task.h"

namespace Mplane {

class ImageTask : public Task {
public:
	ImageTask() ;
	virtual ~ImageTask() ;

	/**
	 * Public method to allow image classes to give this task a kick to keep it alive while they perform lengthy
	 * operations
	 */
	void keepAlive() ;

} ;

}

#endif /* IMAGETASK_H_ */
