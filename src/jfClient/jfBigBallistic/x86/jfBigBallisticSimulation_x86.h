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
#ifndef JFBALLISTICSIMULATION_H
#define JFBALLISTICSIMULATION_H

#include <jfSimulation/jfSimulation.h>
//#include <jfEvent/jfEventHandler.h>
#include <jfClient/jfBigBallistic/x86/jfAmmoRound_x86.h>
#include <jfClient/jfBigBallistic/x86/jfBigBallistic3DGraphicsHandler_x86.h>
#include <jfClient/jfBigBallistic/x86/jfBigBallisticEventHandler_x86.h>
#include <jfClient/jfBigBallistic/x86/jfBox_x86.h>
#include <jfEvent/jfEvent.h>
#include <jfGraphics/jf3DGraphics/jf3DGraphicsHandler.h>
#include <jfGraphics/jf3DGraphics/jfSDLGL/jfSDLGL3DGraphicsHandler.h>
#include <jfGraphics/jfWindowManager/jfSDL/jfSDL.h>
#include <jfGraphics/jfWindowManager/jfWindowManager.h>
#include <jfTimer/jfTimer.h>

#include <jfpx/jfCollisionData.h>
#include <jfpx/x86/jfCollisionDetector_x86.h>
#include <jfpx/x86/jfCollisionPlane_x86.h>
#include <jfpx/x86/jfContactResolver_x86.h>

#include <vector>
using namespace std;

class jfBigBallisticSimulation_x86 : public jfSimulation {
public:
    jfBigBallisticSimulation_x86();
    virtual ~jfBigBallisticSimulation_x86();
    bool init();
    void run();
    void fire();
    void updateObjects(jfReal timeStep);
    void generateContacts();
    void drawDebug();

protected:
    const static unsigned m_MaxContacts = 8;
    const static unsigned m_MaxBoxes = 2;
    const static bool m_RenderDebugInfo = true;
    jfBigBallisticEventHandler_x86* m_EventHandler;
    jfWindowManager* m_WindowManager;
    jfBigBallistic3DGraphicsHandler_x86* m_3DGraphicsHandler;
    jfTimer* m_Timer;
    int m_LastFrameDuration;
    vector<jfAmmoRound_x86*> m_Ammo;
    vector<jfBox_x86*> m_Boxes;
    bool m_MousePressedLast;
    ShotType m_CurrentShotType;
    //vector<jfContact*> m_Contacts;
    jfCollisionData* m_CollisionData;
    jfContactResolver* m_ContactResolver;
    jfCollisionDetector* m_CollisionDetector;
};

#endif
