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
#ifndef JFRIGIDBODY_X86_H
#define JFRIGIDBODY_X86_H

#include <jfpx/jfRigidBody.h>
#include <jfpx/jfMatrix4.h>
#include <jfpx/jfVector3.h>
#include <jfpx/x86/jfVector3_x86.h>
#include <jfpx/x86/jfQuaternion_x86.h>
#include <jfpx/x86/jfMatrix3_x86.h>
#include <jfpx/x86/jfMatrix4_x86.h>

/*
 * =====================================================================================
 *        Class: JfRigidBody_x86
 *  Description: x86 Implementation of RigidBody class
 * =====================================================================================
 */
class jfRigidBody_x86 : public jfRigidBody
{
	public:
		jfRigidBody_x86 ();

		virtual ~jfRigidBody_x86 ();

		/*-----------------------------------------------------------------------------
		 *  Inherited methods
		 *-----------------------------------------------------------------------------*/
		virtual void calculateDerivedData();

		virtual void addForce(const jfVector3& force);

		virtual void integrate(jfReal duration);

		virtual void clearAccumulators();

		virtual void addForceAtBodyPoint(const jfVector3& force, const jfVector3& point);

		virtual void addForceAtPoint(const jfVector3& force, const jfVector3& point);

		virtual void getPointInLocalSpace(const jfVector3& point, jfVector3* result) const;

		virtual void getPointInWorldSpace(const jfVector3& point, jfVector3* result) const;

	protected:
		virtual void transformInertiaTensor(jfMatrix3* iitWorld
											, const jfMatrix3& iitBody
											, const jfMatrix4& rotMat) const;

		virtual void calculateTransformMatrix(jfMatrix4* transformMatrix,
												const jfVector3& pos,
												const jfQuaternion& orientation) const;
	private:
};


#endif // JFRIGIDBODY_X86_H
