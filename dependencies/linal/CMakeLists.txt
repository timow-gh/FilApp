#include(localLinAl.cmake)
FetchContent_Declare(
        linal
        GIT_REPOSITORY https://github.com/timow-gh/LinAl.git
        GIT_TAG v0.1.0
        GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(linal)