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
#include "jfContactResolver.h"

jfContactResolver::jfContactResolver()
    : m_MaxVelocityIterations(0)
    , m_MaxPositionIterations(0)
    , m_VelocityEpsilon(0)
    , m_PositionEpsilon(0)
{
}

jfContactResolver::jfContactResolver(unsigned iterations, jfReal velocityEpsilon, jfReal positionEpsilon)
    : m_MaxVelocityIterations(iterations)
    , m_MaxPositionIterations(iterations)
    , m_VelocityEpsilon(velocityEpsilon)
    , m_PositionEpsilon(positionEpsilon)
{
}

jfContactResolver::jfContactResolver(unsigned velocityIterations, unsigned positionIterations, jfReal velocityEpsilon, jfReal positionEpsilon)
    : m_MaxVelocityIterations(velocityIterations)
    , m_MaxPositionIterations(positionIterations)
    , m_VelocityEpsilon(velocityEpsilon)
    , m_PositionEpsilon(positionEpsilon)
{
}

jfContactResolver::~jfContactResolver()
{
}
