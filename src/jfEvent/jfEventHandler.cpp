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
#include "jfEventHandler.h"

jfEventHandler::jfEventHandler() : m_WindowManager(0)
{
	events = new vector<jfEvent>(INIT_EVENT_VEC_SIZE);
	int i;
	for(i=0;i<JF_MAX_KEY_VALUE;i++)
	{
		keys[i]=0;
	}
}

jfEventHandler::~jfEventHandler()
{
	delete events;
}

void jfEventHandler::addWmEvents(jfWindowManager* windowManager)
{
	windowManager->pollEvent(&tempEvent);
	while (tempEvent.getStatus() != EVENT_NULL)
	{
	    jfEvent newEvent = tempEvent;
		events->push_back(newEvent);
		windowManager->pollEvent(&tempEvent);
	}
}

bool jfEventHandler::handleEvent(jfEvent event)
{
	switch (event.getStatus())
	{
		case EVENT_QUIT:
		{
			return false;
		}
		case EVENT_KEYDOWN:
		{
			keys[event.getKeyNum()] = 1;
			break;
		}
		case EVENT_KEYUP:
		{
			keys[event.getKeyNum()] = 0;
			break;
		}
		case EVENT_NULL:
		{
			break;
		}
		case EVENT_DONE:
		{
		    break;
		}
		case EVENT_NONE:
		{
		    break;
		}
	}
	return true;
}

bool jfEventHandler::handleEvents()
{
    addWmEvents(m_WindowManager);
    while( ! events->empty() )
	{
	    jfEvent ev = events->back();
	    events->pop_back();
		if (! handleEvent(ev))
		{
			return false; //quit signalled
		}
	}
    return true;
}

jfKey jfEventHandler::isKeyPressed(int i)
{
    for(;i<JF_MAX_KEY_VALUE;i++)
	{
		if(keys[i])
		{
                return (jfKey)i;
		}
	}
	return JFK_NULL;
}

void jfEventHandler::setWindowManager(jfWindowManager* windowManager)
{
    m_WindowManager = windowManager;
}

jfEvent jfEventHandler::getMouseEvent()
{
    if(m_WindowManager->isMouseLeftPressed())
    {
        return jfEvent(EVENT_MOUSELEFT);
    }
    if(m_WindowManager->isMouseRightPressed())
    {
        return jfEvent(EVENT_MOUSERIGHT);
    }
    return jfEvent(EVENT_NULL);
}
