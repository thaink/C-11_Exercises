#include <iostream>

using namespace std;

/**
 * example of using sizeof... instead of define seperate function
 */

namespace folly {

  template <typename T, typename... Ts>
  size_t hash_combine(const T& t, const Ts&... ts) {
    size_t seed = std::hash<T>()(t);
    if (sizeof...(ts) == 0) {
      return seed;
    }
    size_t remainder = hash_combine(ts...);   // not recursion!
    return hash_128_to_64(seed, remainder);
  }
} //namespace

// Simple example
struct Obj {
  int x;
  string y;
  float z;

  size_t hash() const { return folly::hash_combine(x,y,z); }
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

