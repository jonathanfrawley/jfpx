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
#ifndef UNITTEST_CHECKS_H
#define UNITTEST_CHECKS_H

#include "Config.h"
#include "TestResults.h"
#include "MemoryOutStream.h"

namespace UnitTest {


template< typename Value >
bool Check(Value const value)
{
    return !!value; // doing double negative to avoid silly VS warnings
}


template< typename Expected, typename Actual >
void CheckEqual(TestResults& results, Expected const& expected, Actual const& actual, TestDetails const& details)
{
    if (!(expected == actual))
    {
        UnitTest::MemoryOutStream stream;
        stream << "Expected " << expected << " but was " << actual;

        results.OnTestFailure(details, stream.GetText());
    }
}

void CheckEqual(TestResults& results, char const* expected, char const* actual, TestDetails const& details);

void CheckEqual(TestResults& results, char* expected, char* actual, TestDetails const& details);

void CheckEqual(TestResults& results, char* expected, char const* actual, TestDetails const& details);

void CheckEqual(TestResults& results, char const* expected, char* actual, TestDetails const& details);

template< typename Expected, typename Actual, typename Tolerance >
bool AreClose(Expected const& expected, Actual const& actual, Tolerance const& tolerance)
{
    return (actual >= (expected - tolerance)) && (actual <= (expected + tolerance));
}

template< typename Expected, typename Actual, typename Tolerance >
void CheckClose(TestResults& results, Expected const& expected, Actual const& actual, Tolerance const& tolerance,
                TestDetails const& details)
{
    if (!AreClose(expected, actual, tolerance))
    { 
        UnitTest::MemoryOutStream stream;
        stream << "Expected " << expected << " +/- " << tolerance << " but was " << actual;

        results.OnTestFailure(details, stream.GetText());
    }
}


template< typename Expected, typename Actual >
void CheckArrayEqual(TestResults& results, Expected const& expected, Actual const& actual,
                int const count, TestDetails const& details)
{
    bool equal = true;
    for (int i = 0; i < count; ++i)
        equal &= (expected[i] == actual[i]);

    if (!equal)
    {
        UnitTest::MemoryOutStream stream;

		stream << "Expected [ ";

		for (int expectedIndex = 0; expectedIndex < count; ++expectedIndex)
            stream << expected[expectedIndex] << " ";

		stream << "] but was [ ";

		for (int actualIndex = 0; actualIndex < count; ++actualIndex)
            stream << actual[actualIndex] << " ";

		stream << "]";

        results.OnTestFailure(details, stream.GetText());
    }
}

template< typename Expected, typename Actual, typename Tolerance >
bool ArrayAreClose(Expected const& expected, Actual const& actual, int const count, Tolerance const& tolerance)
{
    bool equal = true;
    for (int i = 0; i < count; ++i)
        equal &= AreClose(expected[i], actual[i], tolerance);
    return equal;
}

template< typename Expected, typename Actual, typename Tolerance >
void CheckArrayClose(TestResults& results, Expected const& expected, Actual const& actual,
                   int const count, Tolerance const& tolerance, TestDetails const& details)
{
    bool equal = ArrayAreClose(expected, actual, count, tolerance);

    if (!equal)
    {
        UnitTest::MemoryOutStream stream;

        stream << "Expected [ ";
        for (int expectedIndex = 0; expectedIndex < count; ++expectedIndex)
            stream << expected[expectedIndex] << " ";
        stream << "] +/- " << tolerance << " but was [ ";

		for (int actualIndex = 0; actualIndex < count; ++actualIndex)
            stream << actual[actualIndex] << " ";
        stream << "]";

        results.OnTestFailure(details, stream.GetText());
    }
}

template< typename Expected, typename Actual, typename Tolerance >
void CheckArray2DClose(TestResults& results, Expected const& expected, Actual const& actual,
                   int const rows, int const columns, Tolerance const& tolerance, TestDetails const& details)
{
    bool equal = true;
    for (int i = 0; i < rows; ++i)
        equal &= ArrayAreClose(expected[i], actual[i], columns, tolerance);

    if (!equal)
    {
        UnitTest::MemoryOutStream stream;

        stream << "Expected [ ";    

		for (int expectedRow = 0; expectedRow < rows; ++expectedRow)
        {
            stream << "[ ";
            for (int expectedColumn = 0; expectedColumn < columns; ++expectedColumn)
                stream << expected[expectedRow][expectedColumn] << " ";
            stream << "] ";
        }

		stream << "] +/- " << tolerance << " but was [ ";

		for (int actualRow = 0; actualRow < rows; ++actualRow)
        {
            stream << "[ ";
            for (int actualColumn = 0; actualColumn < columns; ++actualColumn)
                stream << actual[actualRow][actualColumn] << " ";
            stream << "] ";
        }

		stream << "]";

        results.OnTestFailure(details, stream.GetText());
    }
}

}

#endif
