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
#include "jfFlightSimulation_x86.h"

jfFlightSimulation_x86::jfFlightSimulation_x86()
{
    m_WindSpeed = new jfVector3_x86(0,0,0);
    m_RightWing = new jfAeroControlForceGenerator_x86(jfMatrix3_x86(0,0,0, -1,-0.5f,0, 0,0,0),
                                                        jfMatrix3_x86(0,0,0, -0.995f,-0.5f,0, 0,0,0),
                                                        jfMatrix3_x86(0,0,0, -1.005f,-0.5f,0, 0,0,0),
                                                        jfVector3_x86(-1.0f, 0.0f, 2.0f),
                                                        m_WindSpeed
                                                      );
    m_LeftWing = new jfAeroControlForceGenerator_x86(jfMatrix3_x86(0,0,0, -1,-0.5f,0, 0,0,0),
                                                        jfMatrix3_x86(0,0,0, -0.995f,-0.5f,0, 0,0,0),
                                                        jfMatrix3_x86(0,0,0, -1.005f,-0.5f,0, 0,0,0),
                                                        jfVector3_x86(-1.0f, 0.0f, -2.0f),
                                                        m_WindSpeed
                                                        );
    m_Rudder = new jfAeroControlForceGenerator_x86(jfMatrix3_x86(0,0,0, 0,0,0, 0,0,0),
                                                    jfMatrix3_x86(0,0,0, 0,0,0, 0.01f,0,0),
                                                    jfMatrix3_x86(0,0,0, 0,0,0, -0.01f,0,0),
                                                    jfVector3_x86(2.0f, 0.5f, 0),
                                                    m_WindSpeed
													);

    m_Tail = new jfAeroForceGenerator_x86(jfMatrix3_x86(0,0,0, -1,-0.5f,0, 0,0,-0.1f),
                                            jfVector3_x86(2.0f, 0, 0),
                                            m_WindSpeed
                                            );
    m_Aircraft = new jfRigidBody_x86();
    m_Registry = new jfForceRegistry_x86();
    m_LeftWingControl = 0.0f;
    m_RightWingControl = 0.0f;
    m_RudderControl = 0.0f;

    m_EventHandler = new jfFlightEventHandler_x86();
    m_WindowManager = new jfSDL();
    m_3DGraphicsHandler = new jfFlight3DGraphicsHandler_x86();
    m_Timer = new jfTimer();
}

jfFlightSimulation_x86::~jfFlightSimulation_x86()
{
    delete m_LeftWing;
    delete m_RightWing;
    delete m_Rudder;
    delete m_Tail;
    delete m_Aircraft;
    delete m_Registry;
    delete m_WindSpeed;
    delete m_EventHandler;
    delete m_3DGraphicsHandler;
    delete m_WindowManager;
    delete m_Timer;
}

void jfFlightSimulation_x86::resetAircraft()
{
	m_Aircraft->setPos(jfVector3_x86(0, 0, 0));
    m_Aircraft->setOrientation(jfQuaternion_x86(1,0,0,0));
    m_Aircraft->setVelocity(jfVector3_x86(0,0,0));
    m_Aircraft->setRotation(jfVector3_x86(0,0,0));
}


bool jfFlightSimulation_x86::init()
{
    if(! m_WindowManager->createWindow(800, 600, 32, false, "Flight Simulation"))
    {
        return false;
    }

    m_EventHandler->setWindowManager(m_WindowManager);
    //@REF:Millington code "flightsim.cpp"
    // Set up the aircraft rigid body.
    resetAircraft();

    m_Aircraft->setMass(2.5f);
    jfMatrix3_x86 tensor;
    tensor.setBlockInertiaTensor(jfVector3_x86(2,1,1), 1);
    m_Aircraft->setInertiaTensor(tensor);
    m_Aircraft->setLinearDamping(0.8f);
    m_Aircraft->setAngularDamping(0.8f);
    m_Aircraft->setAccel(jfVector3_x86(0,-9.81,0));
    m_Aircraft->calculateDerivedData();

    m_Registry->add(m_Aircraft, m_LeftWing);
    m_Registry->add(m_Aircraft, m_RightWing);
    m_Registry->add(m_Aircraft, m_Rudder);
    m_Registry->add(m_Aircraft, m_Tail);

	m_3DGraphicsHandler->setAircraft(m_Aircraft);
    m_3DGraphicsHandler->init();

	m_EventHandler->setAircraft(m_Aircraft);
    m_EventHandler->setRudderControl(&m_RudderControl);
    m_EventHandler->setLeftWingControl(&m_LeftWingControl);
    m_EventHandler->setRightWingControl(&m_RightWingControl);

    m_Timer->start();

    return true;
}

void jfFlightSimulation_x86::run()
{
	//@REF: Millington code "flightsim.cpp"
	glDisable(GL_LIGHT1);

    while(m_EventHandler->handleEvents())
    {
		m_EventHandler->handleKeyEvents();
        // Update the control surfaces
        m_LeftWing->setControl(m_LeftWingControl);
        m_RightWing->setControl(m_RightWingControl);
        m_Rudder->setControl(m_RudderControl);

		m_LastFrameDuration = m_Timer->getTicks();
		m_Timer->start();
		m_3DGraphicsHandler->draw();
		// Find the duration of the last frame in seconds
        float timeStep = (float)m_LastFrameDuration / 1000;
        if (timeStep <= 0.0f)
        {
            continue;
        }

		// Start with no forces or acceleration.
		m_Aircraft->clearAccumulators();

		// Add the propeller force
		jfVector3_x86 propulsion = jfVector3_x86(-10.0f, 0, 0);
		jfMatrix4_x86 transformMatrix;
		m_Aircraft->getTransformMatrix(&transformMatrix);
		transformMatrix.transformDirection(propulsion, &propulsion);
		m_Aircraft->addForce(propulsion);

		// Add the forces acting on the aircraft.
		m_Registry->updateForces(timeStep);

		// Update the aircraft's physics.
		m_Aircraft->integrate(timeStep);

		// Do a very basic collision detection and response with the ground.
		jfVector3_x86 pos;
		jfVector3_x86 velocity;
		m_Aircraft->getPos(&pos);
		m_Aircraft->getVelocity(&velocity);
		if (pos.getY() < 0.0f)
		{
			pos.setY(0.0f);
			m_Aircraft->setPos(jfVector3_x86(pos.getX(),
												pos.getY(),
												pos.getZ()));
			if (velocity.getY() < -10.0f)
			{
				resetAircraft();
			}
		}
	}
}
