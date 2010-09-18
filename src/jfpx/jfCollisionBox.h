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
#ifndef JFCOLLISIONBOX_H
#define JFCOLLISIONBOX_H

#include <jfpx/jfCollisionPrimitive.h>
#include <jfpx/jfVector3.h>

class jfCollisionBox : public jfCollisionPrimitive
{
    public:
        jfCollisionBox();
        virtual ~jfCollisionBox();

		/*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
        virtual void setHalfSize(const jfVector3& val) { (*m_HalfSize) = val; }
		virtual void getHalfSize(jfVector3* val) const { (*val) = (*m_HalfSize); }
    protected:
        jfVector3* m_HalfSize;
    private:
};

#endif // JFCOLLISIONBOX_H
