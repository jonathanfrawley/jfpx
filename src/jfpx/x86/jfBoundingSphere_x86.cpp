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
#include "jfBoundingSphere_x86.h"

jfBoundingSphere_x86::jfBoundingSphere_x86()
    : jfBoundingSphere()
{
}

jfBoundingSphere_x86::jfBoundingSphere_x86(const jfVector3& centre,
    jfReal radius)
    : jfBoundingSphere(centre, radius)
{
}

jfBoundingSphere_x86::~jfBoundingSphere_x86()
{
}

void jfBoundingSphere_x86::recalculateBoundingVolume(const jfBoundingVolume& one,
    const jfBoundingVolume& two)
{
    //@ref : Millington code "collide_coarse.cpp"
    jfVector3_x86 centreOffset;
    jfVector3_x86 oneCentre;
    jfVector3_x86 twoCentre;
    one.getCentre(&oneCentre);
    two.getCentre(&twoCentre);
    twoCentre.subtract(oneCentre, &centreOffset);
    jfReal distance = centreOffset.squareMagnitude();
    jfReal radiusDiff = two.getRadius() - one.getRadius();

    // Check if the larger sphere encloses the small one
    if ((radiusDiff * radiusDiff) >= distance) {
        if (one.getRadius() > two.getRadius()) {
            (*m_Centre) = oneCentre;
            m_Radius = one.getRadius();
        } else {
            (*m_Centre) = twoCentre;
            m_Radius = two.getRadius();
        }
    }
    // Otherwise we need to work with partially
    // overlapping spheres
    else {
        distance = jfRealSqrt(distance);
        m_Radius = (distance + one.getRadius() + two.getRadius()) * ((jfReal)0.5);

        // The new centre is based on one's centre, moved towards
        // two's centre by an amount proportional to the spheres'
        // radii.
        (*m_Centre) = oneCentre;
        if (distance > 0) {
            jfVector3_x86 propCentre;
            centreOffset.multiply((m_Radius - one.getRadius()) / distance, &propCentre);
            (*m_Centre) += propCentre;
        }
    }
}

bool jfBoundingSphere_x86::overlaps(const jfBoundingVolume& other) const
{
    jfVector3_x86 relativeCentre;
    jfVector3_x86 otherCentre;

    other.getCentre(&otherCentre);
    m_Centre->subtract(otherCentre, &relativeCentre);
    jfReal distanceSquared = relativeCentre.squareMagnitude();
    return (distanceSquared < ((m_Radius + other.getRadius()) * (m_Radius + other.getRadius())));
}

jfReal jfBoundingSphere_x86::getGrowth(const jfBoundingVolume& other) const
{
    jfBoundingSphere_x86 newSphere;
    newSphere.recalculateBoundingVolume(*this, other);

    // We return a value proportional to the change in surface
    // area of the sphere.
    return ((newSphere.getRadius() * newSphere.getRadius()) - (m_Radius * m_Radius));
}
