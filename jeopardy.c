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
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players){
    //Sort
    player rankedplayers[NUM_PLAYERS] = {players[0],players[1],players[2],players[3]};

    for (int x = 0; x < 3; x++){
        for (int y = x; y < 4; y++){
            if (rankedplayers[x].score < rankedplayers[y].score){
                player tempplayer = rankedplayers[x];
                rankedplayers[x] = rankedplayers[y];
                rankedplayers[y] = tempplayer;
            }
        }
    }

    //Display
    for (int x = 0; x < 3; x++){
        printf("%d:%s - Score: %d\n",x, rankedplayers[x].name,rankedplayers[x].score);
    }
}

// Clears the buffer since there is issues when using scanf and fgets
void clearBuffer();


int main(int argc, char *argv[])
{

    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
  // Input buffer and and commands
  char buffer[BUFFER_LEN] = { 0 };

  // Display the game introduction and prompt for players names
  printf("Welcome to KATJ Jeopardy!!\n");
  printf("Please enter the 4 players' names (delimited by space):\n");
  // initialize each of the players in the array
  printf(">> ");
  scanf("%s %s %s %s", players[0].name,players[1].name,players[2].name,players[3].name);  //set the names 
  printf("Welcome ");
  for (int i = 0; i < 4; i++){
    printf("%s ", players[i].name);
    players[i].score = 0;      //init all the players' scores to 0
  }
  printf("\n");

    // Perform an infinite loop getting command input from users until game ends
  //    initialize_game();
  //display_categories();
  clearBuffer();
  printf(">> ");//game Promp
  while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {

      // Call functions from the questions and players source files

      // Execute the game until all questions are answered
       
      // Display the final results and exit
      
      printf(">> ");//game Promp
    }
  return EXIT_SUCCESS;
}

void tokenize(char *input, char **tokens){
  
  const char delim[2] = ",";
  char *token;
  int i = 0;
   
  /* get the first token */
  token = strtok(input, delim);
   
  /* walk through other tokens */
  while( token != NULL ) 
    {
      tokens[i] = token;//store current token in array
      
      token = strtok(NULL, delim);//read next token
      i++;
    }
  /*
  // retrieve tokens 1-3 and place in tokens array
  tokens[0] = strtok(input, " ");
  tokens[1] = strtok(NULL, " ");
  tokens[2] = strtok(NULL, " ");*/
}

void clearBuffer(){
  int c;
  while ((c = getchar()) != EOF && c != '\n') ;  
}
