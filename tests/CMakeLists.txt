add_executable(hello-tests test_hello.cpp)
target_link_libraries(hello-tests hello CONAN_PKG::gtest)

add_executable(ip_filter-tests ip_filter-tests.cpp)
target_link_libraries(ip_filter-tests ip_filter_lib CONAN_PKG::gtest)

# add_executable(allocator-tests allocator-tests.cpp)
# target_link_libraries(allocator-tests CONAN_PKG::gtest)

add_test(HelloTest "${CMAKE_BINARY_DIR}/bin/hello-tests")
add_test(IpFilterTest "${CMAKE_BINARY_DIR}/bin/ip_filter-tests")
# add_test(AllocatorTest "${CMAKE_BINARY_DIR}/bin/allocator_tests")