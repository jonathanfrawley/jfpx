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
#ifndef JFGRAVITYFORCEGENERATOR_X86_H
#define JFGRAVITYFORCEGENERATOR_X86_H

#include <jfpx/jfGravityForceGenerator.h>

#include <jfpx/x86/jfVector3_x86.h>

/*
 * =====================================================================================
 *        Class:  jfGravityForceGenerator_x86
 *  Description:
 * =====================================================================================
 */
class jfGravityForceGenerator_x86 : public jfGravityForceGenerator
{
	public:
		jfGravityForceGenerator_x86 ();
		jfGravityForceGenerator_x86 (jfVector3* gravity);
		virtual ~jfGravityForceGenerator_x86 ();

		/* Implemented methods in superclass */
		virtual void updateForce(jfRigidBody* body, jfReal duration);

	protected:
	private:
};


#endif
