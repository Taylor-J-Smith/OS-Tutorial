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

	strncpy(questions[0].category, "numbers", MAX_LEN);
	strncpy(questions[0].question, "2+2", MAX_LEN);
	strncpy(questions[0].answer, "4", MAX_LEN);
	questions[0].value = 200;
	questions[0].answered = false;

	strncpy(questions[0].category, "numbers", MAX_LEN);
	strncpy(questions[0].question, "3+3", MAX_LEN);
	strncpy(questions[0].answer, "6", MAX_LEN);
	questions[0].value = 300;
	questions[0].answered = false;

	strncpy(questions[0].category, "numbers", MAX_LEN);
	strncpy(questions[0].question, "1+2", MAX_LEN);
	strncpy(questions[0].answer, "3", MAX_LEN);
	questions[0].value = 400;
	questions[0].answered = false;

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

}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
	for(int i=0; i<3; i++){
		if(strcmp(category, categories[i])==0){
			for(int j=0; j<4; j++){
				if((value/100 == j) && (strcmp(answer, question[i].answer)==0)){

				}
			}
		}
	}

    // Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    return false;
}
