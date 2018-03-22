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
#include "jfAeroControlForceGenerator_x86.h"

jfAeroControlForceGenerator_x86::jfAeroControlForceGenerator_x86()
    : jfAeroControlForceGenerator()
{
}

jfAeroControlForceGenerator_x86::jfAeroControlForceGenerator_x86(const jfMatrix3& baseTensor,
    const jfMatrix3& minTensor,
    const jfMatrix3& maxTensor,
    const jfVector3& pos,
    jfVector3* windSpeed)
    : jfAeroControlForceGenerator(windSpeed)
{
    m_Tensor = new jfMatrix3_x86(baseTensor);
    m_Pos = new jfVector3_x86(pos);
    m_MinTensor = new jfMatrix3_x86(minTensor);
    m_MaxTensor = new jfMatrix3_x86(maxTensor);
}

jfAeroControlForceGenerator_x86::~jfAeroControlForceGenerator_x86()
{
}

void jfAeroControlForceGenerator_x86::updateForce(jfRigidBody* body,
    jfReal timeStep) const
{
    jfMatrix3_x86 t;
    getTensor(&t);
    updateForceFromTensor(body, timeStep, t);
}

void jfAeroControlForceGenerator_x86::getTensor(jfMatrix3* result) const
{
    //@REF:Millington code "fgen.cpp"
    if (m_ControlSetting <= -1.0f) {
        (*result) = (*m_MinTensor);
        return;
    } else if (m_ControlSetting >= 1.0f) {
        (*result) = (*m_MaxTensor);
        return;
    } else if (m_ControlSetting < 0) {
        result->linearInterpolate(*m_MinTensor, *m_Tensor, m_ControlSetting + 1.0f, result);
        return;
    } else if (m_ControlSetting > 0) {
        result->linearInterpolate(*m_Tensor, *m_MaxTensor, m_ControlSetting, result);
        return;
    } else {
        (*result) = (*m_Tensor);
        return;
    }
}

void jfAeroControlForceGenerator_x86::updateForceFromTensor(jfRigidBody* body,
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
