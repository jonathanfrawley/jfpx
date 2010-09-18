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
#include "jfBox_x86.h"

jfBox_x86::jfBox_x86()
{
}

jfBox_x86::~jfBox_x86()
{
}

void jfBox_x86::drawCube(float halfSideLength) const
{
    glPushMatrix();
        //glColor3f(0.3,0.3,0.3);
        glBegin(GL_QUADS);
            // Front Face
            glNormal3f( 0.0f, 0.0f, halfSideLength);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-halfSideLength, -halfSideLength,  halfSideLength);
            glTexCoord2f(halfSideLength, 0.0f); glVertex3f( halfSideLength, -halfSideLength,  halfSideLength);
            glTexCoord2f(halfSideLength, halfSideLength); glVertex3f( halfSideLength,  halfSideLength,  halfSideLength);
            glTexCoord2f(0.0f, halfSideLength); glVertex3f(-halfSideLength,  halfSideLength,  halfSideLength);
            // Back Face
            glNormal3f( 0.0f, 0.0f,-halfSideLength);
            glTexCoord2f(halfSideLength, 0.0f); glVertex3f(-halfSideLength, -halfSideLength, -halfSideLength);
            glTexCoord2f(halfSideLength, halfSideLength); glVertex3f(-halfSideLength,  halfSideLength, -halfSideLength);
            glTexCoord2f(0.0f, halfSideLength); glVertex3f( halfSideLength,  halfSideLength, -halfSideLength);
            glTexCoord2f(0.0f, 0.0f); glVertex3f( halfSideLength, -halfSideLength, -halfSideLength);
            // Top Face
            glNormal3f( 0.0f, halfSideLength, 0.0f);
            glTexCoord2f(0.0f, halfSideLength); glVertex3f(-halfSideLength,  halfSideLength, -halfSideLength);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-halfSideLength,  halfSideLength,  halfSideLength);
            glTexCoord2f(halfSideLength, 0.0f); glVertex3f( halfSideLength,  halfSideLength,  halfSideLength);
            glTexCoord2f(halfSideLength, halfSideLength); glVertex3f( halfSideLength,  halfSideLength, -halfSideLength);
            // Bottom Face
            glNormal3f( 0.0f,-halfSideLength, 0.0f);
            glTexCoord2f(halfSideLength, halfSideLength); glVertex3f(-halfSideLength, -halfSideLength, -halfSideLength);
            glTexCoord2f(0.0f, halfSideLength); glVertex3f( halfSideLength, -halfSideLength, -halfSideLength);
            glTexCoord2f(0.0f, 0.0f); glVertex3f( halfSideLength, -halfSideLength,  halfSideLength);
            glTexCoord2f(halfSideLength, 0.0f); glVertex3f(-halfSideLength, -halfSideLength,  halfSideLength);
            // Right Face
            glNormal3f( halfSideLength, 0.0f, 0.0f);
            glTexCoord2f(halfSideLength, 0.0f); glVertex3f( halfSideLength, -halfSideLength, -halfSideLength);
            glTexCoord2f(halfSideLength, halfSideLength); glVertex3f( halfSideLength,  halfSideLength, -halfSideLength);
            glTexCoord2f(0.0f, halfSideLength); glVertex3f( halfSideLength,  halfSideLength,  halfSideLength);
            glTexCoord2f(0.0f, 0.0f); glVertex3f( halfSideLength, -halfSideLength,  halfSideLength);
            // Left Face
            glNormal3f(-halfSideLength, 0.0f, 0.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-halfSideLength, -halfSideLength, -halfSideLength);
            glTexCoord2f(halfSideLength, 0.0f); glVertex3f(-halfSideLength, -halfSideLength,  halfSideLength);
            glTexCoord2f(halfSideLength, halfSideLength); glVertex3f(-halfSideLength,  halfSideLength,  halfSideLength);
            glTexCoord2f(0.0f, halfSideLength); glVertex3f(-halfSideLength,  halfSideLength, -halfSideLength);

        glEnd();
    glPopMatrix();
}

void jfBox_x86::render() const
{
    // Get the OpenGL transformation
    GLfloat mat[16];
    jfMatrix4_x86 transformMat;
    m_Body->getTransformMatrix(&transformMat);
    transformMat.fillColumnMajorArray(mat);

    jfVector3_x86 pos;
    m_Body->getPos(&pos);
    cout <<"Box pos is : "<<pos<<endl;

    //glPushMatrix();
    glMultMatrixf(mat);
    //glScalef(m_HalfSize->getX()*2, m_HalfSize->getY()*2, m_HalfSize->getZ()*2);
    //glutSolidCube(1.0f);
    drawCube(1.0f);
    //glPopMatrix();
}

void jfBox_x86::setState(const jfVector3& pos)
{
    m_Body->setPos(pos);
    m_Body->setOrientation(jfQuaternion_x86(0,0,0,0));
    m_Body->setVelocity(jfVector3_x86(0,0,0));
    m_Body->setRotation(jfVector3_x86(0,0,0));
    (*m_HalfSize) = jfVector3_x86(2,2,2);

    jfReal mass = m_HalfSize->getX() * m_HalfSize->getY() * m_HalfSize->getZ();// * 8.0f;
    //jfReal mass = 1.1;
    m_Body->setMass(mass);

    jfMatrix3_x86 tensor;
    tensor.setBlockInertiaTensor(*m_HalfSize, mass);
    m_Body->setInertiaTensor(tensor);

    m_Body->setLinearDamping(0.95f);
    m_Body->setAngularDamping(0.99f);
    m_Body->clearAccumulators();
    //Gravity
    m_Body->setAccel(jfVector3_x86(0,-9.81f,0));

    m_Body->setCanSleep(true);
    m_Body->setAwake();
    m_Body->calculateDerivedData();
    calculateInternals();
}
