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
#ifndef UNITTEST_TESTRUNNER_H
#define UNITTEST_TESTRUNNER_H

#include "Test.h"
#include "TestList.h"
#include "CurrentTest.h"

namespace UnitTest {

class TestReporter;
class TestResults;
class Timer;

int RunAllTests();

struct True
{
	bool operator()(const Test* const) const
	{
		return true;	
	}
};

class TestRunner
{
public:
	explicit TestRunner(TestReporter& reporter);
	~TestRunner();

	template <class Predicate>
	int RunTestsIf(TestList const& list, char const* suiteName, 
				   const Predicate& predicate, int maxTestTimeInMs) const
	{
	    Test* curTest = list.GetHead();

	    while (curTest != 0)
	    {
		    if (IsTestInSuite(curTest,suiteName) && predicate(curTest))
			{
				RunTest(m_result, curTest, maxTestTimeInMs);
			}

			curTest = curTest->next;
	    }

	    return Finish();
	}	

private:
	TestReporter* m_reporter;
	TestResults* m_result;
	Timer* m_timer;

	int Finish() const;
	bool IsTestInSuite(const Test* const curTest, char const* suiteName) const;
	void RunTest(TestResults* const result, Test* const curTest, int const maxTestTimeInMs) const;
};

}

#endif
