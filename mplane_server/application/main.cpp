/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      main.cpp
 * \brief     Mplane ORAN radio application
 *
 *
 * \details   Mplane ORAN radio application
 *
 */
#include <signal.h>
#include <functional>

#include "Application.h"

using namespace Mplane;

namespace {
void sigintHandler(int signum) {
	std::shared_ptr<IApplication> app = IApplication::getInstance();
	app->quit();
}
} // namespace

/*!
 * \brief The first start point for the program
 */
int main(int argc, const char** argv)
{
	struct sigaction sa;

	// Create application
	std::shared_ptr<IApplication> app = IApplication::getInstance();

	// Go through full shutdown sequence when SIGINT is received
	sa.sa_handler = &sigintHandler;
	sigfillset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGINT, &sa, NULL);

	// Run the app
	return app->run("Mplane O-RAN M-Plane", argc, argv) ;
}
