#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>


int factorial(int n_factorial);

int main() {

	double x_value = 0.0;
	double relative_error = 0.0;
	double exact_value = 0.0;
	double absolute_error = 0.0;
	double maclaurin_Series = 0.0;
	int num_of_terms = 5;
	char input[5] = { 0 };

	printf("Please, enter a value for x: ");
	fgets(input, 5, stdin);
	x_value = (double)atof(input);

	printf("Enter a pre-specified approximate relative error: "); 
	fgets(input, 5, stdin);
	double given_relative_error = (float)atof(input);
	
	maclaurin_Series = 0.0f;

	// real value of the operation cos(x_value)
	exact_value = cos(x_value);

	printf("exact value		maclaurin series	absolute error		relative error");
	for (int n = 0.; n <= num_of_terms; n++) {

		maclaurin_Series += (pow(-1, n) * (pow(x_value, 2*n) / (double)factorial(2*n)));

		//absolute error
		absolute_error = maclaurin_Series - exact_value;
		//relative error
		relative_error = ((absolute_error / maclaurin_Series) * 100);
		if (relative_error < 0) {
			relative_error *= (-1);
		}

		printf("\n%7lf		%7lf		%7lf		%7lf", exact_value, maclaurin_Series, absolute_error, relative_error);

		if (relative_error < given_relative_error) {
			break;
		}
		}
	

	return 0;
}

int factorial(int n_factorial) {

	if (n_factorial <= 1) {
		return 1;
	}
	return (n_factorial * factorial(n_factorial - 1));
}