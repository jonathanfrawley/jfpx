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

#include <jfpx/x86/jfMatrix4_x86.h>

namespace
{

    TEST(Multiply)
    {
        jfMatrix4_x86 a,b;
        a.setElem(0,1.0);
        a.setElem(1,2.0);
        a.setElem(2,3.0);
        a.setElem(3,4.0);
        a.setElem(4,5.0);
        a.setElem(5,6.0);
        a.setElem(6,7.0);
        a.setElem(7,8.0);
        a.setElem(8,9.0);
        a.setElem(9,10.0);
        a.setElem(10,11.0);
        a.setElem(11,12.0);
        a.setElem(12,0.0);
        a.setElem(13,0.0);
        a.setElem(14,0.0);
        a.setElem(15,0.0);
        b.setElem(0,1.0);
        b.setElem(1,2.0);
        b.setElem(2,3.0);
        b.setElem(3,4.0);
        b.setElem(4,5.0);
        b.setElem(5,6.0);
        b.setElem(6,7.0);
        b.setElem(7,8.0);
        b.setElem(8,9.0);
        b.setElem(9,10.0);
        b.setElem(10,11.0);
        b.setElem(11,12.0);
        b.setElem(12,0.0);
        b.setElem(13,0.0);
        b.setElem(14,0.0);
        b.setElem(15,0.0);
		//copy matrices to octave matrices
        Matrix A(4,4);
		Matrix B(4,4);
		int i;
		for(i=0; i<16 ;i++)
		{
			A(i/4,i%4) = a.getElem(i);
			B(i/4,i%4) = b.getElem(i);
		}
        jfMatrix4_x86 c;
        a.multiply(b,&c);
		Matrix C(4,4);
	    C = (A * B);
		for(i=0; i<16 ;i++)
		{
			CHECK(C(i/4,i%4) == c.getElem(i));
		}
    }

	TEST(Determinant)
	{
        jfMatrix4_x86 a;
        a.setElem(0,10.0);
        a.setElem(1,20.0);
        a.setElem(2,30.0);
        a.setElem(3,40.0);
        a.setElem(4,50.0);
        a.setElem(5,60.0);
        a.setElem(6,70.0);
        a.setElem(7,80.0);
        a.setElem(8,90.0);
        a.setElem(9,100.0);
        a.setElem(10,110.0);
        a.setElem(11,120.0);
        a.setElem(12,0.0);
        a.setElem(13,0.0);
        a.setElem(14,0.0);
        a.setElem(15,1.0);
        //Use octave to create similar matrix
        Matrix A(4,4);
		int i;
		for(i=0; i<16 ;i++)
		{
			A(i/4,i%4) = a.getElem(i);
		}
        DET D = A.determinant();
        jfReal d = a.getDeterminant();
		CHECK_CLOSE(d, D, 0.0001);
	}

    TEST(SetInverse)
    {
        jfMatrix4_x86 a;
        a.setElem(0,1.0);
        a.setElem(1,2.0);
        a.setElem(2,3.0);
        a.setElem(3,4.0);
        a.setElem(4,5.0);
        a.setElem(5,6.0);
        a.setElem(6,7.0);
        a.setElem(7,8.0);
        a.setElem(8,9.0);
        a.setElem(9,10.0);
        a.setElem(10,11.0);
        a.setElem(11,12.0);
        a.setElem(12,0.0);
        a.setElem(13,0.0);
        a.setElem(14,0.0);
        a.setElem(15,0.0);
        //Use octave to create similar matrix
        Matrix A(4,4);
		int i;
		for(i=0; i<16 ;i++)
		{
			A(i/4,i%4) = a.getElem(i);
		}
        A = A.inverse();
        a.setInverse(a);
        for(i=0 ; i<16 ; i++)
        {
            CHECK_CLOSE(a.getElem(i), (A((i/4),(i%4))), 0.0001);
        }
    }

    TEST(GetInverse)
    {
        jfMatrix4_x86 a,b;
        a.setElem(0,1.0);
        a.setElem(1,20.0);
        a.setElem(2,30.0);
        a.setElem(3,40.0);
        a.setElem(4,50.0);
        a.setElem(5,60.0);
        a.setElem(6,70.0);
        a.setElem(7,80.0);
        a.setElem(8,90.0);
        a.setElem(9,100.0);
        a.setElem(10,110.0);
        a.setElem(11,120.0);
        a.setElem(12,0.0);
        a.setElem(13,0.0);
        a.setElem(14,0.0);
        a.setElem(15,1.0);
        //Use octave to create similar matrix
        Matrix A(4,4);
		int i;
		for(i=0; i<16 ;i++)
		{
			A(i/4,i%4) = a.getElem(i);
		}
        A = A.inverse();
        a.getInverse(&b);
        for(i=0 ; i<16 ; i++)
        {
            CHECK_CLOSE(b.getElem(i), (A((i/4),(i%4))), 0.0001);
        }
    }

    TEST(IdentityTest)
    {
        jfMatrix4_x86 a, aInv, I;
        a.setElem(0,1.0);
        a.setElem(1,20.0);
        a.setElem(2,30.0);
        a.setElem(3,40.0);
        a.setElem(4,50.0);
        a.setElem(5,60.0);
        a.setElem(6,70.0);
        a.setElem(7,80.0);
        a.setElem(8,90.0);
        a.setElem(9,100.0);
        a.setElem(10,110.0);
        a.setElem(11,120.0);
        a.setElem(12,0.0);
        a.setElem(13,0.0);
        a.setElem(14,0.0);
        a.setElem(15,1.0);
        I.setElem(0,1.0);
        I.setElem(5,1.0);
        I.setElem(10,1.0);
        I.setElem(15,1.0);
        a.getInverse(&aInv);
        a.multiply(aInv, &a);
        int i;
        for(i=0 ; i<16 ; i++)
        {
            CHECK_CLOSE(a.getElem(i), I.getElem(i), 0.0001);
        }
    }
}
