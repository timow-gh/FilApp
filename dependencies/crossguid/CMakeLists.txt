set(CPM_crossguid_SOURCE "C:/Users/testUser/dev/repos/CrossGuid")
CPMAddPackage(
        NAME crossguid
        GITHUB_REPOSITORY "timow-gh/CrossGuid"
        GIT_TAG main
        GIT_SHALLOW TRUE
        OPTIONS
        "CrossGuid_INSTALL ON"
)