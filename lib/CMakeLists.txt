cmake_minimum_required(VERSION 3.20)

project(
    ITCHMarketDataEngineCore
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

find_package(cxxopts REQUIRED)
find_package(nlohmann_json REQUIRED)

add_library(${PROJECT_NAME} SHARED src/ArgParser.cpp src/ConfigParser.cpp src/FeedHandler.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_libraries(${PROJECT_NAME} PRIVATE
    cxxopts::cxxopts
    nlohmann_json::nlohmann_json)