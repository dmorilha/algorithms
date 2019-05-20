#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include <cassert>

using namespace std;

template < class I, class C >
I partition(I i, I j) {
  static random_device rd;
  static mt19937 gen(rd());
  const C c;
  assert(i + 2 < j);
  const typename I::value_type pivot = *(i
      + uniform_int_distribution< size_t >(1, (j - i) - 2)(gen));
  cerr << "pivot " << pivot << endl;
  while (i <= j) {
    do --j;
    while (c(pivot, *j));

    while (c(*i, pivot))
        ++i;

    if (i < j)
      swap(*i++, *j);
  }

  return ++j; //counter intuitive as fuck, but we have sentinel end iterators.
}

template < class I, class C = less< typename I::value_type > >
void quickSort(const I i, I j) {
  if (i + 2 < j) {
    for (I x = i; x != j; ++x)
      cerr << *x << " ";
    cerr << endl;
    const I l = partition< I, C >(i, j);
    for (I x = i; x != j; ++x)
      cerr << *x << " ";
    cerr << endl << endl;
    quickSort(i, l);
    quickSort(l, j);
  } else if (i + 1 == --j)
    if (C()(*j, *i))
      swap(*j, *i);
}

int main(void) {
  vector< int > v = {2, 7, 1, 0, 1000, 5, 3, 8, 6, 4, 9, 1, 1, 1, 2, 9, 2, 9, 2, 9};
  quickSort(v.begin(), v.end());
  for (const auto & item : v)
    cout << item << " ";
  cout << endl;
  return ! is_sorted(v.begin(), v.end());
}
