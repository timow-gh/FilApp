function(build_resources)
    # Target system
    #set(MATC_TARGET mobile)
    set(MATC_TARGET desktop)

    if (FILAMENT_SUPPORTS_OPENGL)
        set(MATC_API_FLAGS ${MATC_API_FLAGS} -a opengl)
    endif()
    if (FILAMENT_SUPPORTS_VULKAN)
        set(MATC_API_FLAGS ${MATC_API_FLAGS} -a vulkan)
    endif()
    if (FILAMENT_SUPPORTS_METAL)
        set(MATC_API_FLAGS ${MATC_API_FLAGS} -a metal)
    endif()

    ## ==================================================================================================
    ## Build materials
    ## ==================================================================================================

    set(MATC_BASE_FLAGS ${MATC_API_FLAGS} -p ${MATC_TARGET} ${MATC_OPT_FLAGS})

    set(MATERIAL_DIR "${CMAKE_BINARY_DIR}/generated/material")
    file(MAKE_DIRECTORY ${MATERIAL_DIR})
    set(RESOURCE_BINS)

    set(MATERIALSRC resources/material/bakedColor.mat)
    get_filename_component(localname ${MATERIALSRC} NAME_WE)
    message(STATUS "LOCALNAME: ${localname}")
    get_filename_component(fullname ${MATERIALSRC} ABSOLUTE)
    message(STATUS "FULLNAME: ${fullname}")
    set(output_path "${MATERIAL_DIR}/${localname}.filamat")
    add_custom_command(
            OUTPUT ${output_path}
            COMMAND matc ${MATC_BASE_FLAGS} -o ${output_path} ${fullname}
            MAIN_DEPENDENCY ${MATERIALSRC}
            DEPENDS matc
            COMMENT "Compiling material ${MATERIALSRC} to ${output_path}"
    )
    message(STATUS "MATC_BASE_FLAGS: ${MATC_BASE_FLAGS}")

    list(APPEND RESOURCE_BINS ${output_path})
    message(STATUS "RESOURCE_BINS: ${RESOURCE_BINS}")

    ## ==================================================================================================
    ## Build resources
    ## ==================================================================================================
    set(RESOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated/resources")
    file(MAKE_DIRECTORY ${RESOURCE_DIR})

    get_resgen_vars(${RESOURCE_DIR} resources)

    add_custom_command(
            OUTPUT ${RESGEN_OUTPUTS}
            COMMAND resgen ${RESGEN_FLAGS} ${RESOURCE_BINS}
            DEPENDS resgen ${RESOURCE_BINS}
            COMMENT "Aggregating resources")
    message(STATUS "RESGEN_OUTPUTS: ${RESGEN_OUTPUTS}")

    if (DEFINED RESGEN_SOURCE_FLAGS)
        set_source_files_properties(${RESGEN_SOURCE} PROPERTIES COMPILE_FLAGS ${RESGEN_SOURCE_FLAGS})
    endif()

    # CMake fails to invoke ar on Windows unless there is at least one C/C++ file in the library.
    set(DUMMY_SRC "${RESOURCE_DIR}/dummy.c")
    add_custom_command(OUTPUT ${DUMMY_SRC} COMMAND echo "//" > ${DUMMY_SRC})

    add_library(filamentapp_sources ${DUMMY_SRC} ${RESGEN_OUTPUTS})
    message(STATUS "RESGEN_SOURCE: ${RESGEN_SOURCE}")
endfunction()