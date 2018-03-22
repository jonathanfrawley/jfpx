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
#ifndef JFBOUNDINGVOLUME_H
#define JFBOUNDINGVOLUME_H

#include <jfpx/jfCore.h>
#include <jfpx/jfVector3.h>

/*
 * =====================================================================================
 *        Class: jfBoundingVolume
 *  Description: Interface for bounding volume classes.
 * =====================================================================================
 */
class jfBoundingVolume {
public:
    jfBoundingVolume();

    virtual ~jfBoundingVolume();

    /*-----------------------------------------------------------------------------
		 *  Interface
		 *-----------------------------------------------------------------------------*/
    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  overlaps
		 *  Description:  Returns true if this volume overlaps with the other one, false
		 *  otherwise.
		 * =====================================================================================
		 */
    virtual bool overlaps(const jfBoundingVolume& other) const = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getGrowth
		 *  Description:  Reports how much the Bounding Volume would grow to incorporate the
		 *  given bounding volume. This is a relative measurement.
		 * =====================================================================================
		 */
    virtual jfReal getGrowth(const jfBoundingVolume& other) const = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  recalculateBoundingVolume
		 *  Description:  Recalculates the bounding volume to include the two passed in bounding
		 *  volumes.
		 * =====================================================================================
		 */
    virtual void recalculateBoundingVolume(const jfBoundingVolume& one,
        const jfBoundingVolume& two)
        = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getSize
		 *  Description:  Returns the size of this bounding volume
		 * =====================================================================================
		 */
    virtual jfReal getSize() const = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getCentre
		 *  Description:  Returns the centre of this bounding volume
		 * =====================================================================================
		 */
    virtual void getCentre(jfVector3* centre) const = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getRadius
		 *  Description:  Returns the radius of this bounding volume
		 * =====================================================================================
		 */
    virtual jfReal getRadius() const = 0;

protected:
private:
};

#endif // JFBOUNDINGVOLUME_H
