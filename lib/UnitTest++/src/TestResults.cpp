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
#include "TestResults.h"
#include "TestReporter.h"

#include "TestDetails.h"

namespace UnitTest {

TestResults::TestResults(TestReporter* testReporter)
    : m_testReporter(testReporter)
    , m_totalTestCount(0)
    , m_failedTestCount(0)
    , m_failureCount(0)
    , m_currentTestFailed(false)
{
}

void TestResults::OnTestStart(TestDetails const& test)
{
    ++m_totalTestCount;
    m_currentTestFailed = false;
    if (m_testReporter)
        m_testReporter->ReportTestStart(test);
}

void TestResults::OnTestFailure(TestDetails const& test, char const* failure)
{
    ++m_failureCount;
    if (!m_currentTestFailed)
    {
        ++m_failedTestCount;
        m_currentTestFailed = true;
    }

    if (m_testReporter)
        m_testReporter->ReportFailure(test, failure);
}

void TestResults::OnTestFinish(TestDetails const& test, float secondsElapsed)
{
    if (m_testReporter)
        m_testReporter->ReportTestFinish(test, secondsElapsed);
}

int TestResults::GetTotalTestCount() const
{
    return m_totalTestCount;
}

int TestResults::GetFailedTestCount() const
{
    return m_failedTestCount;
}

int TestResults::GetFailureCount() const
{
    return m_failureCount;
}


}
