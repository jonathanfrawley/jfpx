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
#include "jfBoxesAndBallsSimulation_x86.h"

jfBoxesAndBallsSimulation_x86::jfBoxesAndBallsSimulation_x86()
{
    m_PhysicsFactory = new jfFactory_x86();
    m_ShapeFactory = new jfShapeFactory_x86();
    m_EventHandler = new jfBoxesAndBallsEventHandler_x86();
    m_WindowManager = new jfSDL();
    m_3DGraphicsHandler = new jfBoxesAndBalls3DGraphicsHandler_x86();
    m_Timer = new jfTimer();

    unsigned i;
    for (i = 0; i < m_MaxBalls; i++) {
        m_Balls.push_back(m_ShapeFactory->makeBall());
    }
    for (i = 0; i < m_MaxBoxes; i++) {
        m_Boxes.push_back(m_ShapeFactory->makeBox());
    }
    m_CollisionData = m_PhysicsFactory->makeCollisionData();
    m_ContactResolver = m_PhysicsFactory->makeContactResolver(m_MaxContacts);
    m_CollisionDetector = m_PhysicsFactory->makeCollisionDetector();
    m_Plane = m_PhysicsFactory->makeCollisionPlane();
    m_Cam = new jfFPSCamera();
#ifdef PERF_TIMING
    m_PerformanceTimer = new jfPerformanceTimer();
#endif
}

jfBoxesAndBallsSimulation_x86::~jfBoxesAndBallsSimulation_x86()
{
    delete m_EventHandler;
    delete m_WindowManager;
    delete m_3DGraphicsHandler;
    delete m_Timer;
    delete m_Plane;
    delete m_CollisionData;
    delete m_ContactResolver;
    delete m_CollisionDetector;
    delete m_PhysicsFactory;
    delete m_ShapeFactory;
    delete m_Cam;
#ifdef PERF_TIMING
    delete m_PerformanceTimer;
#endif
}

void jfBoxesAndBallsSimulation_x86::drawDebug()
{
    if (!m_RenderDebugInfo) {
        return;
    }

    // Recalculate the contacts, so they are current (in case we're
    // paused, for example).
    //generateContacts();
    vector<jfContact*> contacts;
    m_CollisionData->getContacts(&contacts);
    m_3DGraphicsHandler->drawDebug(contacts);
}

bool jfBoxesAndBallsSimulation_x86::init()
{
    if (!m_WindowManager->createWindow(800, 600, 32, false, "Ballistic Simulation")) {
        return false;
    }

    m_Cam->setPos(jfVector3_x86(0, 10, 50));
    m_Cam->setRot(jfVector3_x86(0, 0, 0));
    m_EventHandler->setWindowManager(m_WindowManager);
    //    m_EventHandler->setSimulation(this);
    m_EventHandler->setCam(m_Cam);
    m_3DGraphicsHandler->init();
    m_3DGraphicsHandler->setBalls(&m_Balls);
    m_3DGraphicsHandler->setBoxes(&m_Boxes);
    m_3DGraphicsHandler->setCam(m_Cam);

    vector<jfBall*>::iterator ball;
    jfReal y = 1.f;
    for (ball = m_Balls.begin(); ball != m_Balls.end(); ball++) {
        jfVector3_x86 pos = jfVector3_x86(y * 0.1, y, 0);
        (*ball)->setState(JF_BALL_HEAVY, pos);
        (*ball)->setRadius(1.0);
        (*ball)->getBody()->setAccel(jfVector3_x86(0, -9.8, 0));
        y += 3;
        //(*ball)->setType(JF_BALL_UNUSED);
    }
    y = 10;
    // Initialise the boxes
    vector<jfBox*>::iterator box;
    for (box = m_Boxes.begin(); box != m_Boxes.end(); box++) {
        (*box)->init();
        jfVector3_x86 pos = jfVector3_x86(0, y, 3);
        (*box)->setState(JF_BOX_HEAVY, pos);
        y += 3;
    }

    m_Timer->start();
    m_MousePressedLast = false;

#ifdef PERF_TIMING
    //Remove performance timing file from before.
    remove(timingFilename);
#endif

    return true;
}

void jfBoxesAndBallsSimulation_x86::fire()
{
    /*    // Find the first available round.
    vector<jfAmmoRound_x86*>::iterator shot;
    for (shot = m_Ammo.begin(); shot != m_Ammo.end() ; shot++)
    {
        if ((*shot)->getType() == UNUSED)
        {
            break;
        }
    }
    if(shot == m_Ammo.end())
    {
        return;
    }
    //cout <<"Setting Shot"<<endl;
    // Set the shot
    (*shot)->setState(m_CurrentShotType);
    */
}

void jfBoxesAndBallsSimulation_x86::updateObjects(jfReal timeStep)
{
    // Update the physics of each particle in turn
    vector<jfBall*>::iterator ball;
    for (ball = m_Balls.begin(); ball != m_Balls.end(); ball++) {
        if ((*ball)->getType() != JF_BALL_UNUSED) {
            //jfVector3_x86 bodyPos;

            // Run the physics
            (*ball)->getBody()->calculateDerivedData();
            (*ball)->getBody()->integrate(timeStep);
            (*ball)->calculateInternals();

            //(*ball)->getBody()->getPos(&bodyPos);
        }
    }

    vector<jfBox*>::iterator box;
    // Update the boxes
    for (box = m_Boxes.begin(); box != m_Boxes.end(); box++) {
        if ((*box)->getType() != JF_BOX_UNUSED) {
            // Run the physics
            (*box)->getBody()->calculateDerivedData();
            (*box)->getBody()->integrate(timeStep);
            (*box)->calculateInternals();
        }
    }
}

void jfBoxesAndBallsSimulation_x86::generateContacts()
{
    vector<jfBox *>::iterator box, otherBox;
    vector<jfBall *>::iterator ball, otherBall;

    m_Plane->setDirection(jfVector3_x86(0, 1, 0));
    m_Plane->setOffset(0);

    // Set up the collision data structure
    m_CollisionData->reset();
    m_CollisionData->setFriction((jfReal)0.4);
    m_CollisionData->setRestitution((jfReal)0.0001);
    m_CollisionData->setTolerance((jfReal)0.001);

    //m_CollisionDetector->boxAndBoxBatch(m_Boxes, m_CollisionData);

    for (box = m_Boxes.begin(); box != m_Boxes.end(); box++) {
        // Check ground plane collisions
        m_CollisionDetector->boxAndHalfSpace((*(*box)), (*m_Plane), m_CollisionData);

        // Check for collisions with each ball
        for (ball = m_Balls.begin(); ball != m_Balls.end(); ball++) {
            if (m_CollisionDetector->boxAndSphere((*(*box)), (*(*ball)), m_CollisionData)) {
                cout << "Box and Sphere Collision." << endl;
            }
        }
        /*
        //Check for collisions with other boxes
        for(otherBox = m_Boxes.begin(); otherBox != m_Boxes.end();otherBox++)
        {
            if(box != otherBox)
            {
                m_CollisionDetector->boxAndBox(*(*box), (*(*otherBox)), m_CollisionData);
            }
        }
        */
    }
    m_CollisionDetector->boxAndBoxBatch(m_Boxes, m_CollisionData);
    m_CollisionDetector->sphereAndSphereBatch(m_Balls, m_CollisionData);

    // Check for collisions with each ball
    for (ball = m_Balls.begin(); ball != m_Balls.end(); ball++) {
        //Check for collisions with ground
        m_CollisionDetector->sphereAndHalfSpace((*(*ball)), (*m_Plane), m_CollisionData);
        /*
        //Check for collisions with other balls
        for(otherBall = m_Balls.begin(); otherBall != m_Balls.end(); otherBall++)
        {
            if(ball != otherBall)
            {
                if (m_CollisionDetector->sphereAndSphere((*(*ball)), (*(*otherBall)), m_CollisionData))
                {
                    cout<<"Sphere and Sphere Collision."<<endl;
                }
            }
        }
*/
    }
}

void jfBoxesAndBallsSimulation_x86::run()
{
    while (m_EventHandler->handleEvents()) {
        m_EventHandler->handleKeyEvents();
        m_EventHandler->handleMouseEvents();

        m_LastFrameDuration = m_Timer->getTicks();
        m_Timer->start();
        //jfReal timeStep = ((jfReal)m_LastFrameDuration)/1000.0;

        jfReal timeStep = 0.01; // Fix it so both x86 and x86 versions will have around same amounts of work to do on each frame.

        if ((m_EventHandler->getMouseEvent().getStatus() == EVENT_MOUSELEFT)) {
            if (!m_MousePressedLast) {
                m_MousePressedLast = true;
                fire();
            }
        } else {
            m_MousePressedLast = false;
        }

        // start timer
        //        gettimeofday(&t1, NULL);

        updateObjects(timeStep);
/*
        // stop timer
        gettimeofday(&t2, NULL);
        m_ElapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
        m_ElapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
        char buf[255];
        sprintf(buf, "%d\n", m_ElapsedTime);
        logToFile(buf, "CollisionDetectionTimes.dat");
        //gettimeofday(&t1, NULL);
*/
#ifdef PERF_TIMING
        m_PerformanceTimer->start();
#endif
        generateContacts();
#ifdef PERF_TIMING
        m_PerformanceTimer->stop();
        m_ElapsedTime = m_PerformanceTimer->getElapsedTime();
        char buf[255];
        sprintf(buf, "%lf\n", m_ElapsedTime);
        logToFile(buf, timingFilename);
#endif

        vector<jfContact*> contacts; // = m_CollisionData->getContacts();
        m_CollisionData->getContacts(&contacts);
        //cout <<"contacts.size() is : " <<contacts.size()<<endl;
        m_ContactResolver->resolveContacts(contacts,
            timeStep);

        /*m_ContactResolver->resolveContacts(m_CollisionData->getContactArray(),
                                            m_CollisionData->getContactCount(),
                                            timeStep);
                                            */
        m_3DGraphicsHandler->draw();

        //drawDebug();
    }
}
