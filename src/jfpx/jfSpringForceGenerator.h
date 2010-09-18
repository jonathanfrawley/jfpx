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
#ifndef JFSPRINGFORCEGENERATOR_H
#define JFSPRINGFORCEGENERATOR_H

#include <jfpx/jfForceGenerator.h>

class jfSpringForceGenerator : public jfForceGenerator
{
	public:
		jfSpringForceGenerator();
		jfSpringForceGenerator(jfVector3* connectionPoint,
								jfRigidBody* other,
								jfVector3* otherConnectionPoint,
								jfReal springConstant,
								jfReal restLength);
		virtual ~jfSpringForceGenerator();

		/* Interface */
		virtual void updateForce(jfRigidBody* body, jfReal duration) = 0;

	protected:
		jfVector3* m_ConnectionPoint; //local coords
		jfVector3* m_OtherConnectionPoint; //local coords
		jfRigidBody* m_Other;
		jfReal m_SpringConstant; //k
		jfReal m_RestLength;
	private:


};

#endif
