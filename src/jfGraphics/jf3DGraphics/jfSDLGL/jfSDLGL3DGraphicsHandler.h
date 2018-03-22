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
#ifndef JFSDLGL3DGRAPHICSHANDLER_H
#define JFSDLGL3DGRAPHICSHANDLER_H

#include <jfGraphics/jf3DGraphics/jf3DGraphicsHandler.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

class jfSDLGL3DGraphicsHandler : public jf3DGraphicsHandler {
public:
    jfSDLGL3DGraphicsHandler();
    virtual ~jfSDLGL3DGraphicsHandler();
    void init();
    /* Interface */
    virtual void initObjects() = 0;
    virtual void drawObjects() const = 0;
    void draw();

protected:
private:
};

#endif // JFSDLGL3DGRAPHICSHANDLER_H
