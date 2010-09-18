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
#ifndef UNITTEST_TESTRESULTS_H
#define UNITTEST_TESTRESULTS_H

namespace UnitTest {

class TestReporter;
class TestDetails;

class TestResults
{
public:
    explicit TestResults(TestReporter* reporter = 0);

    void OnTestStart(TestDetails const& test);
    void OnTestFailure(TestDetails const& test, char const* failure);
    void OnTestFinish(TestDetails const& test, float secondsElapsed);

    int GetTotalTestCount() const;
    int GetFailedTestCount() const;
    int GetFailureCount() const;

private:
    TestReporter* m_testReporter;
    int m_totalTestCount;
    int m_failedTestCount;
    int m_failureCount;

    bool m_currentTestFailed;

    TestResults(TestResults const&);
    TestResults& operator =(TestResults const&);
};

}

#endif
