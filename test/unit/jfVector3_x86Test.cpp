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
#include "UnitTest++.h"

#include <jfpx/x86/jfVector3_x86.h>

#include <iostream>
#include <vector>
using namespace std;

namespace
{
    TEST(CreationDeletion)
    {
        jfVector3_x86* vec = new jfVector3_x86();
        delete vec;
    }

    TEST(multiply)
    {
        jfVector3_x86 a,c;
        a.setX(-1);
        a.setY(-2);
        a.setZ(-3);
        a.multiply(-1, &c);
        CHECK_CLOSE(c.getX(), 1, 0.1);
        CHECK_CLOSE(c.getY(), 2, 0.1);
        CHECK_CLOSE(c.getZ(), 3, 0.1);
    }

    TEST(crossProduct)
    {
        jfVector3_x86 a,b,c;
        a.setX(-1);
        a.setY(-2);
        a.setZ(-3);
        b.setX(40);
        b.setY(500);
        b.setZ(60);
        a.crossProduct(b, &c);
        CHECK_CLOSE(c.getX(), 1380, 0.1);
        CHECK_CLOSE(c.getY(), -60, 0.1);
        CHECK_CLOSE(c.getZ(), -420, 0.1);
    }
}
