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
#include "jfMatrix4_x86.h"

jfMatrix4_x86::jfMatrix4_x86()
    : jfMatrix4()
{
}

jfMatrix4_x86::~jfMatrix4_x86()
{
}

jfMatrix4_x86::jfMatrix4_x86(const jfMatrix4& other)
    : jfMatrix4(other)
{
}
/*
jfMatrix4_x86* jfMatrix4_x86::clone() const
{
	return new jfMatrix4_x86(*this);
}
*/

void jfMatrix4_x86::multiply(const jfVector3& vec, jfVector3* result) const
{
    jfVector3_x86 tempResult;
    tempResult.setX((vec.getX() * m_Elems[0]) + (vec.getY() * m_Elems[1]) + (vec.getZ() * m_Elems[2]) + m_Elems[3]);
    tempResult.setY((vec.getX() * m_Elems[4]) + (vec.getY() * m_Elems[5]) + (vec.getZ() * m_Elems[6]) + m_Elems[7]);
    tempResult.setZ((vec.getX() * m_Elems[8]) + (vec.getY() * m_Elems[9]) + (vec.getZ() * m_Elems[10]) + m_Elems[11]);
    (*result) = tempResult;
}

void jfMatrix4_x86::multiply(const jfMatrix4& other, jfMatrix4* result) const
{
    jfMatrix4_x86 tempResult;
    //Row by columns
    tempResult.setElem(0,
        (m_Elems[0] * other.getElem(0)) + (m_Elems[1] * other.getElem(4)) + (m_Elems[2] * other.getElem(8)) + (m_Elems[3] * other.getElem(12)));
    tempResult.setElem(1,
        (m_Elems[0] * other.getElem(1)) + (m_Elems[1] * other.getElem(5)) + (m_Elems[2] * other.getElem(9)) + (m_Elems[3] * other.getElem(12)));
    tempResult.setElem(2,
        (m_Elems[0] * other.getElem(2)) + (m_Elems[1] * other.getElem(6)) + (m_Elems[2] * other.getElem(10)) + (m_Elems[3] * other.getElem(14)));
    tempResult.setElem(3,
        (m_Elems[0] * other.getElem(3)) + (m_Elems[1] * other.getElem(7)) + (m_Elems[2] * other.getElem(11)) + (m_Elems[3] * other.getElem(15)));
    tempResult.setElem(4,
        (m_Elems[4] * other.getElem(0)) + (m_Elems[5] * other.getElem(4)) + (m_Elems[6] * other.getElem(8)) + (m_Elems[7] * other.getElem(12)));
    tempResult.setElem(5,
        (m_Elems[4] * other.getElem(1)) + (m_Elems[5] * other.getElem(5)) + (m_Elems[6] * other.getElem(9)) + (m_Elems[7] * other.getElem(13)));
    tempResult.setElem(6,
        (m_Elems[4] * other.getElem(2)) + (m_Elems[5] * other.getElem(6)) + (m_Elems[6] * other.getElem(10)) + (m_Elems[7] * other.getElem(14)));
    tempResult.setElem(7,
        (m_Elems[4] * other.getElem(3)) + (m_Elems[5] * other.getElem(7)) + (m_Elems[6] * other.getElem(11)) + (m_Elems[7] * other.getElem(15)));
    tempResult.setElem(8,
        (m_Elems[8] * other.getElem(0)) + (m_Elems[9] * other.getElem(4)) + (m_Elems[10] * other.getElem(8)) + (m_Elems[11] * other.getElem(12)));
    tempResult.setElem(9,
        (m_Elems[8] * other.getElem(1)) + (m_Elems[9] * other.getElem(5)) + (m_Elems[10] * other.getElem(9)) + (m_Elems[11] * other.getElem(13)));
    tempResult.setElem(10,
        (m_Elems[8] * other.getElem(2)) + (m_Elems[9] * other.getElem(6)) + (m_Elems[10] * other.getElem(10)) + (m_Elems[11] * other.getElem(14)));
    tempResult.setElem(11,
        (m_Elems[8] * other.getElem(3)) + (m_Elems[9] * other.getElem(7)) + (m_Elems[10] * other.getElem(11)) + (m_Elems[11] * other.getElem(15)));
    tempResult.setElem(12,
        (m_Elems[12] * other.getElem(0)) + (m_Elems[13] * other.getElem(4)) + (m_Elems[14] * other.getElem(8)) + (m_Elems[15] * other.getElem(12)));
    tempResult.setElem(13,
        (m_Elems[12] * other.getElem(1)) + (m_Elems[13] * other.getElem(5)) + (m_Elems[14] * other.getElem(9)) + (m_Elems[15] * other.getElem(13)));
    tempResult.setElem(14,
        (m_Elems[12] * other.getElem(2)) + (m_Elems[13] * other.getElem(6)) + (m_Elems[14] * other.getElem(10)) + (m_Elems[15] * other.getElem(14)));
    tempResult.setElem(15,
        (m_Elems[12] * other.getElem(3)) + (m_Elems[13] * other.getElem(7)) + (m_Elems[14] * other.getElem(11)) + (m_Elems[15] * other.getElem(15)));
    (*result) = tempResult;
}

jfReal jfMatrix4_x86::getDeterminant() const
{
    //Make copy so we don't overwrite our elements
    jfReal a11 = getElem(0);
    jfReal a12 = getElem(1);
    jfReal a13 = getElem(2);
    jfReal a14 = getElem(3);
    jfReal a21 = getElem(4);
    jfReal a22 = getElem(5);
    jfReal a23 = getElem(6);
    jfReal a24 = getElem(7);
    jfReal a31 = getElem(8);
    jfReal a32 = getElem(9);
    jfReal a33 = getElem(10);
    jfReal a34 = getElem(11);
    jfReal a41 = getElem(12);
    jfReal a42 = getElem(13);
    jfReal a43 = getElem(14);
    jfReal a44 = getElem(15);
    return ((a11 * a22 * a33 * a44)
        + (a11 * a23 * a34 * a42)
        + (a11 * a24 * a32 * a43)

        + (a12 * a21 * a34 * a43)
        + (a12 * a23 * a31 * a44)
        + (a12 * a24 * a33 * a41)

        + (a13 * a21 * a32 * a44)
        + (a13 * a22 * a34 * a41)
        + (a13 * a24 * a31 * a42)

        + (a14 * a21 * a33 * a42)
        + (a14 * a22 * a31 * a43)
        + (a14 * a23 * a32 * a41)

        - (a11 * a22 * a34 * a43)
        - (a11 * a23 * a32 * a44)
        - (a11 * a24 * a33 * a42)

        - (a12 * a21 * a33 * a44)
        - (a12 * a23 * a34 * a41)
        - (a12 * a24 * a31 * a43)

        - (a13 * a21 * a34 * a42)
        - (a13 * a22 * a31 * a44)
        - (a13 * a24 * a32 * a41)

        - (a14 * a21 * a32 * a43)
        - (a14 * a22 * a33 * a41)
        - (a14 * a23 * a31 * a42));
}

void jfMatrix4_x86::setInverse(const jfMatrix4& other)
{
    //Make copy so we don't overwrite our elements
    jfReal a11 = other.getElem(0);
    jfReal a12 = other.getElem(1);
    jfReal a13 = other.getElem(2);
    jfReal a14 = other.getElem(3);
    jfReal a21 = other.getElem(4);
    jfReal a22 = other.getElem(5);
    jfReal a23 = other.getElem(6);
    jfReal a24 = other.getElem(7);
    jfReal a31 = other.getElem(8);
    jfReal a32 = other.getElem(9);
    jfReal a33 = other.getElem(10);
    jfReal a34 = other.getElem(11);
    jfReal a41 = other.getElem(12);
    jfReal a42 = other.getElem(13);
    jfReal a43 = other.getElem(14);
    jfReal a44 = other.getElem(15);
    jfReal det = other.getDeterminant();

    if ((jfReal)det == 0) {
        return;
    }
    jfReal detInv = ((jfReal)1.0) / det;

    m_Elems[0] = (detInv * ((a22 * a33 * a44)
                               + (a23 * a34 * a42)
                               + (a24 * a32 * a43)
                               - (a22 * a34 * a43)
                               - (a23 * a32 * a44)
                               - (a24 * a33 * a42)));
    m_Elems[1] = (detInv * ((a12 * a34 * a43)
                               + (a13 * a32 * a44)
                               + (a14 * a33 * a42)
                               - (a12 * a33 * a44)
                               - (a13 * a34 * a42)
                               - (a14 * a32 * a43)));
    m_Elems[2] = (detInv * ((a12 * a23 * a44)
                               + (a13 * a24 * a42)
                               + (a14 * a22 * a43)
                               - (a12 * a24 * a43)
                               - (a13 * a22 * a44)
                               - (a14 * a23 * a42)));
    m_Elems[3] = (detInv * ((a12 * a24 * a33)
                               + (a13 * a22 * a34)
                               + (a14 * a23 * a32)
                               - (a12 * a23 * a34)
                               - (a13 * a24 * a32)
                               - (a14 * a22 * a33)));
    m_Elems[4] = (detInv * ((a21 * a34 * a43)
                               + (a23 * a31 * a44)
                               + (a24 * a33 * a41)
                               - (a21 * a33 * a44)
                               - (a23 * a34 * a41)
                               - (a24 * a31 * a43)));
    m_Elems[5] = (detInv * ((a11 * a33 * a44)
                               + (a13 * a34 * a41)
                               + (a14 * a31 * a43)
                               - (a11 * a34 * a43)
                               - (a13 * a31 * a44)
                               - (a14 * a33 * a41)));
    m_Elems[6] = (detInv * ((a11 * a24 * a43)
                               + (a13 * a21 * a44)
                               + (a14 * a23 * a41)
                               - (a11 * a23 * a44)
                               - (a13 * a24 * a41)
                               - (a14 * a21 * a43)));
    m_Elems[7] = (detInv * ((a11 * a23 * a34)
                               + (a13 * a24 * a31)
                               + (a14 * a21 * a33)
                               - (a11 * a24 * a33)
                               - (a13 * a21 * a34)
                               - (a14 * a23 * a31)));
    m_Elems[8] = (detInv * ((a21 * a32 * a44)
                               + (a22 * a34 * a41)
                               + (a24 * a31 * a42)
                               - (a21 * a34 * a42)
                               - (a22 * a31 * a44)
                               - (a24 * a32 * a41)));
    m_Elems[9] = (detInv * ((a11 * a34 * a42)
                               + (a12 * a31 * a44)
                               + (a14 * a32 * a41)
                               - (a11 * a32 * a44)
                               - (a12 * a34 * a41)
                               - (a14 * a31 * a42)));
    m_Elems[10] = (detInv * ((a11 * a22 * a44)
                                + (a12 * a24 * a41)
                                + (a14 * a21 * a42)
                                - (a11 * a24 * a42)
                                - (a12 * a21 * a44)
                                - (a14 * a22 * a41)));
    m_Elems[11] = (detInv * ((a11 * a24 * a32)
                                + (a12 * a21 * a34)
                                + (a14 * a22 * a31)
                                - (a11 * a22 * a34)
                                - (a12 * a24 * a31)
                                - (a14 * a21 * a32)));
    m_Elems[12] = (detInv * ((a21 * a33 * a42)
                                + (a22 * a31 * a43)
                                + (a23 * a32 * a41)
                                - (a21 * a32 * a43)
                                - (a22 * a33 * a41)
                                - (a23 * a31 * a42)));
    m_Elems[13] = (detInv * ((a11 * a32 * a43)
                                + (a12 * a33 * a41)
                                + (a13 * a31 * a42)
                                - (a11 * a33 * a42)
                                - (a12 * a31 * a43)
                                - (a13 * a32 * a41)));
    m_Elems[14] = (detInv * ((a11 * a23 * a42)
                                + (a12 * a21 * a43)
                                + (a13 * a22 * a41)
                                - (a11 * a22 * a43)
                                - (a12 * a23 * a41)
                                - (a13 * a31 * a42)));
    m_Elems[15] = (detInv * ((a11 * a22 * a33)
                                + (a12 * a23 * a31)
                                + (a13 * a21 * a32)
                                - (a11 * a23 * a32)
                                - (a12 * a21 * a33)
                                - (a13 * a22 * a31)));
}

void jfMatrix4_x86::getInverse(jfMatrix4* result) const
{
    result->setInverse(*this);
}

void jfMatrix4_x86::invert()
{
    setInverse(*this);
}

void jfMatrix4_x86::setOrientationAndPos(const jfQuaternion& q, const jfVector3& pos)
{
    m_Elems[0] = 1.0 - ((2.0 * q.getJ() * q.getJ()) + (2.0 * q.getK() * q.getK()));
    m_Elems[1] = (2.0 * q.getI() * q.getJ()) + (2.0 * q.getK() * q.getR());
    m_Elems[2] = (2.0 * q.getI() * q.getK()) - (2.0 * q.getJ() * q.getR());
    m_Elems[3] = pos.getX();
    m_Elems[4] = (2.0 * q.getI() * q.getJ()) - (2.0 * q.getK() * q.getR());
    m_Elems[5] = 1.0 - ((2.0 * q.getI() * q.getI()) + (2.0 * q.getK() * q.getK()));
    m_Elems[6] = (2.0 * q.getJ() * q.getK()) + (2.0 * q.getI() * q.getR());
    m_Elems[7] = pos.getY();
    m_Elems[8] = (2.0 * q.getI() * q.getK()) + (2.0 * q.getJ() * q.getR());
    m_Elems[9] = (2.0 * q.getJ() * q.getK()) - (2.0 * q.getI() * q.getR());
    m_Elems[10] = 1.0 - ((2.0 * q.getI() * q.getI()) + (2.0 * q.getJ() * q.getJ()));
    m_Elems[11] = pos.getZ();
}

void jfMatrix4_x86::transform(const jfVector3& vec, jfVector3* result) const
{
    multiply(vec, result);
}

void jfMatrix4_x86::transformInverse(const jfVector3& vec, jfVector3* result) const
{
    jfMatrix4_x86 tempResult;
    getInverse(&tempResult);
    tempResult.multiply(vec, result);
}

void jfMatrix4_x86::transformDirection(const jfVector3& vec, jfVector3* result) const
{
    jfVector3_x86 tempResult;
    tempResult.setX((vec.getX() * m_Elems[0]) + (vec.getY() * m_Elems[1]) + (vec.getZ() * m_Elems[2]));
    tempResult.setY((vec.getX() * m_Elems[4]) + (vec.getY() * m_Elems[5]) + (vec.getZ() * m_Elems[6]));
    tempResult.setZ((vec.getX() * m_Elems[8]) + (vec.getY() * m_Elems[9]) + (vec.getZ() * m_Elems[10]));
    (*result) = tempResult;
}

void jfMatrix4_x86::transformInverseDirection(const jfVector3& vec, jfVector3* result) const
{
    jfVector3_x86 tempResult;
    tempResult.setX((vec.getX() * m_Elems[0]) + (vec.getY() * m_Elems[4]) + (vec.getZ() * m_Elems[8]));
    tempResult.setY((vec.getX() * m_Elems[1]) + (vec.getY() * m_Elems[5]) + (vec.getZ() * m_Elems[9]));
    tempResult.setZ((vec.getX() * m_Elems[2]) + (vec.getY() * m_Elems[6]) + (vec.getZ() * m_Elems[10]));
    (*result) = tempResult;
}

void jfMatrix4_x86::fillColumnMajorArray(float array[16]) const
{
    array[0] = (float)m_Elems[0];
    array[1] = (float)m_Elems[4];
    array[2] = (float)m_Elems[8];
    array[3] = (float)0;

    array[4] = (float)m_Elems[1];
    array[5] = (float)m_Elems[5];
    array[6] = (float)m_Elems[9];
    array[7] = (float)0;

    array[8] = (float)m_Elems[2];
    array[9] = (float)m_Elems[6];
    array[10] = (float)m_Elems[10];
    array[11] = (float)0;

    array[12] = (float)m_Elems[3];
    array[13] = (float)m_Elems[7];
    array[14] = (float)m_Elems[11];
    array[15] = (float)1;
}

void jfMatrix4_x86::getAxisVector(unsigned index, jfVector3* result) const
{
    result->setX(m_Elems[index]);
    result->setY(m_Elems[index + 4]);
    result->setZ(m_Elems[index + 8]);
}
