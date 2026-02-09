add_executable(hello_world_tests src/test_Addition.cpp)

target_link_libraries(
    hello_world_tests
    PRIVATE GTest::gtest_main
    PRIVATE hello_world_lib
)

# Ensure test target sees library headers
target_include_directories(hello_world_tests PRIVATE src)

include(GoogleTest)
gtest_discover_tests(hello_world_tests)
