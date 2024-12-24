#include <memory>

template <class T> class my_iterator;

template <class T, class Allocator = std::allocator<T>> class my_container {
public:
  explicit my_container(int capacity);
  ~my_container();

  bool add(T element);
  bool get(int num, T *return_val);
  bool set(int num, T new_val);
  int length();

  typedef my_iterator<T> iterator;

  iterator begin();
  iterator end();

private:
  T *m_array;

  int m_length;
  int m_capacity;

  Allocator m_allocator;
};

template <typename T> class my_iterator {
private:
  template <class U, class Allocator> friend class my_container;

public:
  my_iterator(const my_iterator &it);

  bool operator!=(my_iterator const &other) const;
  bool operator==(my_iterator const &other) const;
  T &operator*() const;
  my_iterator &operator++();

private:
  my_iterator(T *p);
  T *m_p;
};

template <class T, class Allocator>
my_container<T, Allocator>::my_container(int capacity) : m_capacity(capacity) {
  m_array = m_allocator.allocate(m_capacity);
  m_length = 0;
}

template <class T, class Allocator>
my_container<T, Allocator>::~my_container() {
  m_allocator.destroy(m_array);
  m_allocator.deallocate(m_array, m_capacity);
}

template <class T, class Allocator>
bool my_container<T, Allocator>::add(T element) {
  if (m_length == m_capacity) {
    return false;
  } else {
    m_allocator.construct(m_array + m_length, element);
    ++m_length;
    return true;
  }
}

template <class T, class Allocator>
bool my_container<T, Allocator>::get(int num, T *return_val) {
  if (num < m_length) {
    *return_val = m_array[num];
    return true;
  } else {
    return false;
  }
}

template <class T, class Allocator>
bool my_container<T, Allocator>::set(int num, T new_val) {
  if (num < m_length) {
    m_array[num] = new_val;
    return true;
  } else {
    return false;
  }
}

template <class T, class Allocator> int my_container<T, Allocator>::length() {
  return m_length;
}

template <class T, class Allocator>
my_iterator<T> my_container<T, Allocator>::begin() {
  return my_iterator<T>(m_array);
}

template <class T, class Allocator>
my_iterator<T> my_container<T, Allocator>::end() {
  return my_iterator<T>(m_array + m_length - 1);
}

//--------my_iterator---------
template <typename T>
my_iterator<T>::my_iterator(const my_iterator &it) : m_p(it.m_p) {}

template <typename T>
bool my_iterator<T>::operator!=(my_iterator const &other) const {
  return (m_p != other.m_p);
}

template <typename T>
bool my_iterator<T>::operator==(my_iterator const &other) const {
  return (m_p == other.m_p);
}

template <typename T> T &my_iterator<T>::operator*() const { return *m_p; }

template <typename T> my_iterator<T> &my_iterator<T>::operator++() {
  m_p = m_p + 1;
  return *this;
}

template <typename T> my_iterator<T>::my_iterator(T *p) : m_p(p) {}