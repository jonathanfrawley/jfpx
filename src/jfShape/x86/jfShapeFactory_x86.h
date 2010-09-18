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

#ifndef  JFSHAPEFACTORY_X86_H
#define  JFSHAPEFACTORY_X86_H

#include <jfShape/jfShapeFactory.h>

#include <jfShape/x86/jfBox_x86.h>
#include <jfShape/x86/jfBall_x86.h>

/*
 * =====================================================================================
 *        Class: jfShapeFactory_x86
 *  Description:
 * =====================================================================================
 */
class jfShapeFactory_x86 : public jfShapeFactory
{
	public:
		jfShapeFactory_x86();

		virtual jfBox_x86* makeBox();

		virtual jfBall_x86* makeBall();
	protected:
	private:
};


#endif   // JFSHAPEFACTORY_X86_H
