project (ip_filters)

add_library(ip_filter_lib ip_filter.cpp)
target_compile_features(ip_filter_lib PUBLIC cxx_std_17)

add_executable(ip_filter ip_filter_main.cpp)
target_link_libraries(ip_filter ip_filter_lib)