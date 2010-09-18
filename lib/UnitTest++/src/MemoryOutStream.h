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
#ifndef UNITTEST_MEMORYOUTSTREAM_H
#define UNITTEST_MEMORYOUTSTREAM_H

#include "Config.h"

#ifndef UNITTEST_USE_CUSTOM_STREAMS

#include <sstream>

namespace UnitTest
{

class MemoryOutStream : public std::ostringstream
{
public:
    MemoryOutStream() {}
    char const* GetText() const;

private:
    MemoryOutStream(MemoryOutStream const&);
    void operator =(MemoryOutStream const&);

    mutable std::string m_text;
};

}

#else

#include <cstddef>

namespace UnitTest
{

class MemoryOutStream
{
public:
    explicit MemoryOutStream(int const size = 256);
    ~MemoryOutStream();

    char const* GetText() const;

    MemoryOutStream& operator << (char const* txt);
    MemoryOutStream& operator << (int n);
    MemoryOutStream& operator << (long n);
    MemoryOutStream& operator << (unsigned long n);
    MemoryOutStream& operator << (float f);
    MemoryOutStream& operator << (double d);
    MemoryOutStream& operator << (void const* p);
    MemoryOutStream& operator << (unsigned int s);

    enum { GROW_CHUNK_SIZE = 32 };
    int GetCapacity() const;

private:
    void operator= (MemoryOutStream const&);
    void GrowBuffer(int capacity);

    int m_capacity;
    char* m_buffer;
};

}

#endif

#endif
