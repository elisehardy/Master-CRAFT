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
TARGET_LINK_LIBRARIES(${TARGET_NAME} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} tbb)
TARGET_COMPILE_OPTIONS(
<<<<<<< HEAD
<<<<<<< HEAD
    ${TARGET_NAME} PRIVATE
    -g
    -O3
    -Werror
    -Weverything
    -Wfatal-errors
    -std=c++17

=======
        ${TARGET_NAME} PRIVATE
        -g
        -O2
        -Werror
        -Weverything
        -Wfatal-errors
        -std=c++17
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87
)

# Disable some warnings
TARGET_COMPILE_OPTIONS(
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    ${TARGET_NAME} PRIVATE
    -Wno-unused-parameter
    -Wno-effc++
    -Wno-shadow
    -Wno-c++98-compat
    -Wno-sign-conversion
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
=======
=======
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87
        ${TARGET_NAME} PRIVATE
        -std=c++17
        -Wno-unused-parameter
        -Wno-effc++
        -Wno-shadow
        -Wno-c++98-compat
        -Wno-sign-conversion
        -Wno-padded
        -Wno-global-constructors
        -Wno-weak-vtables
        -Wno-exit-time-destructors
        -Wno-c++11-narrowing
        -Wno-unneeded-internal-declaration
        -Wno-float-conversion
        -Wno-unused-template
        -Wno-documentation-unknown-command
        -Wno-documentation
        -Wno-undefined-reinterpret-cast
        -Wno-implicit-float-conversion
        -Wno-double-promotion
        -Wno-old-style-cast
        -Wno-reserved-id-macro
        -Wno-shorten-64-to-32
        -Wno-cast-qual
        -Wno-disabled-macro-expansion
        -Wno-comma
        -Wno-unknown-warning-option
        -Wno-conversion
        -Wno-deprecated
        -Wno-unused-exception-parameter
<<<<<<< HEAD
        -Wno-unused-variable
>>>>>>> move slime
=======
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87
)


IF (CLANG_VERSION_MAJOR GREATER_EQUAL 9)
    TARGET_COMPILE_OPTIONS(
            ${TARGET_NAME} PRIVATE
            -Wno-delete-non-abstract-non-virtual-dtor
    )
ELSE ()
    TARGET_COMPILE_OPTIONS(
            ${TARGET_NAME} PRIVATE
            -Wno-delete-non-virtual-dtor
    )
ENDIF ()