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
#ifndef JFBALLISTICSDLGL3DGRAPHICSHANDLER_H
#define JFBALLISTICSDLGL3DGRAPHICSHANDLER_H

#include <jfGraphics/jf3DGraphics/jfSDLGL/jfSDLGL3DGraphicsHandler.h>
#include <jfClient/jfBigBallistic/x86/jfAmmoRound_x86.h>
#include <jfClient/jfBigBallistic/x86/jfBox_x86.h>
#include <jfpx/jfContact.h>
#include <jfpx/x86/jfVector3_x86.h>

#include <vector>
using namespace std;

class jfBigBallistic3DGraphicsHandler_x86 : public jfSDLGL3DGraphicsHandler
{
    public:
        jfBigBallistic3DGraphicsHandler_x86();
        virtual ~jfBigBallistic3DGraphicsHandler_x86();
        virtual void initObjects();
        virtual int loadGLTextures();
        void drawSphere(float radius, int subdivisions) const;
        virtual void drawObjects() const;
        void setAmmo(vector<jfAmmoRound_x86*>* ammo) { m_Ammo = ammo; }
        void setBoxes(vector<jfBox_x86*>* boxes) { m_Boxes = boxes; }
        void drawDebug(vector<jfContact*> contacts);
    protected:
    private:
        GLUquadricObj* m_SphereQuadric;
        vector<jfAmmoRound_x86*>* m_Ammo;
        vector<jfBox_x86*>* m_Boxes;
        GLuint m_Textures[1];
};

#endif // JFBALLISTICSDLGL3DGRAPHICSHANDLER_H
