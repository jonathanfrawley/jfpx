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
#ifndef JFFLIGHTEVENTHANDLER_X86_H
#define JFFLIGHTEVENTHANDLER_X86_H

#include <jfEvent/jfEventHandler.h>

#include <jfpx/x86/jfQuaternion_x86.h>
#include <jfpx/x86/jfVector3_x86.h>
#include <jfpx/jfRigidBody.h>

class jfFlightEventHandler_x86 : public jfEventHandler
{
    public:
        jfFlightEventHandler_x86();
        virtual ~jfFlightEventHandler_x86();
        /* Inherited methods */
        virtual void handleKeyEvents();

		void resetAircraft();

        /* Getters and setters */
        void setAircraft(jfRigidBody* val) { aircraft = val; }
        void setRudderControl(jfReal* val) { rudderControl = val; }
        void setLeftWingControl(jfReal* val) { leftWingControl = val; }
        void setRightWingControl(jfReal* val) { rightWingControl = val; }
    protected:
        jfRigidBody* aircraft; //Reference only
        jfReal* rudderControl; //Reference only
        jfReal* leftWingControl; //Reference only
        jfReal* rightWingControl; //Reference only
    private:
};

#endif // JFFLIGHTEVENTHANDLER_X86_H
