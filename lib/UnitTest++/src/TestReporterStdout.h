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
#ifndef UNITTEST_TESTREPORTERSTDOUT_H
#define UNITTEST_TESTREPORTERSTDOUT_H

#include "TestReporter.h"

namespace UnitTest {

class TestReporterStdout : public TestReporter
{
private:
    virtual void ReportTestStart(TestDetails const& test);
    virtual void ReportFailure(TestDetails const& test, char const* failure);
    virtual void ReportTestFinish(TestDetails const& test, float secondsElapsed);
    virtual void ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed);
};

}

#endif 
