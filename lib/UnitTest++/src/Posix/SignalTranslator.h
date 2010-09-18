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
#ifndef UNITTEST_SIGNALTRANSLATOR_H
#define UNITTEST_SIGNALTRANSLATOR_H

#include <setjmp.h>
#include <signal.h>

namespace UnitTest {

class SignalTranslator
{
public:
    SignalTranslator();
    ~SignalTranslator();

    static sigjmp_buf* s_jumpTarget;

private:
    sigjmp_buf m_currentJumpTarget;
    sigjmp_buf* m_oldJumpTarget;

    struct sigaction m_old_SIGFPE_action;
    struct sigaction m_old_SIGTRAP_action;
    struct sigaction m_old_SIGSEGV_action;
    struct sigaction m_old_SIGBUS_action;
    struct sigaction m_old_SIGABRT_action;
    struct sigaction m_old_SIGALRM_action;
};

#if !defined (__GNUC__)
    #define UNITTEST_EXTENSION
#else
    #define UNITTEST_EXTENSION __extension__
#endif

#define UNITTEST_THROW_SIGNALS \
	UnitTest::SignalTranslator sig; \
	if (UNITTEST_EXTENSION sigsetjmp(*UnitTest::SignalTranslator::s_jumpTarget, 1) != 0) \
        throw ("Unhandled system exception"); 

}

#endif
