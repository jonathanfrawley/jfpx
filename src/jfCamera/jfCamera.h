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
#ifndef JFCAMERA_H
#define JFCAMERA_H

#include <jfpx/jfVector3.h>

class jfCamera
{
    public:
        jfCamera();

        virtual ~jfCamera();

		/*-----------------------------------------------------------------------------
		 *  Interface
		 *-----------------------------------------------------------------------------*/
		/*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
        void getPos(jfVector3* pos) const
        {
            (*pos) = (*m_Pos);
        }
        virtual void setPos(const jfVector3& newPos)
        {
            (*m_Pos) = newPos;
        }

        void getRot(jfVector3* rot) const
        {
            (*rot) = (*m_Rot);
        }
        void setRot(const jfVector3& newRot)
        {
            (*m_Rot) = newRot;
        }

        jfReal getHeading()
        {
            return m_Heading;
        }
        void setHeading(jfReal val)
        {
            m_Heading = val;
        }

    protected:
        jfVector3* m_Pos;
        jfVector3* m_Rot;
        jfReal m_Heading;
};

#endif //JFCAMERA_H
