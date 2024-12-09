#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

auto split(const std::string &str, char d);

std::vector<std::array<int, 4>> filter_ip_pool(
    const std::vector<std::array<int, 4>> &ip_pool,
    bool (*filter)(const std::array<int, 4> &) = [](auto &ip) { return true; });

void output_ip_pool(std::ostream &out,
                    const std::vector<std::array<int, 4>> &ip_pool);

std::vector<std::array<int, 4>> &get_ip_pool_from_file(std::string filename);