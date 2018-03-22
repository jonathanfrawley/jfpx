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

#ifndef JFCONTACT_X86_H
#define JFCONTACT_X86_H

#include <jfpx/jfContact.h>
#include <jfpx/x86/jfMatrix3_x86.h>
#include <jfpx/x86/jfRigidBody_x86.h>
#include <jfpx/x86/jfVector3_x86.h>

#include <assert.h>

/*
 * =====================================================================================
 *        Class: jfContact_x86
 *  Description:
 * =====================================================================================
 */
class jfContact_x86 : public jfContact {
public:
    jfContact_x86();

    jfContact_x86(const jfContact_x86& other);

    virtual jfContact_x86* clone() const
    {
        return new jfContact_x86(*this);
    }

    virtual ~jfContact_x86();

    /*-----------------------------------------------------------------------------
		 *  Inherited methods
		 *-----------------------------------------------------------------------------*/
    virtual void calculateInternals(jfReal timeStep);

    virtual void swapBodies();

    virtual void calculateDesiredDeltaVelocity(jfReal timeStep);

    virtual void calculateLocalVelocity(unsigned bodyIndex,
        jfReal timeStep,
        jfVector3* result);

    virtual void calculateContactBasis();

    virtual void applyVelocityChange(jfVector3* velocityChange,
        jfVector3* rotationChange);

    virtual void applyPositionChange(jfVector3* linearChange,
        jfVector3* angularChange,
        jfReal penetration);

    virtual void calculateFrictionlessImpulse(jfMatrix3* inverseInertiaTensor,
        jfVector3* result);

    virtual void calculateFrictionImpulse(jfMatrix3* inverseInertiaTensor,
        jfVector3* result);

protected:
private:
};

#endif // JFCONTACT_X86_H
