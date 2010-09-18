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
#ifndef  JFBOUNDINGSPHERE_H
#define  JFBOUNDINGSPHERE_H

#include <jfpx/jfBoundingVolume.h>
#include <jfpx/jfVector3.h>

/*
 * =====================================================================================
 *        Class: jfBoundingSphere
 *  Description:
 * =====================================================================================
 */
class jfBoundingSphere : public jfBoundingVolume
{
	public:
		jfBoundingSphere();

        jfBoundingSphere(const jfVector3& centre, jfReal radius);

        jfBoundingSphere(const jfBoundingVolume& one, const jfBoundingVolume& two);

		~jfBoundingSphere();

		/*-----------------------------------------------------------------------------
		 *  Implemented Methods
		 *-----------------------------------------------------------------------------*/
		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getSize
		 *  Description:  Returns the volume of the sphere.
		 * =====================================================================================
		 */
		virtual jfReal getSize() const
		{
			return (((jfReal)1.333333) * JF_MATH_PI * m_Radius * m_Radius * m_Radius);
		}

		/*-----------------------------------------------------------------------------
		 *  Inherited Methods
		 *-----------------------------------------------------------------------------*/
		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  overlaps
		 *  Description:  Returns true if this sphere overlaps with the other one, false
		 *  otherwise.
		 * =====================================================================================
		 */
        virtual bool overlaps(const jfBoundingVolume& other) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  getGrowth
		 *  Description:  Reports how much the bounding sphere would grow to incorporate the
		 *  given bounding sphere.
		 * =====================================================================================
		 */
		virtual jfReal getGrowth(const jfBoundingVolume& other) const = 0;

		/*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  recalculateBoundingVolume
		 *  Description:  Recalculates the bounding volume to include the two other spheres
		 * =====================================================================================
		 */
		virtual void recalculateBoundingVolume(const jfBoundingVolume& one,
                                                const jfBoundingVolume& two) = 0;

		/*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
		virtual void getCentre(jfVector3* centre) const { (*centre) = (*m_Centre); }

		virtual jfReal getRadius() const { return m_Radius; }

	protected:
		jfVector3* m_Centre;
		jfReal m_Radius;
	private:
};

#endif   // JFBOUNDINGSPHERE_H
