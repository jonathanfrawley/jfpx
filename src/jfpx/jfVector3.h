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

#ifndef JFVECTOR_H
#define JFVECTOR_H

#include <jfpx/jfCore.h>
#include <jfpx/jfPrecision.h>
#include <math.h>

#include <iostream>
using namespace std;

class jfVector3 {
public:
    jfVector3();
    jfVector3(const jfReal x, const jfReal y, const jfReal z);

    /*-----------------------------------------------------------------------------
		 *  Virtual Constructor idiom
		 *  @REF : http://www.parashift.com/c++-faq-lite/virtual-functions.html#faq-20.8
		 *  DLA : 12/3/2010
		 *-----------------------------------------------------------------------------*/
    virtual jfVector3* clone() const = 0;
    //		virtual jfVector3* create() const = 0;

    virtual ~jfVector3();

    /*-----------------------------------------------------------------------------
		 *  Implemented methods
		 *-----------------------------------------------------------------------------*/
    virtual bool operator==(const jfVector3& other) const
    {
        return ((m_X == other.getX()) && (m_Y == other.getY()) && (m_Z == other.getZ()));
    }

    virtual bool operator!=(const jfVector3& other) const
    {
        return !((*this) == other);
    }

    /*-----------------------------------------------------------------------------
		 *  Interface
		 *-----------------------------------------------------------------------------*/
    virtual void invert() = 0;

    virtual jfReal magnitude() const = 0;

    virtual jfReal squareMagnitude() const = 0;

    virtual void normalize() = 0;

    virtual void operator*=(jfReal value) = 0;

    virtual void operator+=(const jfVector3& v) = 0;

    virtual void operator-=(const jfVector3& v) = 0;

    virtual void addScaledVector(const jfVector3& v, jfReal scale) = 0;

    virtual void componentProductUpdate(const jfVector3& v) = 0;

    virtual jfReal dotProduct(const jfVector3& v) const = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  multiply
		 *  Description:  Multiplies the current vector by the scalar and puts the result in the passed in value.
		 * =====================================================================================
		 */
    virtual void multiply(jfReal val, jfVector3* result) const = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  add
		 *  Description:  Adds the two vectors together and puts the result in
		 *  the passed in vector.
		 * =====================================================================================
		 */
    virtual void add(const jfVector3& vec, jfVector3* result) const = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  subtract
		 *  Description:  Subtracts the passed in vector from this and puts the
		 *  result in the passed in vector.
		 * =====================================================================================
		 */
    virtual void subtract(const jfVector3& vec, jfVector3* result) const = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  subtract
		 *  Description:  Subtracts the passed in value from each component in the vector.
		 * =====================================================================================
		 */
    virtual void subtract(jfReal val, jfVector3* result) const = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  componentProduct
		 *  Description:  Multiply each component by the passed in vectors component and
		 *  store result in passed in vector.
		 * =====================================================================================
		 */
    virtual void componentProduct(const jfVector3& vec, jfVector3* result) const = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  crossProduct
		 *  Description:  Gets the vector perpendicular to this and the passed in vector and
		 *  stores it in result.
		 * =====================================================================================
		 */
    virtual void crossProduct(const jfVector3& vec, jfVector3* result) const = 0;

    /* Implemented Methods */
    virtual void clear()
    {
        m_X = 0;
        m_Y = 0;
        m_Z = 0;
    }

    /* Accessors */
    virtual jfReal getX() const { return m_X; }
    virtual jfReal getY() const { return m_Y; }
    virtual jfReal getZ() const { return m_Z; }
    virtual void setX(jfReal val) { m_X = val; }
    virtual void setY(jfReal val) { m_Y = val; }
    virtual void setZ(jfReal val) { m_Z = val; }
    virtual jfReal getElem(unsigned i)
    {
        if (i == 0) {
            return m_X;
        } else if (i == 1) {
            return m_Y;
        } else {
            return m_Z;
        }
    }
    virtual void setElem(unsigned i, jfReal val)
    {
        if (i == 0) {
            m_X = val;
        } else if (i == 1) {
            m_Y = val;
        } else {
            m_Z = val;
        }
    }

protected:
    virtual void copyHere(const jfVector3& other);

    jfReal m_X;
    jfReal m_Y;
    jfReal m_Z;
    jfReal m_pad; //To ensure 4-word alignment
private:
};

inline ostream& operator<<(ostream& out, const jfVector3& vec)
{
    out << "<";
    out << vec.getX() << ",";
    out << vec.getY() << ",";
    out << vec.getZ();
    out << ">";
    return out;
}

#endif
