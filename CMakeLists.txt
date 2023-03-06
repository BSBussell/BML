cmake_minimum_required(VERSION 3.14)

#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_mixer REQUIRED)


# Project's Name
project(BML VERSION 0.2.0 DESCRIPTION "SDL Wrapper For Bee")


# Set the output folder where The program will be created
#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_VERBOSE_MAKEFILE ON)

# Define an option to build the tests
option(TESTS "Build tests" ON)



# The following folder will be included

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


# Grabbing BML .cpp files
set (LIBRARY_SOURCES
	src/BML.cpp
	src/bEvent.cpp
	src/bRect.cpp
	src/bSheet.cpp
	src/bSound.cpp
	src/bTexture.cpp
	src/bWindow.cpp
)

# Grabbing BML .h files
set (LIBRARY_HEADERS
	inc/BML.h
	inc/bEvent.h
	inc/bRect.h
	inc/bSheet.h
	inc/bSound.h
	inc/bTexture.h
	inc/bWindow.h
	inc/json.h
)


add_library(
	BML
	STATIC
	${LIBRARY_SOURCES}
	${LIBRARY_HEADERS}
)

target_include_directories(	BML PUBLIC inc )

install(TARGETS BML
    ARCHIVE DESTINATION lib
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/inc/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/usr/local/include/BML
        FILES_MATCHING PATTERN "*.h")


# Conditionally add the tests directory
if(TESTS)
  
	find_package(SDL2 REQUIRED)
	include_directories(${SDL2_INCLUDE_DIRS})

	# Yeah I'm gonna have to look into these a bit more :3
	
	#find_package(SDL2_IMAGE_LIBRARY REQUIRED)
	#include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

	#find_package(SDL2_MIXER_LIBRARY REQUIRED)
	#include_directories(${SDL2_MIXER_INCLUDE_DIRS})

	set(TEST_SOURCES

		tests/src/eventTest.cpp
		tests/src/jsonTest.cpp
		tests/src/soundTest.cpp
		tests/src/textureTest.cpp
		tests/src/windowTest.cpp
	)

	foreach(test_src ${TEST_SOURCES})

		get_filename_component(test_name ${test_src} NAME_WE)
		add_executable(${test_name} ${test_src})
	    target_link_libraries(${test_name} BML ${SDL2_LIBRARIES} -lSDL2_image -lSDL2_mixer)
	    target_include_directories(${test_name} PRIVATE inc/)
	    set_target_properties(${test_name} PROPERTIES
	        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../tests/bin
	    )
	    add_dependencies(${test_name} BML)

	endforeach()
endif()

