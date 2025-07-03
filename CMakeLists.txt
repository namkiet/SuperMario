cmake_minimum_required(VERSION 3.10...3.26)

project(DS CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Gather source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/source/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/lib/")

# Find raylib installed on the system
add_subdirectory(external/raylib)

# Declare the executable
add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}  
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${PROJECT_INCLUDE}
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

set(CMAKE_BUILD_TYPE Debug) # Ensure the build type is Debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g") # Add debugging symbols

# Setting RES_PATH
target_compile_definitions(${PROJECT_NAME} PUBLIC RES_PATH="${CMAKE_CURRENT_LIST_DIR}/res/")