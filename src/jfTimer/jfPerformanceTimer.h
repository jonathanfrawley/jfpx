/**
jfpx - A cross platform physics engine using CUDA    
Copyright (C) 2010 Jonathan Frawley

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
#ifndef TIMER_H
#define TIMER_H

#define __linux__ //Change to platform we are running on

#ifdef __WIN32__
#include <windows.h>
typedef struct {
    LARGE_INTEGER start;
    LARGE_INTEGER stop;
} stopWatch;
#endif

#ifdef __linux__
#include <sys/time.h>
#endif

/*
 * =====================================================================================
 *        Class: jfPerformanceTimer
 *  Description: Cross-platform, microsecond accurate timer
 * =====================================================================================
 */
class jfPerformanceTimer
{
    public:
        jfPerformanceTimer();

        virtual ~jfPerformanceTimer();

        void start();

        void stop();

        double getElapsedTime();

        double getCurrentTime();

    protected:
#ifdef __WIN32__
		stopWatch timer;
        LARGE_INTEGER frequency;
#endif
#ifdef __linux__
		timeval startTime, endTime;
#endif
    private:
};

#endif 
