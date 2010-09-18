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
#include "jfMatrix3_x86.h"

jfMatrix3_x86::jfMatrix3_x86()
{
}

jfMatrix3_x86::jfMatrix3_x86(jfReal e0, jfReal e1, jfReal e2,
								jfReal e3, jfReal e4, jfReal e5,
								jfReal e6, jfReal e7, jfReal e8)
	:
		jfMatrix3(e0,e1,e2,
					e3,e4,e5,
					e6,e7,e8)
{
}

jfMatrix3_x86::jfMatrix3_x86(const jfMatrix3& other)
	:
		jfMatrix3(other)
{
}

jfMatrix3_x86::~jfMatrix3_x86()
{
}

void jfMatrix3_x86::multiply(const jfMatrix3& other, jfMatrix3* result) const
{
    jfMatrix3_x86 tempResult;
    tempResult.setElem(0, (m_Elems[0] * other.getElem(0)) +
                           (m_Elems[1] * other.getElem(3)) +
                           (m_Elems[2] * other.getElem(6)));
    tempResult.setElem(1, (m_Elems[0] * other.getElem(1)) +
                           (m_Elems[1] * other.getElem(4)) +
                           (m_Elems[2] * other.getElem(7)));
    tempResult.setElem(2, (m_Elems[0] * other.getElem(2)) +
                           (m_Elems[1] * other.getElem(5)) +
                           (m_Elems[2] * other.getElem(8)));
    tempResult.setElem(3, (m_Elems[3] * other.getElem(0)) +
                           (m_Elems[4] * other.getElem(3)) +
                           (m_Elems[5] * other.getElem(6)));
    tempResult.setElem(4, (m_Elems[3] * other.getElem(1)) +
                           (m_Elems[4] * other.getElem(4)) +
                           (m_Elems[5] * other.getElem(7)));
    tempResult.setElem(5, (m_Elems[3] * other.getElem(2)) +
                           (m_Elems[4] * other.getElem(5)) +
                           (m_Elems[5] * other.getElem(8)));
    tempResult.setElem(6, (m_Elems[6] * other.getElem(0)) +
                           (m_Elems[7] * other.getElem(3)) +
                           (m_Elems[8] * other.getElem(6)));
    tempResult.setElem(7, (m_Elems[6] * other.getElem(1)) +
                           (m_Elems[7] * other.getElem(4)) +
                           (m_Elems[8] * other.getElem(7)));
    tempResult.setElem(8, (m_Elems[6] * other.getElem(2)) +
                           (m_Elems[7] * other.getElem(5)) +
                           (m_Elems[8] * other.getElem(8)));
    (*result) = tempResult;
}

void jfMatrix3_x86::multiply(const jfVector3& vec, jfVector3* result) const
{
    //@REF: Transform the matrix by the vector
    jfVector3_x86 tempResult;
   	tempResult.setX((vec.getX()*m_Elems[0]) +
					(vec.getY()*m_Elems[1]) +
					(vec.getZ()*m_Elems[2]));
	tempResult.setY((vec.getX()*m_Elems[3]) +
					(vec.getY()*m_Elems[4]) +
					(vec.getZ()*m_Elems[5]));
	tempResult.setZ((vec.getX()*m_Elems[6]) +
					(vec.getY()*m_Elems[7]) +
					(vec.getZ()*m_Elems[8]));
    (*result) = tempResult;
}

void jfMatrix3_x86::add(const jfMatrix3& other, jfMatrix3* result) const
{
	result->setElem(0,m_Elems[0] + other.getElem(0));
	result->setElem(1,m_Elems[1] + other.getElem(1));
	result->setElem(2,m_Elems[2] + other.getElem(2));
	result->setElem(3,m_Elems[3] + other.getElem(3));
	result->setElem(4,m_Elems[4] + other.getElem(4));
	result->setElem(5,m_Elems[5] + other.getElem(5));
	result->setElem(6,m_Elems[6] + other.getElem(6));
	result->setElem(7,m_Elems[7] + other.getElem(7));
	result->setElem(8,m_Elems[8] + other.getElem(8));
}

jfMatrix3_x86& jfMatrix3_x86::operator*=(jfReal val)
{
    unsigned i=0;
    for(i=0;i<9;i++)
    {
        m_Elems[i] = m_Elems[i] * val;
    }
	return (*this);
}

jfMatrix3_x86& jfMatrix3_x86::operator*=(const jfMatrix3& val)
{
	multiply(val,this);
	return (*this);
}

jfMatrix3_x86& jfMatrix3_x86::operator+=(const jfMatrix3& val)
{
	add(val,this);
	return (*this);
}

void jfMatrix3_x86::setInverse(const jfMatrix3& other)
{
    //@REF: Eberly p.636 (A.31)
    //@REF: Millington (p.173)
    jfReal a11 = other.getElem(0);
    jfReal a12 = other.getElem(1);
    jfReal a13 = other.getElem(2);
    jfReal a21 = other.getElem(3);
    jfReal a22 = other.getElem(4);
    jfReal a23 = other.getElem(5);
    jfReal a31 = other.getElem(6);
    jfReal a32 = other.getElem(7);
    jfReal a33 = other.getElem(8);

	jfReal det = ( (a11*a22*a33) + (a12*a23*a31) + (a13*a21*a32) - (a13*a22*a31) - (a12*a21*a33) - (a11*a23*a32) );
	if (det == jfReal(0.0))
	{
		//undefined division
		return;
	}
	jfReal detInv = jfReal(1.0)/det;

	m_Elems[0] = (detInv * ((a22*a33) - (a23*a32)));
	m_Elems[1] = (detInv * ((a13*a32) - (a12*a33)));
	m_Elems[2] = (detInv * ((a12*a23) - (a13*a22)));
	m_Elems[3] = (detInv * ((a23*a31) - (a21*a33)));
	m_Elems[4] = (detInv * ((a11*a33) - (a13*a31)));
	m_Elems[5] = (detInv * ((a13*a21) - (a11*a23)));
	m_Elems[6] = (detInv * ((a21*a32) - (a22*a31)));
	m_Elems[7] = (detInv * ((a12*a31) - (a11*a32)));
	m_Elems[8] = (detInv * ((a11*a22) - (a12*a21)));
}

void jfMatrix3_x86::getInverse(jfMatrix3* result) const
{
    result->setInverse(*this);
}

void jfMatrix3_x86::invert()
{
    setInverse(*this);
}

void jfMatrix3_x86::setTranspose(const jfMatrix3& other)
{
    jfReal a11 = other.getElem(0);
    jfReal a12 = other.getElem(1);
    jfReal a13 = other.getElem(2);
    jfReal a21 = other.getElem(3);
    jfReal a22 = other.getElem(4);
    jfReal a23 = other.getElem(5);
    jfReal a31 = other.getElem(6);
    jfReal a32 = other.getElem(7);
    jfReal a33 = other.getElem(8);

    m_Elems[0] = a11;
    m_Elems[1] = a21;
    m_Elems[2] = a31;
    m_Elems[3] = a12;
    m_Elems[4] = a22;
    m_Elems[5] = a32;
    m_Elems[6] = a13;
    m_Elems[7] = a23;
    m_Elems[8] = a33;
}

void jfMatrix3_x86::getTranspose(jfMatrix3* result) const
{
    result->setTranspose(*this);
}

void jfMatrix3_x86::setOrientation(const jfQuaternion& q)
{
    //Millington p.179
    m_Elems[0] = 1.0 - ((2*q.getJ()*q.getJ()) + (2*q.getK()*q.getK()));
    m_Elems[1] = (2.0*q.getI()*q.getJ()) + (2.0*q.getK()*q.getR());
    m_Elems[2] = (2.0*q.getI()*q.getK()) - (2.0*q.getJ()*q.getR());
    m_Elems[3] = (2.0*q.getI()*q.getJ()) - (2.0*q.getK()*q.getR());
    m_Elems[4] = 1.0 - ((2.0*q.getI()*q.getI()) + (2.0*q.getK()*q.getK()));
    m_Elems[5] = (2.0*q.getJ()*q.getK()) + (2.0*q.getI()*q.getR());
    m_Elems[6] = (2.0*q.getI()*q.getK()) + (2.0*q.getJ()*q.getR());
    m_Elems[7] = (2.0*q.getJ()*q.getK()) - (2.0*q.getI()*q.getR());
    m_Elems[8] = 1.0 - ((2.0*q.getI()*q.getI()) + (2.0*q.getJ()*q.getJ()));
}

void jfMatrix3_x86::transform(const jfVector3& vec, jfVector3* result) const
{
	multiply(vec, result);
}

void jfMatrix3_x86::transformTranspose(const jfVector3& vec,
										jfVector3* result) const
{
    jfVector3_x86 tempResult;
	tempResult.setX( (vec.getX() * m_Elems[0])
					+ (vec.getY() * m_Elems[3])
					+ (vec.getZ() * m_Elems[6]));
	tempResult.setY( (vec.getX() * m_Elems[1])
					+ (vec.getY() * m_Elems[4])
					+ (vec.getZ() * m_Elems[7]));
	tempResult.setZ( (vec.getX() * m_Elems[2])
					+ (vec.getY() * m_Elems[5])
					+ (vec.getZ() * m_Elems[8]));
    (*result) = tempResult;
}

void jfMatrix3_x86::linearInterpolate(const jfMatrix3& a,
												const jfMatrix3& b,
												jfReal prop,
												jfMatrix3* result) const
{
	unsigned int i;
    for (i = 0; i < 9; i++) {
        result->setElem(i, ((a.getElem(i)*(1-prop)) + (b.getElem(i)*prop)));
    }
}

void jfMatrix3_x86::setBlockInertiaTensor(const jfVector3& halfSizes, jfReal mass)
{
	//@REF: Millington code "core.h"
	jfVector3_x86 squares;
    halfSizes.componentProduct(halfSizes, &squares);
	setInertiaTensorCoeffs(0.3f*mass*(squares.getY() + squares.getZ()),
							0.3f*mass*(squares.getX() + squares.getZ()),
							0.3f*mass*(squares.getX() + squares.getY()));
}
