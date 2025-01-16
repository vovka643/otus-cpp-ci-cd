#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>

void print_ip(std::string input)
{
    std::cout<< "std::string \n";
}

template<typename T,
         class = typename std::enable_if_t<std::is_integral_v<T>>>
void print_ip (T input)
{
    std::cout<< "int \n";
    int some = input && 0x15;
    std::cout << some << "\n";
    // some = some << 4;
    // std::cout << some << "\n";
}

template<typename T>
void print_ip (std::initializer_list<T> input)
{
    std::cout<< "int \n";
}

template<typename T>
void print_ip(std::vector<T> input)
{
    std::cout<< "std::vector<T> \n";
}

template<typename T>
void print_ip(std::list<T> input)
{
    std::cout<< "std::list<T> \n";
}

template<typename ...T>
void print_ip(std::tuple<T...> input)
{
    std::cout<< "std::tuple<T> \n";
}

int main()
{
    print_ip( int8_t{-1} ); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
    print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
    
    return 0;
}