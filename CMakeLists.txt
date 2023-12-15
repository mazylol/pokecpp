cmake_minimum_required(VERSION 3.16)
project(PokeCPP VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME}
        include/PokeCPP.h
        src/PokeCPP.cpp
        src/pokemon/export.h
        src/pokemon/base.h)

include (cmake/CPM.cmake)

include(FetchContent)

# cURLpp for HTTP requests
FetchContent_Declare(
        curlpp
        GIT_REPOSITORY https://github.com/jpbarrette/curlpp.git
        GIT_TAG origin/master
)
FetchContent_MakeAvailable(curlpp)

# nlohmann/json for JSON parsing
CPMAddPackage(
        NAME nlohmann_json
        GITHUB_REPOSITORY nlohmann/json
        VERSION 3.11.2
)

target_link_libraries(${PROJECT_NAME} curlpp nlohmann_json::nlohmann_json)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(test test.cpp)
target_link_libraries(test PokeCPP)