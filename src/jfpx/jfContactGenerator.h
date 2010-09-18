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
/*
 * =====================================================================================
 *
 *       Filename:  jfContactGenerator.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/03/10 22:37:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jonathan Frawley (jf), frawleyj@tcd.ie
 *        Company:  Computer Science Dept., Trinity College Dublin
 *
 * =====================================================================================
 */

#ifndef JFCONTACTGENERATOR_H
#define JFCONTACTGENERATOR_H


/*
 * =====================================================================================
 *        Class: jfContactGenerator
 *  Description: Interface for contact generators.
 * =====================================================================================
 */
class jfContactGenerator
{
	public:
		/* 
		 * ===  FUNCTION  ======================================================================
		 *         Name:  addContact
		 *  Description:  Fills the contact structure with the generated contact.
		 *  @return : Number of contacts written to.
		 * =====================================================================================
		 */
		virtual unsigned addContact(Contact *contact, unsigned limit) const = 0;
		
	protected:
	private:
};



#endif //JFCONTACTGENERATOR_H
