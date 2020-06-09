#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

int main() {
	int n = 1;
	int i;
	int j;
	float stirling;
	float absolute_error;
	float relative_error;
	unsigned long long factorial = 1;


	printf("n	|	n!	|	Stirling`s	|	Absolute error	|	Relative Error	|");
	printf("\n------------------------------------------------------------------------------------------------");
	for (j = 0; j < 10; j++) {
		factorial = 1;
		for (i = 1; i <= n; ++i) {
			
			factorial *= i;
		}

		stirling = sqrt(2 * M_PI * n) * pow(n / M_E, n);
		absolute_error = factorial - stirling;
		relative_error = (absolute_error / factorial) * 100;

		printf("\n%d	|	%llu	|	%.6f	|	%.6f	|	%.6f	|", n, factorial, stirling, absolute_error, relative_error);
		printf("\n------------------------------------------------------------------------------------------------");

		n++;
	}
	return 0;
}