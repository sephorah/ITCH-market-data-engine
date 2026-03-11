add_executable(MarketDataEngineTests TestParser.cpp)
target_link_libraries(MarketDataEngineTests PRIVATE ${PROJECT_NAME} gtest::gtest)

add_test(NAME MarketDataEngineTests COMMAND MarketDataEngineTests)