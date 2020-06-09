#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>


int main() {

	double x_value = 0.0;
	double relative_error = 0.0;
	double exact_value = 0.0;
	double absolute_error = 0.0;
	double maclaurin_Series = 0.0;
	int num_of_terms = 10;
	char input[5] = { 0 };

	printf("Please, enter a value for x: ");
	//fgets(input, 5, stdin);
	//x_value = (double)atof(input);
	x_value = 0.5;

	maclaurin_Series = 0.0f;

	exact_value = log(x_value);

	printf("\nexact value		maclaurin series	absolute error		relative error");

	for (int n = 1.; n < num_of_terms; n++) {

		maclaurin_Series += (pow(-1, n-1) * (pow(x_value-1, n) /  n));

		absolute_error = maclaurin_Series - exact_value;

		relative_error = ((absolute_error / maclaurin_Series) * 100);

	}

	printf("\n%7lf		%7lf		%7lf		%7lf", exact_value, maclaurin_Series, absolute_error, relative_error);

	return 0;
}
