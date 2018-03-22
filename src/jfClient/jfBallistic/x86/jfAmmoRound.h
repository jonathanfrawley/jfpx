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

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <jfpx/jfParticle.h>
#include <jfpx/x86/jfParticle_x86.h>

enum ShotType {
    UNUSED = 0,
    PISTOL = 1,
    ARTILLERY = 2,
    FIREBALL = 3,
    LASER = 4
};

const int MAX_AMMO_ROUNDS = 160;

class jfAmmoRound {
public:
    jfAmmoRound();
    virtual ~jfAmmoRound();
    void drawSphere(float radius, int subdivisions);
    void render();

    /* Getters and Setters */
    jfParticle* getParticle() { return m_Particle; }
    ShotType getType() { return m_Type; }
    ShotType setType(ShotType val) { m_Type = val; }
    unsigned int getStartTime() { return m_StartTime; }
    void setStartTime(unsigned int val) { m_StartTime = val; }
protected:
private:
    GLUquadricObj* m_SphereQuadric;
    jfParticle* m_Particle;
    ShotType m_Type;
    unsigned m_StartTime;
};

#endif // JFAMMOROUND_H
