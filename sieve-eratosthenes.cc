#include <iostream>
#include <list>

#include "sieve-eratosthenes.h"

using namespace std;

int main(int argc, char * * argv) {
  typedef list< uint32_t > list;
  list primes;

  uint32_t upperBound = 1000000;

  SieveEratosthenes(upperBound, primes);

  list::const_iterator iterator;
  const list::const_iterator end(primes.end());

  cout << "primes are:" << endl;

  for (iterator = primes.begin(); iterator != end; iterator++) {
    cout << *iterator << endl;
  }

  return 0;
}
