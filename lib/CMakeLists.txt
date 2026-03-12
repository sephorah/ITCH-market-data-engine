find_package(nlohmann_json REQUIRED)

add_library(ITCHMarketDataEngineCore SHARED src/ConfigParser.cpp src/Engine.cpp)

set_target_properties(ITCHMarketDataEngineCore PROPERTIES
    VERSION 1.0
    SOVERSION 1
)

target_include_directories(ITCHMarketDataEngineCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(ITCHMarketDataEngineCore PRIVATE cxx_std_20)
target_link_libraries(ITCHMarketDataEngineCore PUBLIC nlohmann_json::nlohmann_json)

add_subdirectory(tests)