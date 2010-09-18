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
#include <windows.h>

namespace UnitTest {

Timer::Timer()
    : m_startTime(0)
	, m_threadHandle(::GetCurrentThread())
{
#if defined(_MSC_VER) && (_MSC_VER == 1200) // VC6 doesn't have DWORD_PTR?
	typedef unsigned long DWORD_PTR;
#endif

    DWORD_PTR systemMask;
    ::GetProcessAffinityMask(GetCurrentProcess(), &m_processAffinityMask, &systemMask);
    
    ::SetThreadAffinityMask(m_threadHandle, 1);
	::QueryPerformanceFrequency(reinterpret_cast< LARGE_INTEGER* >(&m_frequency));
    ::SetThreadAffinityMask(m_threadHandle, m_processAffinityMask);
}

void Timer::Start()
{
    m_startTime = GetTime();
}

int Timer::GetTimeInMs() const
{
    __int64 const elapsedTime = GetTime() - m_startTime;
	double const seconds = double(elapsedTime) / double(m_frequency);
	return int(seconds * 1000.0f);
}

__int64 Timer::GetTime() const
{
    LARGE_INTEGER curTime;
    ::SetThreadAffinityMask(m_threadHandle, 1);
	::QueryPerformanceCounter(&curTime);
    ::SetThreadAffinityMask(m_threadHandle, m_processAffinityMask);
    return curTime.QuadPart;
}



void TimeHelpers::SleepMs(int const ms)
{
	::Sleep(ms);
}

}
