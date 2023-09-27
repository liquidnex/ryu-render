# Marcos
# Get parent directory
macro(get_parent_dierectory DIR_PATH DEPTH)
    set(GPD_CUR_DIR ${DIR_PATH})
    foreach(var RANGE 1 ${DEPTH})
        cmake_path(GET GPD_CUR_DIR PARENT_PATH GPD_CUR_DIR)
    endforeach()
    set(GPD_RESULT ${GPD_CUR_DIR})
endmacro()

# Set required variables
get_parent_dierectory(${CMAKE_CURRENT_LIST_DIR} 2)
set(PROJECT_ROOT ${GPD_RESULT})
unset(GPD_RESULT)

# Set source directory
set(SOURCE_DIR ${PROJECT_ROOT}/third_party/glfw-3.3.8)

# Add CEF as imported library
set(INCLUDE_DIRS ${SOURCE_DIR}/include)

if (NOT TARGET glfw3)
    if(WIN32)
        find_library(glfw3_LOCATION
                     NAMES glfw3_mt.lib
                     PATHS ${SOURCE_DIR}/libs/windows/${CMAKE_GENERATOR_PLATFORM_STR}/lib
                     NO_DEFAULT_PATH)
    endif()

    add_library(glfw3 STATIC IMPORTED)
    set_target_properties(glfw3 PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${INCLUDE_DIRS}"
        IMPORTED_LOCATION ${glfw3_LOCATION}
    )
endif()