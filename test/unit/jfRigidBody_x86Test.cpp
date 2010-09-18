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

#include <jfpx/x86/jfRigidBody_x86.h>

#include <iostream>
#include <vector>
using namespace std;

namespace
{
    TEST(CreationDeletion)
    {
        jfRigidBody_x86* rigidBody = new jfRigidBody_x86();
        delete rigidBody;
    }

    TEST(IntegrateAccel)
    {
        jfVector3_x86 bodyPos;
        jfRigidBody_x86 rigidBody;
        rigidBody.setPos(jfVector3_x86(0.0, 0.0, 0.0));
        rigidBody.setMass(5.0f);
        rigidBody.setVelocity(jfVector3_x86(0.0f, 0.0f, 0.0f));
        rigidBody.setAccel(jfVector3_x86(0.0f, -10.f, 0.0f));
        rigidBody.setLinearDamping(0.99f);
        rigidBody.setAngularDamping(0.99f);
        rigidBody.integrate(1.0);
        rigidBody.getPos(&bodyPos);
        CHECK_CLOSE(bodyPos.getX(), 0.0, 0.1);
        CHECK_CLOSE(bodyPos.getY(), -10.0, 0.1);
        CHECK_CLOSE(bodyPos.getZ(), 0.0, 0.1);
    }

    TEST(IntegrateVel)
    {
        jfVector3_x86 bodyPos;
        jfRigidBody_x86 rigidBody;
        rigidBody.setPos(jfVector3_x86(0.0, 0.0, 0.0));
        rigidBody.setMass(5.0f);
        rigidBody.setVelocity(jfVector3_x86(0.0f, -10.0f, 0.0f));
        rigidBody.setAccel(jfVector3_x86(0.0f, 0.f, 0.0f));
        rigidBody.setLinearDamping(0.99f);
        rigidBody.setAngularDamping(0.99f);
        rigidBody.integrate(1.0);
        rigidBody.getPos(&bodyPos);
        CHECK_CLOSE(bodyPos.getX(), 0.0, 0.1);
        CHECK_CLOSE(bodyPos.getY(), -10.0, 0.1);
        CHECK_CLOSE(bodyPos.getZ(), 0.0, 0.1);
    }

    TEST(CalculateDerivedData)
    {
        jfRigidBody_x86 rigidBody;
        rigidBody.setPos(jfVector3_x86(0.0, 1.0, 0.0));
        rigidBody.calculateDerivedData();
        jfMatrix4_x86 transform;
        rigidBody.getTransformMatrix(&transform);
        CHECK_EQUAL(transform.getElem(7), 1.0);
    }
}
