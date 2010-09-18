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
#include "../TimeHelpers.h"

#include "RecordingReporter.h"
#include "ScopedCurrentTest.h"

namespace {

TEST (TimeConstraintMacroQualifiesNamespace)
{
    // If this compiles without a "using namespace UnitTest;", all is well.
    UNITTEST_TIME_CONSTRAINT(1);
}

TEST (TimeConstraintMacroUsesCorrectInfo)
{
    int testLine = 0;
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
		ScopedCurrentTest scopedResults(testResults);

        UNITTEST_TIME_CONSTRAINT(10); testLine = __LINE__;
        UnitTest::TimeHelpers::SleepMs(20);
    }

	using namespace std;

    CHECK_EQUAL(1, reporter.testFailedCount);
    CHECK(strstr(reporter.lastFailedFile, __FILE__));
    CHECK_EQUAL(testLine, reporter.lastFailedLine);
    CHECK(strstr(reporter.lastFailedTest, "TimeConstraintMacroUsesCorrectInfo"));
}

}
