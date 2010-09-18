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
#include "jfContactResolver_x86.h"

jfContactResolver_x86::jfContactResolver_x86()
    :
        jfContactResolver()
{
}

jfContactResolver_x86::jfContactResolver_x86(
						unsigned iterations
						, jfReal velocityEpsilion
						, jfReal positionEpsilon
						)
    :
		jfContactResolver(iterations
						, velocityEpsilion
						, positionEpsilon)
{
}

jfContactResolver_x86::jfContactResolver_x86(
						unsigned velocityIterations
						, unsigned positionIterations
						, jfReal velocityEpsilion
						, jfReal positionEpsilon
						)
		:
		jfContactResolver(velocityIterations
						, positionIterations
						, velocityEpsilion
						, positionEpsilon)
{
}

jfContactResolver_x86::~jfContactResolver_x86()
{
}

void jfContactResolver_x86::resolveContacts(vector<jfContact*>& contacts,
                                            jfReal timeStep)
{

	if (!isValid())
	{
		return;
	}

    // Prepare the contacts for processing
    prepareContacts(contacts, timeStep);

    // Resolve the interpenetration problems with the contacts.
    adjustPositions(contacts, timeStep);

    // Resolve the velocity problems with the contacts.
    adjustVelocities(contacts, timeStep);
}

void jfContactResolver_x86::prepareContacts(vector<jfContact*>& contacts,
                                            jfReal timeStep) const
{
    // Generate contact velocity and axis information.
    vector<jfContact*>::iterator contact;
    for(contact = contacts.begin(); contact != contacts.end(); contact++)
    {
        // Calculate the internal contact data (inertia, basis, etc).
        (*contact)->calculateInternals(timeStep);
    }
}

void jfContactResolver_x86::adjustVelocities(vector<jfContact*>& contacts,
                                                jfReal timeStep)
{
    jfVector3_x86 velocityChange[2];
	jfVector3_x86 rotationChange[2];
    jfVector3_x86 deltaVel;

    // iteratively handle impacts in order of severity.
    m_VelocityIterationsUsed = 0;
    while (m_VelocityIterationsUsed < m_MaxVelocityIterations)
    {
        // Find contact with maximum magnitude of probable velocity change.
        jfReal max = m_VelocityEpsilon;
        jfContact* maxContact = NULL;
        vector<jfContact*>::iterator it;

        for (it = contacts.begin(); it != contacts.end() ; it++)
        {
            if ((*it)->getDesiredDeltaVelocity() > max)
            {
                max = (*it)->getDesiredDeltaVelocity();
                maxContact = (*it);
            }
        }
        if (maxContact == NULL)
		{
			//Finished processing contacts
			break;
		}

        // Match the awake state at the contact
        maxContact->matchAwakeState();

        // Do the resolution on the contact that came out top.
        maxContact->applyVelocityChange(velocityChange, rotationChange);

        // With the change in velocity of the two bodies, the update of
        // contact velocities means that some of the relative closing
        // velocities need recomputing.
        for (unsigned i = 0; i < contacts.size(); i++)
        {
			jfContact* currentContact = contacts[i];
            // Check each body in the contact
            for (unsigned b = 0; b < 2; b++)
			{
				if (maxContact->getBody(b))
				{
					// Check for a match with each body in the newly
					// resolved contact
					for (unsigned d = 0; d < 2; d++)
					{
						if (currentContact->getBody(b) == maxContact->getBody(d))
						{
							jfVector3_x86 crossProduct;
							jfVector3_x86 relativeContactPosition;

							currentContact->getRelativeContactPosition(b, &relativeContactPosition);
							rotationChange[d].crossProduct(relativeContactPosition, &crossProduct);
							velocityChange[d].add(crossProduct, &deltaVel);

							// The sign of the change is negative if we're dealing
							// with the second body in a contact.
							int sign=1;
							if(b==1)
							{
								sign = -1;
							}
							jfVector3_x86 transformedDeltaVel;
                            jfVector3_x86 transformedDeltaVelSign;
                            jfVector3_x86 contactVelocity;
							jfMatrix3_x86 contactToWorld;

							currentContact->getContactToWorld(&contactToWorld);
							contactToWorld.transformTranspose(deltaVel, &transformedDeltaVel);
							transformedDeltaVel.multiply(sign, &transformedDeltaVelSign);
							currentContact->getContactVelocity(&contactVelocity);
							contactVelocity += transformedDeltaVelSign;
							currentContact->setContactVelocity(contactVelocity);
							currentContact->calculateDesiredDeltaVelocity(timeStep);
						}
					}
				}
			}
        }
        m_VelocityIterationsUsed++;
    }
}

void jfContactResolver_x86::adjustPositions(vector<jfContact*>& contacts,
                                            jfReal timeStep)
{
    unsigned i;
    jfVector3_x86 linearChange[2], angularChange[2];
    jfVector3_x86 deltaPosition;

    // iteratively resolve interpenetrations in order of severity.
    m_PositionIterationsUsed = 0;
    while (m_PositionIterationsUsed < m_MaxPositionIterations)
    {
        // Find contact with maximum magnitude of probable velocity change.
        jfReal max = m_PositionEpsilon;
        jfContact* maxContact = NULL;
        vector<jfContact*>::iterator it;
        for (it = contacts.begin(); it != contacts.end() ; it++)
        {
            if ((*it)->getPenetration() > max)
            {
                (*it)->setPenetration(max);
                maxContact = (*it);
            }
        }

        if (maxContact == NULL)
		{
			//Finished processing contacts
			break;
		}
        // Match the awake state at the contact
        maxContact->matchAwakeState();

        // Resolve the penetration.
        maxContact->applyPositionChange(linearChange,
                                                angularChange,
                                                max);

        // Again this action may have changed the penetration of other
        // bodies, so we update any affected contacts.
        for (i = 0; i < contacts.size(); i++)
        {
			jfContact* currentContact = contacts[i];
            // Check each body in the contact
            for (unsigned b = 0; b < 2; b++)
			{
				if (maxContact->getBody(b))
				{
					// Check for a match with each body in the newly
					// resolved contact
					for (unsigned d = 0; d < 2; d++)
					{
						if (currentContact->getBody(b) == maxContact->getBody(d))
						{
							jfVector3_x86 crossProduct;
                            jfVector3_x86 relativeContactPosition;
							currentContact->getRelativeContactPosition(b, &relativeContactPosition);
							angularChange[d].crossProduct(relativeContactPosition, &crossProduct);
							linearChange[d].add(crossProduct, &deltaPosition);

							int sign=1;
							if(b==1)
							{
								sign = -1;
							}
							jfVector3_x86 contactNormal;
							currentContact->getContactNormal(&contactNormal);
							currentContact->setPenetration(currentContact->getPenetration() +
															(deltaPosition.dotProduct(contactNormal) * sign));
						}
					}
				}
			}
        }
        m_PositionIterationsUsed++;
    }
}

