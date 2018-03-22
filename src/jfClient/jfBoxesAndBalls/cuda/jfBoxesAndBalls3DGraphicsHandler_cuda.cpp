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
#include "jfBoxesAndBalls3DGraphicsHandler_cuda.h"

jfBoxesAndBalls3DGraphicsHandler_cuda::jfBoxesAndBalls3DGraphicsHandler_cuda()
{
}

jfBoxesAndBalls3DGraphicsHandler_cuda::~jfBoxesAndBalls3DGraphicsHandler_cuda()
{
}

void jfBoxesAndBalls3DGraphicsHandler_cuda::drawSphere(float radius,
    int subdivisions) const
{
    gluQuadricNormals(m_SphereQuadric, GLU_SMOOTH);
    glPushMatrix();
    gluSphere(m_SphereQuadric, radius, subdivisions, subdivisions);
    glPopMatrix();
}

int jfBoxesAndBalls3DGraphicsHandler_cuda::loadGLTextures()
{
    int status = 0;

    SDL_Surface* textureImage[2];

    textureImage[0] = SDL_LoadBMP("../../../media/textures/box.bmp");
    textureImage[1] = SDL_LoadBMP("../../../media/textures/ball.bmp");

    if ((textureImage[0] && textureImage[1])) {
        cout << "Loading texture...";
        status = 0;
        glGenTextures(2, &m_Textures[0]);
        glBindTexture(GL_TEXTURE_2D, m_Textures[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImage[0]->w,
            textureImage[0]->h, 0, GL_BGR,
            GL_UNSIGNED_BYTE, textureImage[0]->pixels);

        glBindTexture(GL_TEXTURE_2D, m_Textures[1]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImage[1]->w,
            textureImage[1]->h, 0, GL_BGR,
            GL_UNSIGNED_BYTE, textureImage[1]->pixels);
    }

    if (textureImage[0]) {
        SDL_FreeSurface(textureImage[0]);
    }
    if (textureImage[1]) {
        SDL_FreeSurface(textureImage[1]);
    }
    return status;
}

void jfBoxesAndBalls3DGraphicsHandler_cuda::initObjects()
{
    loadGLTextures();
    m_SphereQuadric = gluNewQuadric();
    gluQuadricDrawStyle(m_SphereQuadric, GLU_SMOOTH);
}

void jfBoxesAndBalls3DGraphicsHandler_cuda::drawObjects() const
{
    //gluLookAt(-15.0, 8.0, -15.0,  0.0, 5.0, 22.0,  0.0, 1.0, 0.0);
    jfVector3_x86 camRot, camPos;
    cam->getRot(&camRot);
    cam->getPos(&camPos);
    glRotatef(camRot.getX(), 1.0, 0.0, 0.0);
    glRotatef(camRot.getY(), 0.0, 1.0, 0.0);
    glRotatef(camRot.getZ(), 0.0, 0.0, 1.0);

    GLfloat xtrans = -(camPos.getX());
    GLfloat ytrans = -(camPos.getY());
    GLfloat ztrans = -(camPos.getZ());
    glTranslatef(xtrans, ytrans, ztrans);

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
    for (unsigned i = 0; i < 200; i += 3) {
        glVertex3f(-50.0f, 0.0f, i);
        glVertex3f(50.0f, 0.0f, i);
    }
    glEnd();

    vector<jfBall*>::iterator ball;
    // Render each ball in turn
    for (ball = m_Balls->begin(); ball != m_Balls->end(); ball++) {
        glEnable(GL_TEXTURE_2D);
        //glEnable(GL_COLOR_MATERIAL);
        //glColor3f(0.1f, 0.1f, 0.1f);
        glBindTexture(GL_TEXTURE_2D, m_Textures[1]);
        if ((*ball)->getType() != JF_BALL_UNUSED) {
            (*ball)->render();
        }
        glDisable(GL_TEXTURE_2D);
    }
    vector<jfBox*>::iterator box;
    for (box = m_Boxes->begin(); box != m_Boxes->end(); box++) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, m_Textures[0]);
        if ((*box)->getType() != JF_BOX_UNUSED) {
            (*box)->render();
        }
        glDisable(GL_TEXTURE_2D);
    }
}

void jfBoxesAndBalls3DGraphicsHandler_cuda::drawDebug(vector<jfContact*> contacts) const
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
