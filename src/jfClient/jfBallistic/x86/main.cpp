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
#include <jfSimulation/jfSimulation.h>
#include <jfClient/jfBallistic/x86/jfBallisticSimulation.h>

//#undef main
int main(int argc, char **argv)
{
    jfSimulation* simulation = new jfBallisticSimulation();

    if(simulation->init())
    {
	    simulation->run();
    }
    else
    {
	    std::cout << "Simulation init failed! Not running..." << std::endl;
    }

    delete simulation;

    return 0;
}
