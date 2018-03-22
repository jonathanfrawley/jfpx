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
#include "jfBigBallistic3DGraphicsHandler_x86.h"

jfBigBallistic3DGraphicsHandler_x86::jfBigBallistic3DGraphicsHandler_x86()
{
}

jfBigBallistic3DGraphicsHandler_x86::~jfBigBallistic3DGraphicsHandler_x86()
{
}

int jfBigBallistic3DGraphicsHandler_x86::loadGLTextures()
{
    int status = 0;

    SDL_Surface* textureImage[1];

    if ((textureImage[0] = SDL_LoadBMP("../../../media/textures/box.bmp"))) {
        cout << "Loading texture...";
        status = 0;
        glGenTextures(1, &m_Textures[0]);
        glBindTexture(GL_TEXTURE_2D, m_Textures[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImage[0]->w,
            textureImage[0]->h, 0, GL_BGR,
            GL_UNSIGNED_BYTE, textureImage[0]->pixels);
    }

    if (textureImage[0]) {
        SDL_FreeSurface(textureImage[0]);
    }
    return status;
}

void jfBigBallistic3DGraphicsHandler_x86::initObjects()
{
    loadGLTextures();
    m_SphereQuadric = gluNewQuadric();
    gluQuadricDrawStyle(m_SphereQuadric, GLU_SMOOTH);
}

void jfBigBallistic3DGraphicsHandler_x86::drawSphere(float radius, int subdivisions) const
{
    gluQuadricNormals(m_SphereQuadric, GLU_SMOOTH);
    glPushMatrix();
    gluSphere(m_SphereQuadric, radius, subdivisions, subdivisions);
    glPopMatrix();
}

void jfBigBallistic3DGraphicsHandler_x86::drawObjects() const
{
    gluLookAt(0.0, 15.0, -30.0, 0.0, 5.0, 22.0, 0.0, 1.0, 0.0);

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

    vector<jfAmmoRound_x86*>::iterator it;
    // Render each particle in turn
    for (it = m_Ammo->begin(); it != m_Ammo->end(); ++it) {
        if ((*it)->getType() != UNUSED) {
            (*it)->render();
        }
    }

    const static GLfloat lightPosition[] = { -1, 1, 0, 0 };

    // Render the box
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    //glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    //glEnable(GL_COLOR_MATERIAL);
    //glColor3f(0.3,0.3,0.3);
    vector<jfBox_x86*>::iterator box;
    for (box = m_Boxes->begin(); box != m_Boxes->end(); box++) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, m_Textures[0]);
        //glColor3f(0.0,0.0,0.0);
        (*box)->render();
        glDisable(GL_TEXTURE_2D);
    }
    //glDisable(GL_COLOR_MATERIAL);
    //glDisable(GL_LIGHTING);
    //glDisable(GL_DEPTH_TEST);
}

void jfBigBallistic3DGraphicsHandler_x86::drawDebug(vector<jfContact*> contacts)
{
    // Render the contacts, if required
    vector<jfContact*>::iterator contact;
    glBegin(GL_LINES);
    for (contact = contacts.begin(); contact != contacts.end(); contact++) {
        jfVector3_x86 vec;
        jfVector3_x86 contactNormal;

        // Interbody contacts are in green, floor contacts are red.
        if ((*contact)->getBody(1)) {
            glColor3f(0, 1, 0);
        } else {
            glColor3f(1, 0, 0);
        }

        (*contact)->getContactPoint(&vec);
        glVertex3f(vec.getX(), vec.getY(), vec.getZ());

        (*contact)->getContactNormal(&contactNormal);
        vec += contactNormal;
        glVertex3f(vec.getX(), vec.getY(), vec.getZ());
    }

    glEnd();
}
