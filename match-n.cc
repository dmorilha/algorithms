#include <iostream>
#include <stack>
#include <vector>

#include <cassert>

using namespace std;

template < class T, int N >
struct MatchGame {

  struct Entry {
    T type;
    size_t count;
  };

  typedef vector< T > State;
  typedef stack< Entry > Stack;

  static void match(State & v) {
    Stack s;
    int i = 0, j = 0;
    while (v.size() > i) {
      if (s.empty())
        s.emplace(Entry{v[i], 1});

      else if (s.top().type == v[i])
        ++s.top().count;

      else if (N <= s.top().count) {
        j -= s.top().count;
        assert(0 <= j);
        s.pop();

        // we just re-do the same checks without incrementing i or j
        continue;

      } else
        s.emplace(Entry{v[i], 1});

      v[j] = v[i];
      ++i;
      ++j;
    }

    if ( ! s.empty() && N <= s.top().count) {
      j -= s.top().count;
      assert(0 <= j);
      s.pop();
    }

    v.resize(j);
  }

  static void print(const State & s) {
    if ( ! s.empty()) {
      cout << s[0];
      for (int i = 1; s.size() > i; ++i) {
        cout << ", " << s[i];

      }
      cout << endl;
    }
  }
};


int main(void) {
  typedef MatchGame< int, 3 > Match3;

  Match3::State state = {1, 2, 2, 3, 3, 3, 2, 2, 1};

  cout << "input: ";
  Match3::print(state);

  Match3::match(state);

  cout << "output: ";
  Match3::print(state);

  assert(2 == state.size());
  assert(1 == state[0]);
  assert(1 == state[1]);

  return 0;
}
