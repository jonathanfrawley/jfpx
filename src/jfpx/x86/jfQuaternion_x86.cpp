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
#include "jfQuaternion_x86.h"

jfQuaternion_x86::jfQuaternion_x86()
{
}

jfQuaternion_x86::jfQuaternion_x86(jfReal r, jfReal i, jfReal j, jfReal k)
    : jfQuaternion(r, i, j, k)
{
}

jfQuaternion_x86::jfQuaternion_x86(const jfQuaternion& other)
    : jfQuaternion(other)
{
}

jfQuaternion_x86::~jfQuaternion_x86()
{
}

void jfQuaternion_x86::normalize()
{
    //Millington p.187
    jfReal d = (m_R * m_R) + (m_I * m_I) + (m_J * m_J) + (m_K * m_K);

    //Zero length quaternion, so give no-rotation quaternion.
    if (d == 0) {
        m_R = 1;
        return;
    }

    d = ((jfReal)1.0 / jfRealSqrt(d));
    m_R *= d;
    m_I *= d;
    m_J *= d;
    m_K *= d;
}

void jfQuaternion_x86::operator*=(const jfQuaternion& other)
{
    //Millington p.188
    jfReal oldR = m_R;
    jfReal oldI = m_I;
    jfReal oldJ = m_J;
    jfReal oldK = m_K;
    m_R = (oldR * other.getR()) - (oldI * other.getI()) - (oldJ * other.getJ()) - (oldK * other.getK());
    m_I = (oldR * other.getI()) + (oldI * other.getR()) + (oldJ * other.getK()) - (oldK * other.getJ());
    m_J = (oldR * other.getJ()) + (oldJ * other.getR()) + (oldK * other.getI()) - (oldI * other.getK());
    m_K = (oldR * other.getK()) + (oldK * other.getR()) + (oldI * other.getJ()) - (oldJ * other.getI());
}

void jfQuaternion_x86::rotateByVector(const jfVector3& vec)
{
    //Millington p.189
    jfQuaternion_x86 q(0, vec.getX(), vec.getY(), vec.getZ());
    (*this) *= q;
}

void jfQuaternion_x86::addScaledVector(const jfVector3& vec, jfReal scale)
{
    //Millington p.190
    jfQuaternion_x86 q(0,
        vec.getX() * scale,
        vec.getY() * scale,
        vec.getZ() * scale);
    q *= *this;
    m_R += q.getR() * ((jfReal)0.5);
    m_I += q.getI() * ((jfReal)0.5);
    m_J += q.getJ() * ((jfReal)0.5);
    m_K += q.getK() * ((jfReal)0.5);
}
