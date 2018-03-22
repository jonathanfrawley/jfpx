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
#include "jfFlightEventHandler_x86.h"

jfFlightEventHandler_x86::jfFlightEventHandler_x86()
    : aircraft(0)
    , rudderControl(0)
    , leftWingControl(0)
    , rightWingControl(0)
{
}

jfFlightEventHandler_x86::~jfFlightEventHandler_x86()
{
}

void jfFlightEventHandler_x86::resetAircraft()
{
    aircraft->setPos(jfVector3_x86(0, 0, 0));
    aircraft->setOrientation(jfQuaternion_x86(1, 0, 0, 0));
    aircraft->setVelocity(jfVector3_x86(0, 0, 0));
    aircraft->setRotation(jfVector3_x86(0, 0, 0));
}

void jfFlightEventHandler_x86::handleKeyEvents()
{
    jfKey keyNum = isKeyPressed();
    jfReal deltaVal = 0.1;
    while (keyNum != JFK_NULL) {
        switch (keyNum) {
        case (JFK_q):
            (*rudderControl) += deltaVal;
            break;
        case (JFK_e):
            (*rudderControl) -= deltaVal;
            break;
        case (JFK_w):
            (*leftWingControl) -= deltaVal;
            (*rightWingControl) -= deltaVal;
            break;
        case (JFK_s):
            (*leftWingControl) += deltaVal;
            (*rightWingControl) += deltaVal;
            break;
        case (JFK_d):
            (*leftWingControl) -= deltaVal;
            (*rightWingControl) += deltaVal;
            break;
        case (JFK_a):
            (*leftWingControl) += deltaVal;
            (*rightWingControl) -= deltaVal;
            break;
        case (JFK_x):
            (*leftWingControl) = 0.0f;
            (*rightWingControl) = 0.0f;
            (*rudderControl) = 0.0f;
            break;
        case (JFK_r):
            resetAircraft();
            break;
        default:
            break;
        }
        if ((*leftWingControl) < -1.0) {
            (*leftWingControl) = -1.0;
        }
        if ((*leftWingControl) > 1.0) {
            (*leftWingControl) = 1.0;
        }
        if ((*rightWingControl) < -1.0) {
            (*rightWingControl) = -1.0;
        }
        if ((*rightWingControl) > 1.0) {
            (*rightWingControl) = 1.0;
        }
        if ((*rudderControl) < -1.0) {
            (*rudderControl) = -1.0;
        }
        if ((*rudderControl) > 1.0) {
            (*rudderControl) = 1.0;
        }
        keyNum = isKeyPressed(keyNum + 1);
    }
}
