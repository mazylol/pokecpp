cmake_minimum_required(VERSION 3.22)
project(pokecpp)

set(CMAKE_CXX_STANDARD 20)

add_library(pokecpp PokeCPP.cpp
        pokemon/export.h
        pokemon/base.h)

include(FetchContent)

# cURLpp for HTTP requests
FetchContent_Declare(
        cURLpp
        GIT_REPOSITORY https://github.com/jpbarrette/curlpp.git
        GIT_TAG        origin/master
)
FetchContent_MakeAvailable(cURLpp)

# nlohmann/json for JSON parsing
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(${PROJECT_NAME} curlpp nlohmann_json::nlohmann_json)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test test.cpp)
target_link_libraries(test pokecpp)