#include <filesystem>
#include <fstream>
#include <sstream>

#include "../src/ip_filters/ip_filter.h"
#include "gmock/gmock.h"
#include <gtest/gtest.h>

// test parsing
TEST(ip_filter, get_ip_pool_from_file) {
  // write data test to file
  std::ofstream ip_file;
  const char *file_name = "tmp_test_file.txt";
  ip_file.open(file_name);
  ip_file << "192.168.72.2 50 11\n";
  ip_file << "0.0.0.0 17\n";
  ip_file << "192.168..2 \n";

  ip_file.close();

  // read test data from file
  auto ip_pool = get_ip_pool_from_file("tmp_test_file.txt");

  EXPECT_THAT(ip_pool[0], testing::ElementsAre(192, 168, 72, 2));
  EXPECT_THAT(ip_pool[1], testing::ElementsAre(0, 0, 0, 0));
  EXPECT_THAT(ip_pool[2], testing::ElementsAre(192, 168, 0, 2));

  std::filesystem::remove(file_name);
}

// test filtering

TEST(ip_filter, filter_1) {
  // write data test to file
  std::ofstream ip_file;
  const char *file_name = "tmp_test_file.txt";
  ip_file.open(file_name);
  ip_file << "67.183.246.205	2	0\n";
  ip_file << "218.185.237.250	5	0\n";
  ip_file << "74.136.5.194	8	0\n";
  ip_file << "14.187.212.140	11	0\n";
  ip_file << "149.3.43.228	0	1\n";
  ip_file << "141.101.132.191	63	0\n";
  ip_file << "189.216.159.43	2	0\n";
  ip_file << "5.8.47.84	83	0\n";
  ip_file << "50.26.133.146	2	0\n";
  ip_file << "83.221.180.18	0	4\n";
  ip_file << "117.213.109.57	0	1\n";
  ip_file << "109.193.71.64	0	1\n";
  ip_file << "46.70.147.26	1	0\n";
  ip_file << "188.166.49.134	3	2\n";
  ip_file << "117.198.224.130	0	1\n";
  ip_file << "77.179.162.181	0	2\n";
  ip_file << "27.251.253.58	2017	0\n";
  ip_file << "75.69.188.107	7	0\n";
  ip_file << "198.48.136.200	169	0\n";
  ip_file << "186.92.150.52	0	1\n";
  ip_file << "184.170.28.62	1	0\n";
  ip_file << "47.44.49.2	4	0\n";
  ip_file << "24.23.88.218	1	0\n";
  ip_file << "24.23.88.218	1	0\n";
  ip_file << "220.180.121.6	1	0\n";

  ip_file.close();

  // read test data from file
  auto ip_pool = get_ip_pool_from_file("tmp_test_file.txt");

  auto filter1 = [](const auto &ip_addr) { return ip_addr[0] == 24; };

  auto filtered_ip_pool = filter_ip_pool(ip_pool, filter1);

  EXPECT_THAT(filtered_ip_pool[0], testing::ElementsAre(24, 23, 88, 218));
  // EXPECT_THAT(filtered_ip_pool[1], testing::ElementsAre(24,23,88,218));
}

TEST(ip_filter, filter_2) {
  // write data test to file
  std::ofstream ip_file;
  const char *file_name = "tmp_test_file.txt";
  ip_file.open(file_name);
  ip_file << "85.253.112.79	0	4\n";
  ip_file << "190.213.37.222	1	3\n";
  ip_file << "70.234.198.76	2	0\n";
  ip_file << "70.234.198.76	2	0\n";
  ip_file << "5.188.216.204	136	0\n";
  ip_file << "69.251.6.155	2	0\n";
  ip_file << "93.34.197.129	0	2\n";
  ip_file << "5.8.47.202	77	0\n";
  ip_file << "14.162.206.233	6	0\n";
  ip_file << "1.231.69.33	1	0\n";
  ip_file << "69.23.42.183	3	0\n";
  ip_file << "63.87.226.66	1	0\n";
  ip_file << "5.254.65.190	0	3\n";
  ip_file << "37.33.109.179	0	2\n";
  ip_file << "1.1.234.8	0	1\n";
  ip_file << "119.201.4.165	1	0\n";
  ip_file << "179.218.84.120	13	0\n";
  ip_file << "5.101.217.139	322	0\n";
  ip_file << "96.92.198.213	1	0\n";
  ip_file << "96.92.198.213	1	0\n";
  ip_file << "117.248.24.152	0	1\n";
  ip_file << "85.253.148.39	0	2 \n";

  ip_file.close();

  // read test data from file
  auto ip_pool = get_ip_pool_from_file("tmp_test_file.txt");

  auto filter2 = [](const auto &ip_addr) {
    return (ip_addr[1] == 234) && (ip_addr[3] == 76);
  };
  auto filtered_ip_pool = std::move(filter_ip_pool(ip_pool, filter2));

  EXPECT_THAT(filtered_ip_pool[0], testing::ElementsAre(70, 234, 198, 76));
  EXPECT_THAT(filtered_ip_pool[1], testing::ElementsAre(70, 234, 198, 76));
}

TEST(ip_filter, filter_3) {
  // write data test to file
  std::ofstream ip_file;
  const char *file_name = "tmp_test_file.txt";
  ip_file.open(file_name);
  ip_file << "99.169.226.169	1	0 \n";
  ip_file << "73.104.80.103	1	0 \n";
  ip_file << "73.104.80.103	1	0 \n";
  ip_file << "79.206.209.45	0	1 \n";
  ip_file << "103.220.209.173	0	1 \n";
  ip_file << "66.249.92.198	6	0 \n";
  ip_file << "47.16.77.236	0	2 \n";
  ip_file << "89.38.96.66	7	0 \n";
  ip_file << "75.206.129.73	1	0 \n";
  ip_file << "129.56.12.56	30	0 \n";
  ip_file << "5.8.47.44	961	0 \n";
  ip_file << "193.24.92.54	0	4 \n";
  ip_file << "156.222.243.190	1	0 \n";
  ip_file << "176.228.138.151	0	1 \n";
  ip_file << "176.228.138.151	0	1 \n";
  ip_file << "176.228.138.151	0	1 \n";
  ip_file << "181.122.209.200	3	0 \n";
  ip_file << "35.193.144.59	803	0 \n";
  ip_file << "101.24.171.210	32	50 \n";
  ip_file << "188.68.0.185	34	0 \n";
  ip_file << "113.195.165.235	5	0 \n";

  ip_file.close();

  // read test data from file
  auto ip_pool = get_ip_pool_from_file("tmp_test_file.txt");

  auto filter3 = [](const auto &ip_addr) {
    auto value = 138;
    return ((ip_addr[0] == value) || (ip_addr[1] == value) ||
            (ip_addr[2] == value) || (ip_addr[3] == value));
  };

  auto filtered_ip_pool = std::move(filter_ip_pool(ip_pool, filter3));

  EXPECT_THAT(filtered_ip_pool[0], testing::ElementsAre(176, 228, 138, 151));
  EXPECT_THAT(filtered_ip_pool[1], testing::ElementsAre(176, 228, 138, 151));
  EXPECT_THAT(filtered_ip_pool[2], testing::ElementsAre(176, 228, 138, 151));
}