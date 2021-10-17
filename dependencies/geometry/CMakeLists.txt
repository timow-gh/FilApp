#set(FETCHCONTENT_SOURCE_DIR_geometry "/home/timo/dev/repos/Geometry")
FetchContent_Declare(
        geometry
        GIT_REPOSITORY git@github.com:timow-gh/Geometry.git
        GIT_TAG main)
FetchContent_MakeAvailable(geometry)