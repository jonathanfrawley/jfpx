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
#include "Config.h"
#include "Test.h"
#include "TestList.h"
#include "TestResults.h"
#include "AssertException.h"
#include "MemoryOutStream.h"
#include "ExecuteTest.h"

#ifdef UNITTEST_POSIX
    #include "Posix/SignalTranslator.h"
#endif

namespace UnitTest {

TestList& Test::GetTestList()
{
    static TestList s_list;
    return s_list;
}

Test::Test(char const* testName, char const* suiteName, char const* filename, int lineNumber)
    : m_details(testName, suiteName, filename, lineNumber)
    , next(0)
    , m_timeConstraintExempt(false)
{
}

Test::~Test()
{
}

void Test::Run()
{
	ExecuteTest(*this, m_details);
}

void Test::RunImpl() const
{
}

}
