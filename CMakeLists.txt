# Specify the minimum version for CMake

cmake_minimum_required(VERSION 3.11)


# The version number.
set (APP_NAME Leap)

project("${APP_NAME}")


set (Leap_VERSION_MAJOR 1)
set (Leap_VERSION_MINOR 0)

message("compiling ${APP_NAME} ${Leap_VERSION_MAJOR}.${Leap_VERSION_MINOR}")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
        "${PROJECT_SOURCE_DIR}/LeapConfig.h.in"
        "${PROJECT_BINARY_DIR}/LeapConfig.h"
)
set (CMAKE_CXX_STANDARD 11)

if(DEFINED ENV{LEAPSDK})
    message(STATUS "LEAPSDK environment variable defined")
    # some more commands
else()
    message(FATAL_ERROR "LEAPSDK environment variable not defined!")
endif()

set(LEAPSDK $ENV{LEAPSDK})
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(leap my-leap.cpp my-leap.h tux-leap/TuxLeapHand.cpp tux-leap/TuxLeapHand.h tux-leap/TuxLeapFinger.cpp tux-leap/TuxLeapFinger.h tux-leap/TuxLeapBone.cpp tux-leap/TuxLeapBone.h tux-leap/TuxLeap.cpp tux-leap/TuxLeap.h tux-leap/TuxLeapArm.cpp tux-leap/TuxLeapArm.h)
add_executable(leap-opengl-test
        tux-leap-opengl.cpp
        tux-leap/TuxLeapHand.cpp tux-leap/TuxLeapHand.h
        tux-leap/TuxLeapArm.cpp tux-leap/TuxLeapArm.h
        tux-leap/TuxLeapFinger.cpp tux-leap/TuxLeapFinger.h
        tux-leap/TuxLeapBone.cpp tux-leap/TuxLeapBone.h
        tux-leap/TuxLeapHand.h tux-leap/TuxLeapHand.cpp
        tux-leap/TuxLeap.cpp tux-leap/TuxLeap.h
        tux-draw/TuxDraw.h tux-draw/TuxDraw.cpp tux-draw/opengl/TuxDrawOpenGL.cpp)
add_executable(leap-opengl4
        tux-draw/opengl/openglwindow-render.cpp tux-draw/opengl/common/OpenGLWindow.cpp tux-draw/opengl/common/glad/src/glad.c
        tux-draw/opengl/common/shader.cpp tux-draw/opengl/common/shaderProgram.cpp tux-draw/opengl/common/vertexBufferObject.cpp
        tux-draw/opengl/common/uniform.cpp tux-leap-opengl.cpp tux-draw/opengl/staticGeometry.cpp
        tux-draw/opengl/common/flyingCamera.cpp

        tux-leap/TuxLeapHand.cpp
        tux-leap/TuxLeapArm.cpp
        tux-leap/TuxLeapFinger.cpp
        tux-leap/TuxLeapBone.cpp
        tux-leap/TuxLeapHand.cpp
        tux-leap/TuxLeap.cpp
        tux-draw/TuxDraw.cpp
        tux-draw/opengl/TuxDrawOpenGL.cpp
        )

if(LINUX)
    message("linux")
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        # 64 bits
        target_link_libraries(leap ${LEAPSDK}/lib/x64/libLeap.so)
        target_link_libraries(leap-opengl-test ${LEAPSDK}/lib/x64/libLeap.so)
        target_link_libraries(leap-opengl4 ${LEAPSDK}/lib/x64/libLeap.so)
        SET(CMAKE_INSTALL_RPATH "${LEAPSDK}/lib/x64")
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        # 32 bits
        target_link_libraries(leap ${LEAPSDK}/lib/x86/libLeap.so)
        target_link_libraries(leap-opengl-test ${LEAPSDK}/lib/x86/libLeap.so)
        target_link_libraries(leap-opengl4 ${LEAPSDK}/lib/x86/libLeap.so)
        SET(CMAKE_INSTALL_RPATH "${LEAPSDK}/lib/x32")
    endif()
elseif(APPLE)
    target_link_libraries(leap ${LEAPSDK}/lib/libLeap.dylib)
    target_link_libraries(leap-opengl-test ${LEAPSDK}/lib/libLeap.dylib)
    target_link_libraries(leap-opengl4 ${LEAPSDK}/lib/libLeap.dylib)
    add_custom_command(TARGET leap
            POST_BUILD COMMAND
            ${CMAKE_INSTALL_NAME_TOOL} -change @loader_path/libLeap.dylib ${LEAPSDK}/lib/libLeap.dylib
            $<TARGET_FILE:leap>)
    add_custom_command(TARGET leap-opengl-test
            POST_BUILD COMMAND
            ${CMAKE_INSTALL_NAME_TOOL} -change @loader_path/libLeap.dylib ${LEAPSDK}/lib/libLeap.dylib
            $<TARGET_FILE:leap-opengl-test>)
    add_custom_command(TARGET leap-opengl4
            POST_BUILD COMMAND
            ${CMAKE_INSTALL_NAME_TOOL} -change @loader_path/libLeap.dylib ${LEAPSDK}/lib/libLeap.dylib
            $<TARGET_FILE:leap-opengl4>)

    target_link_libraries(leap-opengl-test /opt/X11/lib/libGL.dylib /usr/X11/lib/libglut.dylib ${LEAPSDK}/lib/libLeap.dylib)
    target_include_directories(leap-opengl-test PRIVATE "/opt/X11/include")

    target_link_libraries(leap-opengl4 /opt/X11/lib/libGL.dylib /usr/X11/lib/libglut.dylib ${LEAPSDK}/lib/libLeap.dylib /usr/local/lib/libglfw.dylib)
    target_include_directories(leap-opengl4 PRIVATE "/opt/X11/include")


endif()

# The following folder will be included
include_directories("${PROJECT_BINARY_DIR}")


target_include_directories(leap PRIVATE ${LEAPSDK}/include)
target_include_directories(leap-opengl-test PRIVATE ${LEAPSDK}/include)
target_include_directories(leap-opengl4 PRIVATE ${LEAPSDK}/include)


