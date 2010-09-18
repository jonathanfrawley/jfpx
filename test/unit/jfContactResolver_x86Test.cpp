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

#include <jfpx/x86/jfContactResolver_x86.h>
#include <jfpx/x86/jfCollisionDetector_x86.h>
#include <jfpx/x86/jfCollisionPlane_x86.h>
#include <jfpx/x86/jfCollisionSphere_x86.h>
#include <jfpx/x86/jfCollisionBox_x86.h>
#include <jfpx/x86/jfVector3_x86.h>
#include <jfpx/x86/jfRigidBody_x86.h>
#include <jfpx/jfCollisionData.h>

#include <stdio.h>

namespace
{
    TEST(CreationDeletion)
    {
        jfContactResolver_x86 contactResolver;
    }

    TEST(SphereAndSphere)
    {
        jfContactResolver_x86 contactResolver(1000);
        jfCollisionDetector_x86 collisionDetector;
        jfCollisionData collisionData;
        jfCollisionSphere_x86 sphere1, sphere2;

        sphere1.getBody()->setPos(jfVector3_x86(0, 1, 0));
        sphere1.setRadius(1.0);
        sphere1.getBody()->setMass(1.0);
        sphere1.getBody()->calculateDerivedData();
        sphere1.calculateInternals();
        sphere2.getBody()->setPos(jfVector3_x86(1.5, 0.5, 0.5));
        sphere2.setRadius(1.0);
        sphere2.getBody()->setMass(1.0);
        sphere2.getBody()->calculateDerivedData();
        sphere2.calculateInternals();

        collisionDetector.sphereAndSphere(sphere1, sphere2, &collisionData);

        vector<jfContact*> contacts;
        collisionData.getContacts(&contacts);

 //       cout <<"Contacts.size() is "<<contacts.size()<<endl;

        contactResolver.resolveContacts(contacts, 1);

        sphere1.getBody()->integrate(1);
        sphere2.getBody()->integrate(1);

        jfVector3_x86 sphere1Pos, sphere2Pos;
        sphere1.getBody()->getPos(&sphere1Pos);
//        cout<<"sphere1Pos is :" <<sphere1Pos<<endl;
        sphere2.getBody()->getPos(&sphere2Pos);
//        cout<<"sphere2Pos is :" <<sphere2Pos<<endl;

        //Ensure the sphere's have moved.
        CHECK(sphere1Pos.getX() != 0);
        CHECK(sphere1Pos.getY() != 1);
        CHECK(sphere1Pos.getZ() != 0);
        CHECK(sphere2Pos.getX() != 1.5);
        CHECK(sphere2Pos.getY() != 1);
        CHECK(sphere2Pos.getZ() != 0);
    }

    TEST(SphereAndBox)
    {
        jfContactResolver_x86 contactResolver(1000);
        jfCollisionDetector_x86 collisionDetector;
        jfCollisionData collisionData;
        jfCollisionSphere_x86 sphere;
        jfCollisionBox_x86 box;
        jfVector3_x86 origSpherePos = jfVector3_x86(0,1.5,0);

        sphere.getBody()->setPos(origSpherePos);
        sphere.getBody()->setMass(2);
        sphere.setRadius(1.0);
        sphere.getBody()->calculateDerivedData();
        sphere.calculateInternals();

        jfVector3_x86 origBoxPos = jfVector3_x86(0,2.4,0);
        box.getBody()->setPos(origBoxPos);
        box.setHalfSize(jfVector3_x86(1.0,1.0,1.0));
        box.getBody()->setMass(2);
        box.getBody()->calculateDerivedData();
        box.calculateInternals();

        collisionDetector.boxAndSphere(box, sphere, &collisionData);

        vector<jfContact*> contacts;
        collisionData.getContacts(&contacts);
        contactResolver.resolveContacts(contacts, 1);

        cout <<"Contacts.size() is "<<contacts.size()<<endl;
        vector<jfContact*>::iterator contact;
        for(contact=contacts.begin();contact!=contacts.end();contact++)
        {
            jfVector3_x86 cPos;
            (*contact)->getContactPoint(&cPos);
            cout<<"SEX : contact point is :"<<cPos<<endl;
            fflush(stdout);
        }

        sphere.getBody()->integrate(1);
        box.getBody()->integrate(1);

        jfVector3_x86 spherePos, boxPos;
        sphere.getBody()->getPos(&spherePos);
        cout<<"spherePos is :" <<spherePos<<endl;
        box.getBody()->getPos(&boxPos);
        cout<<"boxPos is :" <<boxPos<<endl;

        CHECK(origSpherePos != spherePos);
        CHECK(origBoxPos != boxPos);
    }

    TEST(BoxAndHalfSpace)
    {
        jfContactResolver_x86 contactResolver(1000);
        jfCollisionDetector_x86 collisionDetector;
        jfCollisionData collisionData;
        jfCollisionPlane_x86 plane;
        jfCollisionBox_x86 box;
        jfVector3_x86 origBoxPos = jfVector3_x86(0.0, 0.5, 0.0);

        plane.setDirection(jfVector3_x86(0,1,0));
        plane.setOffset(0);

        //Do false test first
        box.getBody()->setPos(origBoxPos);
        box.setHalfSize(jfVector3_x86(1.0,1.0,1.0));
        box.getBody()->calculateDerivedData();
        box.calculateInternals();
        collisionDetector.boxAndHalfSpace(box, plane, &collisionData);

        vector<jfContact*> contacts;
        collisionData.getContacts(&contacts);
        contactResolver.resolveContacts(contacts, 1);

        box.getBody()->integrate(1);
        jfVector3_x86 boxPos;
        box.getBody()->getPos(&boxPos);
        CHECK(origBoxPos != boxPos);
    }
}
