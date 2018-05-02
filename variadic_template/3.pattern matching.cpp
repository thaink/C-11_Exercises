#include <iostream>

/**
 *this is an example how we peel off multiple arguments at a time
 */

using namespace std;
template<typename T>
bool pair_comparer(T a, T b) {
  // In real-world code, we wouldn't compare floating point values like
  // this. It would make sense to specialize this function for floating
  // point types to use approximate comparison.
  return a == b;
}

template<typename T, typename... Args>
bool pair_comparer(T a, T b, Args... args) {
  return a == b && pair_comparer(args...);
}

int main()
{
    cout << pair_comparer(1.5, 1.5, 2, 2, 6, 6) << '\n';
    return 0;
}

