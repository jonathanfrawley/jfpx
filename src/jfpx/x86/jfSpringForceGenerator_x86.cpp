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
#include "jfSpringForceGenerator_x86.h"

jfSpringForceGenerator_x86::jfSpringForceGenerator_x86()
{
}

jfSpringForceGenerator_x86::jfSpringForceGenerator_x86(jfVector3* connectionPoint,
    jfRigidBody* other,
    jfVector3* otherConnectionPoint,
    jfReal springConstant,
    jfReal restLength)
    : jfSpringForceGenerator(connectionPoint,
          other,
          otherConnectionPoint,
          springConstant,
          restLength)
{
}

jfSpringForceGenerator_x86::~jfSpringForceGenerator_x86()
{
}

void jfSpringForceGenerator_x86::updateForce(jfRigidBody* body, jfReal duration)
{
    //Millington p.210
    //2 ends
    jfVector3_x86 end0;
    jfVector3_x86 end1;
    jfVector3_x86 force;

    body->getPointInWorldSpace(*m_ConnectionPoint, &end0);
    m_Other->getPointInWorldSpace(*m_OtherConnectionPoint, &end1);
    end0.subtract(end1, &force);

    jfReal magnitude = force.magnitude();
    magnitude = jfRealAbs(magnitude - m_RestLength);
    magnitude *= m_SpringConstant;

    force.normalize();
    force *= (-magnitude);
    body->addForceAtPoint(force, end0);
}
