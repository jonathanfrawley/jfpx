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
#ifndef JFCONTACTRESOLVER_H
#define JFCONTACTRESOLVER_H

#include <jfpx/jfContact.h>
#include <jfpx/jfCore.h>

#include <vector>
using namespace std;

/*
 * =====================================================================================
 *        Class: jfContactResolver
 *  Description:
 * =====================================================================================
 */
class jfContactResolver
{
	public:
		jfContactResolver ();

		jfContactResolver(unsigned iterations
                            , jfReal velocityEpsilion=(jfReal)0.01
                            , jfReal positionEpsilon=(jfReal)0.01);

		jfContactResolver(unsigned velocityIterations
                            , unsigned positionIterations
                            , jfReal velocityEpsilion=(jfReal)0.01
                            , jfReal positionEpsilon=(jfReal)0.01);

		virtual ~jfContactResolver ();

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  isValid
		 *  Description:  Returns whether the resolver has valid settings or not.
		 * =====================================================================================
		 */
		virtual bool isValid() const
		{
			return ( (m_MaxVelocityIterations > 0)
					&& (m_MaxPositionIterations > 0)
					&& (m_VelocityEpsilon >= 0.0f)
					&& (m_PositionEpsilon >= 0.0f)
					);
		}

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  resolveContacts
		 *  Description:  Resolves a set of contacts for both penetration and velocity.
		 * =====================================================================================
		 */
		virtual void resolveContacts(vector<jfContact*>& contacts,
										jfReal timeStep) = 0;


		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  prepareContacts
		 *  Description:  Sets up contacts for processing.
		 * =====================================================================================
		 */
		virtual void prepareContacts(vector<jfContact*>& contacts,
										jfReal timeStep) const = 0;


		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  adjustVelocities
		 *  Description:  Resolves the velocity issues for the given contacts
		 * =====================================================================================
		 */
		virtual void adjustVelocities(vector<jfContact*>& contacts,
										jfReal timeStep) = 0;


		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  adjustPositions
		 *  Description:  Resolves the positional issues for the given contacts.
		 * =====================================================================================
		 */
		virtual void adjustPositions(vector<jfContact*>& contacts,
										jfReal timeStep) = 0;

		/*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
		void setVelocityIterations(unsigned val) { m_VelocityIterationsUsed = val; }

		void setPositionIterations(unsigned val) { m_PositionIterationsUsed = val; }

		void setIterations(unsigned iterations)
		{
			m_VelocityIterationsUsed = iterations;
			m_PositionIterationsUsed = iterations;
		}

		void setEpsilons(jfReal velocityEpsilon,
							jfReal positionEpsilon)
		{
			m_VelocityEpsilon = velocityEpsilon;
			m_PositionEpsilon = positionEpsilon;
		}

	protected:
		/* Max number of iterations when resolving velocity */
		unsigned m_MaxVelocityIterations;

		/* Max number of iterations when resolving position */
		unsigned m_MaxPositionIterations;

		/* Velocities smaller than this are considered to be zero for stability purposes */
		jfReal m_VelocityEpsilon;

		/* Penetrations smaller than this are considered to be not penetrating for stability purposes */
		jfReal m_PositionEpsilon;

		/* Number of velocity iterations used in last call to resolve contacts */
		unsigned m_VelocityIterationsUsed;

		/* Number of position iterations used in last call to resolve contacts */
		unsigned m_PositionIterationsUsed;

        /* Keeps track of whether the internal settings are valid */
		bool m_ValidSettings;

	private:

}; /* -----  end of class jfContactResolver  ----- */

#endif //JFCONTACTRESOLVER_H
