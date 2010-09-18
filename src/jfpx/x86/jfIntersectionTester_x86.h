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
#ifndef  JFINTERSECTIONTESTER_X86_H
#define  JFINTERSECTIONTESTER_X86_H

#include <jfpx/jfIntersectionTester.h>
#include <jfpx/x86/jfVector3_x86.h>

/*
 * =====================================================================================
 *        Class: jfIntersectionTester_x86
 *  Description:
 * =====================================================================================
 */
class jfIntersectionTester_x86 : public jfIntersectionTester
{
	public:

		/*-----------------------------------------------------------------------------
		 *  Inherited Methods
		 *-----------------------------------------------------------------------------*/
        virtual bool sphereAndHalfSpace(const jfCollisionSphere& sphere,
										const jfCollisionPlane& plane);

        virtual bool sphereAndSphere(const jfCollisionSphere& one,
										const jfCollisionSphere& two);

        virtual bool boxAndBox(const jfCollisionBox& one,
								const jfCollisionBox& two);

        virtual bool boxAndHalfSpace(const jfCollisionBox& box,
										const jfCollisionPlane& plane);

		virtual jfReal transformToAxis(const jfCollisionBox& box,
										const jfVector3& axis);

	protected:

		virtual bool overlapOnAxis(const jfCollisionBox& one,
									const jfCollisionBox& two,
									const jfVector3& axis,
									const jfVector3& toCentre
									);

	private:
};


#endif   // JFINTERSECTIONTESTER_X86_H
