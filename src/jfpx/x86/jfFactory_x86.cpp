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
#include "jfFactory_x86.h"

jfFactory_x86::jfFactory_x86()
	:
		jfFactory()
{
}

jfVector3* jfFactory_x86::makeVector3() const
{
	return new jfVector3_x86();
}

jfMatrix3* jfFactory_x86::makeMatrix3() const
{
	return new jfMatrix3_x86();
}

jfMatrix4* jfFactory_x86::makeMatrix4() const
{
	return new jfMatrix4_x86();
}

jfQuaternion* jfFactory_x86::makeQuaternion() const
{
	return new jfQuaternion_x86();
}

jfRigidBody* jfFactory_x86::makeRigidBody() const
{
	return new jfRigidBody_x86();
}

jfCollisionDetector* jfFactory_x86::makeCollisionDetector() const
{
	return new jfCollisionDetector_x86();
}

jfContactResolver* jfFactory_x86::makeContactResolver() const
{
	return new jfContactResolver_x86();
}

jfContactResolver* jfFactory_x86::makeContactResolver(unsigned iterations
                , jfReal velocityEpsilion
                , jfReal positionEpsilon) const
{
    return new jfContactResolver_x86(iterations, velocityEpsilion, positionEpsilon);
}

jfCollisionPlane* jfFactory_x86::makeCollisionPlane() const
{
	return new jfCollisionPlane_x86();
}

jfCollisionBox* jfFactory_x86::makeCollisionBox() const
{
	return new jfCollisionBox_x86();
}

jfCollisionSphere* jfFactory_x86::makeCollisionSphere() const
{
	return new jfCollisionSphere_x86();
}

jfContact* jfFactory_x86::makeContact() const
{
	return new jfContact_x86();
}

jfIntersectionTester* jfFactory_x86::makeIntersectionTester() const
{
	return new jfIntersectionTester_x86();
}
