/*
Program:	structs.c
Course:		SOL1 WS2020
Author(s):	Emmanuel Anokwuru, Oluwapelumi Soyombo
Date:		20.01.2021
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>	// standard I/O library
#define ARRAYSIZE 10	// size of array of power plant structures
#define DEBUG 0		// DEBUG mode if 1


// struct definitions
typedef struct plant_location { // structure for location
	char* latitude;
	char* longitude;
} pl_location;

typedef struct power_plant { // structure of a plant
	char* name;
	pl_location location;
	double power;
} plant;

typedef struct power_plant_array { // array of power plant structures
	plant collection[ARRAYSIZE];
} plants_collection;

// declaring prototypes
int initial_save(plant* collection, int n); // writing the initial 3 arrays to CSV
int print_plant_collection(); // printing the CSV file
void insert_plant_collection(); // inserting new values into a temp. file
int edit_plant_collection(); // editing a line in the orig. file
void save_for_insert(); // saving temp. file into orig. file, "a" to the orig. CSV file
void save_for_edit(); // saving temp. file into orig. file, "w" to the orig. CSV file


// main function
int main() {
	printf("Sturcture for Power Plants.\n");
	printf("Note: 3 arrays have been intialized already.\n\n");
	printf("Press any of the following keys:\n");
	printf("P = Print, I = Insert, E = Edit, and S = Save.\n\n");
	//printf("P = Print, I = Insert, E = Edit, L = Load and S = Save.\n");


	plants_collection pl_collection; // declaring an array of struct
	// Making 5 power plants initialized...

	pl_collection.collection[0].name = "Nordsee-Juist1"; pl_collection.collection[0].location.latitude = "10.55 N"; pl_collection.collection[0].location.longitude = "57.21 E"; pl_collection.collection[0].power = 12.500;
	pl_collection.collection[1].name = "Ringhals"; pl_collection.collection[1].location.latitude = "34.5 N"; pl_collection.collection[1].location.longitude = "43.21 E"; pl_collection.collection[1].power = 12.500;
	pl_collection.collection[2].name = "Bugey"; pl_collection.collection[2].location.latitude = "78.32 S"; pl_collection.collection[2].location.longitude = "57.49 W"; pl_collection.collection[2].power = 12.500;
	pl_collection.collection[3].name = "Gravelines"; pl_collection.collection[3].location.latitude = "60.75 S"; pl_collection.collection[3].location.longitude = "12.54 W"; pl_collection.collection[3].power = 12.500;
	pl_collection.collection[4].name = "Tricastin"; pl_collection.collection[4].location.latitude = "37.765 N"; pl_collection.collection[4].location.longitude = "5.21 E"; pl_collection.collection[4].power = 12.500;

	initial_save(pl_collection.collection, 5); // writing the above arrays readily to file

	char c = _getch();// get input to process command.
	while (c != 'q' && c != 'Q') {
		// switch statement to decide what function to implement
		switch (c) {//checks for both capital and small letter
		case 'P':
		case 'p': print_plant_collection(); break; // writes to file in CSV format
		case 'I':
		case 'i': insert_plant_collection(); break; // writes the first five arrays 
		case 'E':
		case 'e': edit_plant_collection(); break; // editing a line in the orig. file
		case 'S':
		case 's': save_for_insert(); break; // saving temp. file into orig. file
		default: printf("Error: Case '%c' not available. Try again...\n\n", c);
		}
		// this happens if user presses a different key other than specified or for other further commands.
		printf("==================================================\n");
		printf("Press any of the following keys:\n");
		printf("P = Print, I = Insert, E = Edit, and S = Save.\n");
		printf("Or press 'Q' to quit all process and close the program...\n\n");
		c = getch();
	}

	printf("\nBye!");
	return 0;
}


int initial_save(plant* collection, int n) { // writing the initial 5 arrays to file in CSV format
	FILE* fp; // creating a file pointer

	// creating/opening a file for writing
	if (fp = fopen("power_plant_struct.csv", "w")) { // if fopen() successful
		//if (DEBUG) printf("File created and opened successfully; ready for writing...\n...\n");
		for (int i = 0; i < n; i++) {
			fprintf(fp, "%s, ", collection[i].name);
			fprintf(fp, "%s, %s, ", collection[i].location.latitude, collection[i].location.longitude);
			fprintf(fp, "%.2lfkW\n", collection[i].power);
		}
		fclose(fp);
		//if (DEBUG) printf("Writing to file complete.\n");
		return EXIT_SUCCESS;
	}
	else { // if fopen() failed
		fprintf(stderr, "File cannot be opened...\n");
		perror("Reason");
		return EXIT_FAILURE;
	}
}

int print_plant_collection() { 
	// printing the contents of the orig. CSV file

	FILE* fp; //creating a file pointer
	fp = fopen("power_plant_struct.csv", "r"); // opens the file for reading only

	printf("***Printing now...***\n");
	if (fp) { // if fopen() successful
		char buffer[60]; // creating a buffer array
		if (DEBUG) printf("File opened successfully...\n\n");
		while (!feof(fp)) { // when hasn't reached end of file
			char* one_line = fgets(buffer, 60, fp); // getting each line of the orig. file
			if (one_line != NULL) { // if fgets() works
				printf("%s", buffer); // prints the line to the screen
			}
			else if (feof(fp)) printf("End of file reached!\n\n"); // if end-of-file has been reached
			else {
				fprintf(stderr, "File cannot be opened...\n");
				perror("Reason");
				return EXIT_FAILURE;
			}
		}
		fclose(fp);
		return EXIT_SUCCESS;
	}
	else { // if fopen() failed
		fprintf(stderr, "File cannot be opened...\n");
		perror("Reason");
		return EXIT_FAILURE;
	}
}

void insert_plant_collection() { // inserting new values into a temp. file
	// writing new input to a temp. file
	// saving the new input if the user desires

	FILE* fp; // creating a file pointer
	fp = fopen("power_plant_temp.txt", "a");

	printf("***Let's Insert then...***\n");
	if (fp) { // if fopen() works
		char ch = 'w';
		char name[60]; // creating an array to hold new plant name
		char location[2][15]; // creating an array to hold new plant locations
		double power = 0.0; /// creating an array to hold new plant power
		while (ch != '.') {
			printf("Enter name of plant: ");
			scanf("%s", name);

			printf("Enter latitude of plant: ");
			scanf("%s", location[0]);

			printf("Enter longitude of the plant: ");
			scanf("%s", location[1]);

			printf("Enter Power(kilo-Watts) of plant: ");
			scanf("%lf", &power);

			// printing input to user
			printf("\nYou entered: %s, %s, %s, %.2lfkW\n", name, location[0], location[1], power);

			// writing the new input to temp. file
			fprintf(fp, "%s, ", name);
			fprintf(fp, "%s, %s, ", location[0], location[1]);
			fprintf(fp, "%.2lfkW\n", power);

			// prompt to continue or to exit
			printf("\nPress Enter to continue Insert or \".\" to exit Insert...\n\n");
			ch = _getch();
		}
		fclose(fp);

		// asking if user wants to save changes immediately
		if (1) {
			printf("Would you like to save changes immediately? Y/N: ");
			char answer = getch();
			if (answer == 'y' || answer == 'Y') {
				save_for_insert();
				printf("Your changes has been saved.\n\n");
			}
			else printf("Your changes has NOT been saved.\n\n");
		}
	}
	else { // if fopen() fails
		fprintf(stderr, "File cannot be opened...\n");
		perror("Reason");
	}
}

int edit_plant_collection() { // editing a line in the orig. file
	// 1: print all lines with their row index
	// 2: let the user select which index to edit
	// 3: copying all lines before the row (to be edited) in the orig. file to a temp. file
	// 		writing the new input to the temp. file
	// 		copying the rest of the lines in the orig. file to the temp. file
	// 4: saving the changes of temp. file into orig. file


	printf("***You are editing...***\n");
	// 1: print all lines with their row index
	FILE* fp; // creating a file pointer
	fp = fopen("power_plant_struct.csv", "r"); // creating a file for writing
	int index = 1; // counter to determine column index 
	if (fp) { // if fopen() successful
		char buffer[60]; // creating a buffer array
		if (DEBUG) printf("File opened successfully...\n\n");
		while (!feof(fp)) {
			char* oneline = fgets(buffer, 60, fp); // getting each line of the orig. file
			if (oneline != NULL) { // if fgets() works
				printf("Row %d:--> ", index++);
				printf("%s", buffer); // printing the line to the screen
			}
			else if (feof(fp)) printf("End of file reached!\n\n"); // if end-of-file has been reached
			else {
				fprintf(stderr, "File cannot be opened...\n");
				perror("Reason");
				return EXIT_FAILURE;
			}
		}
		fclose(fp);
	}
	else { // if failed
		fprintf(stderr, "File cannot be opened...\n");
		perror("Reason");
		return EXIT_FAILURE;
	}

	// 2: let the user select which index to edit
	int row;
	printf("What row would you like to edit?: ");
	scanf("%d", &row);


	// 3: copying all lines before the row (to be edited) in the orig. file to a temp. file
	// writing the new input to the temp. file
	// copying the rest of the lines in the orig. file to the temp. file

	FILE* fp1, * fp2;
	fp1 = fopen("power_plant_struct.csv", "r");
	fp2 = fopen("power_plant_temp.txt", "w");
	int counter = 0; // counter to get the current row
	printf("\n");

	if (fp1 && fp2) { // if fopen() works on both files
		char buff[60]; // create an array to hold strings
		char name[60]; // creating an array to hold new plant name
		char location[2][15]; // creating an array to hold new plant locations
		double power = 0.0; /// variable for new power plant power
		while (!feof(fp1)) { // while not end of the CSV file
			char* oneline2 = fgets(buff, 60, fp1); // get a line from the orig file
			counter++; // incrementing the row for each iteration
			if (oneline2 != NULL && row == counter) { // reading worked and row == counter
				printf("Enter name of the new plant: ");
				scanf("%s", name);

				printf("Enter latitude of the new plant: ");
				scanf("%s", location[0]);

				printf("Enter longitude of the new plant: ");
				scanf("%s", location[1]);

				printf("Enter Power(kilo-Watts) of the new plant: ");
				scanf("%lf", &power);

				// printing new input to user
				printf("\nYou entered: %s, %s, %s, %.2lfkW\n", name, location[0], location[1], power);

				// printing the result to temp. file
				fprintf(fp2, "%s, ", name);
				fprintf(fp2, "%s, %s, ", location[0], location[1]);
				fprintf(fp2, "%.2lfkW\n", power);

			}
			else if (oneline2 != NULL) { // reading worked
				fputs(buff, fp2); // print that line into the temp. file
			}
			else { // (s == NULL) => failure, can also be EOF
				if (feof(fp1)) { // can happen, very normal
					//printf("EOF.\n");
				}
				else {
					fprintf(stderr, "ERROR: cannot read from file\n");
					perror("Reason"); // OS tells us why it failed ... see "errno -l" on Linux
					break;
				}
			}
		}
		fclose(fp1);
		fclose(fp2);
	}
	else { // if fopen() failed
		fprintf(stderr, "Either file 1 or file 2 cannot be opened...\n");
		perror("Reason");
	}

	// 4: saving the changes of temp. file into orig. file
	save_for_edit();
}

void save_for_insert() { // saving temp. file into orig. file, "a" to the orig. CSV file
	// get each line from the temp. file
	// fprintf out those lines into the orig. file 

	FILE* fp1, * fp2; // pointer for both orig. and temp. files
	fp1 = fopen("power_plant_struct.csv", "a"); // open for appending
	fp2 = fopen("power_plant_temp.txt", "r");

	printf("***Your work is being saved...***\n");
	if (fp1 && fp2) { // if fopen() works on both files
		char buff[60]; // create an array to hold strings
		while (!feof(fp2)) { //
			char* oneline= fgets(buff, 60, fp2); // get a line from the temp file
			if (oneline != NULL) { // reading worked
				fputs(buff, fp1); // print that line into the original file
			}
			else { // (s == NULL) => failure, can also be EOF
				if (feof(fp2)) { // can happen, very normal
					//printf("EOF.\n");
				}
				else {
					fprintf(stderr, "ERROR: cannot read from file\n");
					perror("Reason"); // OS tells us why it failed ... see "errno -l" on Linux
				}
			}
		}
		fclose(fp1);
		fclose(fp2);
		printf("Your work has been saved.\n\n");
		fp2 = fopen("power_plant_temp.txt", "w"); fclose(fp2); // clearing the contents of the temp. file
	}
	else { // if fopen() failed
		fprintf(stderr, "Either file 1 or file 2 cannot be opened...\n");
		perror("Reason");
	}
}

void save_for_edit() { // saving temp. file into orig. file, "w" to the orig. CSV file
	// get each line from the temp. file
	// fprintf out those lines into the orig. file 

	FILE* fp1, * fp2; // pointer for both orig. and temp. files
	fp1 = fopen("power_plant_struct.csv", "w"); // opens for writing
	fp2 = fopen("power_plant_temp.txt", "r"); // opens for reading

	printf("***Your work is being saved...***\n");
	if (fp1 && fp2) { // if fopen() works on both files
		char buff[60]; // create an array to hold strings
		while (!feof(fp2)) { //
			char* oneline = fgets(buff, 60, fp2); // get a line from the temp file
			if (oneline != NULL) { // reading worked
				fputs(buff, fp1); // print that line into the original file
			}
			else { // (s == NULL) => failure, can also be EOF
				if (feof(fp2)) { // can happen, very normal
					//printf("EOF.\n");
				}
				else {
					fprintf(stderr, "ERROR: cannot read from file\n");
					perror("Reason"); // OS tells us why it failed ... see "errno -l" on Linux
				}
			}
		}
		fclose(fp1);
		fclose(fp2);
		printf("Your work has been saved.\n\n");
		fp2 = fopen("power_plant_temp.txt", "w"); fclose(fp2); // clearing the contents of the temp. file
	}
	else { // if fopen() failed
		fprintf(stderr, "Either file 1 or file 2 cannot be opened...\n");
		perror("Reason");
	}
}