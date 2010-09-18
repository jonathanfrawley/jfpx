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
#ifndef JFMATRIX3_H
#define JFMATRIX3_H

#include <jfpx/jfCore.h>
#include <jfpx/jfQuaternion.h>

#include <iostream>
using namespace std;


/*
 * =====================================================================================
 *        Class:  jfMatrix3
 *  Description:  A class to represent 3x3 matrices.
 *  This class is mostly used to hold inertia tensors.
 * =====================================================================================
 */
class jfMatrix3
{
    public:
        jfMatrix3();

        jfMatrix3(jfReal e0, jfReal e1, jfReal e2,
					jfReal e3, jfReal e4, jfReal e5,
					jfReal e6, jfReal e7, jfReal e8);

        jfMatrix3(const jfMatrix3& other);

        jfMatrix3& operator=(const jfMatrix3& other);

        virtual ~jfMatrix3();


		/*-----------------------------------------------------------------------------
		 *  Implemented Methods
		 *-----------------------------------------------------------------------------*/
		/* 
		 * ===  FUNCTION  ======================================================================
		 *         Name:  setSkewSymmetric
		 *  Description:  Sets the matrix to be a skew symmetric matrix based on
         *  the given vector. The skew symmetric matrix is the equivalent
         *  of the vector product. So if a,b are vectors. a x b = A_s b
         *  where A_s is the skew symmetric form of a.
		 *  @ref : Millington p.368 Sec.15.4.2
		 * =====================================================================================
		 */
		virtual void setSkewSymmetric(const jfVector3& vec)
		{
			m_Elems[0] = 0;
			m_Elems[1] = -vec.getZ();
			m_Elems[2] = vec.getY();
			m_Elems[3] = vec.getZ();
			m_Elems[4] = 0;
			m_Elems[5] = -vec.getX();
			m_Elems[6] = -vec.getY();
			m_Elems[7] = vec.getX();
			m_Elems[8] = 0;
		}

		/*-----------------------------------------------------------------------------
		 *  Interface
		 *-----------------------------------------------------------------------------*/
		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  multiply
		 *  Description:  Multiplies this matrix by another using standard matrix multipication.
		 *  Stores result in result param.
		 * =====================================================================================
		 */
        virtual void multiply(const jfMatrix3& other, jfMatrix3* result) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  multiply
		 *  Description:  Multiplies this matrix by a vector, transforming the vector by the
		 *  matrix.
		 *  Stores result in result param.
		 * =====================================================================================
		 */
        virtual void multiply(const jfVector3& vec, jfVector3* result) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  add
		 *  Description:  Adds this matrix to another using standard matrix addition.
		 *  Stores result in result param.
		 * =====================================================================================
		 */
        virtual void add(const jfMatrix3& other, jfMatrix3* result) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  operator*=
		 *  Description:  Multiplies the matrix by the scalar and returns a reference to itself.
		 * =====================================================================================
		 */
        virtual jfMatrix3& operator*=(jfReal val) = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  operator*=
		 *  Description:  Multiplies the matrix by the other matrix and returns a 
		 *  reference to itself.
		 * =====================================================================================
		 */
        virtual jfMatrix3& operator*=(const jfMatrix3& val) = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  operator+=
		 *  Description:  Adds the matrix to the other matrix and returns a 
		 *  reference to itself.
		 * =====================================================================================
		 */
        virtual jfMatrix3& operator+=(const jfMatrix3& val) = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  setInverse
		 *  Description:  Sets this matrix to be the inverse of the matrix passed in.
		 * =====================================================================================
		 */
        virtual void setInverse(const jfMatrix3& other) = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getInverse
		 *  Description:  Gets the inverse of this matrix and returns a pointer to it.
		 *  Stores result in result param.
		 * =====================================================================================
		 */
        virtual void getInverse(jfMatrix3* result) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  invert
		 *  Description:  Inverts this matrix
		 * =====================================================================================
		 */
        virtual void invert() = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  setTranspose
		 *  Description:  Sets this matrix to be the transpose of the matrix passed in.
		 * =====================================================================================
		 */
        virtual void setTranspose(const jfMatrix3& other) = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getTranspose
		 *  Description:  Returns the transpose of this matrix.
		 *  Stores result in result param.
		 * =====================================================================================
		 */
        virtual void getTranspose(jfMatrix3* result) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  setOrientation
		 *  Description:  Sets this matrix to be the orientation matrix for the passed in quaternion.
		 * =====================================================================================
		 */
        virtual void setOrientation(const jfQuaternion& q) = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  transform
		 *  Description:  Transforms the passed in vector by this matrix.
		 *  Stores result in result param.
		 * =====================================================================================
		 */
		/*
        virtual jfVector3* transform(jfVector3& vec) = 0;
		*/
        virtual void transform(const jfVector3& vec, jfVector3* result) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  transformTranspose
		 *  Description:  Transforms the given vector by the transpose of this matrix.
		 * =====================================================================================
		 */
		virtual void transformTranspose(const jfVector3& vec,
										jfVector3* result) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  linearInterpolate
		 *  Description:  Interpolates between a and b using prop as the deciding value.
		 *  Stores result in result param.
		 * =====================================================================================
		 */
		virtual void linearInterpolate(const jfMatrix3& a,
												const jfMatrix3& b,
												jfReal prop,
												jfMatrix3* result) const = 0;

		/*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  setComponents
		 *  Description:  Create a Matrix from the three column vectors supplied.
		 * =====================================================================================
		 */
		virtual void setComponents(const jfVector3& vec1,
									const jfVector3& vec2,
									const jfVector3& vec3)
		{
			m_Elems[0] = vec1.getX();
			m_Elems[1] = vec2.getX();
			m_Elems[2] = vec3.getX();
			m_Elems[3] = vec1.getY();
			m_Elems[4] = vec2.getY();
			m_Elems[5] = vec3.getY();
			m_Elems[6] = vec1.getZ();
			m_Elems[7] = vec2.getZ();
			m_Elems[8] = vec3.getZ();
		}

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  setInertiaTensorCoeffs
		 *  Description:  Sets the value of the matrix from inertia tensor values.
		 * =====================================================================================
		 */
		virtual void setInertiaTensorCoeffs(jfReal ix, jfReal iy, jfReal iz, jfReal ixy=0, jfReal ixz=0, jfReal iyz=0)
		{
			//@REF: Millington code "core.h"
			m_Elems[0] = ix;
			m_Elems[1] = -ixy;
			m_Elems[2] = -ixz;
			m_Elems[3] = -ixy;
			m_Elems[4] = iy;
			m_Elems[5] = -iyz;
			m_Elems[6] = -ixz;
			m_Elems[7] = -iyz;
			m_Elems[8] = iz;
		}

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  setBlockInertiaTensor
		 *  Description:  Sets the value of the matrix as an inertia tensor of
         * a rectangular block aligned with the body's coordinate
         * system with the given axis half-sizes and mass.
		 * =====================================================================================
		 */
		virtual void setBlockInertiaTensor(const jfVector3& halfSizes, jfReal mass) = 0;

        virtual jfReal getElem(int index) const { return m_Elems[index]; }
        virtual void setElem(int index, jfReal val) { m_Elems[index] = val; }

        //friend ostream& operator<< (ostream &out, jfMatrix3 &m);
        //virtual jfMatrix3& operator=(const jfMatrix3& other);
    protected:
        virtual void copyHere(const jfMatrix3& other);

        jfReal m_Elems[9]; // 3x3 Matrix
    private:
};

inline ostream& operator<<(ostream& out, const jfMatrix3& m)
{
    int i;
    out << "<<";
    for(i=0;i<9;i++)
    {
        out << "," << m.getElem(i);
    }
    out << ">>";
    return out;
}

#endif // JFMATRIX3_H
