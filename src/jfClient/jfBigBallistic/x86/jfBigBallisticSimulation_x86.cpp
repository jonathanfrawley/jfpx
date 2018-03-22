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
#include "jfBigBallisticSimulation_x86.h"

jfBigBallisticSimulation_x86::jfBigBallisticSimulation_x86()
    : m_CurrentShotType(LASER)
{
    m_EventHandler = new jfBigBallisticEventHandler_x86();
    m_WindowManager = new jfSDL();
    m_3DGraphicsHandler = new jfBigBallistic3DGraphicsHandler_x86();
    m_Timer = new jfTimer();
    unsigned i;
    for (i = 0; i < MAX_AMMO_ROUNDS; i++) {
        m_Ammo.push_back(new jfAmmoRound_x86());
    }
    for (i = 0; i < m_MaxBoxes; i++) {
        jfBox_x86* newBox = new jfBox_x86();
        newBox->setHalfSize(jfVector3_x86(2, 2, 2));
        m_Boxes.push_back(newBox);
    }
    m_CollisionData = new jfCollisionData();
    m_ContactResolver = new jfContactResolver_x86(m_MaxContacts);
    m_CollisionDetector = new jfCollisionDetector_x86();
}

jfBigBallisticSimulation_x86::~jfBigBallisticSimulation_x86()
{
    delete m_EventHandler;
    delete m_WindowManager;
    delete m_3DGraphicsHandler;
    delete m_Timer;
    delete m_CollisionData;
    delete m_ContactResolver;
    delete m_CollisionDetector;
}

void jfBigBallisticSimulation_x86::drawDebug()
{
    if (!m_RenderDebugInfo) {
        return;
    }

    // Recalculate the contacts, so they are current (in case we're
    // paused, for example).
    generateContacts();
    vector<jfContact*> contacts;
    m_CollisionData->getContacts(&contacts);
    m_3DGraphicsHandler->drawDebug(contacts);
}

bool jfBigBallisticSimulation_x86::init()
{
    if (!m_WindowManager->createWindow(800, 600, 32, false, "Ballistic Simulation")) {
        return false;
    }

    m_EventHandler->setWindowManager(m_WindowManager);
    m_3DGraphicsHandler->init();
    m_3DGraphicsHandler->setAmmo(&m_Ammo);
    m_3DGraphicsHandler->setBoxes(&m_Boxes);

    vector<jfAmmoRound_x86*>::iterator it;
    for (it = m_Ammo.begin(); it != m_Ammo.end(); ++it) {
        (*it)->setType(UNUSED);
    }
    // Initialise the boxes
    vector<jfBox_x86*>::iterator box;
    jfReal z = 50.0f;
    for (box = m_Boxes.begin(); box != m_Boxes.end(); box++) {
        jfVector3_x86 pos = jfVector3_x86(0, 1.5, z);
        (*box)->setState(pos);
        z += 1;
    }

    m_Timer->start();
    m_MousePressedLast = false;
    return true;
}

void jfBigBallisticSimulation_x86::fire()
{
    // Find the first available round.
    vector<jfAmmoRound_x86*>::iterator shot;
    for (shot = m_Ammo.begin(); shot != m_Ammo.end(); shot++) {
        if ((*shot)->getType() == UNUSED) {
            break;
        }
    }
    if (shot == m_Ammo.end()) {
        return;
    }
    // Set the shot
    (*shot)->setState(m_CurrentShotType);
}

void jfBigBallisticSimulation_x86::updateObjects(jfReal timeStep)
{

    // Update the physics of each particle in turn
    vector<jfAmmoRound_x86*>::iterator it;
    for (it = m_Ammo.begin(); it != m_Ammo.end(); it++) {
        if ((*it)->getType() != UNUSED) {
            jfVector3_x86 bodyPos;
            (*it)->getBody()->integrate(timeStep);

            // Run the physics
            (*it)->getBody()->integrate(timeStep);
            (*it)->calculateInternals();

            (*it)->getBody()->getPos(&bodyPos);
            if (bodyPos.getY() < 0.0f || ((*it)->getStartTime() + 10) < m_Timer->getTicks() || bodyPos.getZ() > 200.0f) {
                // We simply set the shot type to be unused, so the
                // memory it occupies can be reused by another shot.
                (*it)->setType(UNUSED);
            }
        }
    }

    vector<jfBox_x86*>::iterator box;
    // Update the boxes
    for (box = m_Boxes.begin(); box != m_Boxes.end(); box++) {
        // Run the physics
        (*box)->getBody()->calculateDerivedData();
        (*box)->getBody()->integrate(timeStep);
        (*box)->calculateInternals();
    }
}

void jfBigBallisticSimulation_x86::generateContacts()
{
    // Create the ground plane data
    jfCollisionPlane_x86 plane;
    plane.setDirection(jfVector3_x86(0, 1, 0));
    plane.setOffset(0);

    // Set up the collision data structure
    m_CollisionData->reset();
    m_CollisionData->setFriction((jfReal)0.01);
    m_CollisionData->setRestitution((jfReal)0.01);
    m_CollisionData->setTolerance((jfReal)0.001);

    vector<jfBox_x86 *>::iterator box, otherBox;
    // Check ground plane collisions
    for (box = m_Boxes.begin(); box != m_Boxes.end(); box++) {
        m_CollisionDetector->boxAndHalfSpace((*(*box)), plane, m_CollisionData);
        // Check for collisions with each shot
        vector<jfAmmoRound_x86*>::iterator shot;
        for (shot = m_Ammo.begin(); shot != m_Ammo.end(); shot++) {
            if ((*shot)->getType() != UNUSED) {
                // When we get a collision, remove the shot
                if (m_CollisionDetector->boxAndSphere((*(*box)), (*(*shot)), m_CollisionData)) {
                    (*shot)->setType(UNUSED);
                }
            }
        }
    }
    // NB We aren't checking box-box collisions.
}

void jfBigBallisticSimulation_x86::run()
{
    while (m_EventHandler->handleEvents()) {
        m_CurrentShotType = m_EventHandler->getCurrentShotType();
        m_EventHandler->handleKeyEvents();
        m_LastFrameDuration = m_Timer->getTicks();
        m_Timer->start();
        jfReal timeStep = ((jfReal)m_LastFrameDuration) / 1000.0;
        if ((m_EventHandler->getMouseEvent().getStatus() == EVENT_MOUSELEFT)) {
            if (!m_MousePressedLast) {
                m_MousePressedLast = true;
                fire();
            }
        } else {
            m_MousePressedLast = false;
        }

        updateObjects(timeStep);

        generateContacts();

        vector<jfContact*> contacts;
        m_CollisionData->getContacts(&contacts);
        m_ContactResolver->resolveContacts(contacts,
            timeStep);
        m_3DGraphicsHandler->draw();

        drawDebug();
    }
}
