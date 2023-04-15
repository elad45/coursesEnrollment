/***********************
* Elad Vizenblit
***********************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ex5.h"
#define COURSE_AMOUNT 5
#define MAX 200
#define SPACE ' '
#define COMMA ','
#define COURSE_NAME 30
#define COURSE_NUMBER 5
#define STUDENT_NAME 20
#define GRADE_MAX_LENGTH 3
#define LOWEST_POSSIBLE 0
#define INITIZALIZE 101

void removeStudent(Student* toDelete, Course* coursePointer);
void options(char choice, Course* coursePointer);
void saveData(char buf[], Course* coursePointer);
void checkExists(char* courseNumber, char* nameCourse, Course* coursePointer);
int isStudentNameValid(char studentName[]);
void isStudentValid(Course* coursePointer, int studentCounter);
int isCourseNumberStudentValid(char courseNumber[], Course* coursePointer);
void addChangeStudent(char buf[], Course* coursePointer, int amountCommas);
int isGradeValid(int grade);
void newStudent(const char studentName[], char courseNumber[], int grade, Course* coursePointer);
void addOrUpdateStudent(Student* std, Course* coursePointer);
void courseMain(Course* coursePointer);
int isRemoveValid(char buf[], int commasCounter, Course* coursePointer);
void removeStudentMain(Course* coursePointer);
void freeMemory(Course* coursePointer);
void printClass(Course* coursePointer);
void averageGrade(Course* coursePointer, int existCourses);
void maximalGrade(Course* coursePointer, int existCourses);
void minimalGrade(Course* coursePointer, int existCourses);
void sumGrade(Course* coursePointer, int existCourses);
void count(Course* coursePointer, int existCourses);
int isCourseRemain(int commasCounter, Course* coursePointer, char* name);
void printComputedScores(Course* coursePointer);

/******************
* Function Name: menu
* Input: Course* coursePointer
* Output: n/a
* Function Operation: Prints a menu for operating a course system. like add,remove students,
					  print class, and some calculates with grades. the user has to choose an option,
					  the function calls another function called options.
******************/
void menu(Course* coursePointer)
{
	char choice = '0';
	//print a menu
	printf("Please select an operation:\n\t0. Exit.\n\t1. Insert or update a class.\n\t"
		   "2. Insert or update a student.\n\t"
		   "3. Remove a student from classes.\n\t4. Print a class.\n\t"
		   "5. Print all classes with their computed scores.\n\t6. Print the menu.\n");
	scanf(" %c", &choice);
	options(choice, coursePointer);
}

/******************
* Function Name: options
* Input: char choice, Course* coursePointer
* Output:n/a
* Function Operation:Based on the choice the user made on the menu function,
					 it calls to the right function to perform the choice.
******************/
void options(char choice, Course* coursePointer)
{
	int studentsCounter = 0;
	while (choice != '0')
	{
		switch (choice)
		{
		case '1':
			courseMain(coursePointer);
			break;
		case '2': isStudentValid(coursePointer, studentsCounter);
			break;
		case '3': removeStudentMain(coursePointer);
			break;
		case '4': printClass(coursePointer);
			break;
		case '5': printComputedScores(coursePointer);
			break;
		case '6':printf("Please select an operation:\n\t0. Exit.\n\t1. Insert or update a class.\n\t"
			 "2. Insert or update a student.\n\t"
			 "3. Remove a student from classes.\n\t4. Print a class.\n\t"
			 "5. Print all classes with their computed scores.\n\t6. Print the menu.\n");
			break;
		default: printf("Error: unrecognized operation.\n");
		}

		if (choice != '6')
			printf("Select the next operation (insert 6 for the entire menu):\n");
		scanf(" %c", &choice);
	}
	freeMemory(coursePointer);
}

/******************
* Function Name: courseMain
* Input: Course* coursePointer
* Output:n/a
* Function Operation: gets an input with details about the course, it has to get course number made of 5 numbers
					  and a course name with up to 30 chars. The function calls saveData to check the input is okay.
******************/
void courseMain(Course* coursePointer)
{
	printf("The format is 5 numbers followed by course name\n");
	char buf[MAX + 1] = { 0 };
	scanf(" %[^\n]", buf);
	//checks if input valid
	saveData(buf, coursePointer);

}


/******************
* Function Name: saveData
* Input: char buf[],Course* coursePointer
* Output: n/a
* Function Operation: The function gets the course Input and checks if it's okay
******************/
void saveData(char buf[], Course* coursePointer)
{
	int i = 0, counter = 0, isValid = 0;
	char* ptr = buf, * checkAll = buf;
	char* courseName = "0";
	// this loop checks if there is only numbers in course number
	while (isdigit(*ptr))
	{
		counter++;
		ptr++;
	}
	//differ than 5 digits
	if (counter != 5)
	{
		printf("Error: invalid class number or name.\n");
		return;
	}
	//checks string contains only letters, digits and spaces
	while (*checkAll != '\0')
	{
		if (isdigit(*checkAll) || isalpha(*checkAll) || *checkAll == SPACE)
			isValid = 1;
		else
		{
			printf("Error: invalid class number or name.\n");
			return;
		}
		checkAll++;
	}
	counter = 0;
	/*
	remove spaces
	*/
	while (*ptr == SPACE)
		ptr++;
	courseName = ptr;

	//course name too long
	if (strlen(ptr) > COURSE_NAME)
	{
		printf("Error: invalid class number or name.\n");
		return;
	}
	//invalid input
	if (*courseName == '\0')
	{
		printf("Error: invalid class number or name.\n");
		return;
	}
	//takes courseNumber
	ptr = strtok(buf, " ");
	checkExists(ptr, courseName, coursePointer);
}

/******************
* Function Name: checkExists
* Input: char* courseNumber,char* nameCourse,Course* coursePointer
* Output:n/a
* Function Operation: the function adds/updates the course name,
		              depends on whether course number is already in the system or not
******************/
void checkExists(char* courseNumber, char* nameCourse, Course* coursePointer)
{
	int isValid = 0;
	/*
	* checks if course is already in the system, and updates if so
	*/
	for (int i = 0; i < COURSE_AMOUNT; i++)
	{
		if (strcmp(coursePointer[i].number, courseNumber) == 0)
		{
			//Updating course
			strcpy(coursePointer[i].name, nameCourse);
			printf("Class \"%s %s\" updated.\n", courseNumber, nameCourse);
			return;
		}
	}

	//adds course
	for (int i = 0; i < COURSE_AMOUNT; i++)
	{
		if (coursePointer[i].isEmpty == 1)
		{
			strcpy(coursePointer[i].name, nameCourse);
			strcpy(coursePointer[i].number, courseNumber);
			coursePointer[i].isEmpty = 0;
			printf("Class \"%s %s\" added.\n", courseNumber, nameCourse);
			return;
		}
	}
	//if both didnt return, means no space left
	printf("Unfortunately, there is no room for more classes.\n");

}
/*end of ex1*/

/*begining of ex2*/

/******************
* Function Name: countCommas
* Input: char buf[]
* Output: amount of commas
* Function Operation: the function returns on how many commas there is in the input.
******************/
int countCommas(char buf[])
{
	int commasCounter = 0;
	//count commas
	for (int i = 0; i < strlen(buf); i++)
	{
		if (buf[i] == COMMA)
			commasCounter++;
	}
	return commasCounter;
}

/******************
* Function Name: isStudentValid
* Input: Course* coursePointer, int studentCounter
* Output:n/a
* Function Operation: checks if the input of the student is okay, using some more function,
					  and in the end calls andChangeStudent to add him to the course.
******************/
void isStudentValid(Course* coursePointer, int studentCounter)
{
	int commasCounter, countLoops = 0, grade;
	char* ptr;
	char  buf[MAX + 1] = { 0 }, studentName[STUDENT_NAME + 1], courseNumber[COURSE_NUMBER + 1], copyBuf[MAX + 1];
	//scans input
	printf("The format is: Elad:89110,100;8911,80;\n");
	scanf(" %[^\n]", buf);
	//makes BackUp
	strcpy(copyBuf, buf);
	commasCounter = countCommas(buf);
	//student name
	ptr = strtok(buf, ":");
	//student name length max is 20
	if (strlen(ptr) > STUDENT_NAME)
	{
		printf("Error: invalid name, class number or grade.\n");
		return;
	}
	strcpy(studentName, ptr);
	//checking the studentName input. 0 means not valid
	if (isStudentNameValid(studentName) == 0)
		return;
	//commas indicates amount of courses requested for the student. this loop checks the input os okay
	while (countLoops < commasCounter)
	{
		//courseNumber
		ptr = strtok(NULL, ",");
		//delete spaces in the begining
		while (*ptr == SPACE)
			ptr++;
		//nuber is too long, error.
		if (strlen(ptr) > COURSE_NUMBER)
		{
			printf("Error: invalid name, class number or grade.\n");
			return;
		}
		strcpy(courseNumber, ptr);
		//checks if course Number is okay, 0 means invalid
		if (isCourseNumberStudentValid(courseNumber, coursePointer) == 0)
		{
			printf("Error: invalid name, class number or grade.\n");
			return;
		}
		//takes the grade
		ptr = strtok(NULL, ";");
		if (ptr == NULL)
		{
			printf("Error: invalid name, class number or grade.\n");
			return;
		}
		//delete spaces
		while (*ptr == SPACE)
			ptr++;
		if (strlen(ptr) > GRADE_MAX_LENGTH)
		{
			printf("Error: invalid name, class number or grade.\n");
			return;
		}
		grade = atoi(ptr);
		//0 means grade is invalid
		if (isGradeValid(grade) == 0)
		{
			printf("Error: invalid name, class number or grade.\n");
			return;
		}
		//continue to the next course
		countLoops++;
	}
	//if this area reached. it means the input is valid.
	addChangeStudent(copyBuf, coursePointer, commasCounter);
}

/******************
* Function Name: isStudentNameValid
* Input: char studentName[]
* Output:0 not valid 1 valid
* Function Operation: checks if the student name input is okay. can be only letters and spaces.
******************/
int isStudentNameValid(char studentName[])
{
	//checks if the name is only formed of letters and spaces.
	for (int i = 0; studentName[i] != '\0'; i++)
		if (isalpha(studentName[i]) == 0 && (studentName[i] != SPACE))
		{
			printf("Error: invalid name,class number or grade.\n");
			return 0;
		}
	return 1;
}

/******************
* Function Name: isCourseNumberStudentValid
* Input: char courseNumber[],Course* coursePointer
* Output:0 not valid 1 valid
* Function Operation: checks if the input of the student's course number is okay.
******************/
int isCourseNumberStudentValid(char courseNumber[], Course* coursePointer)
{
	int isExists = 0;
	//checks if the student course really exists.
	for (int i = 0; i < COURSE_AMOUNT; i++)
		if (strcmp(courseNumber, coursePointer[i].number) == 0)
			isExists = 1;
	return isExists;
}

/******************
* Function Name: isGradeValid
* Input: int grade
* Output: 0 not valid 1 valid
* Function Operation: checks if the input of grade is valid. must be between 0 to 100.
******************/
int isGradeValid(int grade)
{
	//valid grade range is 0-100
	if (grade > 100 || grade < 0)
		return 0;
	return 1;

}


/******************
* Function Name: addStudent
* Input: const char studentName[], char courseNumber[], int grade, Course* coursePointer
* Output:n/a
* Function Operation: The function creates a new student structure, gives it values.
					  and calls addOrUpdateStudent to put him in the course.
******************/
void newStudent(const char studentName[], char courseNumber[], int grade, Course* coursePointer)
{
	Student* std = (Student*)malloc(sizeof(Student));
	if (std == NULL)
	{
		freeMemory(coursePointer);
		exit(1);
	}
	//put the values in the new student
	strcpy(std->name, studentName);
	std->grade = grade;
	strcpy(std->courseStudent, courseNumber);
	std->next = NULL;
	//calls a function to add or update the student
	addOrUpdateStudent(std, coursePointer);
}

/******************
* Function Name: addOrUpdateStudent
* Input: Student* std, Course* coursePointer
* Output:n/a
* Function Operation: Adds/updates the student in the course.
******************/
void addOrUpdateStudent(Student* std, Course* coursePointer)
{
	//1 means new
	int isNew = 1;
	//run on all courses to find the right course number
	for (int i = 0; i < COURSE_AMOUNT; i++)
	{
		//if course nunmber equals to student course number insert the values
		if (strcmp(coursePointer[i].number, std->courseStudent) == 0)
		{
			//in case he is the first student
			if (coursePointer[i].head == NULL)
			{
				coursePointer[i].head = std;
				coursePointer[i].last = std;
				if (std == NULL)
					exit(1);
				printf("Student \"%s\" added to class \"%s %s\" with grade %d.\n",
					std->name, coursePointer[i].number, coursePointer[i].name, std->grade);
			}
			else
			{
				/*Student* runner = (Student*)malloc(sizeof(Student));
				
				if (runner == NULL)
				{
					freeMemory(coursePointer);
					exit(1);
				}*/
				Student* runner = coursePointer[i].head;
				//runs all over the list, updates if the student is found
				while (runner != NULL)
				{
					if (strcmp(std->name, runner->name) == 0)
					{
						//indicates student found, hence no need to add a new one.
						isNew = 0;
						runner->grade = std->grade;
						printf("Student \"%s\" updated on class \"%s %s\" with grade %d.\n",
							std->name, coursePointer[i].number, coursePointer[i].name, std->grade);
					}
					runner = runner->next;
				}
				//no student found, adds it to the list
				if (isNew == 1)
				{
					coursePointer[i].last->next = std;
					coursePointer[i].last = std;
					printf("Student \"%s\" added to class \"%s %s\" with grade %d.\n",
						std->name, coursePointer[i].number, coursePointer[i].name, std->grade);
				}
				//free(runner);			
        free(std);
			}
		}
	}
}

/******************
* Function Name: addChangeStudent
* Input: char buf[],Course* coursePointer, int amountCommas
* Output:n/a
* Function Operation: The function gets an input with list of courses to assign the student,
					  and calls newStudent to assign him in the courses.
******************/
void addChangeStudent(char buf[], Course* coursePointer, int amountCommas)
{
	int countCommas = 0, countLoops = 0;
	char* ptr;
	char studentName[STUDENT_NAME + 1], courseNumber[COURSE_NUMBER + 1];
	int grade = 0;
	//Takes the name
	ptr = strtok(buf, ":");
	strcpy(studentName, ptr);
	//Number of commas indicates number of courses.
	while (countLoops < amountCommas)
	{
		//Takes the course number
		ptr = strtok(NULL, ",");
		while (*ptr == SPACE)
			ptr++;
		strcpy(courseNumber, ptr);
		//Takes grade
		ptr = strtok(NULL, ";");
		while (*ptr == SPACE)
			ptr++;
		grade = atoi(ptr);
		//calls a function to put the values in a student struct
		newStudent(studentName, courseNumber, grade, coursePointer);
		//increasing counter
		countLoops++;
	}
}
/*end of ex2*/

/*begin of ex3*/
/******************
* Function Name: removeStudentMain
* Input: Course* coursePointer
* Output:n/a
* Function Operation: Gets an input and calls another functions to check if valid,
					  if does, calls another function to remove the student from the course.
******************/
void removeStudentMain(Course* coursePointer)
{
	int commasCounter = 0, countDeleted = 0;
	char* nameToken, * courseNumbers;
	char buf[MAX + 1] = { 0 }, copyBuf[MAX + 1];
	Student* toDelete = (Student*)malloc(sizeof(Student));
	if (toDelete == NULL)
	{
		freeMemory(coursePointer);
		exit(1);
	}
	//gets the input, ignors all spaces in the begining
	printf("The format is: Ron Sherman: 89210, 89211,\n");
	scanf(" %[^\n]", buf);
	strcpy(copyBuf, buf);
	//saves amount of commas
	commasCounter = countCommas(buf);
	//no commas means input is invalid
	if (commasCounter == 0)
	{
		printf("Error: invalid name or class number.\n");
		return;
	}
	//check if the input is valid
	if (isRemoveValid(copyBuf, commasCounter, coursePointer) == 0)
	{
		printf("Error: invalid name or class number.\n");
		return;
	}
	//saves the name of the student
	nameToken = strtok(buf, ":");
	if (nameToken == NULL)
	{
		printf("Error: invalid name or class number.\n");
		return;
	}
	//checks if it removes the student from all his classes.
	if (isCourseRemain(commasCounter, coursePointer, nameToken) == 0)
	{
		printf("Error: student cannot be removed from all classes.\n");
		return;
	}
	//puts name in toDelete
	strcpy(toDelete->name, nameToken);
	/*
	* runs as long as there are more courses to delete. (commasCounter indicates amount of courses to delete)
	*/
	while (countDeleted < commasCounter)
	{
		courseNumbers = strtok(NULL, ",");
		//in case no course after the comma
		if (courseNumbers == NULL)
			return;
		//ignore spaces
		while (*courseNumbers == SPACE)
			courseNumbers++;
		//insert coursenumber to the strudent struct
		strcpy(toDelete->courseStudent, courseNumbers);
		//calls function to delete the student from the course
		removeStudent(toDelete, coursePointer);
		countDeleted++;
	}
	free(toDelete);
}

/******************
* Function Name: isRemoveValid
* Input: char buf[],int commasCounter,Course* coursePointer
* Output:n/a
* Function Operation: Checks if valid to remove student based on the input
******************/
int isRemoveValid(char buf[], int commasCounter, Course* coursePointer)
{
	char* courseNumber, * ptr;
	int coursesChecked = 0, isExist = 0;
	//takes name
	ptr = strtok(buf, ":");
	//runs all over the courses to see what courses the student assigned for
	while (coursesChecked < commasCounter)
	{
		//take course number
		courseNumber = strtok(NULL, ",");
		//ignore spaces
		while (*courseNumber == SPACE)
			courseNumber++;
		//check whether the course really exists.
		for (int i = 0; i < COURSE_AMOUNT; i++)
		{
			//this counter used to check whether all courses really exists
			if (strcmp(courseNumber, coursePointer[i].number) == 0)
				isExist++;
		}
		coursesChecked++;
	}
	//if amount of the courses that really exists equivalent to amount of commas, returns 1
	if (isExist == commasCounter)
		return 1;
	return 0;

}
/******************
* Function Name: isCourseRemain
* Input: int commasCounter, Course* coursePointer,char *name)
* Output:1 valid 0 not valid
* Function Operation: Checks whether the student still has courses. returns 0 if not, 1 if has
******************/
int isCourseRemain(int commasCounter, Course* coursePointer, char* name)
{
	int counter = 0, existCourses = 0;;
	Student* runner;
	//set all empty courses as empty in the "isEmpty" field.
	for (int i = 0; i < COURSE_AMOUNT; i++)
	{
		if (coursePointer[i].head == NULL)
			coursePointer[i].isEmpty = 1;
	}
	//runs all over the courses to see how many corses the student is assigned to
	for (int i = 0; i < COURSE_AMOUNT; i++)
	{
		//if the course is empty, continue.
		if (coursePointer[i].isEmpty == 1)
			continue;
		runner = coursePointer[i].head;
		//runs with runner all over the list to see if assigned
		while (runner != NULL)
		{
			//if assigned, increase counter
			if (strcmp(runner->name, name) == 0)
				counter++;
			runner = runner->next;
		}
	}
	// if amount of courses the student has equals to amount he wants to be delted from return 0 else 1
	if (commasCounter == counter)
		return 0;
	return 1;
}
/******************
* Function Name: removeStudent
* Input: Student *toDelete, Course* coursePointer
* Output:n/a
* Function Operation: The function removes a student from a course
******************/
void removeStudent(Student* toDelete, Course* coursePointer)
{
	//runs all over the courses
	for (int i = 0; i < COURSE_AMOUNT; i++)
	{
		Student* prev = coursePointer[i].head;
		Student* current = coursePointer[i].head;
		//if the course number of the student is the correct index in the course array, get in the block.
		if (strcmp(coursePointer[i].number, toDelete->courseStudent) == 0)
		{
			//no students in the course
			if (coursePointer[i].head == NULL)
			{
				printf("Error: student is not a member of class \"%s %s\".\n",
					    coursePointer[i].number, coursePointer[i].name);
				break;
			}
			//run all over the student's list in the course
			while (current != NULL)
			{
				//when the student is found, get in the block.
				if (strcmp(toDelete->name, current->name) == 0)
				{
					//If the student is in the begining of the linked list
					if (current == coursePointer[i].head)
					{
						//moves head to the next student struct 
						coursePointer[i].head = coursePointer[i].head->next;
						printf("Student \"%s\" removed from class \"%s %s\".\n",
							toDelete->name, toDelete->courseStudent, coursePointer[i].name);
						break;
					}
					//If the student is in the end of the linked list
					if (current == coursePointer[i].last)
					{
						prev->next = NULL;
						//sets last to be prev
						coursePointer[i].last = prev;
						printf("Student \"%s\" removed from class \"%s %s\".\n",
							toDelete->name, toDelete->courseStudent, coursePointer[i].name);
						break;
					}
					prev->next = current->next;
					printf("Student \"%s\" removed from class \"%s %s\".\n",
						toDelete->name, toDelete->courseStudent, coursePointer[i].name);
					break;
				}
				//for the middle of the linked list
				prev = current;
				current = current->next;

			}
			//the student wasn't found in the course
			if (current == NULL)
				printf("Error: student is not a member of class \"%s %s\".\n",
					    coursePointer[i].number, coursePointer[i].name);
			free(current); 
		}
	}
}

/******************
* Function Name: freeMemory
* Input: Course* coursePointer
* Output:n/a
* Function Operation: The function deletes all the dynamic memory
******************/

void freeMemory(Course* coursePointer)
{
	Student* current, * temp;
	//runs on all the courses 
	for (int i = 0; i < COURSE_AMOUNT; i++)
	{
		current = coursePointer[i].head;
		//deletes the list
		while (current != NULL)
		{
			temp = current->next;
			free(current);
			current = temp;
		}
	}
}

/******************
* Function Name: swap
* Input: Student *a, Student *b
* Output:n/a
* Function Operation: The function swaps between two students in the linked list.
******************/
void swap(Student* a, Student* b)
{
	int tempGrade = a->grade;
	char tempName[21];
	char tempCourseStudent[6];
	//using temp for the swap
	strcpy(tempName, a->name);
	strcpy(tempCourseStudent, a->courseStudent);
	//swaps student a
	a->grade = b->grade;
	strcpy(a->name, b->name);
	strcpy(a->courseStudent, b->courseStudent);

	//swaps student b
	b->grade = tempGrade;
	strcpy(b->name, tempName);
	strcpy(b->courseStudent, tempCourseStudent);
}

/******************
* Function Name: PrintClass
* Input: Course* coursePointer
* Output:n/a
* Function Operation: The function prints a course in alphabetical sort
******************/
void printClass(Course* coursePointer)
{
	char buf[MAX + 1] = { 0 };
	int isValid = 0;
	Student* runner = NULL, * current;
	printf("Enter course no.\n");
	scanf(" %[^\n]", buf);
	//runs all over the courses
	for (int i = 0; i < COURSE_AMOUNT; i++)
	{
		//if the course has been found, goes inside the block
		if (strcmp(coursePointer[i].number, buf) == 0)
		{
			isValid = 1;
			//no students in the course
			if (coursePointer[i].head == NULL)
			{
				printf("Class \"%s %s\" has no students.\n", coursePointer[i].number, coursePointer[i].name);
				return;
			}
			runner = coursePointer[i].head;
			current = coursePointer[i].head;
			{
				//these 2 loops sort the list by alphabetical order
				while (current->next != NULL)
				{
					while (runner != NULL)
					{
						if (strcmp(current->name, runner->name) > 0)
						{
							swap(current, runner);
						}
						runner = runner->next;
					}
					current = current->next;
					runner = current->next;
				}
			}

			current = coursePointer[i].head;
			printf("Class \"%s %s\" students:\n", coursePointer[i].number, coursePointer[i].name);
			//print course in alphabetical order
			while (current != NULL)
			{
				printf("%s, %d\n", current->name, current->grade);
				current = current->next;
			}
		}
	}
	//no such course 
	if (isValid == 0)
	{
		printf("Error: invalid class number.\n");
		return;
	}
}
/******************
* Function Name: printComputedScores
* Input: Course* coursePointer
* Output:n/a
* Function Operation: Prints a menu to perform some mathematical operations with the grades.
					  it calls another functions based on the choice.
******************/
void printComputedScores(Course* coursePointer)
{

	int isEmpty = 1, existCourses = 0;
	char option;

	//checks how many courses there are
	for (int i = 0; i < COURSE_AMOUNT; i++)
	{
		if (coursePointer[i].isEmpty == 0)
		{
			//isEmpty used to check if there is at least 1 course
			isEmpty = 0;
			existCourses++;
		}
	}
	//if there are no courses at all
	if (isEmpty == 1)
	{
		printf("Error: there are no classes.\n");
		return;
	}
	//menu with functions
	printf("Please select the aggregation method:\n\ta. Average Grade.\n\tb. Maximal Grade.\n\tc. Minimal Grade.\n\t"
		"d. Sum.\n\te. Count.\n\t0. Return to the main menu.\n");
	scanf(" %c", &option);
	switch (option)
	{
	case 'a': averageGrade(coursePointer, existCourses);
		break;
	case 'b': maximalGrade(coursePointer, existCourses);
		break;
	case 'c': minimalGrade(coursePointer, existCourses);
		break;
	case 'd': sumGrade(coursePointer, existCourses);
		break;
	case 'e': count(coursePointer, existCourses);
		break;
	case '0': return;
		break;
	}
}

/******************
* Function Name: averageGrade
* Input: Course* coursePointer, int existCourses
* Output:n/a
* Function Operation: The function prints the average grade in all courses
******************/
void averageGrade(Course* coursePointer, int existCourses)
{
	Student* runner;
	int countStudents = 0, sumGrades = 0;
	//runs all over the courses to find the average in every class
	for (int i = 0; i < existCourses; i++)
	{
		countStudents = 0;
		sumGrades = 0;
		runner = coursePointer[i].head;
		//no students in the course
		if (runner == NULL)
		{
			printf("Class \"%s %s\" has no students.\n", coursePointer[i].number, coursePointer[i].name);
			continue;
		}
		//calculates factors for average
		while (runner != NULL)
		{
			sumGrades += runner->grade;
			countStudents++;
			runner = runner->next;
		}
		printf("Class %s %s, %d\n", coursePointer[i].number, coursePointer[i].name, (sumGrades / countStudents));
	}
}

/******************
* Function Name: maximalGrade
* Input: Course* coursePointer, int existCourses
* Output:n/a
* Function Operation: Prints the highest grade in every course
******************/
void maximalGrade(Course* coursePointer, int existCourses)
{
	Student* runner;
	int maxGrade = LOWEST_POSSIBLE;
	//runs all over the courses to find the maximal grade in every course
	for (int i = 0; i < existCourses; i++)
	{
		maxGrade = LOWEST_POSSIBLE;
		runner = coursePointer[i].head;
		//No students in class
		if (runner == NULL)
		{
			printf("Class \"%s %s\" has no students.\n", coursePointer[i].number, coursePointer[i].name);
			continue;
		}
		//checks for the highest grade
		while (runner != NULL)
		{
			if (runner->grade > maxGrade)
				maxGrade = runner->grade;
			runner = runner->next;
		}
		printf("Class %s %s, %d\n", coursePointer[i].number, coursePointer[i].name, maxGrade);
	}
}
/******************
* Function Name: minimalGrade
* Input: Course* coursePointer,int existCourses
* Output:n/a
* Function Operation: The function prints the minimal grade in every course.
******************/
void minimalGrade(Course* coursePointer, int existCourses)
{
	Student* runner;
	int minGrade = INITIZALIZE;
	//runs all over the courses to check for minimal grade in every course
	for (int i = 0; i < existCourses; i++)
	{
		minGrade = INITIZALIZE;
		runner = coursePointer[i].head;
		//No students in class
		if (runner == NULL)
		{
			printf("Class \"%s %s\" has no students.\n", coursePointer[i].number, coursePointer[i].name);
			continue;
		}
		//Checks for the minimum grade
		while (runner != NULL)
		{
			if (runner->grade < minGrade)
				minGrade = runner->grade;
			runner = runner->next;
		}
		printf("Class %s %s, %d\n", coursePointer[i].number, coursePointer[i].name, minGrade);
	}
}

/******************
* Function Name: sumGrade
* Input: Course* coursePointer, int existCourses
* Output:n/a
* Function Operation: Prints the total grade in every course
******************/
void sumGrade(Course* coursePointer, int existCourses)
{
	Student* runner;
	int sumGrades = 0;
	//runs all over the courses to sum the total grade in every course
	for (int i = 0; i < existCourses; i++)
	{
		sumGrades = 0;
		runner = coursePointer[i].head;
		//no students in the course
		if (runner == NULL)
		{
			printf("Class \"%s %s\" has no students.\n", coursePointer[i].number, coursePointer[i].name);
			continue;
		}
		//sums up grades
		while (runner != NULL)
		{
			sumGrades += runner->grade;
			runner = runner->next;
		}
		printf("Class %s %s, %d\n", coursePointer[i].number, coursePointer[i].name, sumGrades);
	}
}
/******************
* Function Name: count
* Input: Course* coursePointer, int existCourses
* Output:n/a
* Function Operation: The function prints how many students are in every course
******************/
void count(Course* coursePointer, int existCourses)
{
	Student* runner;
	int countStudents = 0, sumGrades = 0;
	//runs on all courses to check how many students there are in every course
	for (int i = 0; i < existCourses; i++)
	{
		countStudents = 0;
		runner = coursePointer[i].head;
		//no students in the course
		if (runner == NULL)
		{
			printf("Class \"%s %s\" has no students.\n", coursePointer[i].number, coursePointer[i].name);
			continue;
		}
		//counts amount of student in the course
		while (runner != NULL)
		{
			countStudents++;
			runner = runner->next;
		}
		printf("%s %s, %d\n", coursePointer[i].number, coursePointer[i].name, countStudents);
	}
}
