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
#ifndef JFFLIGHT3DGRAPHICSHANDLER_X86_H
#define JFFLIGHT3DGRAPHICSHANDLER_X86_H

#include <jfGraphics/jf3DGraphics/jfSDLGL/jfSDLGL3DGraphicsHandler.h>
#include <jfLog/jfLog.h>
#include <jfpx/jfRigidBody.h>
#include <jfpx/x86/jfMatrix4_x86.h>
#include <jfpx/x86/jfVector3_x86.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdio.h>

class jfFlight3DGraphicsHandler_x86 : public jfSDLGL3DGraphicsHandler {
public:
    jfFlight3DGraphicsHandler_x86();
    virtual ~jfFlight3DGraphicsHandler_x86();

    /*
		* ===  FUNCTION  ======================================================================
		*         Name:  setAircraft
		*  Description:  Sets pointer to Aircraft
		* =====================================================================================
		*/
    void setAircraft(jfRigidBody* val) { aircraft = val; }

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  drawAircraft
		 *  Description:  Draws the aircraft using OpenGL.
		 * =====================================================================================
		 */
    void drawAircraft() const;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  drawCube
		 *  Description:  Draws a cube using OpenGL.
		 * =====================================================================================
		 */
    void drawCube(float length) const;
    /* Inherited methods */
    virtual void initObjects();
    virtual void drawObjects() const;

protected:
    jfRigidBody* aircraft; //Not our object
private:
};

#endif // JFFLIGHT3DGRAPHICSHANDLER_X86_H
