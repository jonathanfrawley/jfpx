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
#include "TestRunner.h"
#include "TestResults.h"
#include "TestReporter.h"
#include "TestReporterStdout.h"
#include "TimeHelpers.h"
#include "MemoryOutStream.h"

#include <cstring>


namespace UnitTest {

int RunAllTests()
{
	TestReporterStdout reporter;
	TestRunner runner(reporter);
	return runner.RunTestsIf(Test::GetTestList(), NULL, True(), 0);
}


TestRunner::TestRunner(TestReporter& reporter)
	: m_reporter(&reporter)
	, m_result(new TestResults(&reporter))
	, m_timer(new Timer)
{
	m_timer->Start();
}

TestRunner::~TestRunner()
{
	delete m_result;
	delete m_timer;
}

int TestRunner::Finish() const
{
    float const secondsElapsed = m_timer->GetTimeInMs() / 1000.0f;
    m_reporter->ReportSummary(m_result->GetTotalTestCount(), 
							  m_result->GetFailedTestCount(), 
							  m_result->GetFailureCount(), 
							  secondsElapsed);
    
	return m_result->GetFailureCount();
}

bool TestRunner::IsTestInSuite(const Test* const curTest, char const* suiteName) const
{
	using namespace std;
	return (suiteName == NULL) || !strcmp(curTest->m_details.suiteName, suiteName);
}

void TestRunner::RunTest(TestResults* const result, Test* const curTest, int const maxTestTimeInMs) const
{
	CurrentTest::Results() = result;

	Timer testTimer;
	testTimer.Start();

	result->OnTestStart(curTest->m_details);

	curTest->Run();

	int const testTimeInMs = testTimer.GetTimeInMs();
	if (maxTestTimeInMs > 0 && testTimeInMs > maxTestTimeInMs && !curTest->m_timeConstraintExempt)
	{
	    MemoryOutStream stream;
	    stream << "Global time constraint failed. Expected under " << maxTestTimeInMs <<
	            "ms but took " << testTimeInMs << "ms.";

	    result->OnTestFailure(curTest->m_details, stream.GetText());
	}

	result->OnTestFinish(curTest->m_details, testTimeInMs/1000.0f);
}

}
