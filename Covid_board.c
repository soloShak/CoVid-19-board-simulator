#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE 35
#define MAX 300

/*
* Defining prototypes of functions
*/
void line();
void main_menu();
void add_data();
void edit_data();
void delete_data();
void find_data();
void show_stat();
void locat();
void show_list();
void end();
void choice();
void safety();
void safety_back();

/*
* Definig structure to save
* Patient's Data 
*/
struct data
{
	char sex[MAX];
	int age[MAX];
	char city[MAX][10];
	int id[MAX];
};

struct data patient;

int count = 0;

FILE* list;

/*
* Function: main
* -------------------
* the main fuction than checks if there is already a data in file
* and then goes to main_menu()
* 
* ii: counter for loop
* list: pointer to file
* 
* returns zero
*/
int main(void)
{	
	int ii;

	list = fopen("list.bin", "rb");

	if (list == NULL)//checks the availabilaty of file
	{ 
		printf("  Could not open file:(");
		exit(1);// exits software if file is not available
	}

	fread(&patient, sizeof(struct data), 1, list);

	for (ii = 0; ii < MAX; ii++) //reads file
	{
		fread(&patient, sizeof(struct data), 1, list);
		if (patient.id[ii] != 0) // if there is data in some element of patient.id[]
			count = ii;          // then count equales to this element number
	}

	fclose(list); // closes file
	main_menu(); // goes to main_menu

	return 0;
}

/*
* Function: main_menu()
* --------------------------------
* Prints main menu and allows to move to other functions
* 
* action: to move to other functions
* 
* returs nothing, because type is void
*/
void main_menu()
{	
	system("cls");

	int action;

	//printf("%d\n\n", count);

	printf("    *** Welcome to CoVid-19 Board *** \n");
	line();
	printf("\n\t  System menu \n\n");
	printf("  1. Add Confirmed Patient \n\n");
	printf("  2. Edit Patient\'s Data \n\n");
	printf("  3. Delete Patient\'s Data \n\n");
	printf("  4. Find Patient\'s Data \n\n");
	printf("  5. Show Statistics \n\n");
	printf("  6. Enter Your Current Location \n\n");
	printf("  7. Show Patient\'s List \n\n");
	printf("  8. Show safety rules \n\n");
	printf("  9. Exit \n");
	line();

a:	printf("\n\n  Enter your choice: ");
	scanf("%d", &action);   // scanning for further actions

	switch (action)   // swith case statement for further actions
	{
	case 1:
		fclose(list);
		add_data();
		break;
	case 2:
		fclose(list);
		edit_data();
		break;
	case 3:
		fclose(list);
		delete_data();
		break;
	case 4:
		fclose(list);
		find_data();
		break;
	case 5:
		fclose(list);
		show_stat();
		break;
	case 6:
		fclose(list);
		locat();
		break;
	case 7:
		fclose(list);
		show_list();
		break;
	case 8:
		fclose(list);
		safety();
		break;
	case 9:
		fclose(list);
		end();
		break;
	default: // if user typed wrong number software goes back to scanning "action"
		printf("  There is no such choice!");
		goto a;
		break;
	}
}

/*
* Function: line()
* -------------------------
* Prints lines "==="
* 
* ii: counter for loop
*/
void line()
{
	int ii;
	printf("  "); // prints blank space
	for (ii = 0; ii <= LINE; ii++)
		printf("="); // prints 35 "="
}

/*
* Function: choice()
* -----------------------
* Prints text and allows to go back to main menu 
* 
* back: for going back to main_menu()
*/
void choice()
{
	int back;
	printf("\n\n");
	line();
b:	printf("\n\n  Enter 0 to go back:  ");
	scanf("%d", &back); //scanning for 'back'

	if (back == 0) // if zero then goes back to main_menu()
		main_menu();
	else           // if user types wrong number it goes back to scan 'back'
	{
		printf("There is no such choice\n");
		goto b;
	}
}

/*
* Function: end()
* -----------------------
* exits the software
*/
void end()
{
	exit(1); 
}

/*
* Function: add_data()
* ---------------------------
* Allows to add patient's data to file
* 
* ii: for 'for loop'
* list: pointer to file
* 
*/
void add_data()
{
	system("cls");
	
	count++; // increases "count"
	patient.id[count] = count; // assigns number of count to this patient's id

	int ii;
	list = fopen("list.bin", "wb+");
	printf("      *** New Patient\'s Data *** \n");
	line();

	if (list == NULL) // checks for availabity of file
	{
		printf("  Could not open file:(");
		exit(1);
	}

	for (ii = 0; ii < 1; ii++) // loop to scan patient's data 
	{
		printf("\n  Gender: ");
		scanf("%s", &patient.sex[count]);
		printf("  Age: ");
		scanf("%d", &patient.age[count]);
		printf("  Location: ");
		scanf("%s", &patient.city[count]);

		fwrite(&patient, sizeof(struct data), 1, list);
	}
	fclose(list); // closes file
	main_menu(); // goes to main_menu
}

/*
* Function: edit_data()
* -----------------------------
* Allows to edit patient's gender, age and location
* 
* enter_id: for scanning needed for user patient
* change_num: to select what user wants to change in data
* 
*/
void edit_data()
{	
	system("cls");

	list = fopen("list.bin", "rb+");

	if (list == NULL) // checks the availability of file
	{
		printf("  Could not open file:(");
		exit(1);
	}

	int enter_id;
	int change_num;

	printf("    *** Edit Patient\'s Data ***\n");
	line();

	printf("\n\n  Enter Patient\'s ID:  ");
	scanf("%d", &enter_id);

	if (patient.id[enter_id] != 0) // if this patient's id exists then prints options to change
	{
		fread(&patient, sizeof(struct data), 1, list);

		line();
		printf("\n\n  1. Gender \n");
		printf("  2. Age \n");
		printf("  3. Location \n\n");
		printf("  (Choose 0 to cancel operation) \n\n");
		line();

		printf("\n\n  What do you want to change:  ");
		scanf("%d", &change_num);

		line();

		switch (change_num) // switch case statement 
		{
		case 1:
			printf("\n\n  Enter new Gender:  ");
			scanf("%s", &patient.sex[enter_id]);
			fwrite(&patient, sizeof(struct data), 1, list); // writes new gender
			fclose(list);
			main_menu();
			break;
		case 2:
			printf("\n\n  Enter new Age:  ");
			scanf("%d", &patient.age[enter_id]);
			fwrite(&patient, sizeof(struct data), 1, list); // writes new age
			fclose(list);
			main_menu();
			break;
		case 3:
			printf("\n\n  Enter new Location:  ");
			scanf("%s", patient.city[enter_id]);
			fwrite(&patient, sizeof(struct data), 1, list); // writes new location
			fclose(list);
			main_menu();
			break;
		case 0:
			main_menu(); // goes to main_menu()
			break;
		}
	}
	else // if patient's id doesn't exist
	{
		printf("  Not found &(\n");
		choice();
	}
}

/*
* Function: delete_data()
* ----------------------------
* Allows to delete patient's data
* 
* ii: for for loop
* enter_id: for scanning needed for user patient  
* answer: for scannig user's choice
* 
*/
void delete_data()
{
	system("cls");

	list = fopen("list.bin", "rb+");
	int ii, enter_id;
	char answer;

	if (list == NULL) // checks for availability of file
	{
		printf("  Could not open file:(");
		exit(1);
	}

	printf("    *** Delete Patient\'s Data ***\n");
	line();
	printf("\n\n  Enter Patient\'s ID:  ");
	scanf("%d", &enter_id);
	
	line();
	for (ii = 0; ii < MAX; ii++) // for loop which searches typed patient's data
	{	
		fread(&patient, sizeof(struct data), 1, list);
		if (patient.id[ii] == enter_id) // if software finally finds this patients
		{
			fread(&patient, sizeof(struct data), 1, list);
			printf("\n\n  *** Patient\'s Data***\n\n");
			printf("  Gender:  %c \n", patient.sex[ii]);
			printf("  Age:  %d \n", patient.age[ii]);
			printf("  Location:  %s \n", patient.city[ii]);

			printf("\n  Are you sure to delete? (y/n):  ");
b:			answer = getchar(); // scans for 'answer'

			switch (answer) // swith-case statement
			{
			case 'y':
				fread(&patient, sizeof(struct data), 1, list);
				patient.id[ii] = 0; // id of this patinent becomes zero, so he doesn't exist anymore
				fwrite(&patient, sizeof(struct data), 1, list); // write new data to file
				fclose(list);
				main_menu();
				break;

			case 'n':
				fclose(list);
				choice();
				break;
			default: // if there is no such choice goes back to scanning 'answer'
				goto b;
				break;
			}
		}
	}
}

/*
* Function: find_data()
* ---------------------------
* Allows to find patient's data and see it
* 
* ii: for for loop
* enter_id: for scanning needed for user patient  
* list: pointer to file
* 
*/
void find_data()
{
	system("cls");

	list = fopen("list.bin", "rb");

	if (list == NULL) // checks for availability of file
	{
		printf("  Could not open file:(");
		exit(1);
	}

	int ii, enter_id;

	printf("    *** Find Patient\'s Data ***\n");
	line();
	printf("\n\n  Enter Patient\'s ID:  ");
	scanf("%d", &enter_id);
	
	for (ii = 0; ii < MAX; ii++) // for searching this patient
	{	
		if (patient.id[ii] == enter_id) // if he does exist 
		{
			line();
			fread(&patient, sizeof(struct data), 1, list);
			printf("\n\n   *** Patient Data***\n");
			printf("  Gender:  %c \n", patient.sex[ii]);
			printf("  Age:  %d \n", patient.age[ii]);
			printf("  Location:  %s \n", patient.city[ii]);

			fclose(list);
			choice();
		}
		if ((ii == MAX - 1) && (patient.id[ii] != enter_id)) // if not found
		{
			printf("  Not found &(");
			fclose(list);
			choice();
		}
	}
}

/*
* Function: show_stat()
* ----------------------------
* Allows to see several statics about patients
* 
* action: to go to the next statement
* back: to go to menu of show_stat()
* ii: for for loop
* 
* male_num: to show number of male patients
* female_num: to show number of female patients
* 
* m_percent: to show percentage of male patients among all  
* f_percent: to show percentage of female patients among all  
* 
* seoul: to show number of patients in Seoul
* suwon: to show number of patients in Suwon
* busan: to show number of patients in Busan
* incheon: to show number of patients in Incheon
* ulsan: to show number of patients in Ulsan
* 
* age1: to show number of patients with age < 10 years
* age1_2: to show number of patients with age 10 < age < 20 years
* age2_3: to show number of patients with age 20 < age < 30 years
* age3_4: to show number of patients with age 30 < age < 40 years
* age4_5: to show number of patients with age 40 < age < 50 years
* age5_6: to show number of patients with age 50 < age < 60 years
* age6: to show number of patients with age > 60 years
* 
*/
void show_stat()
{
	system("cls");

	list = fopen("list.bin", "rb");

	if (list == NULL) //  checks for file availabilty
	{
		printf("  Could not open file:(");
		exit(1);
	}

	int action, back, ii;
	int male_num = 0, female_num = 0;
	float m_percent = 0, f_percent = 0;
	int seoul = 0, suwon = 0, busan = 0, incheon = 0, ulsan = 0;
	int age1 = 0, age1_2 = 0, age2_3 = 0, age3_4 = 0, age4_5 = 0, age5_6 = 0, age6 = 0;

	printf("	    *** Statics *** \n");
	line();
	printf("	\n    System menu \n");
	printf("  1. Statics by gender \n");
	printf("  2. Statics by location \n");
	printf("  3. Statics age \n");
	printf("  4. Back to main menu \n");
	line();
c:	printf("\n\n  Enter Your Choice: ");
	scanf("%d", &action); // scans for further action

	switch (action) // swithc-case statement
	{
	case 1:
		system("cls");

		fread(&patient, sizeof(struct data), 1, list);
		printf("   *** Statics by Gender *** \n");
		line();

		for (ii = 0; ii < MAX; ii++) // loop that searches for patients
		{	
			if (patient.id[ii] != 0) // if he does exist
			{
				fread(&patient, sizeof(struct data), 1, list);

				if (patient.sex[ii] == 'M') // if gender of patient is M than male_num increases by one
					male_num++;
				if (patient.sex[ii] == 'F') // if gender of patient is F than female_num increases by one
					female_num++;
			}
		}
		m_percent = (float)male_num / count; // calcullates percentage of M among patients 
		f_percent = (float)female_num / count;// calcullates percentage of F among patients 

		// prints results
		printf("\n\n  Number of male patients: %d(%.2f %%) \n\n", male_num, m_percent);
		printf("  Number of female patients: %d(%.2f %%) \n\n\n", female_num, f_percent);
		printf("  <= Back(choose 0)\n");
		line();
		printf("\n\n  Enter your choice: ");
		scanf("%d", &back); 

		if (back == 0)
			show_stat(); // goes back to menu of show_stat()
		break;
	case 2:
		system("cls");

		printf("   *** Statics by Location *** \n");
		line();

		fread(&patient, sizeof(struct data), 1, list);
		while (!feof(list)) //  while is not end of the file
		{
			for (ii = 1; ii <= count; ii++) // for loop
			{	
				if (patient.id[ii] != 0) // if patient exists
				{	
					// compares location of patient with names of the city
					// and if mathes then increases number of patients in thic city
					if (strcmp(patient.city[ii], "Seoul") == 0)
						seoul++;
					if (strcmp(patient.city[ii], "Suwon") == 0)
						suwon++;
					if (strcmp(patient.city[ii], "Busan") == 0)
						busan++;
					if (strcmp(patient.city[ii], "Incheon") == 0)
						incheon++;
					if (strcmp(patient.city[ii], "Ulsan") == 0)
						ulsan++;
					fread(&patient, sizeof(struct data), 1, list);
				}
			}
		}

		// prints results
		printf("\n\n  Seoul: %d \n\n", seoul++); 
		printf("  Suwon: %d \n\n", suwon++);
		printf("  Busan: %d \n\n", busan++);
		printf("  Incheon: %d \n\n", incheon++);
		printf("  Ulsan: %d \n\n\n", ulsan++);
		printf("  <= Back(choose 0)\n");
		line();
		printf("\n\n  Enter your choice: ");
		scanf("%d", &back);

		if (back == 0)
			show_stat(); // goes back to menu of show_stat()
		break;
	case 3:
		system("cls");

		fread(&patient, sizeof(struct data), 1, list);
		printf("   *** Statics by Age *** \n");
		line();

		for (ii = 0; ii < MAX; ii++) // searches for all patients
		{
			if (patient.id[ii] != 0) // if patient exists
			{	
				// checks for patient's age and
				// increases number of patients in such age category 
				if ((patient.age[ii] < 10) && (patient.age[ii] > 0))
					age1++;
				else if ((patient.age[ii] >= 10) && (patient.age[ii] < 20))
					age1_2++;
				else if ((patient.age[ii] >= 20) && (patient.age[ii] < 30))
					age2_3++;
				else if ((patient.age[ii] >= 30) && (patient.age[ii] < 40))
					age3_4++;
				else if ((patient.age[ii] >= 40) && (patient.age[ii] < 50))
					age4_5++;
				else if ((patient.age[ii] >= 50) && (patient.age[ii] < 60))
					age5_6++;
				else if (patient.age[ii] > 60)
					age6++;
				fread(&patient, sizeof(struct data), 1, list);
			}
		}

		// prints results
		printf("\n\n  Age (< 10): %d \n\n", age1);
		printf("  Age (10 ~ 20): %d \n\n", age1_2);
		printf("  Age (20 ~ 30): %d \n\n", age2_3);
		printf("  Age (30 ~ 40): %d \n\n", age3_4);
		printf("  Age (40 ~ 50): %d \n\n", age4_5);
		printf("  Age (50 ~ 60): %d \n\n", age5_6);
		printf("  Age (60 < ): %d \n\n\n", age6);
		printf("  <= Back(choose 0)\n");
		line();
		printf("\n\n  Enter your choice: ");
		scanf("%d", &back);

		if (back == 0)
			show_stat(); // goes back to menu of show_stat()
		break;
	case 4:
		fclose(list); // closes file if user selected '4'
		main_menu(); // goes to main_menu() of software
		break;
	default: // if user typed wrong number then goes back to scan 'action' 
		printf("  There is no such choice\n"); 
		goto c;
		break;
	}
}

/*
* Function: locat()
* ----------------------
* Allows to see how many patients are in your city 
* 
* locate: to scan current location of user 
* ii: for for loop
* counter_locate: counts number of patients in your city
* 
*/
void locat()
{	
	system("cls");
	
	list = fopen("list.bin", "rb");
	char locate[10];
	int ii, counter_locate = 0;

	if (list == NULL) // checks for availabilty of file
	{
		printf("  Could not open file:(");
		exit(1);
	}

	printf("       *** Check Location *** \n");
	line();
	printf("\n\n  Enter your current location: ");
	scanf("%s", locate);

	fread(&patient, sizeof(struct data), 1, list);

	while (!feof(list)) // while is not the end of file
	{
		for (ii = 0; ii <= count; ii++) // for loop
		{	
			// if such patient exists and his location is the same as user's ones
			if ((strcmp(patient.city[ii], locate) == 0) && (patient.id[ii] != 0))
				counter_locate++;
			fread(&patient, sizeof(struct data), 1, list);
		}
	}

	while (counter_locate != 0) // while number of patients is not zero
	{
		line();
		if (counter_locate <= 20) // if number of patients less than 20
		{
			printf("\n\n  %s (Green Area)\n", locate);
			printf("  Total cases %d\n", counter_locate);
			printf("\n\n  Feel free to go outside:)");
			fclose(list);
			choice();
		}
		else if (counter_locate > 60) // if number of patients greater than 60
		{
			printf("\n\n  %s (Red Area)\n", locate);
			printf("  Total cases %d\n", counter_locate);
			printf("\n  DONT GO OUTSIDE! ");
			fclose(list);
			choice();
		}
		else
		{
			printf("\n\n  %s (Yellow Area)\n", locate);
			printf("  Total cases %d\n", counter_locate);
			printf("\n  Be careful");
			fclose(list);
			choice();
		}
	}
}

/*
* Function: show_list()
* -------------------------
* Allows to see all patient's list with their data
* 
* ii: for for loop
* 
*/
void show_list()
{	
	system("cls");

	printf("    *** Patient\'s List *** \n");
	line();

	int ii;
	list = fopen("list.bin", "rb+");

	if (list == NULL) // checks file availability
	{
		printf("  Could not open file:(");
		exit(1);
	}

	printf("\n\n  ID	Gender	  Age	 Location \n\n");
	fread(&patient, sizeof(struct data), 1, list);

	while (!feof(list)) // while it is not the end of the file
	{	
		fread(&patient, sizeof(struct data), 1, list);
		for (ii = 1; ii <= count; ii++) // for loop
		{	
			if (patient.id[ii] != 0) // if this patient exists
			{
				fread(&patient, sizeof(struct data), 1, list);
				printf("  %d	%c	  %d     %s \n", patient.id[ii], patient.sex[ii], patient.age[ii], patient.city[ii]);
			}
		}
	}
	fclose(list); // closes file
	choice();
}

/*
* Function: safety()
* ------------------------
* A simple functions that reminds the user about safety rules during the pandemic
* 
* action: for further actions
*/
void safety()
{
	system("cls");

	int action;

	printf("      *** Show Safety Rules ***\n");
	line();

	printf("\n\n  What do you want to know?\n\n");
	printf("  1. Masks\n");
	printf("  2. Hands\n");
	printf("  3. Distance\n");
	printf("  4. Main menu\n");
	line();
	printf("\n\n  Enter your choce:  ");
	scanf("%d", &action);

	switch (action) // switch-case statement
	{
	case 1:
		system("cls");

		printf("     *** Masks ***\n");
		line();
		printf("\n\n  Due to corona pandemic situation we all should wear masks\n\n");
		printf("  ALWAYS wear them when you go outside\n");
		printf("  In restoraunts you may take mask off ONLY while eating\n");
		printf("  Please take these advices seriusly, only together we can win CoVid\n");
		printf("  :)\n");
		safety_back();
		break;
	case 2:
		system("cls");

		printf("	*** Hands ***\n");
		line();
		printf("\n\n  Due to corona pandemic situation we all should wash our hands more often than usual\n\n");
		printf("  Wash hands with soap more than 30 SECONDS!\n");
		printf("  And don't forget to use hand sanitizers\n");
		printf("  :)\n");
		safety_back();
		break;
	case 3:
		system("cls");

		printf("	 *** Distance ***\n");
		line();
		printf("\n\n  Due to corona pandemic situation we all should keep social distance \n\n");
		printf("  Keep distance more than 2 METERS! \n");
		printf("  And remember NO HUGS &( and NO HANDSHAKES &(\n");
		printf("  :)\n");
		safety_back();
		break;
	case 4: // if user typed '4' then goes to main_menu()
		main_menu();
		break;
	}
}

/*
* Function: safety_back()
* --------------------------
* Allows to go to either menu of safety() or to main_menu()
* 
* back: to make a decision
* 
*/
void safety_back()
{	
	int back;

	printf("\n\n  1. Go back\n");
	printf("  2. Go to main menu\n");
	line();
	printf("\n\n  Enter your choice:   ");
	scanf("%d", &back);

	switch (back) // switch-case statement
	{
	case 1: // if '1' then goes to safety() menu
		safety();
		break;
	case 2: // if '2' then goes to main_menu()
		main_menu();
		break;
	}
}