/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"


// Initializes the array of questions for the game
void initialize_game(void)
{

	strncpy(questions[0].category, "numbers", MAX_LEN);
	strncpy(questions[0].question, "1+1", MAX_LEN);
	strncpy(questions[0].answer, "2", MAX_LEN);
	questions[0].value = 100;
	questions[0].answered = false;

	strncpy(questions[1].category, "numbers", MAX_LEN);
	strncpy(questions[1].question, "2+2", MAX_LEN);
	strncpy(questions[1].answer, "4", MAX_LEN);
	questions[1].value = 200;
	questions[1].answered = false;

	strncpy(questions[2].category, "numbers", MAX_LEN);
	strncpy(questions[2].question, "3+3", MAX_LEN);
	strncpy(questions[2].answer, "6", MAX_LEN);
	questions[2].value = 300;
	questions[2].answered = false;

	strncpy(questions[3].category, "numbers", MAX_LEN);
	strncpy(questions[3].question, "1+2", MAX_LEN);
	strncpy(questions[3].answer, "3", MAX_LEN);
	questions[3].value = 400;
	questions[3].answered = false;

 //    // initialize each question struct and assign it to the questions array
 //    for (int x = 0; x < sizeof(questions)/sizeof(question) ; x++){
	//     questions[x].answered = false;
 //    }
 	
 // 	for (int y = 0; y < 3; y++){
	//  	for (int x = 0; x < (sizeof(questions)/sizeof(question))/3 ; x++){
	//         	strncpy(questions[x+y*4].category, "test cat", MAX_LEN);
	//     }	
 // 	}


	// strncpy(questions[0].question, "test question", MAX_LEN);
	// questions[0].value = 100;
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
	for(int i = 0; i < sizeof(questions)/sizeof(*questions); i++)
	{
		//printf("%d, %s, %s, %d, ", i, questions[i].category, category, strcmp(questions[i].category,category));
		//printf("%d, %d, %d ", questions[i].value, value, value == questions[i].value);
		//printf("\n");
		if(strcmp(questions[i].category, category) == 0 && questions[i].value == value && questions[i].answered == 0)
		{
			printf("%s", questions[i].question);
		}
	}

	//puts("end of function");
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    return false;
}
