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
#ifndef JFBOX_H
#define JFBOX_H

#include <jfShape/jfShape.h>
#include <jfpx/x86/jfCollisionBox_x86.h>

typedef enum _BoxType {
    JF_BOX_UNUSED,
    JF_BOX_HEAVY,
    JF_BOX_LIGHT
} BoxType;

/*
 * =====================================================================================
 *        Class: jfBox
 *  Description:
 * =====================================================================================
 */
class jfBox : public jfShape, public jfCollisionBox_x86 {
public:
    jfBox();

    virtual ~jfBox();

    /*-----------------------------------------------------------------------------
		 *  Interface
		 *-----------------------------------------------------------------------------*/
    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  setState
		 *  Description:  Sets the box to a position
		 * =====================================================================================
		 */
    virtual void setState(BoxType type, const jfVector3& pos) = 0;

    /*
		 * ===  FUNCTION  ======================================================================
		 *         Name:  init
		 *  Description:  Initialise the box.
		 * =====================================================================================
		 */
    virtual void init() = 0;

    /*-----------------------------------------------------------------------------
		 *  Inherited Methods
		 *-----------------------------------------------------------------------------*/
    virtual void render() const = 0;

    /*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
    virtual BoxType getType() { return m_Type; }
    virtual void setType(BoxType type) { m_Type = type; }

protected:
    /*-----------------------------------------------------------------------------
		 *  Member Variables
		 *-----------------------------------------------------------------------------*/
    BoxType m_Type;

private:
};

#endif // JFBOX_H
