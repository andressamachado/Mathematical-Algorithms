#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main() {

	char input[10] = { 0 };
	float x_values[100] = { 0.0f };
	int num_of_elements = 0;
	float x_point = 0.0f;

	printf("Enter the the total no. of equally spaced data points:\n");
	fgets(input, 10, stdin);
	num_of_elements = atoi(input);

	printf("Enter the value of x`s:\n");
	for (int i = 0; i < num_of_elements; i++) {
		printf("[ %d ]: ", i);
		fgets(input, 10, stdin);
		x_values[i] = atof(input);
	}

	printf("Enter the point where first derivative is calculated:\n");
	fgets(input, 10, stdin);
	x_point = atof(input);

	//Value of Y`s:
	//y=f(x)=x^3
	float first_Y_Value = x_values[0] * x_values[0] * x_values[0];
	float second_Y_Value = x_values[1] * x_values[1] * x_values[1];
	float third_Y_Value = x_values[2] * x_values[2] * x_values[2];

	printf("\nThe value of y`s : \n");
	printf("%.3f\n", first_Y_Value);
	printf("%.3f\n", second_Y_Value);
	printf("%.3f\n", third_Y_Value);

	float delta_x = 0.0f;
	//Derivative of the function f(x) = x^3 
	float exact_value = 3 * pow(x_point, 2);

	//Forward Method:
	delta_x = x_values[2] - x_values[1];
	float forwardResult = 0.0f;
	float forwardError = 0.0f;
	
	float first_term = (x_point + delta_x) * (x_point + delta_x) * (x_point + delta_x);
	float second_term = second_Y_Value;

	forwardResult = (first_term - second_term) / delta_x;
	forwardError = ((forwardResult - exact_value) / exact_value) * 100;

	printf("\n\nThe result is:\n");
	printf("Forward method = %.2f\t\terror = %.2f%%\n", forwardResult, forwardError);

	//Backward Method:
	float backwardResult = 0.0f;
	float backwardError = 0.0f;

	first_term = second_Y_Value;
	second_term = first_Y_Value;
	delta_x = x_point - x_values[0];

	backwardResult = (first_term - second_term)/delta_x;
	backwardError = ((exact_value - backwardResult) / exact_value) * 100;

	printf("Backward method = %.3f\terror = %.3f%%\n", backwardResult, backwardError);

	//Enteral Method:
	float enteralResult = (third_Y_Value - first_Y_Value) / (x_values[2] - x_values[0]);
	float enteralError = ((enteralResult - exact_value) / exact_value) * 100;

	printf("Enteral method = %.3f\t\terror = %.2f%%", enteralResult, enteralError);

}