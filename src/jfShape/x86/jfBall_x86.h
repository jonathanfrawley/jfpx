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
#ifndef JFAMMOROUND_H
#define JFAMMOROUND_H

#include <jfShape/jfBall.h>

#include <jfpx/x86/jfMatrix3_x86.h>
#include <jfpx/x86/jfRigidBody_x86.h>
#include <jfpx/x86/jfCollisionSphere_x86.h>
#include <jfTimer/jfTimer.h>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>


class jfBall_x86 : public jfBall
{
    public:
        jfBall_x86();

        virtual ~jfBall_x86();

		/*-----------------------------------------------------------------------------
		 *  Interface
		 *-----------------------------------------------------------------------------*/
		/*-----------------------------------------------------------------------------
		 *  Inherited Methods
		 *-----------------------------------------------------------------------------*/
	   /*
		* ===  FUNCTION  ======================================================================
		*         Name:  render
		*  Description:  Renders the current sphere.
		* =====================================================================================
		*/
        virtual void render() const;

        void setState(BallType ballType, const jfVector3& pos);
    protected:
		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  drawSphere
		 *  Description:  Draws a sphere using opengl.
		 * =====================================================================================
		 */
        virtual void drawSphere(float radius, int subdivisions) const;

        GLUquadricObj* m_SphereQuadric;
    private:
};

#endif // JFAMMOROUND_H
