find_package(Catch2 REQUIRED)
include(Catch)

add_executable(unit_test unit_test.cpp)
target_link_libraries(unit_test raxpp Catch2::Catch2)
target_compile_features(unit_test PRIVATE cxx_std_17)
catch_discover_tests(unit_test)
