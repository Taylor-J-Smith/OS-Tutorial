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

// void testfunction(player *players){
//     players[0].score = 10;
//     players[1].score = 40;
//     players[2].score = 1;
//     players[3].score = 80;

//     show_results(players);
// }

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
  for (int x = 0; x < NUM_PLAYERS; x++){
    printf("%d:%s - Score: %d\n",x, rankedplayers[x].name,rankedplayers[x].score);
  }
}

// Clears the buffer since there is issues when using scanf and fgets
void clearBuffer();

// Used to print an array of strings given the size of the array
void printStringArray(char **array,int size);

//Used to promp user to enter player names, store those names into a player array, and display a welcome message.
void storePlayers(char buffer[],char *user_output[], int num_players, player players[]);

int main(int argc, char *argv[])
{

  // An array of 4 players, may need to be a pointer if you want it set dynamically
  player players[NUM_PLAYERS];
    
  //Input buffer and and commands
  char buffer[BUFFER_LEN] = { 0 };

  //Array of Strings used to store the user Input
  char *user_output[BUFFER_LEN];
  
  //
  system("clear");
  // Display the game introduction 
  printf("Welcome to KATJ Jeopardy!! Hit ENTER to Begin!");
  
  // Perform an infinite loop getting command input from users until game ends
  while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
      //Promp for player names, store them in players array, and display a welcome message
      storePlayers(buffer,user_output, NUM_PLAYERS, players);

      //Initialize game and display the available categories
      initialize_game(1);
      display_categories();
      
      //loop Until the user enters a valid player name
      while(1){
	printf("Enter player to go first:");           //User Message
	fgets(buffer, BUFFER_LEN, stdin);              //read in the user input
	buffer[strlen(buffer)-1] = 0;                  //remove the newline from last char

	if(player_exists(players,NUM_PLAYERS,buffer)){ //check if player exists
	  break;                                       //A valid player name was entered
	}else{
	  printf("Invalid Name \"%s\"! ",buffer);       //Invalid player name, keep looping
	}
      }
      printf("Hi %s\n",buffer);                        //Found name! Welcome message

      //continue here
      
      printf("----------END OF GAME----------\n");     //game Prompt
    }
  return EXIT_SUCCESS;
}

void tokenize(char *input, char **tokens){
  
  const char delim[2] = " ";       //set delimiter
  char *token;                     //placeholder for token
  int i = 0;                       //keep track of array index
   
  token = strtok(input, delim);    //get the first token

  while( token != NULL ){          //walk through other tokens */
    tokens[i] = token;             //store current token in array      
    token = strtok(NULL, delim);   //read next token
    i++;
  }
}

void clearBuffer(){
  //reference @ http://stackoverflow.com/
  int c;
  while ((c = getchar()) != EOF && c != '\n') ;  
}

void printStringArray(char **array,int size){
  //Prints an array of Strings(*char) given param size
  for (int i = 0; i < size; i++){
    printf("%s\n",array[i]);
  }
}

void storePlayers(char buffer[],char *user_output[], int num_players, player *players){
  //@param buffer       - A string used to store user Input
  //@param user_output  - An array of strings used to store the tokenized strings
  //@param num_players  - The number of players currently in the game
  //@param players      - An array of player structs
  printf("Please enter the 4 players' names (delimited by space):\n");
  // initialize each of the players in the array
  printf(">> ");                             //input prompt
  fgets(buffer, BUFFER_LEN, stdin);          //read in the user input
  buffer[strlen(buffer)-1] = 0;              //remove the newline from last char
  tokenize(buffer,user_output);              //store all the strings delimited by a space into an array

  //store players into the players array
  for(int i = 0; i < num_players; i++){      //iterate through the # of players
    strcpy(players[i].name,user_output[i]);  //copy from array of tokens into the person name
    players[i].score = 0;                    //init all scores to 0
  }

  system("clear");
  //Print a friendly welcome message once all the players have been set
  printf("Welcome! ");                        //Welcome message
  for (int i = 0; i < num_players; i++){     //iterate through all the players
    printf("%s ", players[i].name);          //print the player's name
  }
  printf("\n");                     
}




























