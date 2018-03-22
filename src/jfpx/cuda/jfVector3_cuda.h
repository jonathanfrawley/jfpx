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

#ifndef JFVECTOR3_CUDA_H
#define JFVECTOR3_CUDA_H

#include <jfpx/jfCore.h>

#include <jfpx/x86/jfVector3_x86.h>

#include <cuda.h>
#include <cuda_runtime.h>

#include <stdio.h>

typedef struct {
    jfReal m_X;
    jfReal m_Y;
    jfReal m_Z;
    jfReal m_Pad; // To ensure 4-word alignment
} jfVector3Struct;

inline jfVector3_x86 copyToJfVector3_x86(jfVector3Struct s)
{
    return jfVector3_x86(s.m_X, s.m_Y, s.m_Z);
}

#endif
