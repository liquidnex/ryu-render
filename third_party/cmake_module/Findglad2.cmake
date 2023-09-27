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
set(SOURCE_DIR ${PROJECT_ROOT}/third_party/glad2)

set(GLAD2_INCLUDE_DIR "")
list(APPEND GLAD2_INCLUDE_DIR ${SOURCE_DIR}/include)

set(GLAD2_SOURCES "")
file(GLOB_RECURSE GLAD2_SOURCES
    ${SOURCE_DIR}/src/*.c
    ${SOURCE_DIR}/src/*.cpp)