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
#include "jfIntersectionTester_x86.h"

bool jfIntersectionTester_x86::sphereAndHalfSpace(const jfCollisionSphere& sphere,
    const jfCollisionPlane& plane)
{
    // Find the distance from the origin
    jfVector3_x86 sphereAxis;
    jfVector3_x86 axisMinusRadius;
    jfVector3_x86 planeDirection;

    sphere.getAxisVector(3, &sphereAxis);
    sphereAxis.subtract(sphere.getRadius(), &axisMinusRadius);

    plane.getDirection(&planeDirection);
    jfReal sphereDistance = planeDirection.dotProduct(axisMinusRadius);

    // Check for the intersection
    return (sphereDistance <= plane.getOffset());
}

bool jfIntersectionTester_x86::sphereAndSphere(const jfCollisionSphere& one,
    const jfCollisionSphere& two)
{
    // Find the vector between the objects
    jfVector3_x86 midline;
    jfVector3_x86 oneAxis3;
    jfVector3_x86 twoAxis3;

    one.getAxisVector(3, &oneAxis3);
    two.getAxisVector(3, &twoAxis3);
    oneAxis3.subtract(twoAxis3, &midline);

    // See if it is large enough.
    return (midline.squareMagnitude() < (one.getRadius() + two.getRadius()) * (one.getRadius() + two.getRadius()));
}

jfReal jfIntersectionTester_x86::transformToAxis(const jfCollisionBox& box,
    const jfVector3& axis)
{
    jfVector3_x86 boxHalfSize;
    jfVector3_x86 boxAxis0;
    jfVector3_x86 boxAxis1;
    jfVector3_x86 boxAxis2;

    box.getHalfSize(&boxHalfSize);
    box.getAxisVector(0, &boxAxis0);
    box.getAxisVector(1, &boxAxis1);
    box.getAxisVector(2, &boxAxis2);
    return ((boxHalfSize.getX() * jfRealAbs(axis.dotProduct(boxAxis0))) + (boxHalfSize.getY() * jfRealAbs(axis.dotProduct(boxAxis1))) + (boxHalfSize.getZ() * jfRealAbs(axis.dotProduct(boxAxis2))));
}

bool jfIntersectionTester_x86::overlapOnAxis(const jfCollisionBox& one,
    const jfCollisionBox& two,
    const jfVector3& axis,
    const jfVector3& toCentre)
{
    // Project the half-size of one onto axis
    jfReal oneProject = transformToAxis(one, axis);
    jfReal twoProject = transformToAxis(two, axis);

    // Project this onto the axis
    jfReal distance = jfRealAbs(toCentre.dotProduct(axis));

    // Check for overlap
    return (distance < (oneProject + twoProject));
}

bool jfIntersectionTester_x86::boxAndBox(const jfCollisionBox& one,
    const jfCollisionBox& two)
{
    //@ref: Millington code "collide_fine.cpp"
    // Find the vector between the two centres
    jfVector3_x86 toCentre;
    jfVector3_x86 oneAxis, twoAxis;

    unsigned i, j;
    for (i = 0; i < 3; i++) {
        one.getAxisVector(3, &oneAxis);
        two.getAxisVector(3, &twoAxis);
        twoAxis.subtract(oneAxis, &toCentre);
        //Check on box one and twos' axes
        if (!overlapOnAxis(one, two, oneAxis, toCentre)
            || !overlapOnAxis(one, two, twoAxis, toCentre)) {
            return false;
        }
        //Check on cross Products of axes
        for (j = 0; j < 3; j++) {
            two.getAxisVector(j, &twoAxis);
            jfVector3_x86 crossProduct;
            oneAxis.crossProduct(twoAxis, &crossProduct);
            if (!overlapOnAxis(one, two, crossProduct, toCentre)) {
                return false;
            }
        }
    }
    return true;
}

bool jfIntersectionTester_x86::boxAndHalfSpace(const jfCollisionBox& box,
    const jfCollisionPlane& plane)
{
    // Work out the projected radius of the box onto the plane direction
    jfVector3_x86 planeDirection;
    jfVector3_x86 boxAxis;

    plane.getDirection(&planeDirection);
    jfReal projectedRadius = transformToAxis(box, planeDirection);

    // Work out how far the box is from the origin
    box.getAxisVector(3, &boxAxis);
    jfReal boxDistance = (planeDirection.dotProduct(boxAxis)) - projectedRadius;

    //cout <<"boxDistance:"<<boxDistance<<endl;
    //cout <<"plane.getOffset() is "<<plane.getOffset()<<endl;

    // Check for the intersection
    return (boxDistance <= plane.getOffset());
}
