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
#ifndef JFINTERSECTIONTESTER_H
#define JFINTERSECTIONTESTER_H

#include <jfpx/jfCollisionBox.h>
#include <jfpx/jfCollisionPlane.h>
#include <jfpx/jfCollisionSphere.h>
#include <jfpx/jfVector3.h>

class jfIntersectionTester {
public:
    jfIntersectionTester();

    virtual ~jfIntersectionTester();

    /* 
		 * ===  FUNCTION  ======================================================================
		 *         Name:  sphereAndHalfSpace
		 *  Description:  Returns true if the given sphere is intersecting with the halfspace.
		 * =====================================================================================
		 */
    virtual bool sphereAndHalfSpace(const jfCollisionSphere& sphere,
        const jfCollisionPlane& plane)
        = 0;

    /* 
		* ===  FUNCTION  ======================================================================
		*         Name:  sphereAndSphere
		*  Description:  Returns true if the two spheres are intersecting
		* =====================================================================================
		*/
    virtual bool sphereAndSphere(const jfCollisionSphere& one,
        const jfCollisionSphere& two)
        = 0;

    /* 
		 * ===  FUNCTION  ======================================================================
		 *         Name:  boxAndBox
		 *  Description:  Returns true if the two boxes are intersecting.
		 * =====================================================================================
		 */
    virtual bool boxAndBox(const jfCollisionBox& one,
        const jfCollisionBox& two)
        = 0;

    /* 
		 * ===  FUNCTION  ======================================================================
		 *         Name:  boxAndHalfSpace
		 *  Description:  Returns true if the box is intersecting the half space.
		 * =====================================================================================
		 */
    virtual bool boxAndHalfSpace(const jfCollisionBox& box,
        const jfCollisionPlane& plane)
        = 0;
    /* 
		 * ===  FUNCTION  ======================================================================
		 *         Name:  transformToAxis
		 *  Description:  Transforms the box to the axis vector.
		 * =====================================================================================
		 */
    virtual jfReal transformToAxis(const jfCollisionBox& box,
        const jfVector3& axis)
        = 0;

protected:
    /* 
		 * ===  FUNCTION  ======================================================================
		 *         Name: overlapOnAxis 
		 *  Description: Returns true if the two boxes overlap on the given axis.
		 * =====================================================================================
		 */
    virtual bool overlapOnAxis(const jfCollisionBox& one,
        const jfCollisionBox& two,
        const jfVector3& axis,
        const jfVector3& toCentre)
        = 0;

private:
};

#endif // JFINTERSECTIONTESTER_H
