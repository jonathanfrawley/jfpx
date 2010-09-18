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
#ifndef JFAEROCONTROLFORCEGENERATOR_X86_H
#define JFAEROCONTROLFORCEGENERATOR_X86_H

#include <jfpx/jfAeroControlForceGenerator.h>
#include <jfpx/x86/jfMatrix3_x86.h>
#include <jfpx/x86/jfMatrix4_x86.h>
#include <jfpx/x86/jfVector3_x86.h>
#include <jfpx/x86/jfAeroForceGenerator_x86.h>


class jfAeroControlForceGenerator_x86 :  public jfAeroControlForceGenerator
{
    public:
        jfAeroControlForceGenerator_x86();
        jfAeroControlForceGenerator_x86(const jfMatrix3& baseTensor,
                                        const jfMatrix3& minTensor,
                                        const jfMatrix3& maxTensor,
                                        const jfVector3& pos,
                                        jfVector3* windSpeed);
        virtual ~jfAeroControlForceGenerator_x86();

		/*-----------------------------------------------------------------------------
		 *  Inherited methods
		 *-----------------------------------------------------------------------------*/
        virtual void updateForce(jfRigidBody* body, jfReal timeStep) const;
        virtual void getTensor(jfMatrix3* result) const;
        virtual void updateForceFromTensor(jfRigidBody* body,
												jfReal timeStep,
												jfMatrix3& tensor) const;
    protected:
    private:
};

#endif // JFAEROCONTROLFORCEGENERATOR_X86_H
