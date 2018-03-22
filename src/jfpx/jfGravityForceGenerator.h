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
#ifndef JFGRAVITYFORCEGENERATOR_H
#define JFGRAVITYFORCEGENERATOR_H

#include <jfpx/jfForceGenerator.h>
#include <jfpx/jfVector3.h>

/*
 * =====================================================================================
 *        Class:  jfGravityForceGenerator
 *  Description:
 * =====================================================================================
 */
class jfGravityForceGenerator : public jfForceGenerator {
public:
    jfGravityForceGenerator();
    jfGravityForceGenerator(jfVector3* gravity);
    virtual ~jfGravityForceGenerator();

    /* Interface */
    virtual void updateForce(jfRigidBody* body, jfReal duration) = 0;

    /* Accessors */
    void setGravity(jfVector3* val)
    {
        delete m_Gravity;
        m_Gravity = val;
    }
    jfVector3* getGravity(jfVector3* val) { return m_Gravity; }

protected:
    jfVector3* m_Gravity;

private:
};

#endif //JFGRAVITYFORCEGENERATOR_H
