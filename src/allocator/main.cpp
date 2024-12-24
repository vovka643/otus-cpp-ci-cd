#include "my_allocator.h"
#include "my_container.h"
#include <iostream>
#include <map>
#include <string>

int main() {
  // std::cout <<"создание экземпляра std::map<int, int> \n";
  std::map<int, int> std_map;

  // std::cout <<"заполнение 10 элементами, где ключ - это число от 0 до 9, а
  // значение - факториал ключа\n";
  std_map[0] = 1;
  for (int i = 1; i < 10; ++i) {
    std_map[i] = std_map[i - 1] * i;
  }

  // std::cout <<"создание экземпляра std::map<int, int> с новым аллокатором,
  // ограниченным 10 элементами \n";
  std::map<int, int, std::less<int>, my_allocator<std::pair<int, int>, 10>>
      map1;

  // std::cout <<"заполнение 10 элементами, где ключ - это число от 0 до 9, а
  // значение - факториал ключа \n";
  map1[0] = 1;
  for (int i = 1; i < 10; ++i) {
    map1[i] = map1[i - 1] * i;
  }

  // std::cout <<"вывод на экран всех значений (ключ и значение разделены
  // пробелом) хранящихся в контейнере \n";
  for (const auto &it : map1) {
    std::cout << it.first << " " << it.second << "\n";
  }

  // std::cout <<"создание экземпляра своего контейнера для хранения значений
  // типа int, заполнение 10 элементами от 0 до 9 \n";
  my_container<int> array(10);
  for (int i = 0; i < 10; ++i) {
    array.add(i);
  }

  // std::cout <<"создание экземпляра своего контейнера для хранения значений
  // типа int с новым аллокатором,ограниченным 10 элементами \n";
  my_container<int, my_allocator<int, 10>> array2(10);

  // std::cout <<"заполнение 10 элементами от 0 до 9 \n";
  for (int i = 0; i < 10; ++i) {
    array2.add(i);
  }

  // std::cout <<"вывод на экран всех значений, хранящихся в контейнере \n";
  for (auto &elem : array2) {
    std::cout << elem << "\n";
  }

  return 0;
}