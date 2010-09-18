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
#include <jfGraphics/jfWindowManager/jfSDL/jfSDL.h>

jfSDL::jfSDL():
	m_Width(0),
	m_Height(0),
	m_Bpp(0),
	m_Fullscreen(false)
{

}

jfSDL::~jfSDL()
{
	SDL_Quit();
}

bool jfSDL::init()
{
    if (! createWindow(800, 600, 32, false, ""))
	{
		return false;
	}
	return true;
}

bool jfSDL::createWindow(int width, int height, int bpp, bool fullscreen, const string& title)
{
	if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
	{
        fprintf(stderr,"Couldn't initialize SDL: %s\n", SDL_GetError());
		return false;
	}

	//all values are "at least"!
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Set the title.
	SDL_WM_SetCaption(title.c_str(), title.c_str());

	m_Height = height;
	m_Width = width;
	m_Title = title;
	m_Fullscreen = fullscreen;
	m_Bpp = bpp;


	// Flags tell SDL about the type of window we are creating.
	int flags = SDL_OPENGL | SDL_HWSURFACE | SDL_OPENGLBLIT;
	/*
#ifdef WIN32
	if(MessageBox(HWND_DESKTOP, "Want to use fullscreen mode?",
		"Fullscreen?", MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		flags |= SDL_FULLSCREEN;
	}
#endif
	*/

	// Create the window
	m_Screen = SDL_SetVideoMode( width, height, bpp, flags );

    if ( m_Screen == NULL ) {
        fprintf(stderr, "Couldn't set %dx%dx%d video mode: %s\n",width,height,bpp,SDL_GetError());
        exit(1);
    }

    SDL_FillRect(m_Screen, NULL, SDL_MapRGBA(m_Screen->format,0,0,0,0));

	//SDL doesn't trigger off a ResizeEvent at startup, but as we need this for OpenGL, we do this ourself
	SDL_Event resizeEvent;
	resizeEvent.type = SDL_VIDEORESIZE;
	resizeEvent.resize.w = width;
	resizeEvent.resize.h = height;

	SDL_PushEvent(&resizeEvent);

	return true;
}

void jfSDL::setWindowSize(int width, int height)
{
	m_Height = height;
	m_Width = width;

	if (height <= 0)
	{
		height = 1;
	}

	//Opengl viewport resizing
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,1.0f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int jfSDL::getWindowHeight()
{
	return m_Height;
}

int jfSDL::getWindowWidth()
{
	return m_Width;
}

jfKey jfSDL::translateToJfKey(int sym)
{
    switch(sym)
    {
        case(SDLK_a):
            return JFK_a;
        case(SDLK_w):
            return JFK_w;
        case(SDLK_s):
            return JFK_s;
        case(SDLK_d):
            return JFK_d;
        case(SDLK_e):
            return JFK_e;
        case(SDLK_q):
            return JFK_q;
        case(SDLK_x):
            return JFK_x;
        case(SDLK_r):
            return JFK_r;
        case(SDLK_0):
            return JFK_0;
        case(SDLK_1):
            return JFK_1;
        case(SDLK_2):
            return JFK_2;
        case(SDLK_3):
            return JFK_3;
        case(SDLK_4):
            return JFK_4;
        case(SDLK_5):
            return JFK_5;
        case(SDLK_6):
            return JFK_6;
        case(SDLK_7):
            return JFK_7;
        case(SDLK_8):
            return JFK_8;
        case(SDLK_9):
            return JFK_9;
        default:
            return JFK_NULL;
    }
}

void jfSDL::pollEvent(jfEvent* event)
{
	SDL_Event sdlEvent;

	if ( ! SDL_PollEvent(&sdlEvent) )
	{
		event->nullEvent();
		return;
	}
	switch (sdlEvent.type)
	{
		// Quit event
		case SDL_QUIT:
		{
			event->quitEvent();
			return;
		}
		case SDL_KEYDOWN:
		{
			SDLKey sym = sdlEvent.key.keysym.sym;

			if(sym == SDLK_ESCAPE) //Quit if escape was pressed
			{
				event->quitEvent();
				return;
			}
			jfKey jfSym = translateToJfKey(sym);
			event->keyDownEvent(jfSym);
			return;
		}
		case SDL_KEYUP:
		{
			SDLKey sym = sdlEvent.key.keysym.sym;
			jfKey jfSym = translateToJfKey(sym);
			event->keyUpEvent(jfSym);
			return;
		}
		case SDL_VIDEORESIZE:
		{
			//the window has been resized so we need to set up our viewport and projection according to the new size
			setWindowSize(sdlEvent.resize.w, sdlEvent.resize.h);
			event->doneEvent();
			return;
		}
		// Default case
		default:
		{
			event->noEvent();
			return;
		}
	}
}

bool jfSDL::isMouseLeftPressed()
{
    if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_RMASK)
    {
        return true;
    }
    return false;
}

bool jfSDL::isMouseRightPressed()
{
    if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LMASK)
    {
        return true;
    }
    return false;
}

