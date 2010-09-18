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

#ifndef  JFCOLLISIONSPHERE_X86_H
#define  JFCOLLISIONSPHERE_X86_H

#include <jfpx/jfCollisionSphere.h>
#include <jfpx/x86/jfCollisionPrimitive_x86.h>
#include <jfpx/x86/jfMatrix4_x86.h>

/*
 * =====================================================================================
 *        Class: jfCollisionSphere_x86
 *  Description:
 * =====================================================================================
 */
class jfCollisionSphere_x86 : public jfCollisionSphere
{
	public:
		jfCollisionSphere_x86();

		virtual ~jfCollisionSphere_x86();

		/*-----------------------------------------------------------------------------
		 *  Inherited Methods
		 *-----------------------------------------------------------------------------*/
        virtual void calculateInternals();
	protected:
	private:
};

#endif   // JFCOLLISIONSPHERE_X86_H
