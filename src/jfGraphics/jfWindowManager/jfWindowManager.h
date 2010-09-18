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

#ifndef JF_WINDOW_MANAGER_FACTORY_H
#define JF_WINDOW_MANAGER_FACTORY_H

#include <jfEvent/jfEvent.h>

#include <string>

using std::string;

typedef enum{
    JFK_a,
    JFK_w,
    JFK_s,
    JFK_d,
    JFK_e,
	JFK_q,
	JFK_x,
	JFK_r,
    JFK_0,
    JFK_1,
    JFK_2,
    JFK_3,
    JFK_4,
    JFK_5,
    JFK_6,
    JFK_7,
    JFK_8,
    JFK_9,
    JFK_NULL
} jfKey;

const int JF_MAX_KEY_VALUE=(int)JFK_NULL;

class jfWindowManager
{
	public:
        virtual bool init() = 0;
		virtual bool createWindow(int width, int height, int bpp, bool fullscreen, const string& title) = 0;
		virtual void setWindowSize(int width, int height) = 0;
		virtual int getWindowHeight() = 0;
		virtual int getWindowWidth() = 0;
		virtual void pollEvent(jfEvent* event) = 0;
		virtual bool isMouseLeftPressed() = 0;
		virtual bool isMouseRightPressed() = 0;
	private:
};

#endif
