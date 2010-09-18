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

#ifndef  JFCOLLISIONDETECTOR_H
#define  JFCOLLISIONDETECTOR_H

#include <jfpx/jfCollisionPlane.h>
#include <jfpx/jfCollisionSphere.h>
#include <jfpx/jfCollisionBox.h>
#include <jfpx/jfCollisionData.h>

#include <jfShape/jfBall.h>
#include <jfShape/jfBox.h>

#include <vector>
using namespace std;

/*
 *  =====================================================================================
 *         Class: jfCollisionDetector
 *   Description: Holds the functions needed for narrow-phase collision detection.
 *   Each function takes the details of the two objects, a contact array to fill and
 *   it returns the number of contacts it finds.
 *  =====================================================================================
 */
class jfCollisionDetector
{
	public:
        jfCollisionDetector();

        virtual ~jfCollisionDetector();

        virtual unsigned sphereAndHalfSpace(const jfCollisionSphere& sphere,
												const jfCollisionPlane& plane,
												jfCollisionData* data
												) const = 0;

        virtual unsigned sphereAndTruePlane(const jfCollisionSphere& sphere,
											const jfCollisionPlane& plane,
											jfCollisionData* data
											) const = 0;

        virtual unsigned sphereAndSphere(const jfCollisionSphere& one,
											const jfCollisionSphere& two,
											jfCollisionData* data
											) const = 0;

        virtual unsigned sphereAndSphereBatch(vector<jfBall*>& spheres,
                                                jfCollisionData* collisionData) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  boxAndHalfSpace
		 *  Description:  Does a collision test on a collision box and a plane representing
		 *  a half-space (i.e. the normal of the plane
		 *  points out of the half-space).
		 * =====================================================================================
		 */
        virtual unsigned boxAndHalfSpace(const jfCollisionBox& box,
											const jfCollisionPlane& plane,
											jfCollisionData* data
											) const = 0;

        virtual unsigned boxAndBox(const jfCollisionBox& one,
										const jfCollisionBox& two,
										jfCollisionData* data
										) const = 0;
		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  boxAndBoxBatch
		 *  Description:  Finds the collisions between each pair of boxes in the passed in
		 *  array.
		 * =====================================================================================
		 */
        virtual unsigned boxAndBoxBatch(vector<jfBox*>& boxes,
                                        jfCollisionData* collisionData) const = 0;

        virtual unsigned boxAndPoint(const jfCollisionBox& box,
										const jfVector3& point,
										jfCollisionData* data
										) const = 0;

        virtual unsigned boxAndSphere(const jfCollisionBox& box,
										const jfCollisionSphere& sphere,
										jfCollisionData* data
										) const = 0;
	protected:


	private:
};


#endif   // JFCOLLISIONDETECTOR_H
