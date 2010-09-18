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
#ifndef UNITTEST_SCOPEDCURRENTTEST_H
#define UNITTEST_SCOPEDCURRENTTEST_H

#include "../CurrentTest.h"
#include <cstddef>

class ScopedCurrentTest
{
public:
	ScopedCurrentTest()
		: m_oldTestResults(UnitTest::CurrentTest::Results())
		, m_oldTestDetails(UnitTest::CurrentTest::Details())
	{
	}

	explicit ScopedCurrentTest(UnitTest::TestResults& newResults, const UnitTest::TestDetails* newDetails = NULL)
		: m_oldTestResults(UnitTest::CurrentTest::Results())
		, m_oldTestDetails(UnitTest::CurrentTest::Details())
	{
		UnitTest::CurrentTest::Results() = &newResults;

		if (newDetails != NULL)
			UnitTest::CurrentTest::Details() = newDetails;
	}

	~ScopedCurrentTest()
	{
		UnitTest::CurrentTest::Results() = m_oldTestResults;
		UnitTest::CurrentTest::Details() = m_oldTestDetails;
	}

private:
	UnitTest::TestResults* m_oldTestResults;
	const UnitTest::TestDetails* m_oldTestDetails;
};

#endif
