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
#include "jfBigBallisticEventHandler_x86.h"

jfBigBallisticEventHandler_x86::jfBigBallisticEventHandler_x86()
    : m_CurrentShotType(LASER)
{
}

jfBigBallisticEventHandler_x86::~jfBigBallisticEventHandler_x86()
{
}

ShotType jfBigBallisticEventHandler_x86::getCurrentShotType()
{
    return m_CurrentShotType;
}

void jfBigBallisticEventHandler_x86::handleKeyEvents()
{
    jfKey keyNum = isKeyPressed();
    while (keyNum != JFK_NULL) {
        switch (keyNum) {
        case JFK_1:
            m_CurrentShotType = PISTOL;
            break;
        case JFK_2:
            m_CurrentShotType = ARTILLERY;
            break;
        case JFK_3:
            m_CurrentShotType = FIREBALL;
            break;
        case JFK_4:
            m_CurrentShotType = LASER;
            break;
        case JFK_NULL:
            break;
        default:
            break;
        }
        keyNum = isKeyPressed(keyNum + 1);
    }
}
