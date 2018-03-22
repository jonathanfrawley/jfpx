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
