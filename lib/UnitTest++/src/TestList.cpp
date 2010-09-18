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
#include "TestList.h"
#include "Test.h"

#include <cassert>

namespace UnitTest {

TestList::TestList() 
    : m_head(0)
    , m_tail(0)
{
}

void TestList::Add(Test* test)
{
    if (m_tail == 0)
    {
        assert(m_head == 0);
        m_head = test;
        m_tail = test;
    }
    else
    {
        m_tail->next = test;
        m_tail = test;
    }
}

Test* TestList::GetHead() const
{
    return m_head;
}

ListAdder::ListAdder(TestList& list, Test* test)
{
    list.Add(test);
}

}
