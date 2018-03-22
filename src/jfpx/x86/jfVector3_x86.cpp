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

#include "jfVector3_x86.h"

jfVector3_x86::jfVector3_x86()
{
}

jfVector3_x86::jfVector3_x86(const jfReal x,
    const jfReal y,
    const jfReal z)
    : jfVector3(x, y, z)
{
}

jfVector3_x86::jfVector3_x86(const jfVector3& other)
    : jfVector3(other)
{
}

jfVector3_x86& jfVector3_x86::operator=(const jfVector3& other)
{
    copyHere(other);
    return (*this);
}

jfVector3_x86::~jfVector3_x86()
{
}

void jfVector3_x86::invert()
{
    m_X = -m_X;
    m_Y = -m_Y;
    m_Z = -m_Z;
}

jfReal jfVector3_x86::magnitude() const
{
    return jfRealSqrt((m_X * m_X) + (m_Y * m_Y) + (m_Z * m_Z));
}

jfReal jfVector3_x86::squareMagnitude() const
{
    return ((m_X * m_X) + (m_Y * m_Y) + (m_Z * m_Z));
}

void jfVector3_x86::normalize()
{
    jfReal mag = magnitude();
    if (mag > 0) {
        (*this) *= ((jfReal)1 / mag);
    }
}

void jfVector3_x86::operator*=(jfReal val)
{
    m_X *= val;
    m_Y *= val;
    m_Z *= val;
}

void jfVector3_x86::operator+=(const jfVector3& v)
{
    m_X += v.getX();
    m_Y += v.getY();
    m_Z += v.getZ();
}

void jfVector3_x86::operator-=(const jfVector3& v)
{
    m_X -= v.getX();
    m_Y -= v.getY();
    m_Z -= v.getZ();
}

void jfVector3_x86::addScaledVector(const jfVector3& v, jfReal scale)
{
    m_X += (v.getX() * scale);
    m_Y += (v.getY() * scale);
    m_Z += (v.getZ() * scale);
}

void jfVector3_x86::componentProductUpdate(const jfVector3& v)
{
    m_X *= v.getX();
    m_Y *= v.getY();
    m_Z *= v.getZ();
}

jfReal jfVector3_x86::dotProduct(const jfVector3& v) const
{
    return ((v.getX() * m_X) + (v.getY() * m_Y) + (v.getZ() * m_Z));
}

void jfVector3_x86::multiply(jfReal val, jfVector3* result) const
{
    result->setX(m_X * val);
    result->setY(m_Y * val);
    result->setZ(m_Z * val);
}

void jfVector3_x86::add(const jfVector3& vec, jfVector3* result) const
{
    result->setX(m_X + vec.getX());
    result->setY(m_Y + vec.getY());
    result->setZ(m_Z + vec.getZ());
}

void jfVector3_x86::subtract(const jfVector3& vec, jfVector3* result) const
{
    result->setX(m_X - vec.getX());
    result->setY(m_Y - vec.getY());
    result->setZ(m_Z - vec.getZ());
}

void jfVector3_x86::subtract(jfReal val, jfVector3* result) const
{
    result->setX(m_X - val);
    result->setY(m_Y - val);
    result->setZ(m_Z - val);
}

void jfVector3_x86::componentProduct(const jfVector3& vec, jfVector3* result) const
{
    result->setX(m_X * vec.getX());
    result->setY(m_Y * vec.getY());
    result->setZ(m_Z * vec.getZ());
}

void jfVector3_x86::crossProduct(const jfVector3& vec, jfVector3* result) const
{
    jfVector3_x86 tempResult;
    tempResult.setX((m_Y * vec.getZ()) - (m_Z * vec.getY()));
    tempResult.setY((m_Z * vec.getX()) - (m_X * vec.getZ()));
    tempResult.setZ((m_X * vec.getY()) - (m_Y * vec.getX()));
    (*result) = tempResult;
}
