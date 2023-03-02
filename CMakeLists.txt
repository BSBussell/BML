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
option(BUILD_TESTS "Build tests" ON)



# The following folder will be included

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


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
if(BUILD_TESTS)
  

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
	    target_link_libraries(${test_name} BML SDL2 SDL2_image SDL2_mixer)
	    target_include_directories(${test_name} PRIVATE inc/)
	    set_target_properties(${test_name} PROPERTIES
	        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../tests/bin
	    )

	endforeach()
endif()

