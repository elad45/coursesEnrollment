/***********************
* Elad Vizenblit
***********************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "ex5.h"
#define COURSE_AMOUNT 5

void main()
{
	Course courseArr[COURSE_AMOUNT];
	for (int i = 0; i < COURSE_AMOUNT; i++)
	{
		courseArr[i].isEmpty = 1;
		courseArr[i].head = NULL;
		courseArr[i].last = NULL;
	}	
	menu(courseArr);	
}