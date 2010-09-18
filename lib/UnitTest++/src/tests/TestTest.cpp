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
#include "../TestReporter.h"
#include "../TimeHelpers.h"
#include "ScopedCurrentTest.h"

using namespace UnitTest;

namespace {

TEST(PassingTestHasNoFailures)
{
    class PassingTest : public Test
    {
    public:
        PassingTest() : Test("passing") {}
        virtual void RunImpl() const
        {
            CHECK(true);
        }
    };

    TestResults results;
	{
		ScopedCurrentTest scopedResults(results);
		PassingTest().Run();
	}

    CHECK_EQUAL(0, results.GetFailureCount());
}


TEST(FailingTestHasFailures)
{
    class FailingTest : public Test
    {
    public:
        FailingTest() : Test("failing") {}
        virtual void RunImpl() const
        {
            CHECK(false);
        }
    };

    TestResults results;
	{
		ScopedCurrentTest scopedResults(results);
		FailingTest().Run();
	}

    CHECK_EQUAL(1, results.GetFailureCount());
}


TEST(ThrowingTestsAreReportedAsFailures)
{
    class CrashingTest : public Test
    {
    public:
        CrashingTest() : Test("throwing") {}
        virtual void RunImpl() const
        {
            throw "Blah";
        }
    };
 
    TestResults results;
	{
		ScopedCurrentTest scopedResult(results);
		CrashingTest().Run();
	}

	CHECK_EQUAL(1, results.GetFailureCount());
}


#ifndef UNITTEST_MINGW
TEST(CrashingTestsAreReportedAsFailures)
{
    class CrashingTest : public Test
    {
    public:
        CrashingTest() : Test("crashing") {}
        virtual void RunImpl() const
        {
            reinterpret_cast< void (*)() >(0)();
        }
    };

    TestResults results;
	{
		ScopedCurrentTest scopedResult(results);
		CrashingTest().Run();
	}

	CHECK_EQUAL(1, results.GetFailureCount());
}
#endif

TEST(TestWithUnspecifiedSuiteGetsDefaultSuite)
{
    Test test("test");
    CHECK(test.m_details.suiteName != NULL);
    CHECK_EQUAL("DefaultSuite", test.m_details.suiteName);
}

TEST(TestReflectsSpecifiedSuiteName)
{
    Test test("test", "testSuite");
    CHECK(test.m_details.suiteName != NULL);
    CHECK_EQUAL("testSuite", test.m_details.suiteName);
}

void Fail()
{
	CHECK(false);
}

TEST(OutOfCoreCHECKMacrosCanFailTests)
{
	TestResults results;
	{
		ScopedCurrentTest scopedResult(results);
		Fail();
	}

	CHECK_EQUAL(1, results.GetFailureCount());
}

}
