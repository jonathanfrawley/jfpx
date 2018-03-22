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
#include "jfWorld_x86.h"

jfWorld_x86::jfWorld_x86()
{
}

jfWorld_x86::~jfWorld_x86()
{
}

void jfWorld_x86::startFrame()
{
    //@REF: Millington p.215
    vector<jfRigidBody*>::iterator it;
    for (it = m_Bodies.begin(); it != m_Bodies.end(); it++) {
        (*it)->clearAccumulators();
        (*it)->calculateDerivedData();
    }
}

void jfWorld_x86::step(jfReal timeStep)
{
    //@REF: Millington p.215
    vector<jfRigidBody*>::iterator it;
    for (it = m_Bodies.begin(); it != m_Bodies.end(); it++) {
        (*it)->integrate(timeStep);
    }
}
