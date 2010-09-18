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
#ifndef UNITTEST_TIMECONSTRAINT_H
#define UNITTEST_TIMECONSTRAINT_H

#include "TimeHelpers.h"

namespace UnitTest {

class TestResults;
class TestDetails;

class TimeConstraint
{
public:
    TimeConstraint(int ms, TestDetails const& details);
    ~TimeConstraint();

private:
    void operator=(TimeConstraint const&); 
	TimeConstraint(TimeConstraint const&);

	Timer m_timer;
    TestDetails const& m_details;
	int const m_maxMs;
};

#define UNITTEST_TIME_CONSTRAINT(ms) \
	UnitTest::TimeConstraint unitTest__timeConstraint__(ms, UnitTest::TestDetails(m_details, __LINE__))

#define UNITTEST_TIME_CONSTRAINT_EXEMPT() do { m_timeConstraintExempt = true; } while (0)

}

#endif
