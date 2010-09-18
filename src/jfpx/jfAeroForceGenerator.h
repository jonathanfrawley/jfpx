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
#ifndef JFAEROFORCEGENERATOR_H
#define JFAEROFORCEGENERATOR_H

#include <jfpx/jfForceGenerator.h>
#include <jfpx/jfRigidBody.h>
#include <jfpx/jfCore.h>
#include <jfpx/jfVector3.h>
#include <jfpx/jfMatrix3.h>

class jfAeroForceGenerator : public jfForceGenerator
{
    public:
        jfAeroForceGenerator();
        jfAeroForceGenerator(jfVector3* windSpeed);
        virtual ~jfAeroForceGenerator();


		/*-----------------------------------------------------------------------------
		 *  Implemented Methods
		 *-----------------------------------------------------------------------------*/

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  updateForceFromTensor
		 *  Description:  Updates the Force acting on the rigid body using an explicit tensor.
		 * =====================================================================================
		 */
		virtual void updateForceFromTensor(jfRigidBody* body,
												jfReal timeStep,
												jfMatrix3& tensor) const = 0;
		/*-----------------------------------------------------------------------------
		 *  Interface
		 *-----------------------------------------------------------------------------*/
        virtual void updateForce(jfRigidBody* body, jfReal timeStep) const = 0;
    protected:
        jfMatrix3* m_Tensor;
        jfVector3* m_Pos;
        jfVector3* m_WindSpeed; //Not allocated by us.
    private:
};

#endif // JFAEROFORCEGENERATOR_H
