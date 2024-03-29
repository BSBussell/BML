cmake_minimum_required(VERSION 3.14)

#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_mixer REQUIRED)


# Project's Name
project(BML VERSION 0.2.0 DESCRIPTION "SDL Wrapper For Bee")



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
	src/bEvent.cpp
	src/bFontManager.cpp
	src/BML.cpp
	src/bRect.cpp
	src/bRenderer.cpp
	src/bSheet.cpp
	src/bSound.cpp
	src/bTexture.cpp
	src/bWindow.cpp
)

# Grabbing BML .h files
set (LIBRARY_HEADERS
	inc/bEvent.h
	inc/bFontManager.h
	inc/BML.h
	inc/bRect.h
	inc/bRenderer.h
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

target_compile_options(
	BML
	PRIVATE
	-Wall
	-Wextra
	-std=c++17
	-Ofast
)

target_include_directories(	BML PUBLIC inc )

install(TARGETS BML
		ARCHIVE DESTINATION lib
		COMPONENT BML
		)

file(GLOB_RECURSE HEADER_FILES "${PROJECT_SOURCE_DIR}/inc/*.h")
foreach(header ${HEADER_FILES})
	get_filename_component(header_subdir "${header}" DIRECTORY)
	file(RELATIVE_PATH relative_subdir "${PROJECT_SOURCE_DIR}/inc" "${header_subdir}")
	install(FILES "${header}"
			DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/usr/local/include/BML/${relative_subdir}"
			COMPONENT BML
			)
endforeach()

add_custom_target(Install_BML
		COMMAND "${CMAKE_COMMAND}" -DCMAKE_INSTALL_COMPONENT=BML -P "${CMAKE_BINARY_DIR}/cmake_install.cmake"
		DEPENDS BML
		WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
		COMMENT "Installing BML library"
		)



message("Install Include Directory: ${INSTALL_INCLUDE_DIR}")


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

		#tests/src/eventTest.cpp
		tests/src/jsonTest.cpp
		#tests/src/soundTest.cpp
		#tests/src/textureTest.cpp
		#tests/src/windowTest.cpp
	)

	foreach(test_src ${TEST_SOURCES})

		get_filename_component(test_name ${test_src} NAME_WE)
		add_executable(${test_name} ${test_src})
	    target_link_libraries(${test_name} -lBML ${SDL2_LIBRARIES} -lSDL2_image -lSDL2_mixer -lSDL2_ttf)
	    target_include_directories(${test_name} PRIVATE inc/)
	    target_compile_options(
			${test_name}
			PRIVATE
			-Wall
			-Wextra
			-std=c++17
			-g
		)

	    set_target_properties(${test_name} PROPERTIES
	        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../../BML/tests/bin
	    )
	    add_dependencies(${test_name} BML)

		add_custom_target(clean_${test_name}
				COMMAND ${CMAKE_COMMAND} -E remove ${test_name}
				DEPENDS ${test_name}
		)


	endforeach()
endif()



