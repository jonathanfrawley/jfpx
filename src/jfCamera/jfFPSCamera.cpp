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
#include "jfFPSCamera.h"

jfFPSCamera::jfFPSCamera()
	:
		jfCamera(),
		m_Speed(0.2)
{
	m_Rot = new jfVector3_x86();
	m_Pos = new jfVector3_x86();
}

jfFPSCamera::~jfFPSCamera()
{
	delete m_Rot;
	delete m_Pos;
}

void jfFPSCamera::strafeLeft()
{
        (*m_Pos) += jfVector3_x86( - ((float)cos(m_Rot->getY() * PI_OVER_180) * m_Speed)
                                , 0
                                , - ((float)sin(m_Rot->getY() * PI_OVER_180) * m_Speed)
                                );
}

void jfFPSCamera::strafeRight()
{
        (*m_Pos) += jfVector3_x86( ((float)cos(m_Rot->getY() * PI_OVER_180) * m_Speed)
                                , 0
                                , ((float)sin(m_Rot->getY() * PI_OVER_180) * m_Speed)
                                );
}

void jfFPSCamera::strafeForward()
{
        (*m_Pos) += jfVector3_x86( ((float)sin(m_Rot->getY() * PI_OVER_180) * m_Speed)
                                , 0
                                , - ((float)cos(m_Rot->getY() * PI_OVER_180) * m_Speed)
                                );
}
void jfFPSCamera::strafeBackward()
{
        (*m_Pos) += jfVector3_x86( - ((float)sin(m_Rot->getY() * PI_OVER_180) * m_Speed)
                                , 0
                                , ((float)cos(m_Rot->getY() * PI_OVER_180) * m_Speed)
                                );
}
