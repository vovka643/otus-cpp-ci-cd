#include <cstdlib>
#include <cstring>
#include <new>
#include <utility>

template <typename T, int N> struct my_allocator {
  using value_type = T;

  using pointer = T *;
  using const_pointer = const T *;
  using reference = T &;
  using const_reference = const T &;

  template <typename U> struct rebind { using other = my_allocator<U, N>; };

  my_allocator();
  ~my_allocator();

  template <typename U> my_allocator(const my_allocator<U, N> &);

  T *allocate(std::size_t n);

  void deallocate(T *p, std::size_t n);

  template <typename U, typename... Args> void construct(U *p, Args &&...args);

  template <typename U> void destroy(U *p);

private:
  void *m_p_begin = nullptr; // pointer to pool of memory
  void *m_p = nullptr;       // pointer to current;
  int m_n = 0;               // element counter
};

template <typename T, int N> my_allocator<T, N>::my_allocator() {
  m_p_begin = std::malloc((N + 1) * sizeof(T));
  m_p = m_p_begin;
}

template <typename T, int N> my_allocator<T, N>::~my_allocator() {
  std::free(m_p_begin);
};

template <typename T, int N>
template <typename U>
my_allocator<T, N>::my_allocator(const my_allocator<U, N> &) {}

template <typename T, int N> T *my_allocator<T, N>::allocate(std::size_t n) {
  if (m_n + n <= N) {
    m_p = m_p + n * sizeof(T);
    m_n = m_n + n;
    return reinterpret_cast<T *>(m_p);
  } else {
    throw std::bad_alloc();
  }
}

template <typename T, int N>
void my_allocator<T, N>::deallocate(T *p, std::size_t n) {
  // empty dealocate
}

template <typename T, int N>
template <typename U, typename... Args>
void my_allocator<T, N>::construct(U *p, Args &&...args) {
  new (p) U(std::forward<Args>(args)...);
};

template <typename T, int N>
template <typename U>
void my_allocator<T, N>::destroy(U *p) {
  p->~U();
}