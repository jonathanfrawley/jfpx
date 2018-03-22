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
    void setType(ShotType val) { m_Type = val; }
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
