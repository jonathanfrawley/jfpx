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
#ifndef JFMATRIX4_H
#define JFMATRIX4_H

#include <iostream>
using namespace std;

#include <jfpx/jfCore.h>
#include <jfpx/jfVector3.h>
#include <jfpx/jfQuaternion.h>

class jfMatrix4
{
    public:
        //Identity Matrix
        jfMatrix4();

        jfMatrix4(const jfMatrix4& other);

        jfMatrix4& operator=(const jfMatrix4& other);

        virtual ~jfMatrix4();


		/*-----------------------------------------------------------------------------
		 *  Implemented Methods
		 *-----------------------------------------------------------------------------*/

		/*-----------------------------------------------------------------------------
		 *  Interface
		 *-----------------------------------------------------------------------------*/
		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  multiply
		 *  Description:  Multiplies this matrix by the vector and stores the result in result
		 *  param.
		 *  In effect this transforms the vector by this matrix.
		 *  Useful for moving between coordinate systems (i.e between object and world coords).
		 * =====================================================================================
		 */
		virtual void multiply(const jfVector3& vec, jfVector3* result) const = 0;


		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  multiply
		 *  Description:  Performs standard matrix multipication and stores the result in the
		 *  result param.
		 * =====================================================================================
		 */
        virtual void multiply(const jfMatrix4& other, jfMatrix4* result) const = 0;


		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getDeterminant
		 *  Description:  Calculates the determinant of this matrix and returns it. Used during
		 *  inversion of a matrix.
		 * =====================================================================================
		 */
        virtual jfReal getDeterminant() const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  setInverse
		 *  Description:  Sets this matrix to be the inverse of the passed in matrix.
		 * =====================================================================================
		 */
        virtual void setInverse(const jfMatrix4& other) = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getInverse
		 *  Description:  Stores the inverse of this matrix in the result param.
		 * =====================================================================================
		 */
        virtual void getInverse(jfMatrix4* result) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  invert
		 *  Description:  Inverts this matrix.
		 * =====================================================================================
		 */
		virtual void invert() = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  setOrientationAndPos
		 *  Description:  Sets the matrix to be the rotation matrix corresponding to the passed
		 *  in quaternion at the point passed in.
		 * =====================================================================================
		 */
        virtual void setOrientationAndPos(const jfQuaternion& q, const jfVector3& pos) = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  transform
		 *  Description:  Transforms the vector by this matrix and stores the result in the
		 *  result param.
		 * =====================================================================================
		 */
        virtual void transform(const jfVector3& vec, jfVector3* result) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  transformInverse
		 *  Description:  Transforms the vector by the transformational inverse of this matrix.
		 *  Note: Relies on the fact that the inverse of a pure rotational matrix is its
		 *  transpose.
		 * =====================================================================================
		 */
        virtual void transformInverse(const jfVector3& vec, jfVector3* result) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  transformDirection
		 *  Description:  Transform the given direction vector by this matrix.
		 * =====================================================================================
		 */
        virtual void transformDirection(const jfVector3& vec, jfVector3* result) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  transformInverseDirection
		 *  Description:  Transform the given direction vector by transformational inverse of
		 *  this matrix.
		 *  Note: Relies on the fact that the inverse of a pure rotational matrix is its
		 *  transpose.
		 * =====================================================================================
		 */
        virtual void transformInverseDirection(const jfVector3& vec, jfVector3* result) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  fillColumnMajorArray
		 *  Description:  Fills the column major Array passed with this transform matrix so it
		 *  can be used as a transform matrix. This is done by transposing the current matrix.
		 * =====================================================================================
		 */
        virtual void fillColumnMajorArray(float array[16]) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getAxisVector
		 *  Description:  Gets an axis vector (column in matrix).
		 * =====================================================================================
		 */
		virtual void getAxisVector(unsigned index, jfVector3* result) const = 0;



		/*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
		virtual jfReal getElem(int index) const { return m_Elems[index]; }
        virtual void setElem(int index, jfReal val) { m_Elems[index] = val; }

    protected:
        virtual void copyHere(const jfMatrix4& other);

        jfReal m_Elems[16]; //3x4 matrix
    private:
};

inline ostream& operator<<(ostream& out, const jfMatrix4& m)
{
    int i;
    out << "<<";
    out << " ";
    for(i=0;i<16;i++)
    {
        out << m.getElem(i)<<" ";
    }
    out << ">>";
    return out;
}

#endif // JFMATRIX4_H
