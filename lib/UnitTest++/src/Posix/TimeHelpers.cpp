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
#include "TimeHelpers.h"
#include <unistd.h>

namespace UnitTest {

Timer::Timer()
{
    m_startTime.tv_sec = 0;
    m_startTime.tv_usec = 0;
}

void Timer::Start()
{
    gettimeofday(&m_startTime, 0);
}


int Timer::GetTimeInMs() const
{
    struct timeval currentTime;
    gettimeofday(&currentTime, 0);
    int const dsecs = currentTime.tv_sec - m_startTime.tv_sec;
    int const dus = currentTime.tv_usec - m_startTime.tv_usec;
    return dsecs*1000 + dus/1000;
}


void TimeHelpers::SleepMs (int ms)
{
    usleep(ms * 1000);
}

}
