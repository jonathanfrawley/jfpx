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
#include "../ReportAssert.h"
#include "ScopedCurrentTest.h"

#include <vector>

// These are sample tests that show the different features of the framework

namespace {

TEST(ValidCheckSucceeds)
{
    bool const b = true;
    CHECK(b);
}

TEST(CheckWorksWithPointers)
{
    void* p = (void *)0x100;
    CHECK(p);
    CHECK(p != 0);
}

TEST(ValidCheckEqualSucceeds)
{
    int const x = 3;
    int const y = 3;
    CHECK_EQUAL(x, y);
}

TEST(CheckEqualWorksWithPointers)
{
    void* p = (void *)0;
    CHECK_EQUAL((void*)0, p);
}

TEST(ValidCheckCloseSucceeds)
{
    CHECK_CLOSE(2.0f, 2.001f, 0.01f);
    CHECK_CLOSE(2.001f, 2.0f, 0.01f);
}

TEST(ArrayCloseSucceeds)
{
    float const a1[] = {1, 2, 3};
    float const a2[] = {1, 2.01f, 3};
    CHECK_ARRAY_CLOSE(a1, a2, 3, 0.1f);
}

TEST (CheckArrayCloseWorksWithVectors)
{
    std::vector< float > a(4);
    for (int i = 0; i < 4; ++i)
        a[i] = (float)i;

    CHECK_ARRAY_CLOSE(a, a, (int)a.size(), 0.0001f);
}

TEST(CheckThrowMacroSucceedsOnCorrectException)
{
    struct TestException {};
    CHECK_THROW(throw TestException(), TestException);
}

TEST(CheckAssertSucceeds)
{
    CHECK_ASSERT(UnitTest::ReportAssert("desc", "file", 0));
}

TEST(CheckThrowMacroFailsOnMissingException)
{
    class NoThrowTest : public UnitTest::Test
    {
    public:
        NoThrowTest() : Test("nothrow") {}
        void DontThrow() const
        {
        }

        virtual void RunImpl() const
        {
            CHECK_THROW(DontThrow(), int);
        }
    };

    UnitTest::TestResults results;
	{
		ScopedCurrentTest scopedResults(results);

		NoThrowTest test;
		test.Run();
	}

	CHECK_EQUAL(1, results.GetFailureCount());
}

TEST(CheckThrowMacroFailsOnWrongException)
{
    class WrongThrowTest : public UnitTest::Test
    {
    public:
        WrongThrowTest() : Test("wrongthrow") {}
        virtual void RunImpl() const
        {
            CHECK_THROW(throw "oops", int);
        }
    };

    UnitTest::TestResults results;
	{
		ScopedCurrentTest scopedResults(results);

		WrongThrowTest test;
		test.Run();
	}

	CHECK_EQUAL(1, results.GetFailureCount());
}

struct SimpleFixture
{
    SimpleFixture()
    {
        ++instanceCount;
    }
    ~SimpleFixture()
    {
        --instanceCount;
    }

    static int instanceCount;
};

int SimpleFixture::instanceCount = 0;

TEST_FIXTURE(SimpleFixture, DefaultFixtureCtorIsCalled)
{
    CHECK(SimpleFixture::instanceCount > 0);
}

TEST_FIXTURE(SimpleFixture, OnlyOneFixtureAliveAtATime)
{
    CHECK_EQUAL(1, SimpleFixture::instanceCount);
}

void CheckBool(const bool b)
{
	CHECK(b);
}

TEST(CanCallCHECKOutsideOfTestFunction)
{
	CheckBool(true);
}

}
