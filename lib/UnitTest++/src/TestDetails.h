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
#ifndef UNITTEST_TESTDETAILS_H
#define UNITTEST_TESTDETAILS_H

namespace UnitTest {

class TestDetails
{
public:
    TestDetails(char const* testName, char const* suiteName, char const* filename, int lineNumber);
    TestDetails(const TestDetails& details, int lineNumber);

    char const* const suiteName;
    char const* const testName;
    char const* const filename;
    int const lineNumber;

    TestDetails(TestDetails const&); // Why is it public? --> http://gcc.gnu.org/bugs.html#cxx_rvalbind
private:
    TestDetails& operator=(TestDetails const&);
};

}

#endif
