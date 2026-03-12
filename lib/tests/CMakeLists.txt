find_package(GTest REQUIRED)

add_executable(ParserTests TestParser.cpp)
target_link_libraries(ParserTests PRIVATE ITCHMarketDataEngineCore gtest::gtest)
target_compile_features(ParserTests PRIVATE cxx_std_20)

add_executable(EngineTests TestEngine.cpp)
target_link_libraries(EngineTests PRIVATE ITCHMarketDataEngineCore)
target_compile_features(EngineTests PRIVATE cxx_std_20)

include(GoogleTest)
gtest_discover_tests(ParserTests EngineTests)