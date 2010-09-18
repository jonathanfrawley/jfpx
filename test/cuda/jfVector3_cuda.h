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

#ifndef JFVECTOR_CUDA_H
#define JFVECTOR_CUDA_H

#include <jfpx/jfPrecision.h>
#include <jfpx/jfVector3.h>

#include <math.h>

class jfVector3_cuda : public jfVector3
{
    public:
        jfVector3_cuda();
        jfVector3_cuda(const real x, const real y, const real z);
    private:
        real _x;
        real _y;
        real _z;
        real _pad; //To ensure 4-word alignment
};
#endif
