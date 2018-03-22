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
#ifndef JFFLIGHTSIMULATION_X86_H
#define JFFLIGHTSIMULATION_X86_H

#include <jfClient/jfFlight/x86/jfFlight3DGraphicsHandler_x86.h>
#include <jfClient/jfFlight/x86/jfFlightEventHandler_x86.h>
#include <jfSimulation/jfSimulation.h>

#include <jfTimer/jfTimer.h>

#include <jfGraphics/jfWindowManager/jfSDL/jfSDL.h>

#include <jfpx/x86/jfAeroControlForceGenerator_x86.h>
#include <jfpx/x86/jfAeroForceGenerator_x86.h>
#include <jfpx/x86/jfForceRegistry_x86.h>
#include <jfpx/x86/jfRigidBody_x86.h>
#include <jfpx/x86/jfVector3_x86.h>

class jfFlightSimulation_x86 : public jfSimulation {
public:
    jfFlightSimulation_x86();
    virtual ~jfFlightSimulation_x86();

    void resetAircraft();
    /* Inherited from superclass */
    virtual bool init();
    virtual void run();

protected:
    /* Flight simulator vars*/
    jfVector3* m_WindSpeed;
    jfAeroControlForceGenerator* m_RightWing;
    jfAeroControlForceGenerator* m_LeftWing;
    jfAeroControlForceGenerator* m_Rudder;
    jfAeroForceGenerator* m_Tail;
    jfRigidBody* m_Aircraft;
    jfForceRegistry* m_Registry;
    jfReal m_LeftWingControl;
    jfReal m_RightWingControl;
    jfReal m_RudderControl;

    /* Essentials */
    jfFlightEventHandler_x86* m_EventHandler;
    jfFlight3DGraphicsHandler_x86* m_3DGraphicsHandler;
    jfSDL* m_WindowManager;
    jfTimer* m_Timer;
    int m_LastFrameDuration;

private:
};

#endif // JFFLIGHTSIMULATION_X86_H
