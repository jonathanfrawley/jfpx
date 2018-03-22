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
#include "jfAmmoRound_x86.h"

jfAmmoRound_x86::jfAmmoRound_x86()
{
    m_SphereQuadric = gluNewQuadric();
    gluQuadricDrawStyle(m_SphereQuadric, GLU_SMOOTH);
    m_Timer = new jfTimer();
}

jfAmmoRound_x86::~jfAmmoRound_x86()
{
    delete m_Timer;
}

void jfAmmoRound_x86::drawSphere(float radius, int subdivisions)
{
    gluQuadricNormals(m_SphereQuadric, GLU_SMOOTH);
    glPushMatrix();
    gluSphere(m_SphereQuadric, radius, subdivisions, subdivisions);
    glPopMatrix();
}

void jfAmmoRound_x86::render()
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

void jfAmmoRound_x86::setState(ShotType shotType)
{
    m_Type = shotType;
    switch (m_Type) {
    case PISTOL:
        m_Body->setMass(1.5f);
        m_Body->setVelocity(jfVector3_x86(0.0f, 0.0f, 20.0f));
        m_Body->setAccel(jfVector3_x86(0.0f, -0.5f, 0.0f));
        m_Body->setLinearDamping(0.99f);
        m_Body->setAngularDamping(0.8f);
        m_Radius = 0.2f;
        break;
    case ARTILLERY:
        m_Body->setMass(200.0f); // 200.0kg
        m_Body->setVelocity(jfVector3_x86(0.0f, 30.0f, 40.0f)); // 50m/s
        m_Body->setAccel(jfVector3_x86(0.0f, -21.0f, 0.0f));
        m_Body->setLinearDamping(0.99f);
        m_Body->setAngularDamping(0.8f);
        m_Radius = 0.4f;
        break;
    case FIREBALL:
        m_Body->setMass(4.0f); // 4.0kg - mostly blast damage
        m_Body->setVelocity(jfVector3_x86(0.0f, -0.5f, 10.0)); // 10m/s
        m_Body->setAccel(jfVector3_x86(0.0f, 0.3f, 0.0f)); // Floats up
        m_Body->setLinearDamping(0.9f);
        m_Body->setAngularDamping(0.8f);
        m_Radius = 0.6f;
        break;
    case LASER:
        // Note that this is the kind of laser bolt seen in films,
        // not a realistic laser beam!
        m_Body->setMass(0.1f); // 0.1kg - almost no weight
        m_Body->setVelocity(jfVector3_x86(0.0f, 0.0f, 100.0f)); // 100m/s
        m_Body->setAccel(jfVector3_x86(0.0f, 0.0f, 0.0f)); // No gravity
        //m_Body->setAccel(jfVector3_x86(0.0f, 0.0f, 1.f)); //TEST
        m_Body->setLinearDamping(0.99f);
        m_Body->setAngularDamping(0.8f);
        m_Radius = 0.2f;
        break;
    case UNUSED:
        break;
    }
    m_Body->setCanSleep(false);
    m_Body->setAwake();
    jfMatrix3_x86 tensor;
    jfReal coeff = 0.4f * m_Body->getMass() * m_Radius * m_Radius;
    tensor.setInertiaTensorCoeffs(coeff, coeff, coeff);
    m_Body->setInertiaTensor(tensor);

    // Set the data common to all particle types
    //   m_Body->setPos(jfVector3_x86(0.0f, 0.5f, 0.0f));
    m_Body->setPos(jfVector3_x86(0.0f, 3.0f, 0.0f));
    m_StartTime = m_Timer->getTicks();

    // Clear the force accumulators
    m_Body->calculateDerivedData();
    calculateInternals();
}
