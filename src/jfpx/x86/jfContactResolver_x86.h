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
#ifndef  JFCONTACTRESOLVER_X86_H
#define  JFCONTACTRESOLVER_X86_H

#include <jfpx/jfContactResolver.h>
#include <jfpx/x86/jfVector3_x86.h>
#include <jfpx/x86/jfMatrix3_x86.h>
#include <jfpx/jfContact.h>

#include <vector>
using namespace std;

/*
 * =====================================================================================
 *        Class: jfContactResolver_x86
 *  Description:
 * =====================================================================================
 */
class jfContactResolver_x86 : public jfContactResolver
{
	public:
		jfContactResolver_x86();

		jfContactResolver_x86(unsigned iterations
								, jfReal velocityEpsilion=(jfReal)0.01
								, jfReal positionEpsilon=(jfReal)0.01
								);

		jfContactResolver_x86(unsigned velocityIterations
								, unsigned positionIterations
								, jfReal velocityEpsilion=(jfReal)0.01
								, jfReal positionEpsilon=(jfReal)0.01
								);

		virtual ~jfContactResolver_x86();

		/*-----------------------------------------------------------------------------
		 *  Inherited Methods
		 *-----------------------------------------------------------------------------*/
        virtual void resolveContacts(vector<jfContact*>& contacts,
										jfReal timeStep);


		virtual void prepareContacts(vector<jfContact*>& contacts,
										jfReal timeStep) const;

		virtual void adjustVelocities(vector<jfContact*>& contacts,
										jfReal timeStep);

		virtual void adjustPositions(vector<jfContact*>& contacts,
										jfReal timeStep);

	protected:
	private:
};

#endif   // JFCONTACTRESOLVER_X86_H
