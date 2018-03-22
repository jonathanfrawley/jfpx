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
#include "jfContact.h"

jfContact::jfContact()
    : m_BodyZero(NULL)
    , m_BodyOne(NULL)
    , m_Friction(0)
    , m_Restitution(0)
    , m_ContactPoint(0)
    , m_ContactNormal(0)
    , m_Penetration(0)
    , m_ContactToWorld(0)
    , m_ContactVelocity(0)
    , m_DesiredDeltaVelocity(0)
    , m_RelativeContactPosition(NULL)
{
}

jfContact::jfContact(const jfContact& other)
{
    m_BodyZero = other.getBody(0);
    m_BodyOne = other.getBody(1);
    m_Friction = other.getFriction();
    m_Restitution = other.getRestitution();
    m_Penetration = other.getPenetration();
    m_DesiredDeltaVelocity = other.getDesiredDeltaVelocity();
}

jfContact::~jfContact()
{
}
