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
#ifndef JFBOX_X86_H
#define JFBOX_X86_H

#include <jfpx/x86/jfCollisionBox_x86.h>
#include <jfpx/x86/jfRigidBody_x86.h>
#include <jfpx/x86/jfVector3_x86.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

/*
 * =====================================================================================
 *        Class: jfBox_x86
 *  Description: Represents a box which has a graphical and physical component.
 * =====================================================================================
 */
class jfBox_x86 : public jfCollisionBox_x86 {
public:
    jfBox_x86(); /* constructor */
    ~jfBox_x86(); /* destructor */

    /*-----------------------------------------------------------------------------
		 *  Interface
		 *-----------------------------------------------------------------------------*/
    virtual void render() const;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  setState
		 *  Description:  Sets the box to a position on the z axis along the track.
		 * =====================================================================================
		 */
    virtual void setState(const jfVector3& pos);

protected:
    virtual void drawCube(float halfSideLength) const;

private:
};

#endif //JFBOX_X86_H
