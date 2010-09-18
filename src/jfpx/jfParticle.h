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
#ifndef JFPARTICLE_H
#define JFPARTICLE_H

#include <jfpx/jfPrecision.h>
#include <jfpx/jfVector3.h>

class jfParticle
{
    public:
        jfParticle();
        virtual ~jfParticle();

        /* Interface */
        virtual void integrate( jfReal timeStep ) = 0;

        /* Own Functions */
        virtual void clearAccumulator() { m_ForceAccum->clear(); }

        /* Getters and Setters */
        virtual jfVector3* getPos() { return m_Pos; }
        virtual void setPos(jfVector3* val) { delete m_Pos; m_Pos = val; }
        virtual jfVector3* getVel() { return m_Vel; }
        virtual void setVel(jfVector3* val) { delete m_Vel; m_Vel = val; }
        virtual jfVector3* getAccel() { return m_Accel; }
        virtual void setAccel(jfVector3* val) { delete m_Accel; m_Accel = val; }
        virtual jfReal getDamping() { return m_Damping; }
        virtual void setDamping(jfReal val) { m_Damping = val; }
        virtual jfReal getInverseMass() { return m_InverseMass; }
        virtual void setInverseMass(jfReal val) { m_InverseMass = val; }
        virtual jfReal getMass() { return ((jfReal)(1.0)/m_InverseMass); }
        virtual void setMass(jfReal val) { m_InverseMass = (((jfReal)1.0)/val); }

    protected:
        jfVector3* m_Pos;
        jfVector3* m_Vel;
        jfVector3* m_Accel;
        jfVector3* m_ForceAccum;
        jfReal m_Damping;
        jfReal m_InverseMass; //Inverse mass due to zero division, need to represent infinte mass, etc.
    private:
};

#endif // JFPARTICLE_H
