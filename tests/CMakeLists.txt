add_executable(hello_world_tests
        src/test_Addition.cpp
)

target_link_libraries(hello_world_tests
        PRIVATE GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_world_tests)
