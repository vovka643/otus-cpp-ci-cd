#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
auto split(const std::string &str, char d)
{
    std::vector<std::string> r;

    auto stop = str.find_first_of(d);
    decltype(stop) start = 0;
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void output_ip_pool(std::ostream& out, const std::vector<std::vector<std::string>> & ip_pool, 
                        bool (*filter)(const std::vector<std::string>&) = [](auto & ip){return true;})
{
    for(const auto & ip: ip_pool)
    {
        if (filter(ip))
        {
            for(const auto & ip_part: ip)
            {   
                if (ip_part != ip[0])
                {
                    out << ".";
                }
                out<< ip_part;
            }
            out << std::endl;
        }
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool{};

        std::ifstream file;
        file.open("ip_filter.tsv"); 

        //read from file
        for(std::string line; std::getline(file, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }
        file.close();

        //reverse lexicographically sort
        auto greater = [](const auto & a, const auto & b){
            for (int i = 0; i<4; ++i){
                if (a[i] == b[i]){
                    continue;
                }
                else {
                    return atoi(a[i].c_str())>atoi(b[i].c_str());
                }
            }
            return false; 
        };
        
        std::sort(ip_pool.begin(), ip_pool.end(), greater);

        // output ip pool
        output_ip_pool(std::cout, ip_pool);
       
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // filter by first byte and output
        // ip = filter(1)
        auto filter1 = [](const auto& ip_addr){
            return ip_addr[0] == "1";
        };

        output_ip_pool(std::cout, ip_pool, filter1);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // filter by first and second bytes and output
        // ip = filter(46, 70)
        auto filter2 = [](const auto & ip_addr){
            return (ip_addr[0] == "46") && (ip_addr[1] == "70");
        };

        output_ip_pool(std::cout, ip_pool, filter2);

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        auto filter3 = [](const auto & ip_addr){
            std::string value = "46";
            return ((ip_addr[0] == value) || (ip_addr[1] == value) || (ip_addr[2] == value) || (ip_addr[3] == value));
        };

        output_ip_pool(std::cout, ip_pool, filter3);

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
