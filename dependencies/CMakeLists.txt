include(FetchContent)

#add_subdirectory(boost)
add_subdirectory(core)
add_subdirectory(crossguid)
#add_subdirectory(filament)
add_subdirectory(linal)
add_subdirectory(geometry)

if (meshler_BUILD_TESTS)
    add_subdirectory(googletest)
endif ()
