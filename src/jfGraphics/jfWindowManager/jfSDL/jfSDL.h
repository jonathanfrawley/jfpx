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
#ifndef JF_SDL_H
#define JF_SDL_H

#include <jfGraphics/jfWindowManager/jfWindowManager.h>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <string>
#include <iostream>

using namespace std;

class jfSDL : public jfWindowManager
{
	public:
		jfSDL();
		virtual ~jfSDL();
		bool init();
		bool createWindow(int width, int height, int bpp, bool fullscreen, const string& title);
		void setWindowSize(int width, int height);
		int getWindowHeight();
		int getWindowWidth();
		void pollEvent(jfEvent* event);
        bool isMouseRightPressed();
        bool isMouseLeftPressed();
	private:
        jfKey translateToJfKey(int sym);
		int m_Width;
		int m_Height;
		int m_Bpp;
		bool m_Fullscreen;
		string m_Title;
		SDL_Surface* m_Screen;
};

#endif
