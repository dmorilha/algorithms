#include <iostream>
#include <list>

#include "sieve-eratosthenes.hpp"

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
