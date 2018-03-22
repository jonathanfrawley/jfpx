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
#include "jfBoxesAndBallsEventHandler_x86.h"

jfBoxesAndBallsEventHandler_x86::jfBoxesAndBallsEventHandler_x86()
{
}

jfBoxesAndBallsEventHandler_x86::~jfBoxesAndBallsEventHandler_x86()
{
}

void jfBoxesAndBallsEventHandler_x86::handleKeyEvents()
{
    jfKey keyNum = isKeyPressed();
    while (keyNum != JFK_NULL) {
        switch (keyNum) {
        case JFK_w:
            cam->strafeForward();
            break;
        case JFK_s:
            cam->strafeBackward();
            break;
        case JFK_a:
            cam->strafeLeft();
            break;
        case JFK_d:
            cam->strafeRight();
            break;
        case JFK_NULL:
            break;
        default:
            break;
        }
        keyNum = isKeyPressed(keyNum + 1);
    }
}

void jfBoxesAndBallsEventHandler_x86::handleMouseEvents()
{
    int x, y;
    if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(1)) {
        if (!m_WasMouse1Pressed) {
            m_LastX = x;
            m_LastY = y;
            m_WasMouse1Pressed = true;
        }
        int diffx = x - m_LastX;
        int diffy = y - m_LastY;
        m_LastX = x;
        m_LastY = y;
        jfVector3_x86 camRot, yRot, xRot;
        cam->getRot(&camRot);
        camRot.add(jfVector3_x86((float)diffy, 0.0, 0.0), &xRot);
        camRot.add(jfVector3_x86(0.0, (float)diffx, 0.0), &yRot);
        cam->setRot(xRot);
        cam->setRot(yRot);
    } else {
        m_WasMouse1Pressed = false;
    }
}
