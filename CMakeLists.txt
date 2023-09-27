# Marcos
# Group sources
macro(source_group_by_dir SOURCE_FILES)
    set(SGBD_CUR_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    foreach(SGBD_FILE ${${SOURCE_FILES}})
        string(REGEX REPLACE ${SGBD_CUR_DIR}/\(.*\) \\1 SGBD_FILE_PATH ${SGBD_FILE})
        string(REGEX REPLACE "\(.*\)/.*" \\1 SGBD_GROUP_NAME ${SGBD_FILE_PATH})
        string(COMPARE EQUAL ${SGBD_FILE_PATH} ${SGBD_GROUP_NAME} SGBD_NOGROUP)
        string(REPLACE "/" "\\" SGBD_GROUP_NAME ${SGBD_GROUP_NAME})
        if(SGBD_NOGROUP)
            set(SGBD_GROUP_NAME "\\")
        endif()
        source_group(${SGBD_GROUP_NAME} FILES ${SGBD_FILE})
    endforeach()
    unset(SGBD_CUR_DIR)
    unset(SGBD_FILE)
    unset(SGBD_FILE_PATH)
    unset(SGBD_GROUP_NAME)
    unset(SGBD_NOGROUP)
endmacro()

# Make directory
macro(make_directory DIR)
    if(EXISTS ${DIR})
        file(REMOVE_RECURSE ${DIR})
    endif()
    file(MAKE_DIRECTORY ${DIR})
endmacro()

# Cmake version requirements define
cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

# Define project
project(ryu-render
        LANGUAGES C CXX)

# Set language version
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Check basic project properties
if (NOT CMAKE_GENERATOR_PLATFORM)
    set(CMAKE_GENERATOR_PLATFORM x64)
endif()
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
add_definitions("-DUNICODE" "-D_UNICODE")

# Set output directory
string(TOLOWER ${CMAKE_SYSTEM_NAME} CMAKE_SYSTEM_NAME_STR)
string(TOLOWER ${CMAKE_GENERATOR_PLATFORM} CMAKE_GENERATOR_PLATFORM_STR)
set(OUTPUT_BIN_DIR_DEBUG ${PROJECT_SOURCE_DIR}/output/${CMAKE_SYSTEM_NAME_STR}/${CMAKE_GENERATOR_PLATFORM_STR}/debug/bin)
make_directory(${OUTPUT_BIN_DIR_DEBUG})
set(OUTPUT_BIN_DIR_RELEASE ${PROJECT_SOURCE_DIR}/output/${CMAKE_SYSTEM_NAME_STR}/${CMAKE_GENERATOR_PLATFORM_STR}/release/bin)
make_directory(${OUTPUT_BIN_DIR_RELEASE})

# Create executable
add_executable(${PROJECT_NAME})

# Set properties
if(WIN32 AND MSVC)
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/output/${CMAKE_SYSTEM_NAME_STR}/${CMAKE_GENERATOR_PLATFORM_STR}/$<$<CONFIG:Debug>:debug>$<$<CONFIG:Release>:release>/bin
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
        LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
        LINKER_LANGUAGE CXX
        CXX_VISIBILITY_PRESET hidden
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_BIN_DIR_DEBUG}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_BIN_DIR_RELEASE}
    )
else()
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_VISIBILITY_PRESET hidden
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_BIN_DIR_DEBUG}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_BIN_DIR_RELEASE}
    )
endif()

# Find related libraries
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/third_party/cmake_module)
find_package(OpenGL REQUIRED)
find_package(glad2 REQUIRED)
find_package(glfw3 REQUIRED)

# Collect all source files
file(GLOB_RECURSE HDR_LIST
    ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SRC_LIST
    ${PROJECT_SOURCE_DIR}/src/*.cpp)
set(SOURCE_LIST "")
list(APPEND SOURCE_LIST ${HDR_LIST})
list(APPEND SOURCE_LIST ${SRC_LIST})
list(APPEND SOURCE_LIST ${GLAD2_SOURCES})
source_group_by_dir(SOURCE_LIST)

# Set sources
target_sources(${PROJECT_NAME} PRIVATE
               ${SOURCE_LIST})

# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE
                           ${GLAD2_INCLUDE_DIR}
                           ${PROJECT_SOURCE_DIR}/include)

# Set linked libs
target_link_libraries(${PROJECT_NAME} PRIVATE
                      ${OPENGL_LIBRARIES}
                      glfw3)

# Set dependent runtime binaries
set(${PROJECT_NAME}_DEPENDENT_RUNTIME_DIRS "")
list(APPEND ${PROJECT_NAME}_DEPENDENT_RUNTIME_DIRS
     ${PROJECT_SOURCE_DIR}/res)

# Make build with dependent runtime binaries for windows
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E
        copy_directory_if_different ${${PROJECT_NAME}_DEPENDENT_RUNTIME_DIRS} $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()