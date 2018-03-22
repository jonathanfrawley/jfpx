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
#include "jfPerformanceTimer.h"

jfPerformanceTimer::jfPerformanceTimer()
{
#ifdef __WIN32__
    timer.start.QuadPart = 0;
    timer.stop.QuadPart = 0;
    QueryPerformanceFrequency(&frequency);
#endif
}

jfPerformanceTimer::~jfPerformanceTimer()
{
}

void jfPerformanceTimer::start()
{
#ifdef __WIN32__
    QueryPerformanceCounter(&timer.start);
#endif
#ifdef __linux__
    gettimeofday(&startTime, 0);
#endif
}

void jfPerformanceTimer::stop()
{
#ifdef __WIN32__
    QueryPerformanceCounter(&timer.stop);
#endif
#ifdef __linux__
    gettimeofday(&endTime, 0);
#endif
}

double jfPerformanceTimer::getCurrentTime()
{
#ifdef __WIN32__
    LARGE_INTEGER time;
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time);
    return ((double)time.QuadPart / frequency.QuadPart);
#endif
#ifdef __linux__
    gettimeofday(&endTime, 0);
    double elapsedTime;
    elapsedTime = (endTime.tv_sec - startTime.tv_sec);
    elapsedTime += (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
    return elapsedTime;
#endif
}

double jfPerformanceTimer::getElapsedTime()
{
#ifdef __WIN32__
    LARGE_INTEGER time;
    time.QuadPart = timer.stop.QuadPart - timer.start.QuadPart;
    return ((double)time.QuadPart / (double)frequency.QuadPart);
#endif
#ifdef __linux__
    double elapsedTime;
    elapsedTime = (endTime.tv_sec - startTime.tv_sec);
    elapsedTime += (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
    return elapsedTime;
#endif
}
