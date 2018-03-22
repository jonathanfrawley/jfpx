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

#ifndef JFCOLLISSONPLANE_H
#define JFCOLLISSONPLANE_H

#include <jfpx/jfCollisionPrimitive.h>
#include <jfpx/jfCore.h>
#include <jfpx/jfVector3.h>

/*
 * =====================================================================================
 *        Class: jfCollisionPlane
 *  Description: Not a primitive, used to represent collisions with immovable world
 *  geometry.
 * =====================================================================================
 */
class jfCollisionPlane {
public:
    jfCollisionPlane();

    virtual ~jfCollisionPlane();

    /*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
    virtual void getDirection(jfVector3* direction) const { (*direction) = (*m_Direction); }
    virtual void setDirection(const jfVector3& direction)
    {
        (*m_Direction) = direction;
    }

    virtual jfReal getOffset() const { return m_Offset; }
    virtual void setOffset(jfReal val) { m_Offset = val; }
protected:
    jfVector3* m_Direction;
    jfReal m_Offset;

private:
};

#endif // JFCOLLISSONPLANE_H
