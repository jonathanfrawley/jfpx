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
#include <oct.h>
#include <iostream>
using namespace std;

#include <jfpx/x86/jfMatrix3_x86.h>


namespace
{
    TEST(Multiply)
    {
        jfMatrix3_x86 a,b;
        a.setElem(0,1.0);
        a.setElem(1,2.0);
        a.setElem(2,3.0);
        a.setElem(3,4.0);
        a.setElem(4,5.0);
        a.setElem(5,6.0);
        a.setElem(6,7.0);
        a.setElem(7,8.0);
        a.setElem(8,9.0);
        b.setElem(0,1.0);
        b.setElem(1,2.0);
        b.setElem(2,3.0);
        b.setElem(3,4.0);
        b.setElem(4,5.0);
        b.setElem(5,6.0);
        b.setElem(6,7.0);
        b.setElem(7,8.0);
        b.setElem(8,9.0);
        jfMatrix3_x86 c;
        a.multiply(b, &c);
        bool result = (c.getElem(0) == 30.0);
        CHECK(result);
        result = (c.getElem(1) == 36.0);
        CHECK(result);
        result = (c.getElem(2) == 42.0);
        CHECK(result);
        result = (c.getElem(3) == 66.0);
        CHECK(result);
        result = (c.getElem(4) == 81.0);
        CHECK(result);
        result = (c.getElem(5) == 96.0);
        CHECK(result);
        result = (c.getElem(6) == 102.0);
        CHECK(result);
        result = (c.getElem(7) == 126.0);
        CHECK(result);
        result = (c.getElem(8) == 150.0);
        CHECK(result);
    }

    TEST(MultiplyEquals)
    {
        jfMatrix3_x86 a;
        a.setElem(0,1.0);
        a.setElem(1,2.0);
        a.setElem(2,3.0);
        a.setElem(3,4.0);
        a.setElem(4,5.0);
        a.setElem(5,6.0);
        a.setElem(6,7.0);
        a.setElem(7,8.0);
        a.setElem(8,9.0);
        a *= 2.0;
        int i;
        bool result;
        for(i=0 ; i<9 ; i++)
        {
            result = (a.getElem(i) == (2.0*(i+1)));
            CHECK(result);
        }
        result = (a.getElem(0) == 2.0);
        CHECK(result);
        result = (a.getElem(0) == 4.0);
    }

    TEST(SetInverse)
    {
        jfMatrix3_x86 a;
        a.setElem(0,1.0);
        a.setElem(1,2.0);
        a.setElem(2,3.0);
        a.setElem(3,4.0);
        a.setElem(4,5.0);
        a.setElem(5,6.0);
        a.setElem(6,7.0);
        a.setElem(7,8.0);
        a.setElem(8,10.0);
        //Use octave to create similar matrix
        Matrix A(3,3);
        A(0,0) = a.getElem(0);
        A(0,1) = a.getElem(1);
        A(0,2) = a.getElem(2);
        A(1,0) = a.getElem(3);
        A(1,1) = a.getElem(4);
        A(1,2) = a.getElem(5);
        A(2,0) = a.getElem(6);
        A(2,1) = a.getElem(7);
        A(2,2) = a.getElem(8);
        A = A.inverse();
        a.setInverse(a);
        int i;
        for(i=0 ; i<9 ; i++)
        {
            CHECK_CLOSE(a.getElem(i), (A((i/3),(i%3))), 0.0001);
        }
    }

    TEST(GetInverse)
    {
        jfMatrix3_x86 a,b;
        a.setElem(0,1.0);
        a.setElem(1,2.0);
        a.setElem(2,3.0);
        a.setElem(3,4.0);
        a.setElem(4,5.0);
        a.setElem(5,6.0);
        a.setElem(6,7.0);
        a.setElem(7,8.0);
        a.setElem(8,10.0);
        //Use octave to create similar matrix
        Matrix A(3,3);
        A(0,0) = a.getElem(0);
        A(0,1) = a.getElem(1);
        A(0,2) = a.getElem(2);
        A(1,0) = a.getElem(3);
        A(1,1) = a.getElem(4);
        A(1,2) = a.getElem(5);
        A(2,0) = a.getElem(6);
        A(2,1) = a.getElem(7);
        A(2,2) = a.getElem(8);
        A = A.inverse();
        a.getInverse(&b);
        int i;
        for(i=0 ; i<9 ; i++)
        {
            CHECK_CLOSE(b.getElem(i), (A((i/3),(i%3))), 0.0001);
        }
    }

    TEST(setTranspose)
    {
        jfMatrix3_x86 a;
        a.setElem(0,1.0);
        a.setElem(1,2.0);
        a.setElem(2,3.0);
        a.setElem(3,4.0);
        a.setElem(4,5.0);
        a.setElem(5,6.0);
        a.setElem(6,7.0);
        a.setElem(7,8.0);
        a.setElem(8,10.0);
        //Use octave to create similar matrix
        Matrix A(3,3);
        A(0,0) = a.getElem(0);
        A(0,1) = a.getElem(1);
        A(0,2) = a.getElem(2);
        A(1,0) = a.getElem(3);
        A(1,1) = a.getElem(4);
        A(1,2) = a.getElem(5);
        A(2,0) = a.getElem(6);
        A(2,1) = a.getElem(7);
        A(2,2) = a.getElem(8);
        A = A.transpose();
        a.setTranspose(a);
        int i;
        for(i=0 ; i<9 ; i++)
        {
            CHECK_CLOSE(a.getElem(i), (A((i/3),(i%3))), 0.0001);
        }
    }


    TEST(IdentityTest)
    {
        jfMatrix3_x86 a, aInv, I;
        a.setElem(0,1.0);
        a.setElem(1,2.0);
        a.setElem(2,2.0);
        a.setElem(3,2.0);
        a.setElem(4,1.0);
        a.setElem(5,2.0);
        a.setElem(6,2.0);
        a.setElem(7,2.0);
        a.setElem(8,2.0);
        I.setElem(0,1.0);
        I.setElem(4,1.0);
        I.setElem(8,1.0);
        a.getInverse(&aInv);
        a.multiply(aInv, &a);
        int i;
        for(i=0 ; i<9 ; i++)
        {
            CHECK_CLOSE(a.getElem(i), I.getElem(i), 0.0001);
        }
    }
}
