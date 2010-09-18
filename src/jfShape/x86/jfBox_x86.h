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

#include <jfShape/jfBox.h>
#include <jfpx/x86/jfRigidBody_x86.h>
#include <jfpx/x86/jfVector3_x86.h>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>

/*
 * =====================================================================================
 *        Class: jfBox_x86
 *  Description:
 * =====================================================================================
 */
class jfBox_x86 : public jfBox
{
	public:
		jfBox_x86();

		~jfBox_x86();

		/*-----------------------------------------------------------------------------
		 *  Interface
		 *-----------------------------------------------------------------------------*/

		/*-----------------------------------------------------------------------------
		 *  Inherited Methods
		 *-----------------------------------------------------------------------------*/
        virtual void init();

		virtual void render() const;

        virtual void setState(BoxType type, const jfVector3& pos);

	protected:
        void drawBox(const jfVector3& halfSize) const;

        void buildLists(const jfVector3& halfSideLength) const;

        GLuint	m_BoxList;
	private:

};

#endif //JFBOX_X86_H

