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
#include "jfTimer.h"

jfTimer::jfTimer():m_StartTicks(0),
                    m_PausedTicks(0),
                    m_IsPaused(false),
                    m_IsStarted(false)
{
}

jfTimer::~jfTimer()
{
}

void jfTimer::start()
{
    m_IsStarted = true;
    m_IsPaused = false;
    m_StartTicks = SDL_GetTicks();
}

void jfTimer::stop()
{
    m_IsStarted = false;
    m_IsPaused = false;
}

void jfTimer::pause()
{
    if( m_IsStarted && ! m_IsPaused )
    {
        m_IsPaused = true;
        m_PausedTicks = SDL_GetTicks() - m_StartTicks;
    }
}
void jfTimer::unPause()
{
    if(m_IsPaused)
    {
        m_IsPaused = false;
        m_StartTicks = SDL_GetTicks() - m_PausedTicks;
        m_PausedTicks = 0;
    }
}

unsigned jfTimer::getTicks()
{
    if(m_IsStarted)
    {
        if(m_IsPaused)
        {
            return m_PausedTicks;
        }
        else
        {
            return SDL_GetTicks() - m_StartTicks;
        }
    }
    return 0;
}
bool jfTimer::isStarted()
{
    return m_IsStarted;
}

bool jfTimer::isPaused()
{
    return m_IsPaused;
}
