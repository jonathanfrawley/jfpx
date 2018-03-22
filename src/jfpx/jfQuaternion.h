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
#ifndef JFQUATERNION_H
#define JFQUATERNION_H

#include <jfpx/jfCore.h>
#include <jfpx/jfVector3.h>

class jfQuaternion {
public:
    jfQuaternion();

    jfQuaternion(jfReal r, jfReal i, jfReal j, jfReal k);

    jfQuaternion(const jfQuaternion& other);

    virtual ~jfQuaternion();

    /*-----------------------------------------------------------------------------
		 *  Interface
		 *-----------------------------------------------------------------------------*/

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  normalize
		 *  Description:  Makes this a unit length quaternion.
		 * =====================================================================================
		 */
    virtual void normalize() = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  operator*=
		 *  Description:  Multiplies this quaternion by the one passed in.
		 * =====================================================================================
		 */
    virtual void operator*=(const jfQuaternion& other) = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  rotateByVector
		 *  Description:  Rotates the quaternion by the passed in vector.
		 * =====================================================================================
		 */
    virtual void rotateByVector(const jfVector3& vec) = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  addScaledVector
		 *  Description:  Adds the vector scaled to this quaternion.
		 * =====================================================================================
		 */
    virtual void addScaledVector(const jfVector3& vec, jfReal scale) = 0;

    /*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
    virtual jfReal getR() const { return m_R; }
    virtual jfReal getI() const { return m_I; }
    virtual jfReal getJ() const { return m_J; }
    virtual jfReal getK() const { return m_K; }
protected:
    jfReal m_R, m_I, m_J, m_K;
};

#endif // JFQUATERNION_H
