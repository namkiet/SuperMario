cmake_minimum_required(VERSION 3.28)
project(mario LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Only add -Wno-inconsistent-missing-override for non-MSVC compilers
if(NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-inconsistent-missing-override")
endif()

if (MSVC)
  add_compile_options(/bigobj)
endif()

include(FetchContent)

# ========================
# Fetch SFML
# ========================
FetchContent_Declare(
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        2.6.2
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM)
FetchContent_MakeAvailable(sfml)

# ========================
# Fetch ImGui
# ========================
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG        v1.89.9
)
FetchContent_MakeAvailable(imgui)

# ========================
# Fetch ImGui-SFML
# ========================
FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
  GIT_TAG        2.6.x
)
# Tell ImGui-SFML where to find ImGui (it needs this)
set(IMGUI_DIR ${imgui_SOURCE_DIR} CACHE INTERNAL "")
# Don't use find_package inside ImGui-SFML
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(imgui-sfml)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")


add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio ImGui-SFML::ImGui-SFML)
target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:GNU,Clang>:-frtti>
  $<$<CXX_COMPILER_ID:MSVC>:/GR>
)

if (CMAKE_CXX_COMPILER_ID MATCHES "AppleClang" OR CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=undefined -fsanitize=address")
    target_link_options(mario BEFORE PUBLIC -fsanitize=undefined PUBLIC -fsanitize=address)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

add_definitions(-DSFML_NO_DEPRECATED_WARNINGS)
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Compiler flags: ${CMAKE_CXX_FLAGS}")
