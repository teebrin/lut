

enable_testing()
add_executable(lut_tests EXCLUDE_FROM_ALL
        EvenLut.cpp
        UnevenLut.cpp
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(lut_tests
        PRIVATE
        GTest::gtest_main
        lut)

add_test(NAME all_tests COMMAND lut_tests)