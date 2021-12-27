FetchContent_Declare(
        filament
        GIT_REPOSITORY https://github.com/timow-gh/filament.git
        GIT_TAG 4baa4d60b9320da46e168c7c2b296dfa6c2f8279) # tw-cmake-minimal
FetchContent_GetProperties(filament)
if (NOT filament_POPULATED)
    set(FILAMENT_SUPPORTS_OPENGL ON CACHE BOOL "Include the OpenGL backend" FORCE)
    set(FILAMENT_SUPPORTS_VULKAN ON CACHE BOOL "Include the Vulkan backend" FORCE)
    set(FILAMENT_SUPPORTS_METAL OFF CACHE BOOL "Include the Metal backend" FORCE)

    set(FILAMENT_BUILD_FILAMAT ON CACHE BOOL "Build filamat and JNI buildings" FORCE)
    #    set(FILAMENT_SKIP_SAMPLES ON CACHE BOOL "Don't build samples" FORCE)

    set(FILAMENT_PER_RENDER_PASS_ARENA_SIZE_IN_MB "3" CACHE STRING
            "Per render pass arena size. Must be roughly 1 MB larger than FILAMENT_PER_FRAME_COMMANDS_SIZE_IN_MB, default 2."
            )
    set(FILAMENT_PER_FRAME_COMMANDS_SIZE_IN_MB "2" CACHE STRING
            "Size of the high-level draw commands buffer. Rule of thumb, 1 MB less than FILAMENT_PER_RENDER_PASS_ARENA_SIZE_IN_MB, default 1."
            )
    set(FILAMENT_MIN_COMMAND_BUFFERS_SIZE_IN_MB "5" CACHE STRING
            "Size of the command-stream buffer. As a rule of thumb use the same value as FILAMENT_PER_FRRAME_COMMANDS_SIZE_IN_MB, default 1."
            )
    set(FILAMENT_OPENGL_HANDLE_ARENA_SIZE_IN_MB "32" CACHE STRING
            "Size of the OpenGL handle arena, default 4."
            )
    set(FILAMENT_METAL_HANDLE_ARENA_SIZE_IN_MB "8" CACHE STRING
            "Size of the Metal handle arena, default 8."
            )

    option(FILAMENT_USE_EXTERNAL_GLES3 "Experimental: Compile Filament against OpenGL ES 3" OFF)
    option(FILAMENT_USE_EXTERNAL_GLES3 "Experimental: Compile Filament against OpenGL ES 3" OFF)
    option(FILAMENT_USE_SWIFTSHADER "Compile Filament against SwiftShader" OFF)
    option(FILAMENT_ENABLE_LTO "Enable link-time optimizations if supported by the compiler" OFF)

    set(FILAMENT_SUPPORTS_XLIB ON CACHE BOOL "Include XLIB support in Linux builds" FORCE)
    set(FILAMENT_SUPPORTS_XCB ON CACHE BOOL "Include XCB support in Linux builds" FORCE)
    FetchContent_Populate(filament)

    list(APPEND CMAKE_MODULE_PATH ${filament_SOURCE_DIR})
    add_subdirectory(${filament_SOURCE_DIR} ${filament_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()