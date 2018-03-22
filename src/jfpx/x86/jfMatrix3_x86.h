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
#ifndef JFMATRIX3_X86_H
#define JFMATRIX3_X86_H

#include <jfpx/jfMatrix3.h>
#include <jfpx/x86/jfVector3_x86.h>

class jfMatrix3_x86 : public jfMatrix3 {
public:
    jfMatrix3_x86();
    jfMatrix3_x86(jfReal e0, jfReal e1, jfReal e2,
        jfReal e3, jfReal e4, jfReal e5,
        jfReal e6, jfReal e7, jfReal e8);
    jfMatrix3_x86(const jfMatrix3& other);
    virtual ~jfMatrix3_x86();

    /*-----------------------------------------------------------------------------
		 *  Inherited methods
		 *-----------------------------------------------------------------------------*/
    virtual void multiply(const jfMatrix3& other, jfMatrix3* result) const;

    virtual void multiply(const jfVector3& vec, jfVector3* result) const;

    virtual void add(const jfMatrix3& other, jfMatrix3* result) const;

    virtual jfMatrix3_x86& operator*=(jfReal val);

    virtual jfMatrix3_x86& operator*=(const jfMatrix3& val);

    virtual jfMatrix3_x86& operator+=(const jfMatrix3& val);

    virtual void setInverse(const jfMatrix3& other);

    virtual void getInverse(jfMatrix3* result) const;

    virtual void invert();

    virtual void setTranspose(const jfMatrix3& other);

    virtual void getTranspose(jfMatrix3* result) const;

    virtual void setOrientation(const jfQuaternion& q);

    virtual void transform(const jfVector3& vec, jfVector3* result) const;

    virtual void transformTranspose(const jfVector3& vec,
        jfVector3* result) const;

    virtual void linearInterpolate(const jfMatrix3& a,
        const jfMatrix3& b,
        jfReal prop,
        jfMatrix3* result) const;

    virtual void setBlockInertiaTensor(const jfVector3& halfSizes, jfReal mass);

protected:
private:
};

#endif // JFMATRIX3_X86_H
