set(CPM_LinAl_SOURCE "C:/Users/testUser/dev/repos/LinAl")
CPMAddPackage(
        NAME LinAl
        GITHUB_REPOSITORY timow-gh/LinAl
        GIT_TAG main
        GIT_SHALLOW TRUE
        OPTIONS
        "LinAl_INSTALL ${${PROJECT_NAME}_INSTALL}"
)
