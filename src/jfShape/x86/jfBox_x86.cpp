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

void jfBox_x86::init()
{
    m_BoxList = glGenLists(1);
    buildLists(*m_HalfSize);
}

void jfBox_x86::drawBox(const jfVector3& halfSize) const
{
    GLfloat x, y, z;
    //cout <<"halfSize is : "<<halfSize<<endl;
    x = (GLfloat)halfSize.getX();
    y = (GLfloat)halfSize.getY();
    z = (GLfloat)halfSize.getZ();

    glBegin(GL_QUADS);
    // Bottom Face
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-x, -y, -z); // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, -y, -z); // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, -y, z); // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, -y, z); // Bottom Right Of The Texture and Quad
    // Front Face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-x, -y, z); // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, -y, z); // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x, y, z); // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-x, y, z); // Top Left Of The Texture and Quad
    // Back Face
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-x, -y, -z); // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-x, y, -z); // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, y, -z); // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, -y, -z); // Bottom Left Of The Texture and Quad
    // Right face
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, -y, -z); // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x, y, -z); // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, y, z); // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, -y, z); // Bottom Left Of The Texture and Quad
    // Left Face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-x, -y, -z); // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-x, -y, z); // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-x, y, z); // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-x, y, -z); // Top Left Of The Texture and Quad
    // Top Face
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-x, y, -z); // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-x, y, z); // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, y, z); // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x, y, -z); // Top Right Of The Texture and Quad
    glEnd();
}

void jfBox_x86::buildLists(const jfVector3& halfSideLength) const
{
    glPushMatrix();
    glNewList(m_BoxList, GL_COMPILE);
    drawBox(*m_HalfSize);
    glEndList();
    glPopMatrix();
}

void jfBox_x86::render() const
{
    // Get the OpenGL transformation
    GLfloat mat[16];
    jfMatrix4_x86 transformMat;
    m_Body->getTransformMatrix(&transformMat);
    transformMat.fillColumnMajorArray(mat);

    glPushMatrix();
    glMultMatrixf(mat);
    //glScalef(m_HalfSize->getX()*2, m_HalfSize->getY()*2, m_HalfSize->getZ()*2);
    //glutSolidCube(1.0f);
    //drawCube(1.0f);
    //drawBox(*m_HalfSize);
    glCallList(m_BoxList);
    glPopMatrix();
}

void jfBox_x86::setState(BoxType type, const jfVector3& pos)
{
    m_Type = type;

    switch (m_Type) {
    case JF_BOX_LIGHT:
        //TODO
        break;
    case JF_BOX_HEAVY:
        m_Body->setMass(20.0f); // 20.0kg
        //m_Body->setVelocity(jfVector3_x86(0.0f, 30.0f, 40.0f)); // 50m/s
        //m_Body->setAccel(jfVector3_x86(0.0f, -9.8f, 0.0f));
        m_Body->setLinearDamping(0.99f);
        m_Body->setAngularDamping(0.8f);
        break;
    case JF_BOX_UNUSED:
        break;
    }
    jfMatrix3_x86 tensor;
    m_Body->setPos(pos);
    m_Body->setOrientation(jfQuaternion_x86(0, 0, 0, 0));
    m_Body->setVelocity(jfVector3_x86(0, 0, 0));
    m_Body->setRotation(jfVector3_x86(0, 0, 0));

    (*m_HalfSize) = jfVector3_x86(1, 1, 1);

    jfReal mass = m_HalfSize->getX() * m_HalfSize->getY() * m_HalfSize->getZ();
    m_Body->setMass(mass);

    tensor.setBlockInertiaTensor(*m_HalfSize, mass);
    m_Body->setInertiaTensor(tensor);

    m_Body->clearAccumulators();
    //Gravity
    m_Body->setAccel(jfVector3_x86(0, -9.81f, 0));

    m_Body->setCanSleep(true);
    m_Body->setAwake();
    m_Body->calculateDerivedData();
    calculateInternals();
    //Build OpenGL display lists again.
    buildLists(*m_HalfSize);
}
