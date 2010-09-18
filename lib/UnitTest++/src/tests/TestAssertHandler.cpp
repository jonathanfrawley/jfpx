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
#include "../AssertException.h"
#include "../ReportAssert.h"

using namespace UnitTest;

namespace {

TEST(ReportAssertThrowsAssertException)
{
    bool caught = false;

    try
    {
        ReportAssert("", "", 0);
    }
    catch(AssertException const&)
    {
        caught = true;
    }

    CHECK (true == caught);
}

TEST(ReportAssertSetsCorrectInfoInException)
{
    const int lineNumber = 12345;
    const char* description = "description";
    const char* filename = "filename";

    try
    {
        ReportAssert(description, filename, lineNumber);
    }
    catch(AssertException const& e)
    {
        CHECK_EQUAL(description, e.what());
        CHECK_EQUAL(filename, e.Filename());
        CHECK_EQUAL(lineNumber, e.LineNumber());
    }
}


}
