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
#include "jfQuaternion.h"

jfQuaternion::jfQuaternion()
    : m_R(0)
    , m_I(0)
    , m_J(0)
    , m_K(0)
{
}

jfQuaternion::jfQuaternion(jfReal r, jfReal i, jfReal j, jfReal k)
    : m_R(r)
    , m_I(i)
    , m_J(j)
    , m_K(k)
{
}

jfQuaternion::jfQuaternion(const jfQuaternion& other)
    : m_R(other.getR())
    , m_I(other.getI())
    , m_J(other.getJ())
    , m_K(other.getK())
{
}

jfQuaternion::~jfQuaternion()
{
}
