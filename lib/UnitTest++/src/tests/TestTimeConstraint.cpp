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
#include "../UnitTest++.h"
#include "../TestResults.h"
#include "../TimeHelpers.h"
#include "RecordingReporter.h"
#include "ScopedCurrentTest.h"

using namespace UnitTest;

namespace
{

TEST(TimeConstraintSucceedsWithFastTest)
{
    TestResults result;
    {
		ScopedCurrentTest scopedResult(result);
        TimeConstraint t(200, TestDetails("", "", "", 0));
        TimeHelpers::SleepMs(5);
    }
    CHECK_EQUAL(0, result.GetFailureCount());
}

TEST(TimeConstraintFailsWithSlowTest)
{
    TestResults result;
    {
		ScopedCurrentTest scopedResult(result);
        TimeConstraint t(10, TestDetails("", "", "", 0));
        TimeHelpers::SleepMs(20);
    }
    CHECK_EQUAL(1, result.GetFailureCount());
}

TEST(TimeConstraintFailureIncludesCorrectData)
{
    RecordingReporter reporter;
    TestResults result(&reporter);
    {
		ScopedCurrentTest scopedResult(result);

		TestDetails const details("testname", "suitename", "filename", 10);
        TimeConstraint t(10, details);
        TimeHelpers::SleepMs(20);
    }

	using namespace std;

	CHECK(strstr(reporter.lastFailedFile, "filename"));
    CHECK_EQUAL(10, reporter.lastFailedLine);
    CHECK(strstr(reporter.lastFailedTest, "testname"));
}

TEST(TimeConstraintFailureIncludesTimeoutInformation)
{
    RecordingReporter reporter;
    TestResults result(&reporter);
    {
		ScopedCurrentTest scopedResult(result);
        TimeConstraint t(10, TestDetails("", "", "", 0));
        TimeHelpers::SleepMs(20);
    }

	using namespace std;

	CHECK(strstr(reporter.lastFailedMessage, "ime constraint"));
    CHECK(strstr(reporter.lastFailedMessage, "under 10ms"));
}

}
