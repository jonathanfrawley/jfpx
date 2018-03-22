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
#include "jfBVHNode_x86.h"

jfBVHNode_x86::jfBVHNode_x86(jfBVHNode* parent,
    const jfBoundingVolume& volume,
    jfRigidBody* body)
    : jfBVHNode(parent, volume, body)
{
}

unsigned jfBVHNode_x86::getPotentialContacts(jfPotentialContact* contacts,
    unsigned limit) const
{
    // Early out if we don't have the room for contacts, or
    // if we're a leaf node.
    if (isLeaf() || limit == 0) {
        return 0;
    }

    // Get the potential contacts of one of our m_Children with
    // the other
    return m_Children[0]->getPotentialContactsWith(
        m_Children[1], contacts, limit);
}

void jfBVHNode_x86::insert(jfRigidBody* newBody, const jfBoundingVolume& newVolume)
{
    // If we are a leaf, then the only option is to spawn two
    // new m_Children and place the new body in one.
    if (isLeaf()) {
        // Child one is a copy of us.
        m_Children[0] = new jfBVHNode_x86(this, (*m_Volume), m_Body);

        // Child two holds the new body
        m_Children[1] = new jfBVHNode_x86(this, newVolume, newBody);

        // And we now loose the body (we're no longer a leaf)
        m_Body = NULL;

        // We need to recalculate our bounding volume
        recalculateBoundingVolume();
    }
    // Otherwise we need to work out which child gets to keep
    // the inserted body. We give it to whoever would grow the
    // least to incorporate it.
    else {
        if (m_Children[0]->getVolume()->getGrowth(newVolume) < m_Children[1]->getVolume()->getGrowth(newVolume)) {
            m_Children[0]->insert(newBody, newVolume);
        } else {
            m_Children[1]->insert(newBody, newVolume);
        }
    }
}

bool jfBVHNode_x86::overlaps(const jfBVHNode& other) const
{
    return m_Volume->overlaps(*other.getVolume());
}

unsigned jfBVHNode_x86::getPotentialContactsWith(const jfBVHNode* other,
    jfPotentialContact* contacts,
    unsigned limit) const
{
    // Early out if we don't overlap or if we have no room
    // to report contacts
    if (!overlaps(*other) || limit == 0) {
        return 0;
    }

    // If we're both at leaf nodes, then we have a potential contact
    if (isLeaf() && other->isLeaf()) {
        contacts->body[0] = m_Body;
        contacts->body[1] = other->getBody();
        return 1;
    }

    // Determine which node to descend into. If either is
    // a leaf, then we descend into the other. If both are branches,
    // then we use the one with the largest size.
    if (other->isLeaf() || ((!isLeaf()) && (m_Volume->getSize() >= other->getVolume()->getSize()))) {
        // Recurse into ourself
        unsigned count = m_Children[0]->getPotentialContactsWith(
            other, contacts, limit);

        // Check we have enough slots to do the other side too
        if (limit > count) {
            return count + m_Children[1]->getPotentialContactsWith(other, contacts + count, limit - count);
        } else {
            return count;
        }
    } else {
        // Recurse into the other node
        unsigned count = getPotentialContactsWith(
            other->getChild(0), contacts, limit);

        // Check we have enough slots to do the other side too
        if (limit > count) {
            return count + getPotentialContactsWith(
                               other->getChild(1), contacts + count, limit - count);
        } else {
            return count;
        }
    }
}

void jfBVHNode_x86::recalculateBoundingVolume(bool recurse)
{
    if (isLeaf()) {
        return;
    }

    // Use the bounding volume combining constructor.
    m_Volume->recalculateBoundingVolume(*m_Children[0]->getVolume(), *m_Children[1]->getVolume());

    // Recurse up the tree
    if (m_Parent) {
        m_Parent->recalculateBoundingVolume(true);
    }
}
