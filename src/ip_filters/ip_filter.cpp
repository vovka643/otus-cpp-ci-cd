
#include "ip_filter.h"

auto split(const std::string &str, char d) {
  std::vector<std::string> r;

  auto stop = str.find_first_of(d);
  decltype(stop) start = 0;
  while (stop != std::string::npos) {
    r.push_back(str.substr(start, stop - start));

    start = stop + 1;
    stop = str.find_first_of(d, start);
  }

  r.push_back(str.substr(start));

  return r;
}

std::vector<std::array<int, 4>>
filter_ip_pool(const std::vector<std::array<int, 4>> &ip_pool,
               bool (*filter)(const std::array<int, 4> &)) {
  std::vector<std::array<int, 4>> r;
  for (const auto &ip : ip_pool) {
    if (filter(ip)) {
      r.push_back(ip);
    }
  }

  return r;
}

void output_ip_pool(std::ostream &out,
                    const std::vector<std::array<int, 4>> &ip_pool) {
  for (const auto &ip : ip_pool) {
    for (const auto &ip_part : ip) {
      if (ip_part != ip[0]) {
        out << ".";
      }
      out << ip_part;
    }
    out << std::endl;
  }
}

std::vector<std::array<int, 4>> &get_ip_pool_from_file(std::string filename) {
  static std::vector<std::array<int, 4>> ip_pool{};

  std::ifstream file;
  file.open(filename);
  if (!file.is_open()) {
    return ip_pool;
  }

  // read from file
  for (std::string line; std::getline(file, line);) {
    auto v = split(line, '\t');
    std::vector<std::string> str_ip(split(v.at(0), '.'));
    ip_pool.push_back({atoi(str_ip.at(0).c_str()), atoi(str_ip.at(1).c_str()),
                       atoi(str_ip.at(2).c_str()), atoi(str_ip.at(3).c_str())});
  }
  file.close();

  return ip_pool;
}