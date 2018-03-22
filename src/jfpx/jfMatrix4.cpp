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
#include "jfMatrix4.h"

jfMatrix4::jfMatrix4()
{
    //Create Identity Matrix
    int i;
    for (i = 0; i < 16; i++) {
        m_Elems[i] = (jfReal)0.0;
    }
    m_Elems[0] = 1;
    m_Elems[5] = 1;
    m_Elems[10] = 1;
    m_Elems[15] = 1;
}

jfMatrix4::jfMatrix4(const jfMatrix4& other)
{
    copyHere(other);
}

jfMatrix4& jfMatrix4::operator=(const jfMatrix4& other)
{
    copyHere(other);
    return (*this);
}

jfMatrix4::~jfMatrix4()
{
    //dtor
}

void jfMatrix4::copyHere(const jfMatrix4& other)
{
    unsigned i;
    for (i = 0; i < 16; i++) {
        m_Elems[i] = other.getElem(i);
    }
}
