cmake_minimum_required(VERSION 3.14)

# Project's Name
project(BML VERSION 0.2.0 DESCRIPTION "SDL Wrapper For Bee")

include(GNUInstallDirs)

# Set the output folder where The program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_BUILD_TYPE Debug)


# The following folder will be included

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2_image")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2_mixer")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lBML")


#add_executable(BML)


add_library(
	BML
	src/BML.cpp
	src/bEvent.cpp
	src/bRect.cpp
	src/bSheet.cpp
	src/bSound.cpp
	src/bTexture.cpp
	src/bWindow.cpp
	inc/BML.h
	inc/bEvent.h
	inc/bRect.h
	inc/bSheet.h
	inc/bSound.h
	inc/bTexture.h
	inc/bWindow.h)

target_include_directories(
	BML
	PRIVATE
	src)

target_link_libraries(
	BML
	PRIVATE
	-lSDL2
	-lSDL2_image
	-lSDL2_mixer)



install(TARGETS BML
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})