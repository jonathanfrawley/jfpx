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
#include "../TestList.h"

using namespace UnitTest;

namespace {


TEST (TestListIsEmptyByDefault)
{
    TestList list;
    CHECK (list.GetHead() == 0);
}

TEST (AddingTestSetsHeadToTest)
{
    Test test("test");
    TestList list;
    list.Add(&test);

    CHECK (list.GetHead() == &test);
    CHECK (test.next == 0);
}

TEST (AddingSecondTestAddsItToEndOfList)
{
    Test test1("test1");
    Test test2("test2");

    TestList list;
    list.Add(&test1);
    list.Add(&test2);

    CHECK (list.GetHead() == &test1);
    CHECK (test1.next == &test2);
    CHECK (test2.next == 0);
}

TEST (ListAdderAddsTestToList)
{
    TestList list;

    Test test("");    
    ListAdder adder(list, &test);

    CHECK (list.GetHead() == &test);
    CHECK (test.next == 0);
}

}
