#include <iostream>
#include <list>

template< typename NUMBER_t, typename CONTAINER_t >
static void SieveEratosthenes(const NUMBER_t LIMIT, CONTAINER_t & container) {

	NUMBER_t
		a1 = 3,
		a2 = 0,
		b,
		c;

	uint32_t d;

	int16_t * buffer;

	const uint32_t BUFFER_SIZE(LIMIT / 2.5 / (sizeof(*buffer) * 8) + 1);
	const uint8_t S(sizeof(*buffer) * 8);


	// allocate and clear buffer.

	buffer = new int16_t[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);


	// add first 3 primes.

	if (LIMIT >= 2) {
		container.push_back(2);
	}

	if (LIMIT >= 3) {
		container.push_back(3);
	}

	if (LIMIT >= 5) {
		container.push_back(5);
	}


	// if less than 7 we are good to return.

	if (LIMIT < 7) {
		return;
	}


	// iterate for number 3.

	b = 3;
	c = 3 * 3;

	while (c <= LIMIT) {

		d = static_cast< uint32_t >(c / 2) - static_cast< uint32_t >((c + 5) / 10) - 1;
		buffer[d / S] |= 0x1 << (d % S);

		b += (b % 10 == 3)? 4: 2;
		c = a1 * b;
	}


	// iterate for number 7 and on.

	a1 += (a1 % 10 == 3)? 4: 2;
	a2++;

	while ( a1 <= LIMIT) {

		if ((buffer[a2 / S] & 0x1 << (a2 % S)) == 0) {

			container.push_back(a1);

			b = a1;
			c = a1 * b;

			while (c <= LIMIT) {

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

int main(int argc, char * * argv) {

	typedef std::list< uint32_t > list;
	list primes;

	uint32_t upperBound = 1000000;

	SieveEratosthenes(upperBound, primes);

	list::const_iterator iterator;
	const list::const_iterator end(primes.end());

	std::cout << "primes are:" << std::endl;

	for (iterator = primes.begin(); iterator != end; iterator++) {
		std::cout << *iterator << std::endl;
	}

	return 0;
}
