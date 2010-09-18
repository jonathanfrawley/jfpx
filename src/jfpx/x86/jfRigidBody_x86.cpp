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
#include "jfRigidBody_x86.h"

jfRigidBody_x86::jfRigidBody_x86 ()
    :
        jfRigidBody()
{
	m_Pos = new jfVector3_x86();
	m_Orientation = new jfQuaternion_x86();
	m_Velocity = new jfVector3_x86();
	m_Rotation = new jfVector3_x86();
	m_TransformMatrix = new jfMatrix4_x86();
	m_InverseInertiaTensor = new jfMatrix3_x86();
	m_InverseInertiaTensorWorld = new jfMatrix3_x86();
	m_ForceAccum = new jfVector3_x86();
	m_TorqueAccum = new jfVector3_x86();
	m_Accel = new jfVector3_x86();
	m_LastFrameAccel = new jfVector3_x86();
}

jfRigidBody_x86::~jfRigidBody_x86 ()
{
    delete m_Pos;
	delete m_Orientation;
	delete m_Velocity;
	delete m_Rotation;
	delete m_TransformMatrix;
	delete m_InverseInertiaTensor;
	delete m_InverseInertiaTensorWorld;
	delete m_ForceAccum;
	delete m_TorqueAccum;
	delete m_Accel;
	delete m_LastFrameAccel;
}

void jfRigidBody_x86::calculateDerivedData()
{
    m_Orientation->normalize();

	calculateTransformMatrix(m_TransformMatrix, (*m_Pos), (*m_Orientation));
	transformInertiaTensor(m_InverseInertiaTensorWorld,
							(*m_InverseInertiaTensor),
							(*m_TransformMatrix));

}

void jfRigidBody_x86::addForce(const jfVector3& force)
{
	(*m_ForceAccum) += force;
	m_IsAwake = true;
}

void jfRigidBody_x86::integrate(jfReal timeStep)
{
	//Linear Accel
	if(!m_IsAwake)
	{
	    return;
	}

    jfVector3_x86 angularAccel;
	(*m_LastFrameAccel) = (*m_Accel);
	(*m_LastFrameAccel).addScaledVector((*m_ForceAccum), m_InverseMass);

	m_InverseInertiaTensorWorld->transform(*m_TorqueAccum, &angularAccel);

	//Update velocity and rotation
	m_Velocity->addScaledVector((*m_LastFrameAccel), timeStep);
	m_Rotation->addScaledVector(angularAccel, timeStep);

	//Drag
	(*m_Velocity) *= jfRealPow(m_LinearDamping, timeStep);
	(*m_Rotation) *= jfRealPow(m_AngularDamping, timeStep);

	//Adjust position and orientation
	m_Pos->addScaledVector((*m_Velocity), timeStep);
	m_Orientation->addScaledVector((*m_Rotation), timeStep);

	//Drag
	(*m_Velocity) *= jfRealPow(m_LinearDamping, timeStep);
	(*m_Rotation) *= jfRealPow(m_AngularDamping, timeStep);

	calculateDerivedData();

	clearAccumulators();

    // Update the kinetic energy store, and possibly put the body to
    // sleep.
    if (m_CanSleep) {
        jfReal currentMotion = m_Velocity->dotProduct(*m_Velocity) +
                                m_Rotation->dotProduct(*m_Rotation);

        jfReal bias = jfRealPow(0.05, timeStep);
        m_Motion = bias*m_Motion + (1-bias)*currentMotion;

        if (m_Motion < SleepEpsilon)
        {
            setAwake(false);
        }
        else if (m_Motion > (10 * SleepEpsilon))
        {
            //Limit Motion
            m_Motion = (10 * SleepEpsilon);
        }
    }
}

void jfRigidBody_x86::clearAccumulators()
{
	m_ForceAccum->clear();
	m_TorqueAccum->clear();
}

void jfRigidBody_x86::addForceAtBodyPoint(const jfVector3& force, const jfVector3& point)
{
	jfVector3_x86 pointInWorldSpace;
   	getPointInWorldSpace(point, &pointInWorldSpace);
	addForceAtPoint(force, pointInWorldSpace);
}

void jfRigidBody_x86::addForceAtPoint(const jfVector3& force, const jfVector3& point)
{
    jfVector3_x86 pointCrossForce;
	jfVector3_x86 pointCopy = point;
	pointCopy -= (*m_Pos);

	(*m_ForceAccum) += force;
	pointCopy.crossProduct(force, &pointCrossForce);
	(*m_TorqueAccum) += pointCrossForce;
    m_IsAwake = true;
}

void jfRigidBody_x86::getPointInLocalSpace(const jfVector3& point, jfVector3* result) const
{
	m_TransformMatrix->transformInverse(point, result);
}

void jfRigidBody_x86::getPointInWorldSpace(const jfVector3& point, jfVector3* result) const
{
    m_TransformMatrix->transform(point, result);
}

void jfRigidBody_x86::calculateTransformMatrix(jfMatrix4* transformMatrix,
												const jfVector3& pos,
												const jfQuaternion& orientation) const
{
	//@ref: Millington p.195
    transformMatrix->setElem(0, (1 - (2*orientation.getJ()*orientation.getJ()) -
                                    (2*orientation.getK()*orientation.getK())));
    transformMatrix->setElem(1, ((2*orientation.getI()*orientation.getJ()) -
                                (2*orientation.getR()*orientation.getK())));
    transformMatrix->setElem(2, ((2*orientation.getI()*orientation.getK()) +
                                (2*orientation.getR()*orientation.getJ())));
    transformMatrix->setElem(3, pos.getX());
    transformMatrix->setElem(4,((2*orientation.getI()*orientation.getJ()) +
                                (2*orientation.getR()*orientation.getK())));
    transformMatrix->setElem(5, ((1 - (2*orientation.getI()*orientation.getI())) -
                                    (2*orientation.getK()*orientation.getK())));
    transformMatrix->setElem(6, ((2*orientation.getJ()*orientation.getK()) -
                                (2*orientation.getR()*orientation.getI())));
    transformMatrix->setElem(7, pos.getY());
    transformMatrix->setElem(8, ((2*orientation.getI()*orientation.getK()) -
                                (2*orientation.getR()*orientation.getJ())));
    transformMatrix->setElem(9, ((2*orientation.getJ()*orientation.getK()) +
                                (2*orientation.getR()*orientation.getI())));
    transformMatrix->setElem(10, (1 - (2*orientation.getI()*orientation.getI()) -
                                    (2*orientation.getJ()*orientation.getJ())));
    transformMatrix->setElem(11, pos.getZ());
}


void jfRigidBody_x86::transformInertiaTensor(jfMatrix3* iitWorld
												, const jfMatrix3& iitBody
												, const jfMatrix4& rotMat) const
{
	//@REF:Millington p.203
	//Generated using an optimising compiler
	jfReal t4 = (rotMat.getElem(0)*iitBody.getElem(0)) +
                    (rotMat.getElem(1)*iitBody.getElem(3)) +
                    (rotMat.getElem(2)*iitBody.getElem(6));
	jfReal t9 = (rotMat.getElem(0)*iitBody.getElem(1)) +
                    (rotMat.getElem(1)*iitBody.getElem(4)) +
                    (rotMat.getElem(2)*iitBody.getElem(7));
	jfReal t14 = (rotMat.getElem(0)*iitBody.getElem(2)) +
                    (rotMat.getElem(1)*iitBody.getElem(5)) +
                    (rotMat.getElem(2)*iitBody.getElem(8));
	jfReal t28 = (rotMat.getElem(4)*iitBody.getElem(0)) +
                    (rotMat.getElem(5)*iitBody.getElem(3)) +
                    (rotMat.getElem(6)*iitBody.getElem(6));
	jfReal t33 = (rotMat.getElem(4)*iitBody.getElem(1)) +
                    (rotMat.getElem(5)*iitBody.getElem(4)) +
                    (rotMat.getElem(6)*iitBody.getElem(7));
	jfReal t38 = (rotMat.getElem(4)*iitBody.getElem(2)) +
                    (rotMat.getElem(5)*iitBody.getElem(5)) +
                    (rotMat.getElem(6)*iitBody.getElem(8));
	jfReal t52 = (rotMat.getElem(8)*iitBody.getElem(0)) +
                    (rotMat.getElem(9)*iitBody.getElem(3)) +
                    (rotMat.getElem(10)*iitBody.getElem(6));
	jfReal t57 = (rotMat.getElem(8)*iitBody.getElem(1)) +
                    (rotMat.getElem(9)*iitBody.getElem(4)) +
                    (rotMat.getElem(10)*iitBody.getElem(7));
	jfReal t62 = (rotMat.getElem(8)*iitBody.getElem(2)) +
                    (rotMat.getElem(9)*iitBody.getElem(5)) +
                    (rotMat.getElem(10)*iitBody.getElem(8));
	iitWorld->setElem(0, (t4*rotMat.getElem(0)) +
							(t9*rotMat.getElem(1)) +
							(t14*rotMat.getElem(2)));
	iitWorld->setElem(1, (t4*rotMat.getElem(4)) +
							(t9*rotMat.getElem(5)) +
							(t14*rotMat.getElem(6)));
	iitWorld->setElem(2, (t4*rotMat.getElem(8)) +
							(t9*rotMat.getElem(9)) +
							(t14*rotMat.getElem(10)));
	iitWorld->setElem(3, (t28*rotMat.getElem(0)) +
							(t33*rotMat.getElem(1)) +
							(t38*rotMat.getElem(2)));
	iitWorld->setElem(4, (t28*rotMat.getElem(4)) +
							(t33*rotMat.getElem(5)) +
							(t38*rotMat.getElem(6)));
	iitWorld->setElem(5, (t28*rotMat.getElem(8)) +
							(t33*rotMat.getElem(9)) +
							(t38*rotMat.getElem(10)));
	iitWorld->setElem(6, (t52*rotMat.getElem(0)) +
							(t57*rotMat.getElem(1)) +
							(t62*rotMat.getElem(2)));
	iitWorld->setElem(7, (t52*rotMat.getElem(4)) +
							(t57*rotMat.getElem(5)) +
							(t62*rotMat.getElem(6)));
	iitWorld->setElem(8, (t52*rotMat.getElem(8)) +
							(t57*rotMat.getElem(9)) +
							(t62*rotMat.getElem(10)));
}














