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
#ifndef JFFACTORY_H
#define JFFACTORY_H

#include <jfpx/jfCore.h>

#include <jfpx/jfCollisionBox.h>
#include <jfpx/jfCollisionData.h>
#include <jfpx/jfCollisionDetector.h>
#include <jfpx/jfCollisionPlane.h>
#include <jfpx/jfCollisionSphere.h>
#include <jfpx/jfContact.h>
#include <jfpx/jfContactResolver.h>
#include <jfpx/jfIntersectionTester.h>
#include <jfpx/jfMatrix3.h>
#include <jfpx/jfMatrix4.h>
#include <jfpx/jfQuaternion.h>
#include <jfpx/jfRigidBody.h>
#include <jfpx/jfVector3.h>

/*
 * =====================================================================================
 *        Class: jfFactory
 *  Description: Abstract Factory which defines an interface for concrete factories of
 *  jf objects to inherit from.
 * =====================================================================================
 */
class jfFactory {
public:
    jfFactory();

    virtual jfVector3* makeVector3() const = 0;

    virtual jfMatrix3* makeMatrix3() const = 0;

    virtual jfMatrix4* makeMatrix4() const = 0;

    virtual jfQuaternion* makeQuaternion() const = 0;

    virtual jfRigidBody* makeRigidBody() const = 0;

    virtual jfCollisionData* makeCollisionData() const
    {
        return new jfCollisionData();
    }

    virtual jfCollisionDetector* makeCollisionDetector() const = 0;

    virtual jfContactResolver* makeContactResolver() const = 0;
    virtual jfContactResolver* makeContactResolver(unsigned iterations, jfReal velocityEpsilion = (jfReal)0.01, jfReal positionEpsilon = (jfReal)0.01) const = 0;

    virtual jfCollisionPlane* makeCollisionPlane() const = 0;

    virtual jfCollisionBox* makeCollisionBox() const = 0;

    virtual jfCollisionSphere* makeCollisionSphere() const = 0;

    virtual jfContact* makeContact() const = 0;

    virtual jfIntersectionTester* makeIntersectionTester() const = 0;

protected:
private:
};

#endif //JFFACTORY_H
