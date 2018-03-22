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
#ifndef JFBALL_H
#define JFBALL_H

#include <jfShape/jfShape.h>
#include <jfpx/jfVector3.h>
#include <jfpx/x86/jfCollisionSphere_x86.h>

typedef enum _BallType {
    JF_BALL_UNUSED,
    JF_BALL_HEAVY,
    JF_BALL_LIGHT
} BallType;

/*
 * =====================================================================================
 *        Class: jfBall
 *  Description:
 * =====================================================================================
 */
class jfBall : public jfShape, public jfCollisionSphere_x86 {
public:
    jfBall();

    virtual ~jfBall();

    /*-----------------------------------------------------------------------------
		 *  Inherited Methods
		 *-----------------------------------------------------------------------------*/
    virtual void render() const = 0;

    /*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
    virtual BallType getType() { return m_Type; }
    virtual void setType(BallType val) { m_Type = val; }

    virtual void setState(BallType ballType, const jfVector3& pos) = 0;

protected:
    BallType m_Type;

private:
};

#endif // JFBALL_H
