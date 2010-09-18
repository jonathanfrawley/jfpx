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
#include "SignalTranslator.h"

namespace UnitTest {

sigjmp_buf* SignalTranslator::s_jumpTarget = 0;

namespace {

void SignalHandler(int sig)
{
    siglongjmp(*SignalTranslator::s_jumpTarget, sig );
}

}


SignalTranslator::SignalTranslator()
{
    m_oldJumpTarget = s_jumpTarget;
    s_jumpTarget = &m_currentJumpTarget;

    struct sigaction action;
    action.sa_flags = 0;
    action.sa_handler = SignalHandler;
    sigemptyset( &action.sa_mask );

    sigaction( SIGSEGV, &action, &m_old_SIGSEGV_action );
    sigaction( SIGFPE , &action, &m_old_SIGFPE_action  );
    sigaction( SIGTRAP, &action, &m_old_SIGTRAP_action );
    sigaction( SIGBUS , &action, &m_old_SIGBUS_action  );
    sigaction( SIGILL , &action, &m_old_SIGBUS_action  );
}

SignalTranslator::~SignalTranslator()
{
    sigaction( SIGILL , &m_old_SIGBUS_action , 0 );
    sigaction( SIGBUS , &m_old_SIGBUS_action , 0 );
    sigaction( SIGTRAP, &m_old_SIGTRAP_action, 0 );
    sigaction( SIGFPE , &m_old_SIGFPE_action , 0 );
    sigaction( SIGSEGV, &m_old_SIGSEGV_action, 0 );

    s_jumpTarget = m_oldJumpTarget;
}


}
