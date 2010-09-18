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
#include "jfSDLGL3DGraphicsHandler.h"

jfSDLGL3DGraphicsHandler::jfSDLGL3DGraphicsHandler()
{
}

jfSDLGL3DGraphicsHandler::~jfSDLGL3DGraphicsHandler()
{
}

void jfSDLGL3DGraphicsHandler::init()
{
    /*
    int height = 768;
    int width = 1024;
    glViewport( 0, 0, height, width );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 60.0f, (GLfloat)height/(GLfloat)width, 0.1f, 5000.0f );
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0f, 0.2f, 0.4f, 0.0f);   // Black Background
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    initObjects();
*/
    GLfloat mat_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat mat_specular[] = { 0.9, 0.6, 0.6, 1.0 };
    GLfloat mat_shininess[] = { 30.0 };
    GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };
    GLfloat model_ambient[] = { 0.9, 0.9, 0.9, 0.9 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glViewport( 0, 0, 800, 600 );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 45.0f, (GLfloat)800.0f/(GLfloat)600.0f, 1000.0f, 5000.0f );
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);   // Black Background
    glEnable( GL_TEXTURE_2D );
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    initObjects();
}

void jfSDLGL3DGraphicsHandler::draw()
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();
    drawObjects();
    glFlush();
	//Goes at end
	SDL_GL_SwapBuffers();
}
