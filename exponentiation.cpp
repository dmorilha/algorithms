#include <iostream>

static const long double exponentiation(const long double base, const uint8_t exponent) {

	long double a;
	
	if (exponent < 2) {
		a = 1;

	} else {
		a = exponentiation(base, static_cast< uint8_t >(exponent / 2));
	}

	return a *= a * ((exponent % 2 == 1)? base: 1);
}

int main(int argc, char * * argv) {

	for (int i = 0; i < 6; i += 1) {
		std::cout << "2.1 ^ " << i << " = " << exponentiation(2.1, i) << std::endl;
	}

	return 0;
}
