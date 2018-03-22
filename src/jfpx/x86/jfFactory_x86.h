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

#ifndef JFFACTORY_X86_H
#define JFFACTORY_X86_H

#include <jfpx/jfFactory.h>

#include <jfpx/x86/jfCollisionBox_x86.h>
#include <jfpx/x86/jfCollisionDetector_x86.h>
#include <jfpx/x86/jfCollisionPlane_x86.h>
#include <jfpx/x86/jfCollisionSphere_x86.h>
#include <jfpx/x86/jfContactResolver_x86.h>
#include <jfpx/x86/jfContact_x86.h>
#include <jfpx/x86/jfIntersectionTester_x86.h>
#include <jfpx/x86/jfMatrix3_x86.h>
#include <jfpx/x86/jfMatrix4_x86.h>
#include <jfpx/x86/jfQuaternion_x86.h>
#include <jfpx/x86/jfRigidBody_x86.h>
#include <jfpx/x86/jfVector3_x86.h>

/*
 * =====================================================================================
 *        Class: jfFactory_x86
 *  Description: Factory for x86 physics classes.
 * =====================================================================================
 */
class jfFactory_x86 : public jfFactory {
public:
    jfFactory_x86();

    virtual jfVector3* makeVector3() const;

    virtual jfMatrix3* makeMatrix3() const;

    virtual jfMatrix4* makeMatrix4() const;

    virtual jfQuaternion* makeQuaternion() const;

    virtual jfRigidBody* makeRigidBody() const;

    virtual jfCollisionDetector* makeCollisionDetector() const;

    virtual jfContactResolver* makeContactResolver() const;
    virtual jfContactResolver* makeContactResolver(unsigned iterations, jfReal velocityEpsilion = (jfReal)0.01, jfReal positionEpsilon = (jfReal)0.01) const;

    virtual jfCollisionPlane* makeCollisionPlane() const;

    virtual jfCollisionBox* makeCollisionBox() const;

    virtual jfCollisionSphere* makeCollisionSphere() const;

    virtual jfContact* makeContact() const;

    virtual jfIntersectionTester* makeIntersectionTester() const;

protected:
private:
};

#endif // JFFACTORY_X86_H
