
cmake_minimum_required(VERSION 2.8)

#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake/cuda")
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/cuda" ${CMAKE_MODULE_PATH})
find_package(CUDA)

### Set include dirs
if(WIN32)
	INCLUDE_DIRECTORIES(./ ../lib/SDL/include)
	LINK_DIRECTORIES(../lib/SDL/lib) 
else()
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
	INCLUDE_DIRECTORIES(./)
endif()

### Set common libs
if(WIN32)
	SET(jfCommonClientLib opengl32 sdl sdlmain glu32)
else()
	SET(jfCommonClientLib GL GLU SDL)
endif()

#Set to old gcc version which nvcc on unix supports
if(UNIX)
	set( CUDA_NVCC_FLAGS "--compiler-bindir=/usr/bin/gcc-4.3")
endif()

### Set cpp files
FILE(GLOB jfpx_cpp "./jfpx/*.cpp")
FILE(GLOB jfpx_x86_cpp "./jfpx/x86/*.cpp")
FILE(GLOB_RECURSE jfpx_cuda_cpp "./jfpx/*.cpp") ##Want x86 files too.
FILE(GLOB jfpx_cuda_cu "./jfpx/cuda/*.cu")
FILE(GLOB_RECURSE jfCamera_cpp "./jfCamera/*.cpp")
FILE(GLOB_RECURSE jfEvent_cpp "./jfEvent/*.cpp")
FILE(GLOB_RECURSE jfGraphics_cpp "./jfGraphics/*.cpp")
FILE(GLOB_RECURSE jfLog_cpp "./jfLog/*.cpp")
FILE(GLOB_RECURSE jfShape_cpp "./jfShape/*.cpp")
FILE(GLOB_RECURSE jfSimulation_cpp "./jfSimulation/*.cpp")
FILE(GLOB jfTimer_cpp "./jfTimer/*.cpp")
FILE(GLOB_RECURSE jfBoxesAndBalls_x86_cpp "./jfClient/jfBoxesAndBalls/x86/*.cpp")
FILE(GLOB_RECURSE jfBoxesAndBalls_cuda_cpp "./jfClient/jfBoxesAndBalls/cuda/*.cpp")
FILE(GLOB_RECURSE jfBallistic_x86_cpp "./jfClient/jfBallistic/x86/*.cpp")
FILE(GLOB_RECURSE jfBigBallistic_x86_cpp "./jfClient/jfBigBallistic/x86/*.cpp")
FILE(GLOB_RECURSE jfFlight_x86_cpp "./jfClient/jfFlight/x86/*.cpp")

### Generate core libraries
SET(jfCoreCommon_cpp ${jfpx_cpp} ${jfCamera_cpp} ${jfBoxesAndBalls_cuda_cpp} ${jfEvent_cpp} ${jfGraphics_cpp} ${jfLog_cpp} ${jfShape_cpp} ${jfSimulation_cpp} ${jfTimer_cpp})
ADD_LIBRARY(jfCore_x86 ${jfpx_x86_cpp} ${jfCoreCommon_cpp})
cuda_add_library(jfCore_cuda ${jfpx_cuda_cpp} ${jfpx_cuda_cu} ${jfCoreCommon_cpp})

#FILE(GLOB_RECURSE HEADERS "*.h")

### Generate Executables For Demo Files
add_executable (jfBoxesAndBalls_x86 ${jfBoxesAndBalls_x86_cpp})
target_link_libraries(jfBoxesAndBalls_x86 ${jfCommonClientLib} jfCore_x86)

add_executable (jfBallistic_x86 ${jfBallistic_x86_cpp})
target_link_libraries(jfBallistic_x86 ${jfCommonClientLib} jfCore_x86)

add_executable (jfFlight_x86 ${jfFlight_x86_cpp})
target_link_libraries(jfFlight_x86 ${jfCommonClientLib} jfCore_x86)

cuda_add_executable(jfBoxesAndBalls_cuda ${jfBoxesAndBalls_cuda_cpp})
target_link_libraries(jfBoxesAndBalls_cuda ${jfCommonClientLib} jfCore_cuda)
