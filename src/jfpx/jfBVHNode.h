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
#ifndef  JFBVHNODE_H
#define  JFBVHNODE_H

#include <jfpx/jfBoundingVolume.h>
#include <jfpx/jfRigidBody.h>

typedef struct _jfPotentialContact
{
	jfRigidBody* body[2];
} jfPotentialContact;

/*
 * =====================================================================================
 *        Class: jfBVHNode
 *  Description:
 * =====================================================================================
 */
class jfBVHNode
{
	public:
		jfBVHNode(jfBVHNode* parent,
					const jfBoundingVolume& volume,
					jfRigidBody* body=0);

		~jfBVHNode();

		/*-----------------------------------------------------------------------------
		 *  Implemented methods
		 *-----------------------------------------------------------------------------*/
		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  isLeaf
		 *  Description:  Returns true if the node is a leaf node, false otherwise.
		 * =====================================================================================
		 */
		virtual bool isLeaf() const
		{
			return (m_Body!=0);
		}

		/*-----------------------------------------------------------------------------
		 *  Interface
		 *-----------------------------------------------------------------------------*/
		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getPotentialContacts
		 *  Description:  Checks the potential contacts from this node downwards.
		 *  @return : Number of potential contacts found.
		 * =====================================================================================
		 */
        virtual unsigned getPotentialContacts(jfPotentialContact* contacts,
												  unsigned limit) const = 0;


		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  insert
		 *  Description:  Inserts the given body and volume into the hierarchy.
		 * =====================================================================================
		 */
		virtual void insert(jfRigidBody* newBody, const jfBoundingVolume& newVolume) = 0;


		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  overlaps
		 *  Description:  Checks for overlap between this and the passed in node.
		 * =====================================================================================
		 */
        virtual bool overlaps(const jfBVHNode& other) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getPotentialContactsWith
		 *  Description:
		 * =====================================================================================
		 */
        virtual unsigned getPotentialContactsWith(const jfBVHNode* other,
														jfPotentialContact* contacts,
														unsigned limit) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  recalculateBoundingVolume
		 *  Description:  Recalculate Bounding volume of the volume to include children.
		 * =====================================================================================
		 */
		virtual void recalculateBoundingVolume(bool recurse = true) = 0;

		/*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
		virtual jfBVHNode* getParent() const { return m_Parent; }
		virtual void setParent(jfBVHNode* volume) { m_Parent = volume; }

		virtual jfBoundingVolume* getVolume() const { return m_Volume; }
		virtual void setVolume(jfBoundingVolume* volume) { m_Volume = volume; }

		//TODO: Bounds check
		virtual jfBVHNode* getChild(unsigned index) const { return m_Children[index]; }
		virtual void setChild(unsigned index, jfBVHNode* child) { m_Children[index] = child; }

		virtual jfRigidBody* getBody() const { return m_Body; }
		virtual void setBody(jfRigidBody* body) { m_Body = body; }

	protected:
		jfBVHNode* m_Children[2]; //Binary tree
		jfBVHNode* m_Parent;
		jfBoundingVolume* m_Volume; //Encompasses all children of node
		jfRigidBody* m_Body; //Only leaf nodes have a body

	private:
};


#endif   // JFBVHNODE_H
