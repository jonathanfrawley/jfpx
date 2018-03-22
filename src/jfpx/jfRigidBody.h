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
#ifndef JFRIGIDBODY_H
#define JFRIGIDBODY_H

#include <jfpx/jfCore.h>
#include <jfpx/jfMatrix3.h>
#include <jfpx/jfMatrix4.h>
#include <jfpx/jfQuaternion.h>
#include <jfpx/jfVector3.h>

const jfReal SleepEpsilon = 0.3;

/*
 * =====================================================================================
 *        Class: RigidBody
 *  Description: Represents rigidbodies in space.
 * =====================================================================================
 */
class jfRigidBody {
public:
    jfRigidBody();

    virtual ~jfRigidBody();

    /*-----------------------------------------------------------------------------
		 *  Implemented methods
		 *-----------------------------------------------------------------------------*/
    virtual bool hasFiniteMass()
    {
        return (m_InverseMass >= (jfReal)0);
    }

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  addVelocity
		 *  Description:  Adds the given velocity to the body's.
		 * =====================================================================================
		 */
    virtual void addVelocity(const jfVector3& other)
    {
        (*m_Velocity) += other;
    }

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  addRotation
		 *  Description:  Adds the given rotation to the body's.
		 * =====================================================================================
		 */
    virtual void addRotation(const jfVector3& other)
    {
        (*m_Rotation) += other;
    }

    /*-----------------------------------------------------------------------------
		 *  Interface
		 *-----------------------------------------------------------------------------*/
    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  calculateDerivedData
		 *  Description:  Calculates internal data from state data.
		 * =====================================================================================
		 */
    virtual void calculateDerivedData() = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name: addForce
		 *  Description: Adds the given force to the COG of the rigid body.
		 * =====================================================================================
		 */
    virtual void addForce(const jfVector3& force) = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  integrate
		 *  Description:  Resolves forces and updates position
		 * =====================================================================================
		 */
    virtual void integrate(jfReal duration) = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  clearAccumulators
		 *  Description:  Clears the accumulators of the body.
		 * =====================================================================================
		 */
    virtual void clearAccumulators() = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  addForceAtBodyPoint
		 *  Description:  Adds the force to the point on the rigid body. Useful for springs, etc.
		 *  Force in world coords, point in object coords.
		 * =====================================================================================
		 */
    virtual void addForceAtBodyPoint(const jfVector3& force, const jfVector3& point) = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  addForceAtPoint
		 *  Description:  Adds force at point
		 * =====================================================================================
		 */
    virtual void addForceAtPoint(const jfVector3& force, const jfVector3& point) = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getPointInLocalSpace
		 *  Description:  Gets point in local rigid body coords from world coords
		 * =====================================================================================
		 */
    virtual void getPointInLocalSpace(const jfVector3& point, jfVector3* result) const = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getPointInWorldSpace
		 *  Description:  Gets point in world coords from local body coords
		 * =====================================================================================
		 */
    virtual void getPointInWorldSpace(const jfVector3& point, jfVector3* result) const = 0;

    /*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *  Some are to be defined as they allocate memory dynamically based on subclass.
		 *-----------------------------------------------------------------------------*/
    virtual jfReal getInverseMass() const { return m_InverseMass; }
    virtual void setInverseMass(jfReal val) { m_InverseMass = val; }

    virtual jfReal getMass() const { return (1.0 / m_InverseMass); }
    virtual void setMass(jfReal val) { m_InverseMass = (1.0 / val); }

    virtual jfReal getAngularDamping() const { return m_AngularDamping; }
    virtual void setAngularDamping(jfReal val) { m_AngularDamping = val; }

    virtual jfReal getLinearDamping() const { return m_LinearDamping; }
    virtual void setLinearDamping(jfReal val) { m_LinearDamping = val; }

    virtual void getPos(jfVector3* pos) const
    {
        (*pos) = (*m_Pos);
    }
    virtual void setPos(const jfVector3& val)
    {
        (*m_Pos) = val;
    }

    virtual void getAccel(jfVector3* accel) const
    {
        (*accel) = (*m_Accel);
    }
    virtual void setAccel(const jfVector3& val)
    {
        (*m_Accel) = val;
    }

    virtual void getOrientation(jfQuaternion* orientation) const
    {
        (*orientation) = (*m_Orientation);
    }
    virtual void setOrientation(const jfQuaternion& val)
    {
        (*m_Orientation) = val;
    }

    virtual void getVelocity(jfVector3* velocity) const
    {
        (*velocity) = (*m_Velocity);
    }
    virtual void setVelocity(const jfVector3& val)
    {
        (*m_Velocity) = val;
    }

    virtual void getRotation(jfVector3* rotation) const
    {
        (*rotation) = (*m_Rotation);
    }
    virtual void setRotation(const jfVector3& val)
    {
        (*m_Rotation) = val;
    }

    virtual void getTransformMatrix(jfMatrix4* mat) const
    {
        (*mat) = (*m_TransformMatrix);
    }
    virtual void setTransformMatrix(const jfMatrix4& mat)
    {
        (*m_TransformMatrix) = mat;
    }

    virtual void getInverseInertiaTensor(jfMatrix3* matrix) const
    {
        (*matrix) = (*m_InverseInertiaTensor);
    }

    virtual void getInverseInertiaTensorWorld(jfMatrix3* matrix) const
    {
        (*matrix) = (*m_InverseInertiaTensorWorld);
    }

    virtual void setInertiaTensor(const jfMatrix3& inertiaTensor)
    {
        m_InverseInertiaTensor->setInverse(inertiaTensor);
    }

    virtual void getLastFrameAccel(jfVector3* accel) const
    {
        (*accel) = (*m_LastFrameAccel);
    }

    virtual bool isAwake() { return m_IsAwake; }
    virtual void setAwake(bool awake = true)
    {
        if (awake) {
            m_IsAwake = true;
            // Add a bit of motion to avoid it falling asleep immediately.
            m_Motion = SleepEpsilon * 2.0f;
        } else {
            m_IsAwake = false;
            m_Velocity->clear();
            m_Rotation->clear();
        }
    }

    virtual void setCanSleep(bool val)
    {
        m_CanSleep = val;
        if (!m_CanSleep && !m_IsAwake) {
            setAwake(true);
        }
    }

protected:
    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  calculateTransformMatrix
		 *  Description:  Calculates a transform matrix given a position and an orientation.
		 * =====================================================================================
		 */
    virtual void calculateTransformMatrix(jfMatrix4* transformMatrix,
        const jfVector3& pos,
        const jfQuaternion& orientation) const = 0;
    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  transformInertiaTensor
		 *  Description:  Internal function to do an inertia tensor transform by a
		 *  quaternion
		 * =====================================================================================
		 */
    virtual void transformInertiaTensor(jfMatrix3* iitWorld, const jfMatrix3& iitBody, const jfMatrix4& rotMat) const = 0;

    jfReal m_InverseMass;
    jfVector3* m_Pos;
    jfQuaternion* m_Orientation;
    jfVector3* m_Velocity;
    jfVector3* m_Rotation;
    /**
		 * Cached val, changed by Orientation and Position
		 **/
    jfMatrix4* m_TransformMatrix;
    /**
		 * Inverse of the inertia tensor of the rigidbody.
		 **/
    jfMatrix3* m_InverseInertiaTensor;
    /**
		 * m_InverseInertiaTensor in world coords
		 **/
    jfMatrix3* m_InverseInertiaTensorWorld;
    /**
		 * Accumulators for linear forces and torque.
		 **/
    jfVector3* m_ForceAccum;
    jfVector3* m_TorqueAccum;
    /**
		 * Damping is applied to angular motion to remove energy
		 * added through numerical instability (Millington p.211)
         **/
    jfReal m_LinearDamping;
    jfReal m_AngularDamping;
    /**
		 * Used to set constant acceleration such as gravity.
         **/
    jfVector3* m_Accel;
    jfVector3* m_LastFrameAccel;
    /**
		 * To deal with sleep state
		 */
    jfReal m_Motion; //Recency weighted mean of motion
    bool m_IsAwake;
    bool m_CanSleep; //Some bodies should not be allowed to sleep
private:
};

#endif //JFRIGIDBODY_H
