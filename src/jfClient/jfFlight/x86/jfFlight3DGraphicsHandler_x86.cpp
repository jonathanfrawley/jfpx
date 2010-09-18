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
#include "jfFlight3DGraphicsHandler_x86.h"

jfFlight3DGraphicsHandler_x86::jfFlight3DGraphicsHandler_x86() : aircraft(0)
{
}

jfFlight3DGraphicsHandler_x86::~jfFlight3DGraphicsHandler_x86()
{
}

void jfFlight3DGraphicsHandler_x86::initObjects()
{
}

void jfFlight3DGraphicsHandler_x86::drawCube(float length) const
{
    float halfSideLength = (float)length / 2.0;

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
}

void jfFlight3DGraphicsHandler_x86::drawAircraft() const
{
    // Fuselage
    glPushMatrix();
    glTranslatef(-0.5f, 0, 0);
    glScalef(2.0f, 0.8f, 1.0f);
    drawCube(1.0f);
    glPopMatrix();

    // Rear Fuselage
    glPushMatrix();
    glTranslatef(1.0f, 0.15f, 0);
    glScalef(2.75f, 0.5f, 0.5f);
    drawCube(1.0f);
    glPopMatrix();

    // Wings
    glPushMatrix();
    glTranslatef(0, 0.3f, 0);
    glScalef(0.8f, 0.1f, 6.0f);
    drawCube(1.0f);
    glPopMatrix();

    // Rudder
    glPushMatrix();
    glTranslatef(2.0f, 0.775f, 0);
    glScalef(0.75f, 1.15f, 0.1f);
    drawCube(1.0f);
    glPopMatrix();

    // Tail-plane
    glPushMatrix();
    glTranslatef(1.9f, 0, 0);
    glScalef(0.85f, 0.1f, 2.0f);
    drawCube(1.0f);
    glPopMatrix();
}

void jfFlight3DGraphicsHandler_x86::drawObjects() const
{
	//@REF:Millington code "flightsim.cpp"
	jfVector3_x86 pos;
    jfVector3_x86 velocity;
    jfMatrix4_x86 transformMatrix;

    glLoadIdentity();

    aircraft->getPos(&pos);
    aircraft->getVelocity(&velocity);
    jfVector3_x86 offset = jfVector3_x86((4.0f+velocity.magnitude()),
											0,
											0);
    aircraft->getTransformMatrix(&transformMatrix);
    transformMatrix.transformDirection(offset, &offset);
	//Camera
    gluLookAt((pos.getX()+offset.getX()),
				(pos.getY()+5.0f),
				(pos.getZ()+offset.getZ()),
				pos.getX(),
				pos.getY(),
				pos.getZ(),
				0.0,
				1.0,
				0.0);

    glColor3f(0.6f,0.6f,0.6f);
    int bx = int(pos.getX());
    int bz = int(pos.getZ());
    glBegin(GL_QUADS);
    for (int x = -20; x <= 20; x++) for (int z = -20; z <= 20; z++)
    {
		/* Water grid drawn here*/
        glVertex3f(bx+x-0.1f, 0, bz+z-0.1f);
        glVertex3f(bx+x-0.1f, 0, bz+z+0.1f);
        glVertex3f(bx+x+0.1f, 0, bz+z+0.1f);
        glVertex3f(bx+x+0.1f, 0, bz+z-0.1f);
    }
    glEnd();

    // Set the transform matrix for the aircraft
    GLfloat glTransform[16];
    transformMatrix.fillColumnMajorArray(glTransform);
    glPushMatrix();
    glMultMatrixf(glTransform); //Transformation happens here

    // Draw the aircraft
    glColor3f(0,0,0);
    drawAircraft();
    glPopMatrix();

	//Draw reflection in water
    glColor3f(0.8f, 0.8f, 0.8f);
    glPushMatrix();
    glTranslatef(0, -1.0f - pos.getY(), 0);
    glScalef(1.0f, 0.001f, 1.0f);
    glMultMatrixf(glTransform);
    drawAircraft();
    glPopMatrix();

    char buf[256];
    sprintf(
        buf,
        "Altitude: %.1f | Speed %.1f",
        pos.getY(),
        velocity.magnitude()
        );
    log(buf);
}
