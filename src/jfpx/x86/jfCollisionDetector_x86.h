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

#ifndef  JFCOLLISIONDETECTOR_X86_H
#define  JFCOLLISIONDETECTOR_X86_H

#include <jfpx/jfCollisionDetector.h>

#include <jfpx/x86/jfVector3_x86.h>
#include <jfpx/x86/jfContact_x86.h>
#include <jfpx/x86/jfIntersectionTester_x86.h>

#include <vector>
using namespace std;

/*
 * =====================================================================================
 *        Class: jfCollisionDetector_x86
 *  Description:
 * =====================================================================================
 */
class jfCollisionDetector_x86 : public jfCollisionDetector
{
	public:

        virtual unsigned sphereAndHalfSpace(const jfCollisionSphere& sphere,
												const jfCollisionPlane& plane,
												jfCollisionData* data
												) const;

        virtual unsigned sphereAndTruePlane(const jfCollisionSphere& sphere,
											const jfCollisionPlane& plane,
											jfCollisionData* data
											) const;

        virtual unsigned sphereAndSphere(const jfCollisionSphere& one,
											const jfCollisionSphere& two,
											jfCollisionData* data
											) const;

        virtual unsigned sphereAndSphereBatch(vector<jfBall*>& spheres,
                                                jfCollisionData* collisionData) const;

        virtual unsigned boxAndHalfSpace(const jfCollisionBox& box,
											const jfCollisionPlane& plane,
											jfCollisionData* data
											) const;

        virtual unsigned boxAndBox(const jfCollisionBox& one,
										const jfCollisionBox& two,
										jfCollisionData* data
										) const;

        virtual unsigned boxAndBoxBatch(vector<jfBox*>& boxes,
                                        jfCollisionData* collisionData) const;

        virtual unsigned boxAndPoint(const jfCollisionBox& box,
										const jfVector3& point,
										jfCollisionData* data
										) const;

        virtual unsigned boxAndSphere(const jfCollisionBox& box,
										const jfCollisionSphere& sphere,
										jfCollisionData* data
										) const;
	protected:
		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  penetrationOnAxis
		 *  Description: This function checks if the two boxes overlap
		 * along the given axis, returning the ammount of overlap.
		 * The final parameter toCentre
		 * is used to pass in the vector between the boxes centre
		 * points, to avoid having to recalculate it each time.
		 * =====================================================================================
		 */
		virtual jfReal penetrationOnAxis(
			const jfCollisionBox& one,
			const jfCollisionBox& two,
			jfVector3& axis,
			const jfVector3& toCentre
			) const;

		virtual bool tryAxis(
			const jfCollisionBox& one,
			const jfCollisionBox& two,
			jfVector3& axis,
			const jfVector3& toCentre,
			unsigned index,
			// These values may be updated
			jfReal& smallestPenetration,
			unsigned& smallestCase
			) const;

		virtual void fillPointFaceBoxBox(
			const jfCollisionBox& one,
			const jfCollisionBox& two,
			const jfVector3& toCentre,
			jfCollisionData* data,
			unsigned best,
			jfReal pen
			) const;

		virtual void contactPoint(
			const jfVector3& pOne,
			const jfVector3& dOne,
			jfReal oneSize,
			const jfVector3& pTwo,
			const jfVector3& dTwo,
			jfReal twoSize,
			bool useOne,
			jfVector3* result) const;
	private:
};

#endif   // JFCOLLISIONDETECTOR_X86_H
