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

#ifndef JF_EVENT_H
#define JF_EVENT_H

const int EVENT_NULL=0;
const int EVENT_QUIT=1;
const int EVENT_KEYDOWN=2;
const int EVENT_KEYUP=3;
const int EVENT_DONE=4;
const int EVENT_MOUSELEFT=5;
const int EVENT_MOUSERIGHT=6;
const int EVENT_NONE=7;

const int KEY_NULL=-1;

class jfEvent
{
	public:
		jfEvent();
		jfEvent(int);

        jfEvent(const jfEvent& other)
        {
            m_Status = other.m_Status;
            m_KeyNum = other.m_KeyNum;
        }

        jfEvent& operator=(const jfEvent& other) // Assignment operator
        {
            m_Status = other.getStatus();
            m_KeyNum = other.getKeyNum();

            return (*this);
        }

		virtual ~jfEvent();

		void nullEvent();

		void quitEvent();

		void doneEvent();

		void noEvent();

		void keyDownEvent(int keyNum);

		void keyUpEvent(int keyNum);

        /*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
		int getStatus() const
		{
            return m_Status;
		}

		int getKeyNum() const
		{
		    return m_KeyNum;
		}

	private:
		int m_Status;
		int m_KeyNum;
};

#endif
