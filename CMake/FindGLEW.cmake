FIND_PATH(GLEW_INCLUDE_PATH GL/glew.h
    /usr/include
    /usr/local/include
    /sw/include
    /opt/local/include
    )
FIND_LIBRARY(GLEW_LIBRARY
    NAMES GLEW glew
    PATHS
    /usr/lib64
    /usr/lib
    /usr/local/lib64
    /usr/local/lib
    /sw/lib
    /opt/local/lib
    )
