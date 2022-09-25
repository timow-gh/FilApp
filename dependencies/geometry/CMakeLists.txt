#include(localGeometry.cmake)
FetchContent_Declare(
        geometry
        GIT_REPOSITORY https://github.com/timow-gh/Geometry.git
        GIT_TAG main)
FetchContent_MakeAvailable(geometry)