/***********************
* Elad Vizenblit
***********************/
#include <stdlib.h>
#include <stdio.h>
#define COURSE_NAME 30
#define COURSE_NUMBER 5
#define STUDENT_NAME 20

typedef struct Student{
	char name[STUDENT_NAME+1];
	int grade;
	char courseStudent[COURSE_NUMBER+1];
	struct Student* next;
}Student;

typedef struct Course
{
	char number[COURSE_NUMBER+1];
	char name[COURSE_NAME+1];
	int isEmpty;
	Student *head, *last;
	
}Course;


void menu(Course* coursePointer);
