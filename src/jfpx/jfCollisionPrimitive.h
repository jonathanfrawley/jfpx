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
#ifndef JFCOLLISIONPRIMITIVE_H
#define JFCOLLISIONPRIMITIVE_H

#include <jfpx/jfMatrix4.h>
#include <jfpx/jfRigidBody.h>

class jfCollisionPrimitive {
public:
    jfCollisionPrimitive();

    virtual ~jfCollisionPrimitive();

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getAxisVector
		 *  Description:  Convenience function gets the a specified axis in the transformation matrix
		 * =====================================================================================
		 */
    virtual void getAxisVector(unsigned index, jfVector3* result) const
    {
        m_Transform->getAxisVector(index, result);
    }

    /*-----------------------------------------------------------------------------
		*  Interface
		*-----------------------------------------------------------------------------*/
    /*
		* ===  FUNCTION  ======================================================================
		*         Name:  calculateInternals
		*  Description:  Calculates the internals for the primitive.
		* =====================================================================================
		*/
    virtual void calculateInternals() = 0;

    /*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
    virtual void getTransformMatrix(jfMatrix4* result) const { (*result) = (*m_Transform); }

    //Should only be used in contact generation
    virtual jfRigidBody* getBody() const { return m_Body; }

protected:
    jfRigidBody* m_Body;
    jfMatrix4* m_Offset;
    jfMatrix4* m_Transform;

private:
};

#endif // JFCOLLISIONPRIMITIVE_H
