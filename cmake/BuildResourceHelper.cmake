# Modified version of get_resgen_vars from filament.
# This version creates the file with suffix apple.S only
# if the target platform is APPLE or IOS
function(filapp_get_resgen_vars ARCHIVE_DIR ARCHIVE_NAME)
    if (APPLE OR IOS)
        set(OUTPUTS
                ${ARCHIVE_DIR}/${ARCHIVE_NAME}.bin
                ${ARCHIVE_DIR}/${ARCHIVE_NAME}.S
                ${ARCHIVE_DIR}/${ARCHIVE_NAME}.apple.S
                ${ARCHIVE_DIR}/${ARCHIVE_NAME}.h
                )
    else ()
        set(OUTPUTS
                ${ARCHIVE_DIR}/${ARCHIVE_NAME}.bin
                ${ARCHIVE_DIR}/${ARCHIVE_NAME}.S
                ${ARCHIVE_DIR}/${ARCHIVE_NAME}.h
                )
    endif ()

    if (IOS)
        set(ASM_ARCH_FLAG "-arch ${DIST_ARCH}")
    endif ()
    if (APPLE)
        set(ASM_SUFFIX ".apple")
    endif ()
    set(RESGEN_HEADER "${ARCHIVE_DIR}/${ARCHIVE_NAME}.h" PARENT_SCOPE)
    # Visual Studio makes it difficult to use assembly without using MASM. MASM doesn't support
    # the equivalent of .incbin, so on Windows we'll just tell resgen to output a C file.
    if (WEBGL OR WIN32 OR ANDROID_ON_WINDOWS)
        set(RESGEN_OUTPUTS "${OUTPUTS};${ARCHIVE_DIR}/${ARCHIVE_NAME}.c" PARENT_SCOPE)
        set(RESGEN_FLAGS -qcx ${ARCHIVE_DIR} -p ${ARCHIVE_NAME} PARENT_SCOPE)
        set(RESGEN_SOURCE "${ARCHIVE_DIR}/${ARCHIVE_NAME}.c" PARENT_SCOPE)
    else ()
        set(RESGEN_OUTPUTS "${OUTPUTS}" PARENT_SCOPE)
        set(RESGEN_FLAGS -qx ${ARCHIVE_DIR} -p ${ARCHIVE_NAME} PARENT_SCOPE)
        set(RESGEN_SOURCE "${ARCHIVE_DIR}/${ARCHIVE_NAME}${ASM_SUFFIX}.S" PARENT_SCOPE)
        set(RESGEN_SOURCE_FLAGS "-I${ARCHIVE_DIR} ${ASM_ARCH_FLAG}" PARENT_SCOPE)
    endif ()
endfunction()

function(build_resources)
    # Target system
    #set(MATC_TARGET mobile)
    set(MATC_TARGET desktop)

    if (FILAMENT_SUPPORTS_OPENGL)
        set(MATC_API_FLAGS ${MATC_API_FLAGS} -a opengl)
    endif ()
    if (FILAMENT_SUPPORTS_VULKAN)
        set(MATC_API_FLAGS ${MATC_API_FLAGS} -a vulkan)
    endif ()
    if (FILAMENT_SUPPORTS_METAL)
        set(MATC_API_FLAGS ${MATC_API_FLAGS} -a metal)
    endif ()

    ## ==================================================================================================
    ## Build materials
    ## ==================================================================================================

    set(MATC_BASE_FLAGS ${MATC_API_FLAGS} -p ${MATC_TARGET} ${MATC_OPT_FLAGS})

    set(MATERIAL_DIR "${CMAKE_BINARY_DIR}/generated/material")
    file(MAKE_DIRECTORY ${MATERIAL_DIR})
    set(RESOURCE_BINS)

    message(STATUS "MATC_BASE_FLAGS: ${MATC_BASE_FLAGS}")

    file(GLOB MATERIAL_SRCS ${CMAKE_CURRENT_LIST_DIR}/resources/material/*.mat)
    foreach (MATERIAL_SRC IN LISTS MATERIAL_SRCS)
        message(STATUS "MATERIAL_SRC: ${MATERIAL_SRC}")

        get_filename_component(localname ${MATERIAL_SRC} NAME_WE)
        get_filename_component(fullname ${MATERIAL_SRC} ABSOLUTE)
        set(output_path "${MATERIAL_DIR}/${localname}.filamat")
        add_custom_command(
                OUTPUT ${output_path}
                COMMAND matc ${MATC_BASE_FLAGS} -o ${output_path} ${fullname}
                MAIN_DEPENDENCY ${MATERIAL_SRC}
                DEPENDS matc
                COMMENT "Compiling material ${MATERIAL_SRC} to ${output_path}"
        )

        list(APPEND RESOURCE_BINS ${output_path})
        message(STATUS "RESOURCE_BINS: ${RESOURCE_BINS}")
    endforeach ()

    ## ==================================================================================================
    ## Build resources
    ## ==================================================================================================
    set(RESOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated/resources")
    file(MAKE_DIRECTORY ${RESOURCE_DIR})

    filapp_get_resgen_vars(${RESOURCE_DIR} filapp_resources)

    add_custom_command(
            OUTPUT ${RESGEN_OUTPUTS}
            COMMAND resgen ${RESGEN_FLAGS} ${RESOURCE_BINS}
            DEPENDS resgen ${RESOURCE_BINS}
            COMMENT "Aggregating resources")
    message(STATUS "RESGEN_OUTPUTS: ${RESGEN_OUTPUTS}")

    if (DEFINED RESGEN_SOURCE_FLAGS)
        set_source_files_properties(${RESGEN_SOURCE} PROPERTIES COMPILE_FLAGS ${RESGEN_SOURCE_FLAGS})
    endif ()

    # CMake fails to invoke ar on Windows unless there is at least one C/C++ file in the library.
    set(DUMMY_SRC "${RESOURCE_DIR}/dummy.c")
    add_custom_command(OUTPUT ${DUMMY_SRC} COMMAND echo "//" > ${DUMMY_SRC})

    add_library(fil_app_sources ${DUMMY_SRC} ${RESGEN_OUTPUTS})
    message(STATUS "RESGEN_SOURCE: ${RESGEN_SOURCE}")
endfunction()