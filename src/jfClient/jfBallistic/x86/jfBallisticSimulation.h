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
#include <jfEvent/jfEvent.h>
#include <jfClient/jfBallistic/x86/jfBallisticEventHandler.h>
#include <jfClient/jfBallistic/x86/jfBallisticSDLGL3DGraphicsHandler.h>
#include <jfClient/jfBallistic/x86/jfAmmoRound.h>
#include <jfGraphics/jfWindowManager/jfWindowManager.h>
#include <jfGraphics/jfWindowManager/jfSDL/jfSDL.h>
#include <jfGraphics/jf3DGraphics/jf3DGraphicsHandler.h>
#include <jfGraphics/jf3DGraphics/jfSDLGL/jfSDLGL3DGraphicsHandler.h>
#include <jfTimer/jfTimer.h>

#include <vector>
using namespace std;

class jfBallisticSimulation : public jfSimulation
{
	public:
		jfBallisticSimulation();
		virtual ~jfBallisticSimulation();
		bool init();
		void run();
        void fire();
    private:
        jfBallisticEventHandler* m_EventHandler;
        jfWindowManager* m_WindowManager;
        jfBallisticSDLGL3DGraphicsHandler* m_3DGraphicsHandler;
        jfTimer* m_Timer;
        int m_LastFrameDuration;
        vector<jfAmmoRound*> m_Ammo;
        bool m_MousePressedLast;
};

#endif

