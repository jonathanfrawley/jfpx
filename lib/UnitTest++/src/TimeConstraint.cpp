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
#include "TimeConstraint.h"
#include "TestResults.h"
#include "MemoryOutStream.h"
#include "CurrentTest.h"

namespace UnitTest {


TimeConstraint::TimeConstraint(int ms, TestDetails const& details)
	: m_details(details)
    , m_maxMs(ms)
{
    m_timer.Start();
}

TimeConstraint::~TimeConstraint()
{
    int const totalTimeInMs = m_timer.GetTimeInMs();
    if (totalTimeInMs > m_maxMs)
    {
        MemoryOutStream stream;
        stream << "Time constraint failed. Expected to run test under " << m_maxMs <<
                  "ms but took " << totalTimeInMs << "ms.";

		UnitTest::CurrentTest::Results()->OnTestFailure(m_details, stream.GetText());
    }
}

}
