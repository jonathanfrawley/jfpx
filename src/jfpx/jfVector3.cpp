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

#include <jfpx/jfVector3.h>

jfVector3::jfVector3()
{
    m_X = (jfReal)0.0;
    m_Y = (jfReal)0.0;
    m_Z = (jfReal)0.0;
}

jfVector3::jfVector3(const jfReal x, const jfReal y, const jfReal z)
{
    m_X = (jfReal)x;
    m_Y = (jfReal)y;
    m_Z = (jfReal)z;
}

jfVector3::~jfVector3()
{
}

void jfVector3::copyHere(const jfVector3& other)
{
    m_X = other.getX();
    m_Y = other.getY();
    m_Z = other.getZ();
}
