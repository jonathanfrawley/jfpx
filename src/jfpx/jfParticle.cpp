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
#include "jfParticle.h"

jfParticle::jfParticle() : m_Pos(0),
                            m_Vel(0),
                            m_Accel(0),
                            m_ForceAccum(0),
                            m_Damping(0),
                            m_InverseMass(0)
{
}

jfParticle::~jfParticle()
{
    delete m_Pos;
    delete m_Vel;
    delete m_Accel;
    delete m_ForceAccum;
}
