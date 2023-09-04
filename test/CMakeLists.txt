find_package(Boost REQUIRED
                   COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIR})
add_subdirectory(sat)
