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
#include "jfAeroForceGenerator_x86.h"

jfAeroForceGenerator_x86::jfAeroForceGenerator_x86()
    : jfAeroForceGenerator()
{
    m_WindSpeed = new jfVector3_x86();
    m_Tensor = new jfMatrix3_x86();
    m_Pos = new jfVector3_x86();
}

jfAeroForceGenerator_x86::jfAeroForceGenerator_x86(const jfMatrix3& tensor,
    const jfVector3& pos,
    jfVector3* windSpeed)
    : jfAeroForceGenerator(windSpeed)
{
    m_Tensor = new jfMatrix3_x86(tensor);
    m_Pos = new jfVector3_x86(pos);
}

jfAeroForceGenerator_x86::~jfAeroForceGenerator_x86()
{
}

void jfAeroForceGenerator_x86::updateForce(jfRigidBody* body, jfReal timeStep) const
{
    updateForceFromTensor(body, timeStep, (*m_Tensor));
}

void jfAeroForceGenerator_x86::updateForceFromTensor(jfRigidBody* body,
    jfReal timeStep,
    jfMatrix3& tensor) const
{
    //@REF: Millington code "fgen.cpp"
    jfMatrix4_x86 bodyTransformMatrix;
    jfVector3_x86 velocity;
    jfVector3_x86 bodyVel;
    jfVector3_x86 bodyForce;
    jfVector3_x86 force;

    body->getVelocity(&velocity);
    velocity += (*m_WindSpeed);
    body->getTransformMatrix(&bodyTransformMatrix);
    bodyTransformMatrix.transformInverseDirection(velocity, &bodyVel);
    tensor.transform(bodyVel, &bodyForce);
    bodyTransformMatrix.transformDirection(bodyForce, &force);
    body->addForceAtBodyPoint(force, (*m_Pos));
}
