set(CPM_geometry_SOURCE "C:/Users/testUser/dev/repos/Geometry")
CPMAddPackage(
        NAME geometry
        GITHUB_REPOSITORY "timow-gh/Geometry"
        GIT_TAG main
        GIT_SHALLOW TRUE
        OPTIONS
        "Geometry_INSTALL ${${PROJECT_NAME}_INSTALL}"
)