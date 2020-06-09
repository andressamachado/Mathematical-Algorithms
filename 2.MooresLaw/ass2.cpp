/******************************************************************
Filename:ass2.cpp
Version: 2.0
Author: Andressa Pessoa de Araujo Machado [040923007]
Assignment Number:2
Assignment Name: Moore`s Law
Course Name: Numerical Computing
Course Code:CST8233
Lab Section Number: 302
Professor's Name: Abdullah Kadri
Due Date: 2019/09/15
Submission Date:2019/09/15
List of source files: ass2.cpp
Purpose: The purpose of this program is to fit data using linear regression
least-squares method for an exponential function.
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
//function prototype
void linearRegressionFit(int[], double[], int, double*);

/***********************************************
Function name: main
Purpose: main function.
In parameters: None
Out Parameters: 0 for successful execution
Version: 2.0
Author: Andressa Machado
************************************************/
int main() {
	//controls the user desire to stop or continue the program
	BOOL RUNNING = TRUE;
	//control if it is the first time the prpogram is running. If so, ask to the user the name of the file they wants to open.
	bool is_first_round = true;
	//holds either if the user wants to calculate[1], or quit the program[2]
	char user_choice = '0';
	//holds the value returned from getc(stdin)
	int cleaning_buffer;
	//Arrays containing the data itself.
	int year_values[15] = { 0 };
	double transistorCount_values[15] = { 0.0f };
	//array to hold the regression values
	double regression_values[2] = { 0 };

	printf("LEAST_SQUARES LINEAR REGRESSION\n\n");

	//Continue to run the program until the user press 2 to quit 
	while (RUNNING) {
		if (is_first_round) {
			//name of the file we want to be opened.
			char file_name[100];
			//Pointer to the file we want to open.
			FILE* ptr_data_file;
			//get the line of the file
			char line[256];
			//to skip the first line of the file with the headers
			bool is_first_line = true;
			//allow us to know if it is the values from the first column[year] or second[transistor count]
			int tab_counter = 0;
			//Used to append the next digit to the correct index to form the correct number
			int year_index_controller = 0;
			//Same idea as the yearIndexController, but for the transistor. 
			int transistor_index_controller = 0;
			//arrays containig the digits represented by chars. Each array is a unique number from file
			char year_text[5];
			char transistorCount_text[10] = { " " };
			//Represents the line of the file.
			int line_index = 0;
			//number of records in the given file
			int num_of_records = 1;


			//Main Menu
			printf("MENU");
			printf("\n  1.	Exponential Fit");
			printf("\n  2.	Quit");
			printf("\n");
			scanf_s("%c", &user_choice, 1);
			//cleaning buffer
			cleaning_buffer = getc(stdin);


			//controls if same error occurs so the user can have the chance to reenter 
			bool error;

			switch (user_choice) {
			case '1':

				//try to open the disered file and checking for validation
				do {
					error = false;

					printf("Please enter the name of the file to open: ");
					fgets(file_name, 10, stdin);

					//Openning the file to be consulted
					ptr_data_file = fopen(file_name, "r");


					//Checking for existance. If not available, returns.
					if (ptr_data_file == NULL) {
						printf("**Could not open file. Check your input and try again.\n\n");
						error = true;
					}
				} while (error);

				//Openning the file again to be consulted
				ptr_data_file = fopen(file_name, "r");

				while (fgets(line, sizeof(line), ptr_data_file)) {
					//skip the first line once we do not have data on in
					if (is_first_line) {
						is_first_line = false;
						continue;
					}

					//Resets controllers once we are reading lne by line and saving the values separated by columns
					tab_counter = 0;
					year_index_controller = 0;
					transistor_index_controller = 0;

					//passing through the values and saving them
					for (int i = 0; (unsigned)i < strlen(line); i++) {
						//When tab reaches 1, skip all blank spaces.
						if (tab_counter == 1) {
							if (line[i] == ' ') {
								continue;
							}
							else {
								//When it reaches a new char, increase the counter so we can used to start read the next value
								tab_counter++;
							}
						}

						//if no tab was encountered, means we are dealing with the values representing the years
						if (tab_counter == 0) {
							//encountered a tab
							if (line[i] == ' ') {
								tab_counter++;
								//adding the terminator to the formed number
								year_text[4] = '\0';
								//adding the year at the correct index
								year_values[line_index] = atoi(year_text);
								continue;
							}
							else {
								//adding char by char to the array year_text to form the year at the end
								year_text[year_index_controller++] = line[i];
							}
						}

						//it reached the transistor count value
						if (tab_counter == 2) {
							if (line[i] == ' ') {
								transistorCount_text[9] = '\0';
								transistorCount_values[line_index] = atof(transistorCount_text);
								break;
							}
							transistorCount_text[transistor_index_controller++] = line[i];
						}
					}

					//Increments(goes down to the next line)
					line_index++;
					//holds the number of records in the given file
					num_of_records++;
				}

				//close file 
				fclose(ptr_data_file);

				//Openning the file again to print purposes 
				ptr_data_file = fopen(file_name, "r");

				//get the first char
				int character = fgetc(ptr_data_file);

				printf("\n");

				//prints file char by char until the variable "character" find the End Of File
				while (character != EOF) {
					printf("%c", character);
					//gets the next char 
					character = fgetc(ptr_data_file);
				}
				printf("\nThere are %d records.\n", num_of_records - 1);

				//close file 
				fclose(ptr_data_file);

				//Call the function that will perform the calculation of the linear regression fit
				linearRegressionFit(year_values, transistorCount_values, num_of_records, &regression_values);

				//it is still the first running of the operation
				is_first_round = FALSE;
				break;

			case '2':
				//stop running the application
				RUNNING = FALSE;
				break;

			default:
				printf("**Please, enter a valid option.\n\n");
			}
		}
		else {
			//value entered by the user representing the year to be used in the calculation
			char year_text[5];
			//1970 is the base year
			int year = 1970;
			//holds the value of the calculation
			double transistor_count;

			//cleaning the buffer for the next user input
			cleaning_buffer = getc(stdin);

			//Menu
			printf("\nMENU");
			printf("\n  1.	Extrapolation");
			printf("\n  2.	Main Menu");
			printf("\n");
			scanf_s("%c", &user_choice, 1);
			//cleaning buffer
			cleaning_buffer = getc(stdin);

			//controls if same error occurs so the user can have the change to reenter 
			bool error;

			switch (user_choice) {
			case '1':
				printf("Please enter the year to extrapolate to:");
				fgets(year_text, 5, stdin);

				printf("Year = %s", year_text);

				//getting calculated values that were calculated in the function linearRegressionFit and saved in the array
				double a = regression_values[0];
				double b = regression_values[1];

				//passing the value entered by the user to an int
				year = atoi(year_text);

				//CALCULATION:
				transistor_count = a * pow(M_E, b * ((double)year - 1970));

				printf("\ntransistor count = %.3e\n", transistor_count);

				break;
			case '2':
				//go back to the main menu
				is_first_round = true;
				printf("\n");
				printf("LEAST_SQUARES LINEAR REGRESSION\n\n");
				break;

			default:
				printf("**Please, enter a valid option.\n\n");
			}
		}
	}
	return 0;
}

/***********************************************
Function name: linearRegressionFit
Purpose: perform calculations, print result of the function form.
In parameters: int[], double[], int, double
Out Parameters: void
Version: 1.0
Author: Andressa Machado
************************************************/
void linearRegressionFit(int year_values[], double transistorCount_values[], int num_of_records, double* regression_values) {

	//Variables used in the formula:

	//holds the sum of the values referred to the year
	int sum_year = 0;
	int sum_year2 = 0;
	//holds the sum of the values referred to the transistor count 
	double sum_transistor = 0.0;
	//sum of the year values x transistor count values
	double sum_yearxtransistor = 0.0;

	//a1 is the result of the first formula.
	double a1;
	//a0 holds the result of the second formula.
	double a0;
	//average of both sum_year and sum_transistor 
	double transistor_avg;
	double year_avg;
	//base year used in the formula
	int base_year = 1970;

	//cutting the first line once there is no value in there
	num_of_records = num_of_records - 1;

	//performs the sum of the terms from year_values[] and transistorCount_values[]. 
	//Those results will be used at the first formula
	for (int i = 0; i < num_of_records; i++)
	{
		sum_year += year_values[i] - base_year;
		sum_year2 += (year_values[i] - base_year) * (year_values[i] - base_year);
		sum_transistor += log(transistorCount_values[i]);
		sum_yearxtransistor += ((double)year_values[i] - base_year) * log(transistorCount_values[i]);
	}

	//FIRST FORMULA
	a1 = ((num_of_records * sum_yearxtransistor) - (sum_year * sum_transistor)) / (((double)num_of_records * sum_year2) - ((double)sum_year * sum_year));

	//calculating the average
	transistor_avg = sum_transistor / (double)num_of_records;
	year_avg = sum_year / (double)num_of_records;

	//SECOND FORMULA
	a0 = transistor_avg - a1 * year_avg;

	//represents one term of the function
	double b = a1;
	//a represents another term of the function
	double a = pow(M_E, a0);

	//Printing the result of the linear regression fit for the given data
	printf("\nLinear Regression Fit: transition count = %.3e*exp(%.3e*(year-1970))\n\n", a, b);

	//Saving the values of a and b to an array to be used outside this function.
	*(regression_values) = a;
	*(regression_values + 1) = b;
}