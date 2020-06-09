/******************************************************************
Filename:ass1.cpp
Version: 1.0
Author: Andressa Pessoa de Araujo Machado [040923007]
Assignment Number:1
Assignment Name: Building Motion Simulation
Course Name: Numerical Computing 
Course Code:CST8233
Lab Section Number: 302
Professor's Name: Abdullah Kadri
Due Date: 2019/09/29
Submission Date:2019/09/28
List of source files: ass1.cpp
Purpose: The purpose of this program is to calculate an approximate value for the motion response of a tall building following being hit by a sudden strong gust of wind.
It uses the Maclaurin Series to calculate this approximation.
******************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Enum to emulate a boolean
typedef enum { FALSE = 0, TRUE } BOOL;
//function prototype
void process_maclaurin_series(float, int);

/***********************************************
Function name: main
Purpose: main function.
In parameters: None
Out Parameters: 0 for successful execution
Version: 1.0
Author: Andressa Machado
************************************************/
int main(void) {
	//Boolean to control if the user wants to continue the program
	BOOL RUNNING = TRUE;
	
	//holds either if the user wants to calculate de approximation[1], or quit the program[2]
	char user_choice = '0';
	//holds input string from the user
	char input[5] = { 0 };
	float range_of_t = 0.0f; // 0 to +2.0
	int num_of_terms = 1;
	//holds the value returned from getc(stdin)
	int cleaning_buffer;

	//Continue to run the program until the user press 2 to quit 
	while (RUNNING) {
		//Menu
		printf("\nEvaluate the Maclaurin Series approximation to exp(-t)*cos(t)");
		printf("\n\n1:evaluate the series");
		printf("\n2:quit");
		printf("\n");
		scanf_s("%c", &user_choice, 1);
		//cleaning buffer
		cleaning_buffer = getc(stdin);

		switch (user_choice){
			case '1':
				printf("Evaluating the series");

				//Reads the number of desired terms while checking for validation
				do {
					printf("\nPlease enter the number of terms in the series(max 5 terms): ");
					//receives as a string and then convert it to sn int 
					fgets(input, 4, stdin);
					num_of_terms = atoi(input);
					
					if (num_of_terms < 1 || num_of_terms > 5) {
						printf("\n**You must enter a number of terms between 1 and 5. [1-minimum  5-maximum]");
					}
				} while (num_of_terms < 1 || num_of_terms > 5);
			
				//Reads the desired range while checking for validation and calling the function to perform the calculation
				do {
					printf("\nPlease enter the ranger of t to evaluate in 10 increments (0.0 < t < +2.0): ");
					fgets(input, 5, stdin);
					//cast to float once the function atoi returns a double
					range_of_t = (float) atof(input);

					if (range_of_t <= 0.0 || range_of_t > 2.0) {
						printf("\n**You must enter a range between 0 and +2.0. [0-minimum  +2 -maximum]");
					}
					else {
						printf("\n\nMACLAURIN SERIES\n");
						//call function to perform the calculation
						process_maclaurin_series(range_of_t, num_of_terms);
					}
				} while (range_of_t <= 0.0 || range_of_t > 2.0);
		
				break;
			//User quits the program
			case '2':
				printf("\nThank you for using the Maclaurin Series Calculator!");
				RUNNING = FALSE; 
				break;

			default:
				printf("**Please, enter a valid option.\n\n");
			}
	}
	return 0;
}

/***********************************************
Function name: processMaclaurinSeries
Purpose: perform calculations and print result 
In parameters: float range_of_t, int num_of_terms
Out Parameters: void
Version: 1.0
Author: Andressa Machado
************************************************/
void process_maclaurin_series(float range_of_t, int num_of_terms) {
	//pre-set the number of increments. 
	int increment = 10;
	//increments of t. Used to increase the time (t).
	float fraction_of_t = range_of_t / increment;
	//
	float t = 0;

	double array_of_terms[6];
	double series;
	double exact_value;  
	double exact_error;
	double truncate_error;

	printf("\n t \t\t Series \t\t Exact \t\t\t Exact %% Error \t\t Trunc. %% Error\n");
	printf("\n");

	//Calculates the series value, the exact value, the exact error, and the truncation error by using the time(t) in each interation, then increasing t
	//while i is less/equal than the number of increments(10):
	//	-calculate the max number of terms(5+1 - the last one will be used to calculate the trunc.) and save it in an array.
	for (int i = 0; i <= increment; i++) {
		series = 0.0f;
		array_of_terms[0] = 1;
		array_of_terms[1] = -t;
		array_of_terms[2] = (t * t * t) / 3;
		array_of_terms[3] = -(t * t * t * t) / 6;
		array_of_terms[4] = (t * t * t * t * t) / 30;
		array_of_terms[5] = -(t * t * t * t * t * t * t) / 630;

		//	-for the number of terms desired by the user, it will take from the index of the array and sum to the 
		//	variable series that holds the value of the Maclaurin series.
		for (int j = 0; j < num_of_terms; j++) {
			series += array_of_terms[j];
		}

		//	-Calculates the exact value of the polynomial function.
		exact_value = exp(-t) * cos(t);
		//	-Calculates the Exact % Error from the comparation between the exact value and the series value 
		exact_error = 100 * (exact_value - series) / exact_value;
		//	-Calculates the truncate % error to gives an idea of how well the first truncated term approximates to the error
		truncate_error = (100 * array_of_terms[num_of_terms]) / series;
			
		//print results
		printf("%.3e \t %.5e \t\t %.5e \t\t %.5e \t\t %.5e\n", t, series, exact_value, exact_error, truncate_error);

		//increasing t fraction for the next sequence of calculations
		t += fraction_of_t;
	}
}
