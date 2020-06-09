#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main() {
	char input[10] = { 0 };
	int data_values[100] = { 0 };
	int num_of_elements = 0;

	printf("Please, enter a number of data (n): ");
	fgets(input, 10, stdin);
	num_of_elements = atoi(input);

	printf("Please, enter the data:\n");

	for (int i = 0; i < num_of_elements; i++) {
		printf("[ %d ]: ", i);
		fgets(input, 10, stdin);
		data_values[i] = atoi(input);
	}

	double mean;
	double median;
	double mode;
	double range;
	double variance;
	double standard_deviation;

	//mean/average
	double sum = 0.0;

	for (int i = 0; i <= num_of_elements; i++) {
		sum += data_values[i];
	}

	mean = sum / num_of_elements;

	printf("mean: %lf\n", mean);


	//median
	int median_index;
	int temp = 0;

	for (int i = 0; i < num_of_elements; ++i) {
		for (int j = i + 1; j < num_of_elements; ++j) {
			if (data_values[i] > data_values[j]) {
				temp = data_values[i];
				data_values[i] = data_values[j];
				data_values[j] = temp;
			}
		}
	}
	
	median_index = ((num_of_elements + 1) / 2)-1;

	if (num_of_elements % 2 == 0) {
		median = (data_values[median_index] + data_values[median_index+1]) / 2;
		printf("median: %lf\n", median);
	}
	else {
		median = data_values[median_index];
		printf("median: %lf\n", median);
	}

	//mode
	int current_number;
	int count = 1; 
	temp = data_values[0];
	int max = 0;
	mode = temp;

	for (int i = 1; i < num_of_elements; i++) {
		if (temp == data_values[i]) {
			count += 1;
		}else {
			if (count > max) {
				max = count;
				mode = temp;
			}
			count = 1;
			temp = data_values[i];
		}
	}

	printf("mode: %lf\n", mode);
	 
	//range
	range = (double) data_values[num_of_elements-1] - data_values[0];
	printf("range: %lf\n", range);

	//variance
	sum = 0;

	for (int i = 0; i < num_of_elements; i++) {
		sum += pow(data_values[i] - mean, 2);
	}

	variance = sum / ((float) num_of_elements - 1);
	printf("variance: %lf\n", variance);

	//standard deviation
	standard_deviation = sqrt(variance);
	printf("standard_deviation: %lf\n", standard_deviation);
}