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
#ifndef JFVECTOR_X86_H
#define JFVECTOR_X86_H

#include <jfpx/jfPrecision.h>
#include <jfpx/jfVector3.h>
//#include <jfpx/cuda/jfVector3_cuda.h>

#include <math.h>

class jfVector3_x86 : public jfVector3
{
    public:
        jfVector3_x86();

        jfVector3_x86(const jfReal x, const jfReal y, const jfReal z);

        jfVector3_x86(const jfVector3& other);
/*
        jfVector3_x86(const jfVector3_cuda& other)
        {
            m_X = other.m_X;
            m_Y = other.m_Y;
            m_Z = other.m_Z;
        }

        jfVector3_x86(const jfVector3Struct& other)
        {
            m_X = other.m_X;
            m_Y = other.m_Y;
            m_Z = other.m_Z;
        }
*/
		//Rule of three
		//@ref http://www.drdobbs.com/cpp/184401400
		//DLA:12/3/2010
        jfVector3_x86& operator=(const jfVector3& other);

		virtual jfVector3_x86* clone() const
		{
			return new jfVector3_x86(*this);
		}

        virtual ~jfVector3_x86();

		/*-----------------------------------------------------------------------------
		 *  Inherited methods
		 *-----------------------------------------------------------------------------*/
        virtual void invert();

        virtual jfReal magnitude() const;

        virtual jfReal squareMagnitude() const;

        virtual void normalize();

        virtual void operator*=(jfReal value);

        virtual void operator+=(const jfVector3& v);

        virtual void operator-=(const jfVector3& v);

        virtual void addScaledVector(const jfVector3& v, jfReal scale);

        virtual void componentProductUpdate(const jfVector3& v);

        virtual jfReal dotProduct(const jfVector3& v) const;

		virtual void multiply(jfReal val, jfVector3* result) const;

		virtual void add(const jfVector3& val, jfVector3* result) const;

		virtual void subtract(const jfVector3& val, jfVector3* result) const;

        virtual void subtract(jfReal val, jfVector3* result) const;

		virtual void componentProduct(const jfVector3& val, jfVector3* result) const;

		virtual void crossProduct(const jfVector3& vec, jfVector3* result) const;

    private:
};
#endif
