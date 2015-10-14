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

#define ANSI_BGCOLOR_BLUE     "\x1b[44m"
#define ANSI_BGCOLOR_BLACK    "\x1b[40m"
#define ANSI_BGCOLOR_GREY     "\x1b[47m"
#define ANSI_BGCOLOR_RESET    ""

// Initializes the array of questions for the game
void initialize_game(int round)
{

  // initialize each question struct and assign it to the questions array

  srand(time(NULL));
  int currselect;
  int numCategories;
  int fileCategories;
  int numQuestions;
  FILE *f;

  //set round params
  if (round == 1){
    f = fopen("bank.txt", "r");
    numCategories = 3;
    fileCategories = 5;
    numQuestions = 4;
  }else if (round == 2){
    f = fopen("djqs.txt", "r");
    numCategories = 3;
    fileCategories = 6;
    numQuestions = 4;
  }else{
  	f = fopen("fj.txt","r");
  	numCategories = 1;
  	fileCategories = 2;
  	numQuestions = 1;
  }

	int catselector[numCategories];

  if (f != NULL){
    for (int x = 0; x < numCategories; x++){
      bool repeat;
     	do
     	{
		  repeat = true;
		  currselect = rand() % fileCategories;// 5 is number of categories in the file
		  //check if the random number exists in catselector
		  for (int y = 0; y < numCategories; y++){
		    if (currselect == catselector[y]){
		      repeat = false;
		    }
		  }
		}while (repeat == false);
      catselector[x] = currselect;
    }

    // //iterate over entries in catselector
    for (int x = 0; x < numCategories; x++){
      // printf("%d \n",catselector[x]); 	
      //get to the line we want
      //reset pointer to start
      fseek(f, 0, SEEK_SET);
      char templine[MAX_LEN];

      for (int z = 0; z < catselector[x];z++){
      	for (int i = 0; i < numQuestions; i++)
      	{
			fgets(templine, MAX_LEN*3+10, f);
      	}				
      }

      //iterate over questions in categories
      for (int y = 0; y < numQuestions; y++){
		fscanf(f, "%[^:]:%[^:]:%[^:]:%d\n", &questions[y+x*numQuestions].category, &questions[y+x*4].question, &questions[y+x*4].answer, &questions[y+x*4].value);
		// printf("%d,%d Cat:%s Q:%s A:%s Val:%d \n",x,y,questions[y+x*4].category, questions[y+x*4].question, questions[y+x*4].answer, questions[y+x*4].value );
		// printf("%s\n",questions[y+x*4].category );
      }
    }	

    for (int y = 0; y < numCategories; y++){
      strncpy(categories[y], questions[y*numQuestions].category,MAX_LEN);
    }	
    // printf("categories\n" );
    // printf("%s\n", categories[0]);
    // printf("%s\n", categories[1]);
    // printf("%s\n", categories[2]);


    // initialize each question struct and assign it to the questions array
    for (int x = 0; x < sizeof(questions)/sizeof(question) ; x++){
      questions[x].answered = false;
    }

    /*=====================
    debug code so I don't go insane testing end of game things
    =====================*/
    // for (int x = 0; x < (int)(sizeof(questions)/sizeof(question)) ; x++){
    //   questions[x].answered = true;
    // }

    // questions[0].answered = false; 	
    // questions[1].answered = false;

	/*=====================
    debug code so I don't go insane testing end of game things
    =====================*/

    // strncpy(questions[0].question, "test question", MAX_LEN);

    fclose(f);
  }
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
  // print categories and dollar values for each unanswered question in questions array
  
//  system("clear");

//  print_line(72,ANSI_BGCOLOR_BLACK);

  // OLD FUNCTION HERE:
  printf("\t\t\tRemaining Categories:\n");
  for (int i = 0; i < 3; i++){                           //iterate through all the categories
    char curr_category[MAX_LEN];
    strcpy(curr_category,categories[i]);                 //store current category
    printf("%30s: ", curr_category);                       //print the current category
    for (int j = 0; j < (int)(sizeof(questions)/sizeof(*questions)); j++){
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
    for (int j = 0; j < (int)(sizeof(questions)/sizeof(*questions)); j++){
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
  for(int i = 0; i < (int)(sizeof(questions)/sizeof(*questions)); i++)
    {
      // printf("%d, %s, %s, %d, \n", i, questions[i].category, category, strcmp(questions[i].category,category));
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

void display_answer(char *category, int value){

   for(int i = 0; i < (int)(sizeof(questions)/sizeof(*questions)); i++)
    {
      if(strcmp(questions[i].category, category) == 0 && questions[i].value == value)
      {
        printf("%s", questions[i].answer);
      }
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
	// convert answer to all lowercase
	for(char *currentChar=answer; *currentChar!='\0';currentChar++){
		*currentChar = tolower(*currentChar);
	}

  // loop through categories
  for(int i=0; i<3; i++){
    // find category of question
    if(strcmp(category, categories[i])==0){
      // loop through questions in category
      for(int j=0; j<4; j++){
      	// convert correct answer to lowercase
      	for(char *currentChar=questions[(i)*4+j].answer; *currentChar!='\0';currentChar++){
			*currentChar = tolower(*currentChar);
		}

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
	if(questions[(i)*4+j].value == value){
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
  for (int j = 0; j < (int)(sizeof(questions)/sizeof(*questions)); j++){
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

int get_column_width(int console_width, int num_columns){

  return (console_width - num_columns - 1)/num_columns;
}

int get_row_height(int console_height, int num_rows){

  return (console_height - num_rows - 1)/num_rows;
}

void print_top_line(int line_length, int column_width){

  printf(ANSI_BGCOLOR_BLACK /*"┌"*/ " ");
  for(int i = 1; i < line_length; i++){
    if(i % column_width == 0){
      printf(/*"┬"*/" ");
    }
    else{
      printf(/*"─"*/" ");
    }
  }
  printf(/*"┐"*/" " ANSI_COLOR_RESET);

  printf("\n");
}

void print_line(int line_length, char *color){

  printf(ANSI_BGCOLOR_GREY "  ");

  printf("%s", color);

  for(int i = 0; i < line_length; i++)
  {
    printf(" ");
  }  

  printf(ANSI_BGCOLOR_GREY "  " ANSI_COLOR_RESET "\n");

}
