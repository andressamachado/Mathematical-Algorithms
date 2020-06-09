#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main() {
	int numOfElements = 7;
	float c_values[7] = { 4.0f, 2.25f, 1.45f, 1.0f, 0.65f, 0.25f, 0.006f };
	float r_values[7] = {0.398f, 0.298f, 0.238f, 0.198f, 0.158f, 0.098f, 0.048f};
	float sumC = 0.0, sumC2 = 0.0, sumR = 0.0, sumCR = 0.0;

	//y
	double r;
	//x 
	double c;
	//a
	double k;
	//b
	double n;
	
	double z;
	double zAvg;
	double w;
	double wAvg;
	double a0;
	double a1;


	for (int i = 0; i < numOfElements; i++) {
		sumC += log(c_values[i]);
		sumC2 += log(c_values[i]) * log(c_values[i]);
		sumR += log(r_values[i]);
		sumCR += log(c_values[i]) * log(r_values[i]);

		a1 = ((numOfElements * sumCR) - (sumC * sumR)) / ((numOfElements * sumC2) - (sumC * sumC));
	}

	
	zAvg = sumR / (double) numOfElements;
	wAvg = sumC / (double)numOfElements;

	a0 = zAvg - a1 * wAvg;
	
	k = pow(M_E, a0);
	n = a1;

	printf("The model of progress of that chemical reaction is: -r = %.5f x C^%.5F", k, n);

}