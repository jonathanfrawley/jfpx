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
#ifndef JFAEROFORCEGENERATOR_X86_H
#define JFAEROFORCEGENERATOR_X86_H

#include <jfpx/jfAeroForceGenerator.h>
#include <jfpx/x86/jfVector3_x86.h>
#include <jfpx/x86/jfMatrix3_x86.h>
#include <jfpx/x86/jfMatrix4_x86.h>

class jfAeroForceGenerator_x86 : public jfAeroForceGenerator
{
    public:
        jfAeroForceGenerator_x86();

        jfAeroForceGenerator_x86(const jfMatrix3& tensor,
                                    const jfVector3& pos,
                                    jfVector3* windSpeed);

        virtual ~jfAeroForceGenerator_x86();

		/*-----------------------------------------------------------------------------
		 *  Inherited methods
		 *-----------------------------------------------------------------------------*/
        virtual void updateForce(jfRigidBody* body, jfReal timeStep) const;

        virtual void updateForceFromTensor(jfRigidBody* body,
                                            jfReal timeStep,
                                            jfMatrix3& tensor) const;
    protected:
    private:
};

#endif // JFAEROFORCEGENERATOR_X86_H
