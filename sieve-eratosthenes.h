#ifndef SIEVE_ERATOSTHENES_HPP
#define SIEVE_ERATOSTHENES_HPP

#include <cstring>

//TODO: implement lower bound
template< typename NUMBER_t, typename CONTAINER_t >
static void SieveEratosthenes(const NUMBER_t UPPER_BOUND, CONTAINER_t & container) {

  NUMBER_t a1 = 3, a2 = 0, b, c;

  uint32_t d;

  int16_t * buffer;

  const uint32_t BUFFER_SIZE(UPPER_BOUND / 2.5 / (sizeof(*buffer) * 8) + 1);
  const uint8_t S(sizeof(*buffer) * 8);

  // allocate and clear buffer.
  buffer = new int16_t[BUFFER_SIZE];
  memset(buffer, 0, BUFFER_SIZE);


  // add first 3 primes.
  if (UPPER_BOUND >= 2) {
    container.push_back(2);
  }

  if (UPPER_BOUND >= 3) {
    container.push_back(3);
  }

  if (UPPER_BOUND >= 5) {
    container.push_back(5);
  }


  // if less than 7 we are good to return.
  if (UPPER_BOUND < 7) {
    return;
  }


  // iterate for number 3.
  b = 3;
  c = 3 * 3;

  while (c <= UPPER_BOUND) {
    d = static_cast< uint32_t >(c / 2) - static_cast< uint32_t >((c + 5) / 10) - 1;
    buffer[d / S] |= 0x1 << (d % S);

    b += b % 10 == 3 ? 4 : 2;
    c = a1 * b;
  }


  // iterate for number 7 and on.

  a1 += (a1 % 10 == 3)? 4: 2;
  a2++;

  while (a1 <= UPPER_BOUND) {
    if ((buffer[a2 / S] & 0x1 << (a2 % S)) == 0) {
      container.push_back(a1);

      b = a1;
      c = a1 * b;

      while (c <= UPPER_BOUND) {
        d = static_cast< uint32_t >(c / 2) - static_cast< uint32_t >((c + 5) / 10) - 1;
        buffer[d / S] |= 0x1 << (d % S);

        b += (b % 10 == 3)? 4: 2;
        c = a1 * b;
      }
    }

    a1 += (a1 % 10 == 3)? 4: 2;
    a2++;
  }


  // delete buffer.
  delete [] buffer;
}

#endif
