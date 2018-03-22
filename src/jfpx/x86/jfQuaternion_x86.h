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
#ifndef JFQUATERNION_X86_H
#define JFQUATERNION_X86_H

#include <jfpx/jfQuaternion.h>

class jfQuaternion_x86 : public jfQuaternion {
public:
    jfQuaternion_x86();

    jfQuaternion_x86(jfReal r, jfReal i, jfReal j, jfReal k);

    jfQuaternion_x86(const jfQuaternion& other);

    virtual ~jfQuaternion_x86();

    /*-----------------------------------------------------------------------------
         *  Inherited methods
         *-----------------------------------------------------------------------------*/
    void normalize();

    void operator*=(const jfQuaternion& other);

    void rotateByVector(const jfVector3& vec);

    void addScaledVector(const jfVector3& vec, jfReal scale);

protected:
};

#endif //JFQUATERNION_X86_H
