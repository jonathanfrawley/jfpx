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
#ifndef JFFPSCAMERA_H
#define JFFPSCAMERA_H

#include <jfCamera/jfCamera.h>
#include <jfpx/x86/jfVector3_x86.h>

const float PI_OVER_180 = 0.0174532925f;

class jfFPSCamera : public jfCamera {
public:
    jfFPSCamera();

    ~jfFPSCamera();

    void strafeLeft();

    void strafeRight();

    void strafeForward();

    void strafeBackward();

private:
    float m_Speed;
};

#endif
