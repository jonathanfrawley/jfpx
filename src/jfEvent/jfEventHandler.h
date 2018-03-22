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

#ifndef JF_EVENT_HANDLER_H
#define JF_EVENT_HANDLER_H

#include <jfEvent/jfEvent.h>
#include <jfGraphics/jfWindowManager/jfWindowManager.h>

#include <iostream>
#include <vector>

using namespace std;

const int INIT_EVENT_VEC_SIZE = 0;

class jfEventHandler {
public:
    jfEventHandler();
    ~jfEventHandler();
    void addWmEvents(jfWindowManager* windowManager);
    bool handleEvents();
    bool handleEvent(jfEvent event);
    jfKey isKeyPressed(int i = 0);
    void setWindowManager(jfWindowManager* windowManager);
    jfEvent getMouseEvent();

private:
    vector<jfEvent>* events;
    int keys[JF_MAX_KEY_VALUE];
    jfEvent tempEvent;
    jfWindowManager* m_WindowManager;
};

#endif
