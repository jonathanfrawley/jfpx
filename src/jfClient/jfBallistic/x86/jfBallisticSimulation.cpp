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
#include "jfBallisticSimulation.h"


jfBallisticSimulation::jfBallisticSimulation()
{
    m_EventHandler = new jfBallisticEventHandler();
    m_WindowManager = new jfSDL();
    m_3DGraphicsHandler = new jfBallisticSDLGL3DGraphicsHandler();
    m_Timer = new jfTimer();
    unsigned int i;
    for(i=0;i<MAX_AMMO_ROUNDS;i++)
    {
        m_Ammo.push_back(new jfAmmoRound());
    }
}

jfBallisticSimulation::~jfBallisticSimulation()
{
    delete m_EventHandler;
    delete m_WindowManager;
    delete m_3DGraphicsHandler;
    delete m_Timer;
}

bool jfBallisticSimulation::init()
{
    if(! m_WindowManager->createWindow(800, 600, 32, false, "Ballistic Simulation"))
    {
        return false;
    }

    m_EventHandler->setWindowManager(m_WindowManager);
//    m_EventHandler->setSimulation(this);
    m_3DGraphicsHandler->init();
    m_3DGraphicsHandler->setAmmo(&m_Ammo);

    vector<jfAmmoRound*>::iterator it;
    for( it = m_Ammo.begin() ; it != m_Ammo.end() ; ++it)
    {
        (*it)->setType(UNUSED);
    }

    m_Timer->start();
    m_MousePressedLast = false;
    return true;
}

void jfBallisticSimulation::fire()
{
    // Find the first available round.
    jfAmmoRound* shot;
    vector<jfAmmoRound*>::iterator it;
    for( it = m_Ammo.begin() ; it != m_Ammo.end() ; ++it)
    {
        if ((*it)->getType() == UNUSED)
        {
            break;
        }
    }

    // If we didn't find an usused round, then exit - we can't fire.
    if (it == m_Ammo.end())
    {
        return;
    }
    shot = (*it);

    // Set the properties of the particle
    switch(m_EventHandler->getCurrentShotType())
    {
    case PISTOL:
        shot->getParticle()->setMass(2.0f); // 2.0kg
        shot->getParticle()->setVel(new jfVector3_x86(0.0f, 0.0f, 35.0f)); // 35m/s
        shot->getParticle()->setAccel(new jfVector3_x86(0.0f, -1.0f, 0.0f));
        shot->getParticle()->setDamping(0.99f);
        break;
    case ARTILLERY:
        shot->getParticle()->setMass(200.0f); // 200.0kg
        shot->getParticle()->setVel(new jfVector3_x86(0.0f, 30.0f, 40.0f)); // 50m/s
        shot->getParticle()->setAccel(new jfVector3_x86(0.0f, -20.0f, 0.0f));
        shot->getParticle()->setDamping(0.99f);
        break;
    case FIREBALL:
        shot->getParticle()->setMass(1.0f); // 1.0kg - mostly blast damage
        shot->getParticle()->setVel(new jfVector3_x86(0.0f, 0.0f, 10.0f)); // 5m/s
        shot->getParticle()->setAccel(new jfVector3_x86(0.0f, 0.6f, 0.0f)); // Floats up
        shot->getParticle()->setDamping(0.9f);
        break;
    case LASER:
        // Note that this is the kind of laser bolt seen in films,
        // not a realistic laser beam!
        shot->getParticle()->setMass(0.1f); // 0.1kg - almost no weight
        shot->getParticle()->setVel(new jfVector3_x86(0.0f, 0.0f, 100.0f)); // 100m/s
        shot->getParticle()->setAccel(new jfVector3_x86(0.0f, 0.0f, 0.0f)); // No gravity
        shot->getParticle()->setDamping(0.99f);
        break;
    }

    // Set the data common to all particle types
    shot->getParticle()->setPos(new jfVector3_x86(0.0f, 1.5f, 0.0f));
    //shot->setType(m_EventHandler->getCurrentShotType());

    shot->setType(PISTOL);

    //printf("shot is : <%d> \n", shot);
    // Clear the force accumulators
    //shot->getParticle()->clearAccumulator();

}

void jfBallisticSimulation::run()
{
    while(m_EventHandler->handleEvents())
    {
        m_EventHandler->handleKeyEvents();
        m_LastFrameDuration = m_Timer->getTicks();
        m_Timer->start();
        if((m_EventHandler->getMouseEvent().getStatus() == EVENT_MOUSELEFT))
        {
            if(!m_MousePressedLast)
            {
                m_MousePressedLast = true;
                fire();
            }
        }
        else
        {
            m_MousePressedLast = false;
        }
        m_3DGraphicsHandler->draw();
        // Find the duration of the last frame in seconds
        float duration = (float)m_LastFrameDuration / 1000;
        if (duration <= 0.0f) continue;

        // Update the physics of each particle in turn
        int i;
        for (i=0; i < MAX_AMMO_ROUNDS; i++)
        {
            jfAmmoRound* shot = (m_Ammo[i]);
            if (shot->getType() != UNUSED)
            {
                // Run the physics
                shot->getParticle()->integrate(duration);

                // Check if the particle is now invalid
                if (shot->getParticle()->getPos()->getY() < 0.0f ||
                    shot->getParticle()->getPos()->getZ() > 200.0f)
                {
                    // We simply set the shot type to be unused, so the
                    // memory it occupies can be reused by another shot.
                    shot->setType(UNUSED);
                }
            }
        }
    }
}
