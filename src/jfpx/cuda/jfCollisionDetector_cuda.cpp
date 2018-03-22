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
#include "jfCollisionDetector_cuda.h"

jfCollisionDetector_cuda::jfCollisionDetector_cuda()
    : jfCollisionDetector_x86()
{
}

jfCollisionDetector_cuda::~jfCollisionDetector_cuda() {}

void jfCollisionDetector_cuda::assignStruct(
    jfCollisionSphereStruct* collisionSphere_cuda,
    jfCollisionSphere_x86* collisionSphere_x86) const
{
    jfVector3_x86 centre;
    collisionSphere_x86->getAxisVector(3, &centre);
    collisionSphere_cuda->m_Centre.m_X = centre.getX();
    collisionSphere_cuda->m_Centre.m_Y = centre.getY();
    collisionSphere_cuda->m_Centre.m_Z = centre.getZ();
    collisionSphere_cuda->m_Radius = collisionSphere_x86->getRadius();
}

unsigned
jfCollisionDetector_cuda::computeContactNumCols(unsigned sphere_row) const
{
    return ((N_SPHERES - 1) - sphere_row);
}

unsigned jfCollisionDetector_cuda::sphereAndSphereBatch(
    vector<jfBall*>& spheres, jfCollisionData* collisionData) const
{
    unsigned contactCount = 0;

    // Allocate sphere memory based on number of spheres as we will need them all.
    jfCollisionSphereStruct* sphereStructs;
    sphereStructs = (jfCollisionSphereStruct*)malloc(
        sizeof(jfCollisionSphereStruct) * spheres.size());

    // Load spheres here
    unsigned copyIdx;
    for (copyIdx = 0; copyIdx < spheres.size(); copyIdx++) {
        assignStruct(&(sphereStructs[copyIdx]), spheres[copyIdx]);
    }

    jfContactStruct contactResultsStruct[N_CONTACTS];
    sphereSphereCollisionTiled(sphereStructs, contactResultsStruct);

    int contactIdx_I;
    // Copy contacts back
    for (contactIdx_I = 0; contactIdx_I < N_CONTACTS; contactIdx_I++) {
        if (contactResultsStruct[contactIdx_I].m_Valid == 1) {
            jfContact_x86 contact;
            contact.setPenetration(contactResultsStruct[contactIdx_I].m_Penetration);
            contact.setBodyData(
                spheres[contactResultsStruct[contactIdx_I].m_Body1Idx]->getBody(),
                spheres[contactResultsStruct[contactIdx_I].m_Body2Idx]->getBody(),
                collisionData->getFriction(), collisionData->getRestitution());
            contact.setContactNormal(copyToJfVector3_x86(
                contactResultsStruct[contactIdx_I].m_ContactNormal));
            contact.setContactPoint(copyToJfVector3_x86(
                contactResultsStruct[contactIdx_I].m_ContactPoint));
            collisionData->addContact(contact);
            contactCount++;
        }
    }

    return contactCount;
}
