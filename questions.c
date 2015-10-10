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
#include <time.h>
#include "questions.h"

//Macros for colors
//USE: ANSI_COLOR_RED"This text is RED!"ANSI_COLOR_RESET "this is not\n"
//@reference stackoverflow.com
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define FILE_CATEGORIES 6 //categories in the file

// Initializes the array of questions for the game
void initialize_game(int round)
{

  // initialize each question struct and assign it to the questions array

  srand(time(NULL));
  int catselector[3];
  int currselect;
  FILE *f;
  if (round == 1){
    f = fopen("bank.txt", "r");
  }else{
    f = fopen("djqs.txt", "r");
  }
  if (f != NULL){
    for (int x = 0; x < 3; x++){
      bool repeat;
      do
	{
	  repeat = true;
	  currselect = rand() % FILE_CATEGORIES;// 5 is number of categories in the file
	  //check if the random number exists in catselector
	  for (int y = 0; y < 3; y++){
	    if (currselect == catselector[y]){
	      repeat = false;
	    }
	  }
	}while (repeat == false);
      catselector[x] = currselect;
    }

    // //iterate over entries in catselector
    for (int x = 0; x < 3; x++){
      // printf("%d \n",catselector[x]); 	
      //get to the line we want
      //reset pointer to start
      fseek(f, 0, SEEK_SET);
      char templine[MAX_LEN];

      for (int z = 0; z < catselector[x];z++){
	fgets(templine, MAX_LEN*3+10, f);
	// printf("%s", templine);
	fgets(templine, MAX_LEN*3+10, f);
	// printf("%s", templine);				
	fgets(templine, MAX_LEN*3+10, f);
	// printf("%s", templine);
	fgets(templine, MAX_LEN*3+10, f);
	// printf("%s", templine);					
      }


      //iterate over questions in categories
      for (int y = 0; y < 4; y++){
	fscanf(f, "%[^:]:%[^:]:%[^:]:%d\n", &questions[y+x*4].category, &questions[y+x*4].question, &questions[y+x*4].answer, &questions[y+x*4].value);
	// printf("%d,%d Cat:%s Q:%s A:%s Val:%d \n",x,y,questions[y+x*4].category, questions[y+x*4].question, questions[y+x*4].answer, questions[y+x*4].value );
	// printf("%s\n",questions[y+x*4].category );
      }
    }	

    for (int y = 0; y < 3; y++){
      strncpy(categories[y], questions[y*4].category,MAX_LEN);
    }	
    /*printf("categories\n" );
      printf("%s\n", categories[0]);
      printf("%s\n", categories[1]);
      printf("%s\n", categories[2]);*/


    // initialize each question struct and assign it to the questions array
    for (int x = 0; x < sizeof(questions)/sizeof(question) ; x++){
      questions[x].answered = false;
    }

    // strncpy(questions[0].question, "test question", MAX_LEN);

    fclose(f);
  }
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
  // print categories and dollar values for each unanswered question in questions array
  printf("Remaining Categories:\n");
  for (int i = 0; i < 3; i++){                           //iterate through all the categories
    char curr_category[MAX_LEN];
    strcpy(curr_category,categories[i]);                 //store current category
    printf("%s: ", curr_category);                       //print the current category
    for (int j = 0; j < sizeof(questions)/sizeof(*questions); j++){
      question curr_struct = questions[j];               //store current question
      if(strcmp(curr_category,curr_struct.category) == 0){
	//belongs in the current category
	if (!curr_struct.answered){
	  //question has not been answered
	  printf(ANSI_COLOR_GREEN "%d " ANSI_COLOR_RESET, curr_struct.value );             //category is un-answered + in right cat
	}else{
	  printf(ANSI_COLOR_RED "XXX " ANSI_COLOR_RESET); 	                 //question has already been answered;
	}

      }
    }
    printf("\n");
  }
  printf("\n");
}

//checks to see if there are still atleast one available question that have not been answered
bool questions_left(void)
{
  for (int i = 0; i < 3; i++){                           //iterate through all the categories
    for (int j = 0; j < sizeof(questions)/sizeof(*questions); j++){
      if(!questions[j].answered){                       //check to see if the question is answered
	//question has not been answered
	return true;
      }
    }
  }
  //all the questions have been answered
  return false;
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
  for(int i = 0; i < sizeof(questions)/sizeof(*questions); i++)
    {
      //printf("%d, %s, %s, %d, ", i, questions[i].category, category, strcmp(questions[i].category,category));
      //printf("%d, %d, %d ", questions[i].value, value, value == questions[i].value);
      //printf(" | %s", questions[i].question);
      //printf("\n");
      if(strcmp(questions[i].category, category) == 0 && questions[i].value == value && questions[i].answered == 0)
	{
	  printf("In the category %s, For %d:",category,value);
	  printf("\n\n");
	  printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET,questions[i].question);
	  printf("\n\n");
	}
    }

  //puts("end of function");
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{	
  // loop through categories
  for(int i=0; i<3; i++){
    // find category of question
    if(strcmp(category, categories[i])==0){
      // loop through questions in category
      for(int j=0; j<4; j++){
	// check question of value if answer matches
	if((questions[(i)*4+j].value == value) && (strcmp(answer, questions[(i)*4+j].answer)==0)){
	  return true;
	}
      }
    }
  }

  // Look into string comparison functions
  return false;
}

//marks the category and value as completed
void mark_completed(char *category, int value)
{	
  // loop through categories
  for(int i=0; i<3; i++){
    // find category of question
    if(strcmp(category, categories[i])==0){
      // loop through questions in category
      for(int j=0; j<4; j++){
	// check question of value if answer matches
	if((questions[(i)*4+j].value == value)){
	  //update the question for the category as answered
	  questions[(i)*4+j].answered = true;
	  return;
	}
      }
    }
  }
}

// Returns true if the question has already been answered or not found
bool already_answered(char *category, int value)
{
  // lookup the question and see if it's already been marked as answered
  for (int j = 0; j < sizeof(questions)/sizeof(*questions); j++){
    question curr_struct = questions[j];               //store current question
    if (strcmp(category,curr_struct.category) == 0){
      if(value == curr_struct.value){
	//found the right question
	return curr_struct.answered;
      }
    } 
  }
  // printf("[already_answered]question was not found!\n");
  return true;
}

//marks all the questions as answered
void test_answer_all(void){
  // loop through categories
  for(int i=0; i<3; i++){
    // loop through questions in category
    for(int j=0; j<4; j++){
      questions[(i)*4+j].answered = true;
    }
  }  
}
