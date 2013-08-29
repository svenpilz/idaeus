#include <math.h>
#include <stdio.h>

double factorial(unsigned int n) {
	if (n <= 1) {
		return 1;
	} else {
		return factorial(n-1) * n;
	}
}

double pow(double base, unsigned int exp) {
	if (exp == 0) {
		return 1;
	} else if (exp == 1) {
		return base;
	} else {
		double result = 1;
		
		for (; exp > 0; --exp) {
			result *= base;
		}
		
		return result;
	}
}

double sin(double x) {
	double s = 0;
	
	for (unsigned int k = 0; k < 13; ++k) {
		s += pow(-1, k)/factorial(2*k+1) * pow(x, 2*k+1);
	}
	
	return s;
}

double cos(double x) {

}
