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
#include "jfBVHNode.h"

jfBVHNode::jfBVHNode(jfBVHNode* m_Parent,
						const jfBoundingVolume& volume,
						jfRigidBody* body)
            :
				m_Parent(m_Parent),
				m_Body(body)
{
    (*m_Volume) = volume;
	m_Children[0] = 0;
	m_Children[1] = 0;
}

jfBVHNode::~jfBVHNode()
{
	// If we don't have a m_Parent, then we ignore the sibling
	// processing
	if (m_Parent)
	{
		// Find our sibling
		jfBVHNode* sibling;
		if (m_Parent->m_Children[0] == this)
		{
			sibling = m_Parent->getChild(1);
		}
		else
		{
			sibling = m_Parent->getChild(0);
		}

		// Write its data to our m_Parent
		m_Parent->setVolume(sibling->getVolume());
		m_Parent->setBody(sibling->getBody());
		m_Parent->setChild(0,sibling->getChild(0));
		m_Parent->setChild(1,sibling->getChild(1));

		// Delete the sibling (we blank its m_Parent and
		// m_Children to avoid processing/deleting them)
		sibling->setParent(0);
		sibling->setBody(0);
		sibling->setChild(0,0);
		sibling->setChild(1,0);
		delete sibling;

		// Recalculate the m_Parent's bounding volume
		m_Parent->recalculateBoundingVolume();
	}

	// Delete our m_Children (again we remove their
	// m_Parent data so we don't try to process their siblings
	// as they are deleted).
	if (m_Children[0]) {
		m_Children[0]->m_Parent = NULL;
		delete m_Children[0];
	}
	if (m_Children[1]) {
		m_Children[1]->m_Parent = NULL;
		delete m_Children[0];
	}
}
