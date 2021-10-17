set(FETCHCONTENT_SOURCE_DIR_GEOMETRY "/home/timo/dev/repos/Geometry")
FetchContent_Declare(
        geometry
        GIT_REPOSITORY git@github.com:timow-gh/Geometry.git
        GIT_TAG refactor_halfedgemeshbuilder)
FetchContent_MakeAvailable(geometry)