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
#ifndef UNITTEST_EXECUTE_TEST_H
#define UNITTEST_EXECUTE_TEST_H

#include "TestDetails.h"
#include "MemoryOutStream.h"
#include "AssertException.h"
#include "CurrentTest.h"

#ifdef UNITTEST_POSIX
	#include "Posix/SignalTranslator.h"
#endif

namespace UnitTest {

template< typename T >
void ExecuteTest(T& testObject, TestDetails const& details)
{
	CurrentTest::Details() = &details;

	try
	{
#ifdef UNITTEST_POSIX
		UNITTEST_THROW_SIGNALS
#endif
		testObject.RunImpl();
	}
	catch (AssertException const& e)
	{
		CurrentTest::Results()->OnTestFailure(
			TestDetails(details.testName, details.suiteName, e.Filename(), e.LineNumber()), e.what());
	}
	catch (std::exception const& e)
	{
		MemoryOutStream stream;
		stream << "Unhandled exception: " << e.what();
		CurrentTest::Results()->OnTestFailure(details, stream.GetText());
	}
	catch (...)
	{
		CurrentTest::Results()->OnTestFailure(details, "Unhandled exception: Crash!");
	}
}

}

#endif
