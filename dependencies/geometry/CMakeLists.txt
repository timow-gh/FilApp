#include(localGeometry.cmake)
FetchContent_Declare(
        geometry
        GIT_REPOSITORY https://github.com/timow-gh/Geometry.git
        GIT_TAG v0.1.0
        GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(geometry)