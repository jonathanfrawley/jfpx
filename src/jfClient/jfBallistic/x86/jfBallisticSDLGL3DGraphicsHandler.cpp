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
#include "jfBallisticSDLGL3DGraphicsHandler.h"

jfBallisticSDLGL3DGraphicsHandler::jfBallisticSDLGL3DGraphicsHandler()
{
}

jfBallisticSDLGL3DGraphicsHandler::~jfBallisticSDLGL3DGraphicsHandler()
{
}

void jfBallisticSDLGL3DGraphicsHandler::initObjects()
{
    m_SphereQuadric = gluNewQuadric();
    gluQuadricDrawStyle(m_SphereQuadric, GLU_SMOOTH);
}

void jfBallisticSDLGL3DGraphicsHandler::drawSphere(float radius, int subdivisions) const
{
    gluQuadricNormals(m_SphereQuadric, GLU_SMOOTH);
    glPushMatrix();
    gluSphere(m_SphereQuadric, radius, subdivisions, subdivisions);
    glPopMatrix();
}

void jfBallisticSDLGL3DGraphicsHandler::drawObjects() const
{
    gluLookAt(-15.0, 8.0, -15.0, 0.0, 5.0, 22.0, 0.0, 1.0, 0.0);

    // Draw a sphere at the firing point, and add a shadow projected
    // onto the ground plane.
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, 0.0f);
    drawSphere(0.1f, 5);
    glTranslatef(0.0f, -1.5f, 0.0f);
    glColor3f(0.75f, 0.75f, 0.75f);
    glScalef(1.0f, 0.1f, 1.0f);
    drawSphere(0.1f, 5);
    glPopMatrix();

    // Draw some scale lines
    glColor3f(0.75f, 0.75f, 0.75f);
    glBegin(GL_LINES);
    for (unsigned i = 0; i < 200; i += 10) {
        glVertex3f(-5.0f, 0.0f, i);
        glVertex3f(5.0f, 0.0f, i);
    }
    glEnd();

    vector<jfAmmoRound*>::iterator it;
    // Render each particle in turn
    for (it = m_Ammo->begin(); it != m_Ammo->end(); ++it) {
        if ((*it)->getType() != UNUSED) {
            (*it)->render();
        }
    }
}
