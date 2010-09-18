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

#ifndef  JFCOLLISIONDATA_H
#define  JFCOLLISIONDATA_H

#include <jfpx/jfContact.h>

#include <vector>
using namespace std;


/*
 * =====================================================================================
 *        Class: jfCollisionData
 *  Description:
 * =====================================================================================
 */
class jfCollisionData
{
	public:
		jfCollisionData();

		virtual ~jfCollisionData();

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  reset
		 *  Description:  Resets the data so that it has no used contacts recorded.
		 * =====================================================================================
		 */
        virtual void reset()
        {
            m_Contacts.clear();
        }


		virtual void addContact(const jfContact& newContact)
		{
            m_Contacts.push_back(newContact.clone());
		}

		/*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
        /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getContacts
		 *  Description:  Fills the passed in vector with the contacts in the current array.
		 * =====================================================================================
		 */
		virtual void getContacts(vector<jfContact*>* result)
		{
            vector<jfContact*>::iterator it;
            for(it=m_Contacts.begin(); it != m_Contacts.end(); it++)
            {
                result->push_back(*it);
            }
		}

		virtual jfReal getFriction() const { return m_Friction; }
		virtual void setFriction(jfReal val) { m_Friction = val; }

		virtual jfReal getRestitution() const { return m_Restitution; }
        virtual void setRestitution(jfReal val) { m_Restitution = val; }

        virtual unsigned getContactCount() { return m_Contacts.size(); }

        virtual jfReal getTolerance() { return m_Tolerance; }
        virtual void setTolerance(jfReal val) { m_Tolerance = val; }

	protected:
		/*-----------------------------------------------------------------------------
		 * Holds the base of the collision data: the first contact
		 * in the array. This is used so that the contact pointer (below)
		 * can be incremented each time a contact is detected, while
		 * this pointer points to the first contact found.
		 *-----------------------------------------------------------------------------*/
		vector<jfContact*> m_Contacts;

        /** Holds the friction value to write into any collisions. */
        jfReal m_Friction;

        /** Holds the restitution value to write into any collisions. */
        jfReal m_Restitution;

        /**
         * Holds the collision tolerance, even uncolliding objects this
         * close should have collisions generated.
         */
        jfReal m_Tolerance;

	private:
};

#endif   // JFCOLLISIONDATA_H
