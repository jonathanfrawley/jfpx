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
#ifndef JFBOUNDINGSPHERE_X86_H
#define JFBOUNDINGSPHERE_X86_H

#include <jfpx/jfBoundingSphere.h>
#include <jfpx/x86/jfCollisionPrimitive_x86.h>
#include <jfpx/x86/jfVector3_x86.h>

/*
 * =====================================================================================
 *        Class: jfBoundingSphere_x86
 *  Description:
 * =====================================================================================
 */
class jfBoundingSphere_x86 : public jfCollisionPrimitive_x86, public jfBoundingSphere {
public:
    jfBoundingSphere_x86();

    jfBoundingSphere_x86(const jfVector3& centre, jfReal radius);

    jfBoundingSphere_x86(const jfBoundingVolume& one, const jfBoundingVolume& two);

    virtual ~jfBoundingSphere_x86();

    /*-----------------------------------------------------------------------------
		 *  Inherited Methods
		 *-----------------------------------------------------------------------------*/
    virtual bool overlaps(const jfBoundingVolume& other) const;

    virtual jfReal getGrowth(const jfBoundingVolume& other) const;

    virtual void recalculateBoundingVolume(const jfBoundingVolume& one,
        const jfBoundingVolume& two);

protected:
private:
};

#endif // JFBOUNDINGSPHERE_X86_H
