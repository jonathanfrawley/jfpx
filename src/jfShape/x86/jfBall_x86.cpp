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
#include "jfBall_x86.h"

jfBall_x86::jfBall_x86()
{
    m_SphereQuadric = gluNewQuadric();
    gluQuadricDrawStyle(m_SphereQuadric, GLU_SMOOTH);
    gluQuadricTexture(m_SphereQuadric, GL_TRUE);
}

jfBall_x86::~jfBall_x86()
{
    gluDeleteQuadric(m_SphereQuadric);
}

void jfBall_x86::drawSphere(float radius, int subdivisions) const
{
    glPushMatrix();
    gluSphere(m_SphereQuadric, radius, subdivisions, subdivisions);
    glPopMatrix();
}

void jfBall_x86::render() const
{
    // Get the OpenGL transformation
    GLfloat mat[16];
    jfMatrix4_x86 transformMat;
    m_Body->getTransformMatrix(&transformMat);
    transformMat.fillColumnMajorArray(mat);

    glPushMatrix();
    glMultMatrixf(mat);
    drawSphere(m_Radius, 20);
    glPopMatrix();
}

void jfBall_x86::setState(BallType ballType, const jfVector3& pos)
{
    jfMatrix3_x86 tensor;

    m_Type = ballType;
    switch (m_Type) {
    case JF_BALL_LIGHT:
        //TODO
        break;
    case JF_BALL_HEAVY:
        m_Body->setMass(20.0f); // 20.0kg
        //m_Body->setVelocity(jfVector3_x86(0.0f, 30.0f, 40.0f)); // 50m/s
        //m_Body->setAccel(jfVector3_x86(0.0f, -9.8f, 0.0f));
        m_Body->setLinearDamping(0.99f);
        m_Body->setAngularDamping(0.8f);
        break;
    case JF_BALL_UNUSED:
        break;
    }
    m_Radius = 1.0f;
    m_Body->setCanSleep(true);
    m_Body->setAwake();

    jfReal coeff = 0.4f * m_Body->getMass() * m_Radius * m_Radius;
    tensor.setInertiaTensorCoeffs(coeff, coeff, coeff);
    m_Body->setInertiaTensor(tensor);

    //Our good friend gravity
    m_Body->setAccel(jfVector3_x86(0.0f, -9.8f, 0.0f));

    // Set the data common to all particle types
    m_Body->setPos(pos);

    // Clear the force accumulators
    m_Body->calculateDerivedData();
    calculateInternals();
}
