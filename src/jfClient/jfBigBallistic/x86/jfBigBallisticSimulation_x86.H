#ifndef JFBALLISTICSIMULATION_H
#define JFBALLISTICSIMULATION_H

#include <jfSimulation/jfSimulation.h>
#include <jfEvent/jfEvent.h>
#include <jfClient/jfBigBallistic/x86/jfBigBallisticEventHandler_x86.h>
#include <jfClient/jfBigBallistic/x86/jfBigBallistic3DGraphicsHandler_x86.h>
#include <jfClient/jfBigBallistic/x86/jfAmmoRound_x86.h>
#include <jfGraphics/jfWindowManager/jfWindowManager.h>
#include <jfGraphics/jfWindowManager/jfSDL/jfSDL.h>
#include <jfGraphics/jf3DGraphics/jf3DGraphicsHandler.h>
#include <jfGraphics/jf3DGraphics/jfSDLGL/jfSDLGL3DGraphicsHandler.h>
#include <jfTimer/jfTimer.h>

#include <jfpx/jfCollisionData.h>
#include <jfpx/x86/jfContactResolver_x86.h>
#include <jfpx/x86/jfCollisionDetector_x86.h>
#include <jfpx/x86/jfCollisionPlane_x86.h>

#include <jfShape/x86/jfBox_x86.h>

#include <vector>
using namespace std;

class jfBigBallisticSimulation_x86 : public jfSimulation
{
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

