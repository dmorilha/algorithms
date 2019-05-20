#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

template < class I, class C = less< typename I::value_type > >
void mergeSort(I i, const I j) {
  const C c;
  using MyVector = vector< typename I::value_type >;
  const auto size = j - i;
  if (1 < size) {
    const auto half = size / 2;
    mergeSort(i, i + half);
    mergeSort(i + half, j);
    const I k = i + half, n = i;
    I l = i + half;
    MyVector v(size);
    auto m = v.begin();

    while (i != k && l != j)
      if (c(*i, *l))
        *(m++) = *(i++);

      else
        *(m++) = *(l++);

    while (i != k)
      *(m++) = *(i++);

    while (l != j)
      *(m++) = *(l++);

    assert(v.end() == m);

    //ideally we can remove this copy by just alternating the vectors.
    copy(v.begin(), m, n);
  }
}

int main(void) {
  vector< int > v = {2, 7, 1, 0, 5, 3, 8};
  mergeSort(v.begin(), v.end());
  for (const auto & item : v) {
    cout << item << " ";
  }
  cout << endl;
  return 0;
}
