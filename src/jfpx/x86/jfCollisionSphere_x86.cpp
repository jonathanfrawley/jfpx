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
#include "jfCollisionSphere_x86.h"

jfCollisionSphere_x86::jfCollisionSphere_x86()
{
    m_Body = new jfRigidBody_x86();
    m_Offset = new jfMatrix4_x86();
    m_Transform = new jfMatrix4_x86();
}

jfCollisionSphere_x86::~jfCollisionSphere_x86()
{
    delete m_Body;
    delete m_Offset;
    delete m_Transform;
}

void jfCollisionSphere_x86::calculateInternals()
{
    //@ref: Millington p.274
    //Used in case sphere body doesn't match up with collision sphere
    jfMatrix4_x86 bodyTransform;
    m_Body->getTransformMatrix(&bodyTransform);
    bodyTransform.multiply((*m_Offset), m_Transform);
}
