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
#include "jfParticle_x86.h"

jfParticle_x86::jfParticle_x86()
{
    m_ForceAccum = new jfVector3_x86();
    m_ForceAccum->clear();
}

jfParticle_x86::~jfParticle_x86()
{
}

void jfParticle_x86::integrate(jfReal timeStep)
{
    if (timeStep < 0.0) {
        return;
    }

    m_Pos->addScaledVector((*m_Vel), timeStep); //Update position

    jfVector3_x86* newAccel = new jfVector3_x86(m_Accel->getX(), m_Accel->getY(), m_Accel->getZ());
    newAccel->addScaledVector((*m_ForceAccum), m_InverseMass);

    m_Vel->addScaledVector((*newAccel), timeStep);

    (*m_Vel) *= jfRealPow(m_Damping, timeStep);

    m_ForceAccum->clear();

    delete newAccel;
}
