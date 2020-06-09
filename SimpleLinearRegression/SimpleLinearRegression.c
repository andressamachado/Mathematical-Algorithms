#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main() {

	char input[10] = { 0 };
	float x_values[100] = { 0.0 };
	float y_values[100] = { 0.0 };
	int num_of_elements = 0;

	printf("Enter the number of data pairs to be entered: ");
	fgets(input, 10, stdin);
	num_of_elements = atoi(input);

	printf("Enter the x-axis values:\n");
	for (int i = 0; i < num_of_elements; i++) {
		printf("[ %d ]: ", i);
		fgets(input, 10, stdin);
		x_values[i] = atof(input);
	}

	printf("Enter the y-axis values:\n");
	for (int i = 0; i < num_of_elements; i++) {
		printf("[ %d ]: ", i);
		fgets(input, 10, stdin);
		y_values[i] = atof(input);
	}
	
//	Setting the values for test
//	float x_values[100] = {20.5f, 32.7f, 51.0f, 73.2f, 95.7f};
//	float y_values[100] = {765.f, 826.f, 873.f, 942.f, 1032.f};
//	int num_of_elements = 5;

	// Calculating Required Sum 
	float sumX = 0.0, sumX2 = 0.0, sumY = 0.0, sumXY = 0.0;

	for (int i = 0; i <= num_of_elements -1; i++)
	{
		sumX += x_values[i];
		sumX2 += x_values[i] * x_values[i];
		sumY += y_values[i];
		sumXY += x_values[i] * y_values[i];
	}

	//Calculating m and b 
	float m, b, y;

	m = ((num_of_elements * sumXY) - (sumX * sumY)) / ((num_of_elements * sumX2)- (sumX * sumX));
	b = (sumY - (m * sumX))/num_of_elements;


	for (int i = 0; i <= num_of_elements - 1; i++) {

		//fitting y = m + bx
		y = (m * x_values[i]) + b;
		printf("\n%d		%.2f		%.2f		%.3f", i, x_values[i], y_values[i], y);
	}
	
	printf("\nThe linear fit line is of the form:\n y= %fx + %f", m, b);
}