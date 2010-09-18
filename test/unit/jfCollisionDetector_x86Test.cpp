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
#include "UnitTest++.h"

#include <jfpx/x86/jfCollisionDetector_x86.h>
#include <jfpx/x86/jfCollisionPlane_x86.h>
#include <jfpx/x86/jfCollisionSphere_x86.h>
#include <jfpx/x86/jfCollisionBox_x86.h>
#include <jfpx/x86/jfVector3_x86.h>
#include <jfpx/x86/jfRigidBody_x86.h>
#include <jfpx/jfCollisionData.h>

namespace
{
    TEST(CreationDeletion)
    {
        jfCollisionDetector_x86 collisionDetector;
    }

    TEST(sphereAndSphere)
    {
        jfCollisionDetector_x86 collisionDetector;
        jfCollisionData collisionData;
        jfCollisionSphere_x86 sphere1, sphere2;

        //Do negative test first
        sphere1.getBody()->setPos(jfVector3_x86(0,1,0));
        sphere1.setRadius(1.0);
        sphere1.getBody()->calculateDerivedData();
        sphere1.calculateInternals();
        sphere2.getBody()->setPos(jfVector3_x86(3,1,0));
        sphere2.setRadius(1.0);
        sphere2.getBody()->calculateDerivedData();
        sphere2.calculateInternals();
        CHECK_EQUAL(0, collisionDetector.sphereAndSphere(sphere1, sphere2, &collisionData));

        sphere2.getBody()->setPos(jfVector3_x86(1.5,1,0));
        sphere2.getBody()->calculateDerivedData();
        sphere2.calculateInternals();

        CHECK_EQUAL(1, collisionDetector.sphereAndSphere(sphere1, sphere2, &collisionData));
    }

    TEST(boxAndSphere)
    {
        jfCollisionDetector_x86 collisionDetector;
        jfCollisionData collisionData;
        jfCollisionSphere_x86 sphere;
        jfCollisionBox_x86 box;
        sphere.getBody()->setPos(jfVector3_x86(0,1,0));
        sphere.setRadius(1.0);
        sphere.getBody()->calculateDerivedData();
        sphere.calculateInternals();

        //Do false test first
        box.getBody()->setPos(jfVector3_x86(0,1,3));
        box.setHalfSize(jfVector3_x86(1.0,1.0,1.0));
        box.getBody()->calculateDerivedData();
        box.calculateInternals();
        CHECK_EQUAL(0, collisionDetector.boxAndSphere(box, sphere, &collisionData));

        //Now do positive test
        box.getBody()->setPos(jfVector3_x86(0,1.5,0));
        box.setHalfSize(jfVector3_x86(1.0,1.0,1.0));
        box.getBody()->calculateDerivedData();
        box.calculateInternals();
        CHECK_EQUAL(1, collisionDetector.boxAndSphere(box, sphere, &collisionData));
    }

    TEST(boxAndHalfSpace)
    {
        jfCollisionDetector_x86 collisionDetector;
        jfCollisionData collisionData;
        jfCollisionPlane_x86 plane;
        jfCollisionBox_x86 box;

        plane.setDirection(jfVector3_x86(0,1,0));
        plane.setOffset(0);

        //Do false test first
        box.getBody()->setPos(jfVector3_x86(0,2,3));
        box.setHalfSize(jfVector3_x86(1.0,1.0,1.0));
        box.getBody()->calculateDerivedData();
        box.calculateInternals();
        CHECK_EQUAL(0, collisionDetector.boxAndHalfSpace(box, plane, &collisionData));

        //Now do positive test
        box.getBody()->setPos(jfVector3_x86(0,0.5,0));
        box.setHalfSize(jfVector3_x86(1.0,1.0,1.0));
        box.getBody()->calculateDerivedData();
        box.calculateInternals();
        CHECK_EQUAL(4, collisionDetector.boxAndHalfSpace(box, plane, &collisionData));

        box.getBody()->setPos(jfVector3_x86(0,-2,0));
        box.setHalfSize(jfVector3_x86(1.0,1.0,1.0));
        box.getBody()->calculateDerivedData();
        box.calculateInternals();
        CHECK_EQUAL(8, collisionDetector.boxAndHalfSpace(box, plane, &collisionData));
    }

    TEST(BoxAndBox)
    {
        jfCollisionDetector_x86 collisionDetector;
        jfCollisionData collisionData;
        jfCollisionPlane_x86 plane;
        jfCollisionBox_x86 box0, box1;

        //Do false test first
        box0.getBody()->setPos(jfVector3_x86(3,3,3));
        box0.setHalfSize(jfVector3_x86(1.0,1.0,1.0));
        box0.getBody()->calculateDerivedData();
        box0.calculateInternals();
        box1.getBody()->setPos(jfVector3_x86(1,1,1));
        box1.setHalfSize(jfVector3_x86(1.0,1.0,1.0));
        box1.getBody()->calculateDerivedData();
        box1.calculateInternals();
        CHECK_EQUAL(0, collisionDetector.boxAndBox(box0, box1, &collisionData));

        //Now do positive test
        box0.getBody()->setPos(jfVector3_x86(1,1.5,1));
        box0.setHalfSize(jfVector3_x86(1.0,1.0,1.0));
        box0.getBody()->calculateDerivedData();
        box0.calculateInternals();
        CHECK_EQUAL(2, collisionDetector.boxAndBox(box0, box1, &collisionData));
    }

}
