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
#ifndef JFMATRIX4_X86_H
#define JFMATRIX4_X86_H

#include <jfpx/jfMatrix4.h>
#include <jfpx/x86/jfVector3_x86.h>


class jfMatrix4_x86 : public jfMatrix4
{
    public:
        jfMatrix4_x86();

        jfMatrix4_x86(const jfMatrix4& other);

        virtual ~jfMatrix4_x86();

	   /*-----------------------------------------------------------------------------
		*  Inherited methods
		*-----------------------------------------------------------------------------*/
		virtual void multiply(const jfVector3& vec, jfVector3* result) const;

        virtual void multiply(const jfMatrix4& other, jfMatrix4* result) const;

        virtual jfReal getDeterminant() const;

        virtual void setInverse(const jfMatrix4& other);

        virtual void getInverse(jfMatrix4* result) const;

		virtual void invert();

        virtual void setOrientationAndPos(const jfQuaternion& q, const jfVector3& pos);

        virtual void transform(const jfVector3& vec, jfVector3* result) const;

        virtual void transformInverse(const jfVector3& vec, jfVector3* result) const;

        virtual void transformDirection(const jfVector3& vec, jfVector3* result) const;

        virtual void transformInverseDirection(const jfVector3& vec, jfVector3* result) const;

		virtual void fillColumnMajorArray(float array[16]) const;

		virtual void getAxisVector(unsigned index, jfVector3* result) const;
    protected:
    private:
};

#endif // JFMATRIX4_X86_H
