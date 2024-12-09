project (ip_filters)

add_library(ip_filter_lib ip_filter.cpp)

add_executable(ip_filter ip_filter_main.cpp)
target_link_libraries(ip_filter ip_filter_lib)