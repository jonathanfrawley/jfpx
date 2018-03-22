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
#ifndef JFCONTACT_H
#define JFCONTACT_H

#include <jfpx/jfCore.h>
#include <jfpx/jfMatrix3.h>
#include <jfpx/jfRigidBody.h>
#include <jfpx/jfVector3.h>

/*
 * =====================================================================================
 *        Class: jfContact
 *  Description:
 * =====================================================================================
 */
class jfContact {
public:
    jfContact();

    jfContact(const jfContact& other);

    virtual ~jfContact();

    /*-----------------------------------------------------------------------------
		 * @ref : http://www.parashift.com/c++-faq-lite/virtual-functions.html#faq-20.8
		 * DLA 11 / 3 / 2010
		 *-----------------------------------------------------------------------------*/
    virtual jfContact* clone() const = 0;

    /*-----------------------------------------------------------------------------
		 *  Interface
		 *-----------------------------------------------------------------------------*/
    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  calculateInternals
		 *  Description:  Calculates internal data from state data.
		 * =====================================================================================
		 */
    virtual void calculateInternals(jfReal timeStep) = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  swapBodies
		 *  Description:  Swaps the contact's bodies.
		 * =====================================================================================
		 */
    virtual void swapBodies() = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  matchAwakeState
		 *  Description:  Updates bodies to have same awake state as contact.
		 * =====================================================================================
		 */
    virtual void matchAwakeState()
    {
        // Collisions with the world never cause a body to wake up.
        if (!m_BodyOne) {
            return;
        }

        bool bodyZeroAwake = m_BodyZero->isAwake();
        bool bodyOneAwake = m_BodyOne->isAwake();

        // Wake up only the sleeping one
        if (bodyZeroAwake ^ bodyOneAwake) {
            if (bodyZeroAwake) {
                m_BodyOne->setAwake(true);
            } else {
                m_BodyZero->setAwake(true);
            }
        }
    }

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  calculateDesiredDeltaVelocity
		 *  Description:  Calculates and sets the value for the desired delta velocity.
		 * =====================================================================================
		 */
    virtual void calculateDesiredDeltaVelocity(jfReal timeStep) = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  calculateLocalVelocity
		 *  Description:  Calculates and returns the velocity of the contact point on the given body.
		 * =====================================================================================
		 */
    virtual void calculateLocalVelocity(unsigned bodyIndex,
        jfReal timeStep,
        jfVector3* result)
        = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  calculateContactBasis
		 *  Description:  Calculates an orthonormal basis for the contact point, based on
         * the primary friction direction (for anisotropic friction) or
         * a random orientation (for isotropic friction).*
		 *
		 * =====================================================================================
		 */
    virtual void calculateContactBasis() = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  applyVelocityChange
		 *  Description:  Performs an inertia-weighted impulse based on the resolution of this contact alone.
         *  Note: linearChange and angularChange are arrays of 2 jfVector3s.
		 * =====================================================================================
		 */
    virtual void applyVelocityChange(jfVector3* velocityChange,
        jfVector3* rotationChange)
        = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  applyPositionChange
		 *  Description:  Performs an inertia weighted penetration resolution of this contact alone.
		 *  Note: linearChange and angularChange are arrays of 2 jfVector3s.
		 * =====================================================================================
		 */
    virtual void applyPositionChange(jfVector3* linearChange,
        jfVector3* angularChange,
        jfReal penetration)
        = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  calculateFrictionlessImpulse
		 *  Description:  Calculates the impules needed to resolve the contact given that it has no friction.
         *  Note: inverseInertiaTensor is an array of 2 jfMatrix3s.
		 * =====================================================================================
		 */
    virtual void calculateFrictionlessImpulse(jfMatrix3* inverseInertiaTensor,
        jfVector3* result)
        = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  calculateFrictionImpulse
		 *  Description:  Calculates the impulses needed to resolve the contact given that it has friction.
		 * =====================================================================================
		 */
    virtual void calculateFrictionImpulse(jfMatrix3* inverseInertiaTensor,
        jfVector3* result)
        = 0;

    /*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  setBodyData
		 *  Description:  Sets the data that doesn't depend on the position of the contact
		 * =====================================================================================
		 */
    void setBodyData(jfRigidBody* one,
        jfRigidBody* two,
        jfReal friction,
        jfReal restitution)
    {
        m_BodyZero = one;
        m_BodyOne = two;
        m_Friction = friction;
        m_Restitution = restitution;
    }

    virtual jfReal getDesiredDeltaVelocity() const
    {
        return m_DesiredDeltaVelocity;
    }

    virtual jfRigidBody* getBody(unsigned index) const
    {
        if (index == 0) {
            return m_BodyZero;
        } else {
            return m_BodyOne;
        }
    }
    virtual void setBody(unsigned index, jfRigidBody* body)
    {
        if (index == 0) {
            m_BodyZero = body;
        } else {
            m_BodyOne = body;
        }
    }

    virtual void getRelativeContactPosition(unsigned index, jfVector3* result) const
    {
        (*result) = m_RelativeContactPosition[index];
    }

    virtual jfReal getPenetration() const
    {
        return m_Penetration;
    }
    virtual void setPenetration(jfReal val)
    {
        m_Penetration = val;
    }

    virtual void getContactPoint(jfVector3* val) const
    {
        (*val) = (*m_ContactPoint);
    }
    virtual void setContactPoint(const jfVector3& val)
    {
        (*m_ContactPoint) = val;
    }

    virtual void getContactNormal(jfVector3* result) const
    {
        (*result) = (*m_ContactNormal);
    }
    virtual void setContactNormal(const jfVector3& val)
    {
        (*m_ContactNormal) = val;
    }

    virtual void getContactToWorld(jfMatrix3* result) const
    {
        (*result) = (*m_ContactToWorld);
    }

    virtual void getContactVelocity(jfVector3* result) const
    {
        (*result) = (*m_ContactVelocity);
    }
    virtual void setContactVelocity(const jfVector3& val)
    {
        (*m_ContactVelocity) = val;
    }

    virtual jfReal getFriction() const { return m_Friction; }

    virtual jfReal getRestitution() const { return m_Restitution; }

protected:
    jfRigidBody* m_BodyZero;
    jfRigidBody* m_BodyOne;
    jfReal m_Friction;
    jfReal m_Restitution;
    jfVector3* m_ContactPoint; //Position of contact in world coords
    jfVector3* m_ContactNormal; //Direction of contact in world coords
    jfReal m_Penetration; //Depth of penetration at the contact point
    jfMatrix3* m_ContactToWorld; //Converts from contacts coords to world coords, columns of matrix form an orthonormal set of vectors
    jfVector3* m_ContactVelocity; //Holds the closing velocity at the point of contact. Set by calculateInternals().
    jfReal m_DesiredDeltaVelocity; //Holds required change in velocity for contact to be resolved
    jfVector3* m_RelativeContactPosition; //Holds the world space position of the contact point relative to the centre of each body. Set by calculateInternals().
private:
};

#endif //JFCONTACT_H
