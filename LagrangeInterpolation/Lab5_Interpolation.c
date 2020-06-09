#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>

int main() {

	int number_of_points = 0;
	char input[10] = { 0 };
	int interpolation_point = 0;
	double x_data_values[100];
	double y_data_values[100];

	printf("Please, enter a number of data (n): ");
	fgets(input, 10, stdin);
	number_of_points = atoi(input);


	printf("Enter data: \n");

	for (int i = 0; i < number_of_points; i++) {
		printf("x[ %d ]: ", i);
		fgets(input, 10, stdin);
		x_data_values[i] = atoi(input);

		printf("y[ %d ]: ", i);
		fgets(input, 10, stdin);
		y_data_values[i] = atoi(input);
	}

	printf("Enter a inperpolation point: ");
	fgets(input, 10, stdin);
	interpolation_point = atoi(input);

	double p;
	double interpolation_result = 0.0;

	for (int i = 0; i < number_of_points; i++) {
		p = 1;
		for (int j = 0; j <= number_of_points; j++) {
			if (j != i) {
				p = p * ((interpolation_point - x_data_values[j])/(x_data_values[i] - x_data_values[j]));
			}
		}
		
		interpolation_result = interpolation_result + p * y_data_values[i];
	
	}

	printf("Interpolation value at %d is %lf", interpolation_point, interpolation_result);
	
	return 0;
}