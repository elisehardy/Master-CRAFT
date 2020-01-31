CMAKE_MINIMUM_REQUIRED(VERSION 3.7)

PROJECT(Mastercraft)

SET(CMAKE_CXX_COMPILER /usr/bin/clang++)
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

SET(OpenGL_GL_PREFERENCE GLVND)
SET(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)


############################## 3RD PARTIES LIBS ################################
FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)

SET(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)
SET(LIBS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/include)

INCLUDE_DIRECTORIES(
    SYSTEM
    ${SDL2_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${LIBS_INCLUDE_DIR}
)
INCLUDE_DIRECTORIES(
    ${INCLUDE_DIR}
)


################################# MASTERCRAFT ##################################
FILE(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
FILE(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.hpp)
FILE(GLOB_RECURSE SHADER_FILES ${CMAKE_SOURCE_DIR}/shader/*.glsl)

SET(TARGET_NAME mastercraft)
ADD_EXECUTABLE(${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES})
TARGET_LINK_LIBRARIES(${TARGET_NAME} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})
TARGET_COMPILE_OPTIONS(
    ${TARGET_NAME} PRIVATE
    -g
    -O2
    -Werror
    -Weverything
    -Wfatal-errors
    -std=c++17
)

# Disable some warnings
TARGET_COMPILE_OPTIONS(
    ${TARGET_NAME} PRIVATE
    -Wno-unused-parameter
    -Wno-effc++
    -Wno-shadow
    -Wno-c++98-compat
#    -Wno-sign-conversion
    -Wno-padded
    -Wno-global-constructors
    -Wno-weak-vtables
    -Wno-delete-non-abstract-non-virtual-dtor
    -Wno-exit-time-destructors
    -Wno-c++11-narrowing
    -Wno-unneeded-internal-declaration
    -Wno-float-conversion
    -Wno-unused-template
    -Wno-documentation-unknown-command
    -Wno-documentation
    -Wno-undefined-reinterpret-cast
#    -Wno-implicit-float-conversion
#    -Wno-double-promotion
    -Wno-old-style-cast
    -Wno-reserved-id-macro
    -Wno-shorten-64-to-32
    -Wno-cast-qual
    -Wno-disabled-macro-expansion
    -Wno-unknown-warning-option
    -Wno-conversion
    -Wno-unused-exception-parameter
    -Wno-c++98-c++11-compat-binary-literal
)
