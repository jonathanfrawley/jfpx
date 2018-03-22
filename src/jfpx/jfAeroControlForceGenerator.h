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
#ifndef JFAEROCONTROLFORCEGENERATOR_H
#define JFAEROCONTROLFORCEGENERATOR_H

#include <jfpx/jfAeroForceGenerator.h>

/*
 * =====================================================================================
 *        Class:  jfAeroControlForceGenerator
 *  Description:  Used to control an object using aero forces.
 * =====================================================================================
 */
class jfAeroControlForceGenerator : public jfAeroForceGenerator {
public:
    jfAeroControlForceGenerator();
    jfAeroControlForceGenerator(jfVector3* windSpeed);
    virtual ~jfAeroControlForceGenerator();

    /*-----------------------------------------------------------------------------
		 *  Interface
		 *-----------------------------------------------------------------------------*/
    /*-----------------------------------------------------------------------------
		 *  Inherited methods
		 *-----------------------------------------------------------------------------*/
    virtual void updateForce(jfRigidBody* body, jfReal timeStep) const = 0;
    virtual void updateForceFromTensor(jfRigidBody* body,
        jfReal timeStep,
        jfMatrix3& tensor) const = 0;

    /*-----------------------------------------------------------------------------
		 *  Own Functions
		 *-----------------------------------------------------------------------------*/
    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getTensor
		 *  Description:  Decides on which tensor value to use and if none appropriate, it uses the
		 *  two most suitable values available.
		 * =====================================================================================
		 */
    virtual void getTensor(jfMatrix3* result) const = 0;

    /*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
    virtual void setControl(jfReal val)
    {
        m_ControlSetting = val;
    }

protected:
    jfMatrix3* m_MaxTensor;
    jfMatrix3* m_MinTensor;
    jfReal m_ControlSetting; //Goes from -1 to 0 to 1 and chooses appropriate tensor to use (Millington p.219)
private:
};

#endif // JFAEROCONTROLFORCEGENERATOR_H
