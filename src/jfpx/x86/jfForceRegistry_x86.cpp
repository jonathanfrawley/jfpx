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
#include "jfForceRegistry_x86.h"

jfForceRegistry_x86::jfForceRegistry_x86()
{
    //ctor
}

jfForceRegistry_x86::~jfForceRegistry_x86()
{
    //dtor
}

void jfForceRegistry_x86::add(jfRigidBody* body, jfForceGenerator* forceGen)
{
    jfBodyForceGen bodyForceGen;
    bodyForceGen.body = body;
    bodyForceGen.forceGen = forceGen;
    m_BodyForceGens.push_back(bodyForceGen);
}

void jfForceRegistry_x86::remove(jfRigidBody* body, jfForceGenerator* forceGen)
{
    vector<jfBodyForceGen>::iterator it;
    for (it = m_BodyForceGens.begin(); it != m_BodyForceGens.end(); it++) {
        if ((body == (*it).body) && (forceGen == (*it).forceGen)) {
            m_BodyForceGens.erase(it);
            return;
        }
    }
}

void jfForceRegistry_x86::clear()
{
    m_BodyForceGens.clear();
}

void jfForceRegistry_x86::updateForces(jfReal timeStep)
{
    vector<jfBodyForceGen>::iterator it;
    for (it = m_BodyForceGens.begin(); it != m_BodyForceGens.end(); it++) {
        (*it).forceGen->updateForce((*it).body, timeStep);
    }
}
