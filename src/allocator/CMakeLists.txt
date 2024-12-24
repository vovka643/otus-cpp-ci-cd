project(allocator)

# add_library(my_allocator_lib my_allocator.cpp)
# target_compile_features(my_allocator_lib PUBLIC cxx_std_17)

# add_library(my_container_lib my_container.cpp my_iterator.cpp)
# target_compile_features(my_container_lib PUBLIC cxx_std_17)

add_executable(allocator_main main.cpp)
# target_link_libraries(allocator_main my_allocator_lib my_container_lib)