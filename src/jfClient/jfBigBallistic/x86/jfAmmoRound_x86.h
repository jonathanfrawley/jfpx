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
#ifndef JFAMMOROUND_H
#define JFAMMOROUND_H

#include <jfTimer/jfTimer.h>
#include <jfpx/x86/jfCollisionSphere_x86.h>
#include <jfpx/x86/jfMatrix3_x86.h>
#include <jfpx/x86/jfRigidBody_x86.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

typedef enum _ShotType {
    UNUSED = 0,
    PISTOL = 1,
    ARTILLERY = 2,
    FIREBALL = 3,
    LASER = 4
} ShotType;

const unsigned MAX_AMMO_ROUNDS = 160;

class jfAmmoRound_x86 : public jfCollisionSphere_x86 {
public:
    jfAmmoRound_x86();
    virtual ~jfAmmoRound_x86();
    void drawSphere(float radius, int subdivisions);
    void render();

    /* Getters and Setters */
    ShotType getType() { return m_Type; }
    void setType(ShotType val) { m_Type = val; }
    unsigned getStartTime() { return m_StartTime; }
    void setStartTime(unsigned val) { m_StartTime = val; }
    void setState(ShotType shotType);

protected:
private:
    GLUquadricObj* m_SphereQuadric;
    ShotType m_Type;
    unsigned m_StartTime;
    jfTimer* m_Timer;
};

#endif // JFAMMOROUND_H
