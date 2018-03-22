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
#ifndef JFFORCEREGISTRY_X86_H
#define JFFORCEREGISTRY_X86_H

#include <jfpx/jfForceRegistry.h>

class jfForceRegistry_x86 : public jfForceRegistry {
public:
    jfForceRegistry_x86();
    virtual ~jfForceRegistry_x86();

    /* Inherited methods */
    virtual void add(jfRigidBody* body, jfForceGenerator* forceGen);
    virtual void remove(jfRigidBody* body, jfForceGenerator* forceGen);
    virtual void clear();
    virtual void updateForces(jfReal timeStep);

protected:
private:
};

#endif // JFFORCEREGISTRY_X86_H
