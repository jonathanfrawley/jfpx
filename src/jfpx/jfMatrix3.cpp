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
#include "jfMatrix3.h"

jfMatrix3::jfMatrix3()
{
    int i;
    for(i=0;i<9;i++)
    {
        m_Elems[i] = (jfReal)0.0;
    }
    //Create Identity Matrix
    m_Elems[0] = 1;
    m_Elems[4] = 1;
    m_Elems[8] = 1;
}

jfMatrix3::jfMatrix3(jfReal e0, jfReal e1, jfReal e2,
                        jfReal e3, jfReal e4, jfReal e5,
                        jfReal e6, jfReal e7, jfReal e8)
{
	m_Elems[0] = e0;
	m_Elems[1] = e1;
	m_Elems[2] = e2;
	m_Elems[3] = e3;
	m_Elems[4] = e4;
	m_Elems[5] = e5;
	m_Elems[6] = e6;
	m_Elems[7] = e7;
	m_Elems[8] = e8;
}

jfMatrix3::jfMatrix3(const jfMatrix3& other)
{
    copyHere(other);
}

jfMatrix3& jfMatrix3::operator=(const jfMatrix3& other)
{
    copyHere(other);
    return (*this);
}

jfMatrix3::~jfMatrix3()
{
}

void jfMatrix3::copyHere(const jfMatrix3& other)
{
    unsigned i;
    for(i=0;i<9;i++)
    {
        m_Elems[i] = other.getElem(i);
    }
}
