#include <iostream>
#include <math.h>

static const long double exponentiation(const long double base, const unsigned char exponent) {

	long double a;
	
	if (exponent < 2) {
		a = 1;

	} else {
		a = exponentiation(base, floor(exponent / 2));
	}

	return a *= a * ((exponent % 2 == 1)? base: 1);
}

int main(int argc, char * * argv) {

	for (int i = 0; i < 6; i += 1) {
		std::cout << "2.1 ^ " << i << " = " << exponentiation(2.1, i) << std::endl;
	}

	return 0;
}
