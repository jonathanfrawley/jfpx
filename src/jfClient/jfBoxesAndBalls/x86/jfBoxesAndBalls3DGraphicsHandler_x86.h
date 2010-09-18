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
#ifndef JFBOXESANDBALLSSDLGL3DGRAPHICSHANDLER_H
#define JFBOXESANDBALLSSDLGL3DGRAPHICSHANDLER_H

#include <jfGraphics/jf3DGraphics/jfSDLGL/jfSDLGL3DGraphicsHandler.h>
#include <jfpx/jfContact.h>
#include <jfpx/x86/jfVector3_x86.h>
#include <jfCamera/jfFPSCamera.h>

#include <jfShape/jfBox.h>
#include <jfShape/jfBall.h>

#include <vector>
using namespace std;

class jfBoxesAndBalls3DGraphicsHandler_x86 : public jfSDLGL3DGraphicsHandler
{
    public:
        jfBoxesAndBalls3DGraphicsHandler_x86();

        virtual ~jfBoxesAndBalls3DGraphicsHandler_x86();

        virtual void initObjects();

        virtual void drawSphere(float radius,
                                  int subdivisions) const;

        virtual int loadGLTextures();

        virtual void drawObjects() const;

        virtual void setBalls(vector<jfBall*>* val) { m_Balls = val; }

        virtual void setBoxes(vector<jfBox*>* val) { m_Boxes = val; }

        virtual void drawDebug(vector<jfContact*> contacts) const;

        virtual void setCam(jfFPSCamera* val) { cam = val; }
    protected:
    private:
        GLUquadricObj* m_SphereQuadric;

        //Pointer to shapes to draw
        vector<jfBall*>* m_Balls;
        vector<jfBox*>* m_Boxes;

        GLuint m_Textures[1];

        jfFPSCamera* cam;
};

#endif // JFBOXESANDBALLSSDLGL3DGRAPHICSHANDLER_H
