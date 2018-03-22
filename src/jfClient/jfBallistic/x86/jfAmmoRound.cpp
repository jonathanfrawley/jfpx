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
#include "jfAmmoRound.h"

jfAmmoRound::jfAmmoRound()
{
    m_SphereQuadric = gluNewQuadric();
    gluQuadricDrawStyle(m_SphereQuadric, GLU_SMOOTH);
    m_Particle = new jfParticle_x86();
}

jfAmmoRound::~jfAmmoRound()
{
    delete m_Particle;
}

void jfAmmoRound::drawSphere(float radius, int subdivisions)
{
    gluQuadricNormals(m_SphereQuadric, GLU_SMOOTH);
    glPushMatrix();
    gluSphere(m_SphereQuadric, radius, subdivisions, subdivisions);
    glPopMatrix();
}

void jfAmmoRound::render()
{
    jfVector3* position = m_Particle->getPos();

    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(position->getX(), position->getY(), position->getZ());
    drawSphere(1.3f, 5);
    glPopMatrix();

    glColor3f(0.75, 0.75, 0.75);
    glPushMatrix();
    glTranslatef(position->getX(), 0, position->getZ());
    glScalef(1.0f, 0.1f, 1.0f);
    drawSphere(1.6f, 5);
    glPopMatrix();
}
