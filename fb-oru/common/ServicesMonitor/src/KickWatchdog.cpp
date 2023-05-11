/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      KickWatchdog.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>

#include <linux/types.h>
#include <linux/watchdog.h>

#include <string.h>
#include <iostream>
#include <pthread.h>

#include "ServicesMonitor.h"
#include "KickWatchdog.h"


using namespace std;

Mplane::KickWatchdog::KickWatchdog():
        Task(LOW_KICK_WATCHDOG_PRIORITY, Task::SMALL_STACK, "KickWatchdog", "SY"),
        mShutdown( false )
{
}

void Mplane::KickWatchdog::shutdown()
{
    mShutdown = true;
}

int Mplane::KickWatchdog::run()
{
    int fd;         /* File handler for watchdog */
    int interval;   /* Watchdog timeout interval (in secs) */
    int bootstatus; /* Watchdog last boot status */

     /*
      * Init variables
      */
    interval = WATCHDOG_TIMEOUT;

     /*
      * Once the watchdog device file is open, the watchdog will be activated by
      * the driver
      */
     if( (fd = open("/dev/watchdog", O_RDWR)) == -1 )
     {
        logDebugNormal("Failed to open watchdog device");

        // no idea why cppcheck would think this was leaking the fd? If we get here then we've failed to open it in the
        // first place!
        // cppcheck-suppress resourceLeak
        return -1;
     }

     if (ioctl(fd, WDIOC_SETTIMEOUT, &interval) != 0)
     {
         logDebugNormal("Failed to set watchdog interval");
         close( fd );
         return -1;
     }


     /*
      * Check if last boot is caused by watchdog
      */
     if (ioctl(fd, WDIOC_GETBOOTSTATUS, &bootstatus) == 0)
     {
        fprintf(stdout, "Last boot is caused by : %s\n",
           (bootstatus != 0) ? "Watchdog" : "Power-On-Reset");
     }
     else
     {
        fprintf(stderr, "Error: Cannot read watchdog status\n");
        close ( fd );
        return -1;
     }

    while( !mShutdown )
    {
    	int dummy(0) ;
        Mplane::Task::msSleep( 1000 );
        ioctl(fd, WDIOC_KEEPALIVE, &dummy);
    }
    /*
     * The 'V' value needs to be written into watchdog device file to indicate
     * that we intend to close/stop the watchdog. Otherwise, debug message
     * 'Watchdog timer closed unexpectedly' will be printed
     */
    write(fd, "V", 1);
    /*
     * Closing the watchdog device will deactivate the watchdog.
     */
     close(fd);

     return 0;
}

Mplane::KickWatchdog::~KickWatchdog()
{
}
