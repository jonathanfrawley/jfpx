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

#include <jfpx/x86/jfForceRegistry_x86.h>
#include <jfpx/x86/jfRigidBody_x86.h>
#include <jfpx/x86/jfAeroForceGenerator_x86.h>

#include <iostream>
#include <vector>
using namespace std;

namespace
{
    TEST(CreationDeletion)
    {
        jfForceRegistry_x86* forceReg = new jfForceRegistry_x86();
        delete forceReg;
    }

    TEST(Insertion)
    {
        jfForceRegistry_x86* forceReg = new jfForceRegistry_x86();
		jfRigidBody* body = new jfRigidBody_x86();
		jfAeroForceGenerator_x86* forceGen = new jfAeroForceGenerator_x86();
		forceReg->add(body, forceGen);
		vector<jfBodyForceGen> bodyForceGens = forceReg->getForceGens();

		vector<jfBodyForceGen>::iterator it;
		int i=0;
		for (it = bodyForceGens.begin(); it != bodyForceGens.end(); it++,i++)
		{
			CHECK(i<=0);
		}
        delete forceReg;
		delete body;
		delete forceGen;
    }

    TEST(Remove)
    {
        jfForceRegistry_x86* forceReg = new jfForceRegistry_x86();
		jfRigidBody* body = new jfRigidBody_x86();
		jfAeroForceGenerator_x86* forceGen = new jfAeroForceGenerator_x86();
		forceReg->add(body, forceGen);
		forceReg->remove(body, forceGen);
		vector<jfBodyForceGen>::iterator it;
		vector<jfBodyForceGen> bodyForceGens = forceReg->getForceGens();
		int i=0;
		for (it = bodyForceGens.begin(); it != bodyForceGens.end(); it++,i++)
		{
			CHECK(i<=0);
		}
        delete forceReg;
		delete body;
		delete forceGen;
    }

    TEST(Clear)
    {
        jfForceRegistry_x86* forceReg = new jfForceRegistry_x86();
		jfRigidBody* body = new jfRigidBody_x86();
		jfAeroForceGenerator_x86* forceGen = new jfAeroForceGenerator_x86();
		forceReg->add(body, forceGen);
		forceReg->clear();
		vector<jfBodyForceGen>::iterator it;
		vector<jfBodyForceGen> bodyForceGens = forceReg->getForceGens();
		int i=0;
		for (it = bodyForceGens.begin(); it != bodyForceGens.end(); it++,i++)
		{
			CHECK(i<=0);
		}
        delete forceReg;
		delete body;
		delete forceGen;
	}

	TEST(Update)
	{
	    jfForceRegistry_x86* forceReg = new jfForceRegistry_x86();
		jfRigidBody* body = new jfRigidBody_x86();
		jfAeroForceGenerator_x86* forceGen = new jfAeroForceGenerator_x86(
                                                    jfMatrix3_x86(0,0,0, 0,0,0, 0,0,0),
                                                    jfVector3_x86(0,0,0),
                                                    new jfVector3_x86(0,0,0));
		forceReg->add(body, forceGen);
		forceReg->updateForces(0.1);
        delete forceReg;
		delete body;
		delete forceGen;
	}
}
