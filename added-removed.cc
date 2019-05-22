#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <cassert>

using namespace std;

typedef vector< string > StringVector;

struct Result {
  vector< string > added;
  vector< string > removed;
};

template < class C = less< string > >
Result compare(const vector< string > & previous, const vector< string > & current) {
  assert(is_sorted(previous.begin(), previous.end()));
  assert(is_sorted(current.begin(), current.end()));

  Result result;

  C c;

  int i = 0, j = 0;

  while (previous.size() > i && current.size() > j)
    if (c(previous[i], current[j]))
      result.removed.push_back(previous[i++]);

    else if (c(current[j], previous[i]))
        result.added.push_back(current[j++]);

    else {
      ++i;
      ++j;
    }

  while (previous.size() > i)
    result.removed.push_back(previous[i++]);

  while (current.size() > j)
    result.added.push_back(current[j++]);

  return result;
}

int main(void) {
  StringVector a = {"foo", "bar", "baz"},
               b = {"bar", "bar1", "foo"};

  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  Result result = compare(a, b);

  if ( ! result.added.empty()) {
    cout << "added: " << result.added[0];
    for (int i = 1; result.added.size() > i; ++i)
      cout << ", " << result.added[i];
    cout << endl;
  }

  if ( ! result.removed.empty()) {
    cout << "removed: " << result.removed[0];
    for (int i = 1; result.removed.size() > i; ++i)
      cout << ", " << result.removed[i];
    cout << endl;
  }
}
