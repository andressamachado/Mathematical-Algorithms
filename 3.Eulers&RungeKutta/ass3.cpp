/******************************************************************
Filename:ass3.cpp
Version: 2.0
Author: Andressa Pessoa de Araujo Machado [040923007]
Assignment Number:3
Assignment Name: Transient-Response Analysis of 1st Order Systems
Course Name: Numerical Computing
Course Code:CST8233
Lab Section Number: 302
Professor's Name: Abdullah Kadri
Due Date: 2019/12/06
Submission Date:2019/12/06
List of source files: ass3.cpp
Purpose: The purpose of this program is to Find the solution of 1st order Ordinary Differential Equations (ODE) using well known
methods; namely, Euler’s and Runge-Kutta 4th Order Methods.
******************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h> 

//Enum to emulate a boolean
typedef enum { FALSE = 0, TRUE } BOOL;
//function prototypes
double actual_equation(double time_in_seconds);
double derivative_of_theta_time(double time_in_seconds, double thetha_of_time);
double relative_error(double extimated_temp_value, double exact_temp_value);

/***********************************************
Function name: main
Purpose: main function.
In parameters: None
Out Parameters: 0 for successful execution
Version: 2.0
Author: Andressa Machado
************************************************/;
int main() {
	//controls the flow of the program
	BOOL RUNNING = TRUE;
	//holds either if the user wants to calculate using Euler`s Method, or using Runge-Kutta`s Method
	char user_choice;
	//holds the desired value of the step size(h) as a string to converted later to double. As a string allows us to check for validation
	char h_input[4];

	//Variables used for the calculation:
	//Holds the initial temperature is 3C (Thetha of 0)
	double previous_temp_value = 3;
	//Holds the result of the methods calculation
	double extimated_temp_value = 0.0L;
	//Holds the exact temperature value to be used in the relative error calculation
	double exact_temp_value = 0.0L;
	//Holds the fraction of time needed to calculate the temperature
	double time_in_seconds = 0.2L;
	//Holdsthe step size value converted from the h_input variable
	double h_value = 0.0;

	while (RUNNING) {
		//controls if same error occurs so the user can have the chance to reenter 
		bool error;

		//Resets variables
		double previous_temp_value = 3;
		double extimated_temp_value = 0.0L;
		double exact_temp_value = 0.0L;
		double time_in_seconds = 0.2L;
		double h_value = 0.0;

		//Main Menu
		printf(">> Choose the method for solving the ODE: ");
		printf("\n1. Euler`s Method");
		printf("\n2. Runge-Kutta 4th Order Method\n>> ");

		//Loop to control the users input. Loop until the user enter a valid option 
		do {
			error = false;

			//Read the methods choice made by the user 
			scanf_s("%c", &user_choice, 1);

			//If not valid, sets error to true and starts the loop again
			if(user_choice != '1' && user_choice != '2'){
				//cleaning buffer
				while ((getchar()) != '\n');
				printf("***Please enter a valid option\n>> ");
				error = true;
			}
		} while (error);

		//cleaning buffer
		while ((getchar()) != '\n');

		//Step size option
		printf("\n>> Choose step size \"h\" (0.8, 0.2, 0.05)\n>> ");

		do {
			error = false;
			
			//Reads the input as a string to be easily checked 
			fgets(h_input, 5, stdin);

			//cleaning buffer
			while ((getchar()) != '\n');
			
			//strcmp returns a integer. 0 indicates that the strings are identical 
			if (strcmp(h_input, "0.2") != 0 && strcmp(h_input, "0.8") != 0 && strcmp(h_input, "0.05") != 0) {
				printf("%s", h_input);
				printf("***Please enter a valid option\n>> ");
				error = true;
			}
			
		} while (error);

		//Passing the string containing the h value to a double
		h_value = atof(h_input);
		//Count the steps
		int steps = (int)(2 / h_value);

		//Switch case to call the desired calculation method
		switch (user_choice) {
			case '1':
				//Euler`s method:
				printf("\nTime(second)\tExact Temp(C)\tEstimated Temp(C)\tPercentage Error(%%)\n\n");
				time_in_seconds = 0.0;

				//For the number of the steps, perform the calculation
				for (int i = 0; i < steps; i++) {

					//Formula
					extimated_temp_value = previous_temp_value + (cos(4 * time_in_seconds) - (2.0 * previous_temp_value)) * h_value;
					previous_temp_value = extimated_temp_value;

					//increment the fraction time to the next step
					time_in_seconds += h_value;

					//Calls function to perform the actual result
					exact_temp_value = actual_equation(time_in_seconds);

					//print results
					printf("%.1f\t\t%.3f\t\t%.3f\t\t\t%.2f\n", time_in_seconds, exact_temp_value, extimated_temp_value, relative_error(extimated_temp_value, exact_temp_value));
				}
				break;

			case '2':
				//Runge-Kutta method:
				printf("\nTime(second)\tExact Temp(C)\tEstimated Temp(C)\tPercentage Error(%%)\n\n");
				double k1, k2, k3, k4;

				time_in_seconds = 0.0;

				for (int i = 0; i < steps; i++) {

					//Calculation portions of the area to be used in the formula:
					k1 = derivative_of_theta_time(time_in_seconds, previous_temp_value);
					k2 = derivative_of_theta_time(time_in_seconds + 0.5 * h_value, previous_temp_value + 0.5 * h_value * k1);
					k3 = derivative_of_theta_time(time_in_seconds + 0.5 * h_value, previous_temp_value + 0.5 * h_value * k2);
					k4 = derivative_of_theta_time(time_in_seconds + h_value, previous_temp_value + k3 * h_value);

					//Formula:
					extimated_temp_value = previous_temp_value + (1.0 / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4) * h_value;
					previous_temp_value = extimated_temp_value;

					//increment the fraction time to the next step
					time_in_seconds += h_value;

					//Calls function to perform the actual result
					exact_temp_value = actual_equation(time_in_seconds);

					//Print results
					printf("%.1f\t\t%.3f\t\t%.3f\t\t\t%.2f\n", time_in_seconds, exact_temp_value, extimated_temp_value, relative_error(extimated_temp_value, exact_temp_value));
				}
				break;

			default:
				printf("**Please, enter a valid option.\n\n");
				break;
		}
		printf("\n\n");
	}
	return 0;
}

/***********************************************
Function name: actual_equation
Purpose: perform the calculation for the exact temperature value for that exact time
In parameters: double
Out Parameters: double
Version: 1.0
Author: Andressa Machado
************************************************/
double actual_equation(double time_in_seconds){
	return (0.1 * cos(4 * time_in_seconds)) + (0.2 * sin(4 * time_in_seconds)) + (2.9 * pow(M_E, (-2 * time_in_seconds)));
}

/***********************************************
Function name: derivative_of_theta_time
Purpose: perform the derivative calculation to be used in the Runge-Kutta formula
In parameters: double, double
Out Parameters: double
Version: 1.0
Author: Andressa Machado
************************************************/
double derivative_of_theta_time(double time_in_seconds, double thetha_of_time) {
	return cos(4.0 * time_in_seconds) - (2.0 * thetha_of_time);
}

/***********************************************
Function name: relative_error
Purpose: perform the relative error calculation
In parameters: double, double
Out Parameters: double
Version: 1.0
Author: Andressa Machado
************************************************/
double relative_error(double extimated_temp_value, double exact_temp_value) {
	double absulute_error = 0.0;
	double relative_error = 0.0;

	absulute_error = exact_temp_value - extimated_temp_value;
	relative_error = (absulute_error / exact_temp_value) * 100;

	//fabs() return the absolute value of a float-point number
	return fabs(relative_error);
}