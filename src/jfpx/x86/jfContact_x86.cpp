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
#include "jfContact_x86.h"


jfContact_x86::jfContact_x86()
	:
        jfContact()
{
	m_ContactPoint = new jfVector3_x86();
	m_ContactNormal = new jfVector3_x86();
	m_ContactToWorld = new jfMatrix3_x86();
	m_ContactVelocity = new jfVector3_x86();
	m_RelativeContactPosition = new jfVector3_x86[2];
}

jfContact_x86::jfContact_x86(const jfContact_x86& other)
    :
        jfContact(other)
{
	m_ContactPoint = new jfVector3_x86();
	other.getContactPoint(m_ContactPoint);
	m_ContactNormal = new jfVector3_x86();
    other.getContactNormal(m_ContactNormal);
	m_ContactToWorld = new jfMatrix3_x86();
	other.getContactToWorld(m_ContactToWorld);
	m_ContactVelocity = new jfVector3_x86();
	other.getContactVelocity(m_ContactVelocity);
	m_RelativeContactPosition = new jfVector3_x86[2];
	other.getRelativeContactPosition(0, &m_RelativeContactPosition[0]);
    other.getRelativeContactPosition(1, &m_RelativeContactPosition[1]);
}

jfContact_x86::~jfContact_x86()
{
    delete m_ContactPoint;
	delete m_ContactNormal;
	delete m_ContactToWorld;
	delete m_ContactVelocity;
	delete [] m_RelativeContactPosition;
}

void jfContact_x86::calculateInternals(jfReal timeStep)
{
    jfVector3_x86 bodyPos;
	//@ref: Millington code "contacts.cpp"
	// Check if the first object is NULL, and swap if it is.
    if (!m_BodyZero)
	{
		swapBodies();
	}
	assert(m_BodyZero);

    // Calculate a set of axes at the contact point.
    calculateContactBasis();

    // Store the relative position of the contact relative to each body
    m_BodyZero->getPos(&bodyPos);
    m_ContactPoint->subtract(bodyPos, &m_RelativeContactPosition[0]);
    if (m_BodyZero)
    {
        m_BodyZero->getPos(&bodyPos);
        m_ContactPoint->subtract(bodyPos, &m_RelativeContactPosition[1]);
    }

    // Find the relative velocity of the bodies at the contact point.
    calculateLocalVelocity(0, timeStep, m_ContactVelocity);
    if (m_BodyOne)
    {
		jfVector3_x86 secondVelocity;
		calculateLocalVelocity(1, timeStep, &secondVelocity);
        (*m_ContactVelocity) -= secondVelocity;
    }

    // Calculate the desired change in velocity for resolution
    calculateDesiredDeltaVelocity(timeStep);
}

void jfContact_x86::swapBodies()
{
    //@ref: Millington code 'contacts.cpp'
    (*m_ContactNormal) *= -1;

    jfRigidBody* temp = m_BodyZero;
    m_BodyZero = m_BodyOne;
    m_BodyOne = temp;
}

void jfContact_x86::calculateDesiredDeltaVelocity(jfReal timeStep)
{
	//@ref: Millington code "contacts.cpp"
    const static jfReal velocityLimit = (jfReal)0.25f;
    jfVector3_x86 lastFrameAccel;
    jfVector3_x86 lastFrameAccelAdjusted;

    // Calculate the acceleration induced velocity accumulated this frame
    jfReal velocityFromAccel = (jfReal)0.0;

    if (m_BodyZero->isAwake())
    {
		m_BodyZero->getLastFrameAccel(&lastFrameAccel);
		lastFrameAccel.multiply(timeStep, &lastFrameAccelAdjusted);
        velocityFromAccel += lastFrameAccelAdjusted.dotProduct(*m_ContactNormal);
    }

    if (m_BodyOne && m_BodyOne->isAwake())
    {
		m_BodyOne->getLastFrameAccel(&lastFrameAccel);
		lastFrameAccel.multiply(timeStep, &lastFrameAccelAdjusted);
		velocityFromAccel -= lastFrameAccelAdjusted.dotProduct(*m_ContactNormal);
    }

    // If the velocity is very slow, limit the restitution
    jfReal thisRestitution = m_Restitution;
    if (jfRealAbs(m_ContactVelocity->getX()) < velocityLimit)
    {
        thisRestitution = (jfReal)0.0f;
    }

    // Combine the bounce velocity with the removed
    // acceleration velocity.
    m_DesiredDeltaVelocity = (- m_ContactVelocity->getX() -
                                (thisRestitution *
                                 (m_ContactVelocity->getX() -
                                  velocityFromAccel
                                  )
                                 ));
}

void jfContact_x86::calculateContactBasis()
{
	/**
	 * Generates an orthonormal group of axes and a
	 * corresponding matrix with which we can move from
	 * contact to world coordinates.
	 */
	jfVector3_x86 contactTangent[2];

    // Check whether the Z-axis is nearer to the X or Y axis
    if (jfRealAbs(m_ContactNormal->getX()) > jfRealAbs(m_ContactNormal->getY()))
    {
        // Scaling factor to ensure the results are normalised
        const jfReal scalingFactor = (jfReal)1.0f/jfRealSqrt((m_ContactNormal->getZ()*m_ContactNormal->getZ()) +
                                        (m_ContactNormal->getX()*m_ContactNormal->getX()));

        // The new X-axis is at right angles to the world Y-axis
        contactTangent[0].setX(m_ContactNormal->getZ()*scalingFactor);
        contactTangent[0].setY(0);
        contactTangent[0].setZ(- (m_ContactNormal->getX()*scalingFactor) );

        // The new Y-axis is at right angles to the new X- and Z- axes
        contactTangent[1].setX(m_ContactNormal->getY()*contactTangent[0].getX());
        contactTangent[1].setY(m_ContactNormal->getZ()*contactTangent[0].getX() -
								m_ContactNormal->getX()*contactTangent[0].getZ());
        contactTangent[1].setZ(-m_ContactNormal->getY()*contactTangent[0].getX());
    }
    else
    {
        // Scaling factor to ensure the results are normalised
        const jfReal scalingFactor = (jfReal)1.0/jfRealSqrt(m_ContactNormal->getZ()*m_ContactNormal->getZ() +
                                                            m_ContactNormal->getY()*m_ContactNormal->getY());

        // The new X-axis is at right angles to the world X-axis
        contactTangent[0].setX(0);
        contactTangent[0].setY(- (m_ContactNormal->getZ()*scalingFactor));
        contactTangent[0].setZ(m_ContactNormal->getY()*scalingFactor);

        // The new Y-axis is at right angles to the new X- and Z- axes
        contactTangent[1].setX(m_ContactNormal->getY()*contactTangent[0].getZ() -
                                m_ContactNormal->getZ()*contactTangent[0].getY());
        contactTangent[1].setY(-m_ContactNormal->getX()*contactTangent[0].getZ());
        contactTangent[1].setZ(m_ContactNormal->getX()*contactTangent[0].getY());
    }

    // Make a matrix from the three vectors.
    m_ContactToWorld->setComponents((*m_ContactNormal),
                                    contactTangent[0],
                                    contactTangent[1]);
}


void jfContact_x86::calculateLocalVelocity(unsigned bodyIndex,
													jfReal timeStep,
													jfVector3* result)
{
	jfVector3_x86 velocity;
	jfVector3_x86 thisBodyVelocity;
	jfVector3_x86 rotation;
	jfVector3_x86 lastFrameAccel;
	jfVector3_x86 accVelocity;
	jfRigidBody* thisBody = getBody(bodyIndex);

	// Work out velocity at the contact point.
	thisBody->getRotation(&rotation);
	rotation.crossProduct(m_RelativeContactPosition[bodyIndex], &velocity);
	thisBody->getVelocity(&thisBodyVelocity);
    velocity += thisBodyVelocity;

    // Convert velocity to contact-coordinates.
    m_ContactToWorld->transformTranspose(velocity, result);

 	//Calculate the amount of velocity that is due to forces without
 	//reactions.
	thisBody->getLastFrameAccel(&lastFrameAccel);
	lastFrameAccel.multiply(timeStep, &accVelocity);

 	//Calculate the velocity in contact-coordinates.
    m_ContactToWorld->transformTranspose(accVelocity, &accVelocity);

	//We ignore any component of acceleration in the contact normal
	//direction, we are only interested in planar acceleration
    accVelocity.setX(0);

    (*result) += accVelocity;
}


void jfContact_x86::applyVelocityChange(jfVector3* velocityChange,
										jfVector3* rotationChange)
{
    jfMatrix3_x86 inverseInertiaTensor[2];
    jfVector3_x86 impulseContact;
	jfVector3_x86 impulse;
	jfVector3_x86 impulsiveTorque;

    m_BodyZero->getInverseInertiaTensorWorld(&inverseInertiaTensor[0]);
    if (m_BodyOne)
	{
		m_BodyOne->getInverseInertiaTensorWorld(&inverseInertiaTensor[1]);
	}

    if (m_Friction == (jfReal)0.0)
    {
		calculateFrictionlessImpulse(inverseInertiaTensor, &impulseContact);
    }
    else
    {
        calculateFrictionImpulse(inverseInertiaTensor, &impulseContact);
    }

    // Convert impulse to world coordinates
    m_ContactToWorld->transform(impulseContact, &impulse);

    // Split the impulse into linear and angular components
	m_RelativeContactPosition[1].crossProduct(impulse, &impulsiveTorque);
    inverseInertiaTensor[0].transform(impulsiveTorque, &rotationChange[0]);

    // Apply the changes to both bodies
    velocityChange[0].clear();
    velocityChange[0].addScaledVector(impulse, m_BodyZero->getInverseMass());
    m_BodyZero->addVelocity(velocityChange[0]);
    m_BodyZero->addRotation(rotationChange[0]);

    if (m_BodyOne)
    {
        impulse.crossProduct(m_RelativeContactPosition[1], &impulsiveTorque);
		inverseInertiaTensor[1].transform(impulsiveTorque, &rotationChange[1]);
        velocityChange[1].clear();
        velocityChange[1].addScaledVector(impulse, - m_BodyOne->getInverseMass());
		m_BodyOne->addVelocity(velocityChange[1]);
		m_BodyOne->addRotation(rotationChange[1]);
    }
}

void jfContact_x86::applyPositionChange(jfVector3* linearChange,
											jfVector3* angularChange,
											jfReal m_Penetration)
{
	jfVector3_x86 pos;
    jfRigidBody* body;
    const jfReal angularLimit = (jfReal)0.2f;
    jfReal angularMove[2];
    jfReal linearMove[2];

    jfReal totalInertia = 0;
    jfReal linearInertia[2];
    jfReal angularInertia[2];

    /**
	 * Work out the inertia of each object in the direction
     * of the contact normal, due to angular inertia only.
	 */
    for (unsigned i = 0; i < 2; i++)
	{
	    body = getBody(i);
		if (body)
		{
			jfMatrix3_x86 inverseInertiaTensor;
			jfVector3_x86 angularInertiaWorld;

			body->getInverseInertiaTensorWorld(&inverseInertiaTensor);
			/** 
			 * Use the same procedure as for calculating frictionless
			 * velocity change to work out the angular inertia.
			 */
			m_RelativeContactPosition[i].crossProduct((*m_ContactNormal), &angularInertiaWorld);
			inverseInertiaTensor.transform(angularInertiaWorld, &angularInertiaWorld);
			angularInertiaWorld.crossProduct(m_RelativeContactPosition[i], &angularInertiaWorld);
			angularInertia[i] = angularInertiaWorld.dotProduct(*m_ContactNormal);

			/*
			 * The linear component is simply the inverse mass
			 */
			linearInertia[i] = body->getInverseMass();

			/*
			 *  Keep track of the total inertia from all components
			 */
			totalInertia += linearInertia[i] + angularInertia[i];
		}
	}

    /* Will cause zero division later on otherwise.
       totalInertia of 0 is usually caused by 0 mass objects which
       aren't allowed
	   */
    if(totalInertia>0)
    {
        return;
    }

	// Loop through again calculating and applying the changes
	for (unsigned i = 0; i < 2; i++)
	{
        body = getBody(i);
		if (body)
		{
			jfReal sign = 1;
		   	if(i == 1)
			{
				sign = -1;
			}
			angularMove[i] = (sign * m_Penetration) * (angularInertia[i] / totalInertia);
			linearMove[i] =	(sign * m_Penetration) * (linearInertia[i] / totalInertia);

			/* Limit angular move in certain situations */
			jfVector3_x86 projection = m_RelativeContactPosition[i];
			projection.addScaledVector(
				(*m_ContactNormal),
				-m_RelativeContactPosition[i].dotProduct(*m_ContactNormal)
				);

			jfReal maxMagnitude = angularLimit * projection.magnitude();

			jfReal totalMove = angularMove[i] + linearMove[i];
			if (angularMove[i] < -maxMagnitude)
			{
				angularMove[i] = -maxMagnitude;
			}
			else if (angularMove[i] > maxMagnitude)
			{
				angularMove[i] = maxMagnitude;
			}
			linearMove[i] = totalMove - angularMove[i];

			// We have the linear amount of movement required by turning
			// the rigid body (in angularMove[i]). We now need to
			// calculate the desired rotation to achieve that.
			if (angularMove[i] == 0)
			{
				// Easy case - no angular movement means no rotation.
				angularChange[i].clear();
			}
			else
			{
				jfMatrix3_x86 inverseInertiaTensor;
				jfVector3_x86 targetAngularDirection;
				jfVector3_x86 transformedTargetAngularDirection;

				// Work out the direction we'd like to rotate in.
				m_RelativeContactPosition[i].crossProduct(*m_ContactNormal, &targetAngularDirection);
				body->getInverseInertiaTensorWorld(&inverseInertiaTensor);
				// Work out the direction we'd need to rotate to achieve that
				inverseInertiaTensor.transform(targetAngularDirection, &transformedTargetAngularDirection);
                transformedTargetAngularDirection.multiply((angularMove[i] / angularInertia[i]), &angularChange[i]);
			}

			// Velocity change is linear movement in the direction of the contact normal.
			m_ContactNormal->multiply(linearMove[i], &linearChange[i]);

			// Apply the linear movement
			body->getPos(&pos);
			pos.addScaledVector(*m_ContactNormal, linearMove[i]);
			body->setPos(pos);

			// Apply Angular movement
			jfQuaternion_x86 q;
			body->getOrientation(&q);
			q.addScaledVector(angularChange[i], ((jfReal)1.0));
			body->setOrientation(q);

			/**
			 * Calculate derived data for sleeping objects
			 **/
			if (!body->isAwake())
			{
				body->calculateDerivedData();

			}
		}
	}

}

void jfContact_x86::calculateFrictionlessImpulse(jfMatrix3* inverseInertiaTensor,
													jfVector3* result)
{
    jfVector3_x86 deltaVelWorld;
	jfReal deltaVelocity;

    // Build a vector that shows the change in velocity in
    // world space for a unit impulse in the direction of the contact
    // normal.
    m_RelativeContactPosition[0].crossProduct(*m_ContactNormal, &deltaVelWorld);
    inverseInertiaTensor[0].transform(deltaVelWorld, &deltaVelWorld);
    deltaVelWorld.crossProduct(m_RelativeContactPosition[0], &deltaVelWorld);

    // Work out the change in velocity in contact coordiantes.
    deltaVelocity = deltaVelWorld.dotProduct(*m_ContactNormal);

    // Add the linear component of velocity change
    deltaVelocity += m_BodyZero->getInverseMass();

    // Check if we need to the second m_Bodies's data
    if (m_BodyOne)
    {
		m_RelativeContactPosition[1].crossProduct(*m_ContactNormal, &deltaVelWorld);
		inverseInertiaTensor[1].transform(deltaVelWorld, &deltaVelWorld);
		deltaVelWorld.crossProduct(m_RelativeContactPosition[1], &deltaVelWorld);

		// Work out the change in velocity in contact coordiantes.
		jfReal deltaVelocity = deltaVelWorld.dotProduct(*m_ContactNormal);

		// Add the linear component of velocity change
		deltaVelocity += m_BodyOne->getInverseMass();
    }

    // Calculate the required size of the impulse
	// TODO : is this correct?
    result->setX(m_DesiredDeltaVelocity / deltaVelocity);
    result->setY(0);
    result->setZ(0);
}

void jfContact_x86::calculateFrictionImpulse(jfMatrix3* inverseInertiaTensor,
												jfVector3* result)
{
	//TODO: This method from body.cpp
    jfVector3_x86 impulseContact;
    jfReal inverseMass = m_BodyZero->getInverseMass();

    // The equivalent of a cross product in matrices is multiplication
    // by a skew symmetric matrix - we build the matrix for converting
    // between linear and angular quantities.
    jfMatrix3_x86 impulseToTorque;
    impulseToTorque.setSkewSymmetric(m_RelativeContactPosition[0]);

    // Build the matrix to convert contact impulse to change in velocity
    // in world coordinates.
    jfMatrix3_x86 deltaVelWorld = impulseToTorque;
    deltaVelWorld *= inverseInertiaTensor[0];
    deltaVelWorld *= impulseToTorque;
    deltaVelWorld *= -1;

    // Check if we need to add body two's data
    if (m_BodyOne)
    {
        // Set the cross product matrix
        impulseToTorque.setSkewSymmetric(m_RelativeContactPosition[1]);

        // Calculate the velocity change matrix
        jfMatrix3_x86 deltaVelWorld2 = impulseToTorque;
        deltaVelWorld2 *= inverseInertiaTensor[1];
        deltaVelWorld2 *= impulseToTorque;
        deltaVelWorld2 *= -1;

        // Add to the total delta velocity.
        deltaVelWorld += deltaVelWorld2;

        // Add to the inverse mass
        inverseMass += m_BodyOne->getInverseMass();
    }

    // Do a change of basis to convert into contact coordinates.
    jfMatrix3_x86 deltaVelocity;

   	m_ContactToWorld->getTranspose(&deltaVelocity);
    deltaVelocity *= deltaVelWorld;
    deltaVelocity *= (*m_ContactToWorld);

    // Add in the linear velocity change
    deltaVelocity.setElem(0, deltaVelocity.getElem(0) + inverseMass);
    deltaVelocity.setElem(4, deltaVelocity.getElem(4) + inverseMass);
    deltaVelocity.setElem(8, deltaVelocity.getElem(8) + inverseMass);

    // Invert to get the impulse needed per unit velocity
    jfMatrix3_x86 impulseMatrix;
	deltaVelocity.getInverse(&impulseMatrix);

    // Find the target velocities to kill
    jfVector3_x86 velKill(m_DesiredDeltaVelocity,
		   					-m_ContactVelocity->getY(),
							-m_ContactVelocity->getZ());

    // Find the impulse to kill target velocities
    impulseMatrix.transform(velKill, &impulseContact);

    // Check for exceeding friction
    jfReal planarImpulse = jfRealSqrt(impulseContact.getY()*impulseContact.getY() +
										impulseContact.getZ()*impulseContact.getZ());

    if (planarImpulse > (impulseContact.getX() * m_Friction))
    {
        // We need to use dynamic friction
        impulseContact.setY(impulseContact.getY() / planarImpulse);
        impulseContact.setZ(impulseContact.getZ() / planarImpulse);

        impulseContact.setX(deltaVelocity.getElem(0) +
								(deltaVelocity.getElem(1)*m_Friction*impulseContact.getY()) +
								(deltaVelocity.getElem(2)*m_Friction*impulseContact.getZ()));
        impulseContact.setX(m_DesiredDeltaVelocity / impulseContact.getX());
        impulseContact.setY(impulseContact.getY() * m_Friction * impulseContact.getX());
        impulseContact.setZ(impulseContact.getZ() * m_Friction * impulseContact.getX());
    }
    (*result) = impulseContact;
}
