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
#include <sys/types.h>
#include <sys/ioctl.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

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

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens, char *delim);

// void testfunction(player *players){
//     players[0].score = 10;
//     players[1].score = 40;
//     players[2].score = 1;
//     players[3].score = 80;

//     show_results(players);
// }

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players);

// Clears the buffer since there is issues when using scanf and fgets
void clearBuffer();

// Used to print an array of strings given the size of the array
void printStringArray(char **array,int size);

//Used to promp user to enter player names, store those names into a player array, and display a welcome message.
void storePlayers(char buffer[],char *user_output[], int num_players, player players[]);

//picks a question
void pickQuestion(char *user_output[], char buffer[], char currPlayer[]);

//trim Removes any post/prepended whitespace from a string(char[])
void trim(char padded_string[]);

//Ensures that the user_input is of "what is/who is" format
bool validJeopardyFormat(char *user_input, char *delim);

//Prints the player with the current
void print_winner(player *players, int num_players);

int main(int argc, char *argv[])
{

  // Source: http://www.linuxquestions.org/questions/programming-9/scripting-question-the-width-of-the-terminal-window-81570/
    struct winsize ws;

    ioctl(1, TIOCGWINSZ, &ws);

  // An array of 4 players, may need to be a pointer if you want it set dynamically
  player players[NUM_PLAYERS];
    
  //Input buffer and and commands
  char buffer[BUFFER_LEN] = { 0 };

  //Array of Strings used to store the user Input
  char *user_output[BUFFER_LEN];

  //current player
  char currPlayer[BUFFER_LEN];
  
  //current category and value
  int currVal;
  char *currCat[BUFFER_LEN];

  //variables for locking players
  int *lockedPlayers[NUM_PLAYERS];
  bool areAnyLocked;

  //clear out the console at the start of the game
  system("clear");
 
  // Perform an infinite loop getting command input from users until game ends
  //while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
  do
  {
    // Display the game introduction 
    //printf("Columns: %d\tRows: %d\n", ws.ws_col, ws.ws_row);
    //printf("Column Width:  %d\tRow Height: %d\n", get_column_width(ws.ws_col,4), get_row_height(ws.ws_row,5));
    printf(ANSI_COLOR_GREEN "Welcome to JATJ Jeopardy!! Hit" ANSI_COLOR_RESET
	  ANSI_COLOR_RED" ENTER " ANSI_COLOR_RESET
	  ANSI_COLOR_GREEN "to Begin!" ANSI_COLOR_RESET);
    fgets(buffer, BUFFER_LEN, stdin);
      
    //Promp for player names, store them in players array, and display a welcome message
    storePlayers(buffer,user_output, NUM_PLAYERS, players);

    //Initialize game and display the available categories
    initialize_game(1);

    //Loops while there are questions unanswered
	  //loop Until the user enters a valid player name
    while(1){
      printf("Enter player to go:");                     //User Message
	    fgets(buffer, BUFFER_LEN, stdin);                  //read in the user input
	    buffer[strlen(buffer)-1] = 0;                      //remove the newline from last char
	    trim(buffer);                                      //Trim any whitespace around the name
	    strcpy(currPlayer, buffer);                        //store the current player
	    if(player_exists(players,NUM_PLAYERS,currPlayer)){ //check if player exists
	      break;                                           //A valid player name was entered
	    }else{
	      system("clear");
	      printf("Current Players: " ANSI_COLOR_CYAN);    //Welcome message
	      
        for (int i = 0; i < NUM_PLAYERS; i++){          //iterate through all the players
	        printf("%s ", players[i].name);               //print the player's name
	      }
	      printf(ANSI_COLOR_RESET"\n");                     
	      printf("Invalid Name \"%s\"! ",buffer);         //Invalid player name, keep looping
	    }
	  }
  
    while(questions_left()){
      
    	system("clear");
    	show_results(players);
    	pickQuestion(user_output, buffer, currPlayer);              
    	do{
    	  currVal = atoi(user_output[1]); //not sure why this is needed but it is.
    	  strcpy(currCat,user_output[0]);
    	  if(already_answered(currCat,currVal)){
    	    system("clear");
    	    printf(ANSI_COLOR_RED "Invalid Question, pick again.\n \n \n"ANSI_COLOR_RESET);

    	    show_results(players);
    	    pickQuestion(user_output,buffer,currPlayer);
    	  }else{
    	    break;
    	  }
    	}while(true);

      system("clear");
    	//display question
    	currVal = atoi(user_output[1]);
    	strcpy(currCat,user_output[0]);
    	display_question(currCat,currVal);

      //nobody is locked out at the start
      for (int i = 0; i < NUM_PLAYERS; i++){
        lockedPlayers[i] = 0;
      }

    	//ask for answer:
    	do{
        do{
          areAnyLocked = false;
          //display locked players if there are any
          for (int i = 0; i < NUM_PLAYERS; i++){
            if (lockedPlayers[i] == 1){
              areAnyLocked = true;
            }
          }

          if(areAnyLocked){
            printf("\nLocked Players:");

            for (int i = 0; i < NUM_PLAYERS; i++){
              if (lockedPlayers[i] == 1){
                printf("%s ",players[i].name);
              }
            }
            printf("\n\n");
          }

          //prompt user for player to answer:
          printf("Enter player that buzzed:");
          fgets(buffer, BUFFER_LEN, stdin);                      //read in the user input
          buffer[strlen(buffer)-1] = 0;                          //remove the newline
          trim(buffer);                                          //remove any pre/post whitespace

          //check if the player is locked out 
          bool lockedOut = true;
          for (int i = 0; i < NUM_PLAYERS; i++){
            if(strcmp(players[i].name, buffer)==0){
              if(lockedPlayers[i] == 1){
                printf("That player is locked!\n");
              }else{
                //player is not locked out, they are now curr player
                strcpy(currPlayer, players[i].name);
                lockedOut = false;
              }
            }
          }

          if (lockedOut == false){
            break;
          }
        }while(true);

    	  //promp user for answer
    	  printf(ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET " enter your response:", currPlayer);
    	  fgets(buffer, BUFFER_LEN, stdin);                      //read in the user input
    	  buffer[strlen(buffer)-1] = 0;                          //remove the nelinw
    	  trim(buffer);                                          //remove any pre/post whitespace

    	  //must check if the answer begins with "what is" or "who is"
    	  //Check if the user 1. used the right format(what is/who is) AND 2. has the right answer
    	  //***validJeopardyFormat MUST be called first since it modifies buffer (remove the what if)
    	  if (validJeopardyFormat(buffer," ") && valid_answer(currCat,currVal,buffer)){
    	    system("clear");
    	    printf(ANSI_COLOR_RED "Correct! " ANSI_COLOR_RESET
    		   ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET
    		   " you get "
    		   ANSI_COLOR_GREEN "%d" ANSI_COLOR_RESET
    		   " points!\n", currPlayer,currVal);
    	    update_score(players, NUM_PLAYERS, currPlayer, currVal);     //update the player's score
    	    mark_completed(currCat,currVal);                             //mark category/val complete
    	    show_results(players);                                       //display current standings
    	    display_categories();
    	    break;
    	  } else{
    	    // system("clear");
    	    printf(ANSI_COLOR_RED "Incorrect!\n" ANSI_COLOR_RESET);
    	    // mark_completed(currCat,currVal);                             //mark cat/val completed
    	    // show_results(players);                                       //display current standings
    	    // display_categories();                                        //display remaining cat
    	    //even is person gets it wrong, mark the category as completed
    	    // break;

          for (int i = 0; i < NUM_PLAYERS; i++){
            if(strcmp(players[i].name, currPlayer)==0){
              lockedPlayers[i] = 1;
            }
          }
    	  }
    	}while(true);
    }

    system("clear");
    printf("The final Standings are:\n");
    show_results(players);
    print_winner(players, NUM_PLAYERS);
    printf("----------END OF GAME----------\n");     //game Prompt
    printf("Type " ANSI_COLOR_RED "exit" ANSI_COLOR_RESET " to stop playing"
     " or press " ANSI_COLOR_GREEN "ENTER" ANSI_COLOR_RESET " to play again!\n");
    fgets(buffer, BUFFER_LEN, stdin);          //read in the user input
    buffer[strlen(buffer)-1] = 0;              //remove the newline from last char
  }while(strcmp(buffer,"exit") == 0);
  return EXIT_SUCCESS;
}

void tokenize(char *input, char **tokens, char *delim){
  
  // const char delim[2] = " ";       //set delimiter
  char *token;                     //placeholder for token
  int i = 0;                       //keep track of array index
   
  token = strtok(input, delim);    //get the first token

  while( token != NULL ){          //walk through other tokens */
    trim(token);
    tokens[i] = token;             //store current token in array      
    token = strtok(NULL, delim);   //read next token
    i++;
  }
  tokens[i] = NULL;                //to indicate where the tokens end
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
  tokenize(buffer,user_output," ");              //store all the strings delimited by a space into an array

  //store players into the players array
  for(int i = 0; i < num_players; i++){      //iterate through the # of players
    strcpy(players[i].name,user_output[i]);  //copy from array of tokens into the person name
    players[i].score = 0;                    //init all scores to 0
  }

  system("clear");
  //Print a friendly welcome message once all the players have been set
  printf("Welcome! "ANSI_COLOR_CYAN);        //Welcome message
  for (int i = 0; i < num_players; i++){     //iterate through all the players
    printf("%s ", players[i].name);          //print the player's name
  }
  printf(ANSI_COLOR_RESET"\n");                     
}

void pickQuestion(char *user_output[], char buffer[], char currPlayer[]){
  display_categories();
  printf("Hi " ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET ", you have control of the board\n",currPlayer);                        //Found name! Welcome message
  printf("Please enter the category name, followed by a comma, and then the dollar amount (no spaces) \n");
  //get the player to select a question
  printf(">> ");
  fgets(buffer, BUFFER_LEN, stdin);              //read in the user input
  buffer[strlen(buffer)-1] = 0;                  //remove the newline from last char
  //All categories are 2 words long
  tokenize(buffer, user_output, ",");
  // user_output[0]; //category
  // user_output[1]; //value
}

void trim(char padded_string[]){
  //Takes a string and removes any existing whitespace before or after the string
  //@param padded_string A string with whitespace before and/or after it
  char trimmed_string[strlen(padded_string)];  //The original string with the 
  int j = 0;                                   //keeps track of the new trimmed string
  int a = 0;                                   //start of trimmed string
  int z = 0;                                   //end of trimmed string
  
  //find the index for the first nonwhitespace character
  for (int i = 0; i < strlen(padded_string); i++){
    if (padded_string[i] == ' '){
      a++;                                    //only increment a when a whitespace is found
    }else{
      break;                                  //exit for loop once we reach the actual string
    }    
  }
  //a no contains the index for where the string actually begins

  //Find the index for the last ninwhitespace character
  for (int i = strlen(padded_string) - 1; i >=0; i--){
    if (padded_string[i] == ' '){
      z++;                                  //only increment z when a whitespace is found
    }else{
      break;                                //exit the for loop once the actual string is found
    }
  }
  //z no contains the number of whitespaces from right to left
  //get the index of where the actual string ends  
  z = strlen(padded_string) - z;

  //Now that we have the indicies of where the actual string begins and ends we can copy it
  //copy only the string without whitespace
  //i is used to iterate through original string, j is used as index for the trimmed string
  for (int i = a; i < z; i++){             
    trimmed_string[j] = padded_string[i];
    j++;  
  }

  trimmed_string[j] = 0;                  //indicate where the string should end
  strcpy(padded_string,trimmed_string);   //copy the actual string into the trimmed one
}
bool validJeopardyFormat(char *user_input, char *delim){
  char bankAnswer[BUFFER_LEN] = {0};
  char *tokens[BUFFER_LEN];

  tokenize(user_input, tokens,delim);              //split the user input into tokens

  //Must check if user prepended answer with "who is" OR "what is"
  if (((strcmp(tokens[0],"what") == 0) || (strcmp(tokens[0],"who") == 0)) &&
      (strcmp(tokens[1],"is") ==0)){
    //TRUE Users included "who is" OR "what is"
    for (int i = 2; i < BUFFER_LEN; i++){
      if (tokens[i] == NULL){                     //check if end of tokens has been reached
	break;                                    //if so, break from Loop to stop appending
      }
      strcat(bankAnswer,tokens[i]);               //append answer to the bankAnswer
      strcat(bankAnswer,delim);                   //append the delimter to the string
    }
  }else{
    //User did not prepend their answer
    return false;
  }
  
  trim(bankAnswer);                               //trim the final bankAnswer
  strcpy(user_input,bankAnswer);                  //copy the answer into user_input
  return true;
}

void show_results(player *players){
  //Sort
  player rankedplayers[NUM_PLAYERS] = {players[0],players[1],players[2],players[3]};

  printf("Current Standings:\n");
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
    printf("%d:%s - Score: %d\n",x+1, rankedplayers[x].name,rankedplayers[x].score);
  }
  printf("\n");
}

//Prints the player with the current
void print_winner(player *players, int num_players){
  player winners[num_players];                //array of winners (possible 4 way tie)
  int num_winners = 1;                           //keeps track of how many ties (winners)
  winners[0]= players[0];                     //set first player as winner
  for (int i = 1; i < num_players; i++){      //iterate through the players
    if (players[i].score > winners[0].score){ //if current player has higher score
      if (num_winners > 1){
	//if there was an existing tie
	winners[0] = players[i];
	num_winners = 1;
      }else{
	//no ties, can just add player as new winner
	winners[0] = players[i];
      }
    }else if(players[i].score == winners[0].score){
      //there is a tie
      winners[num_winners] = players[i];
      num_winners++;
    }
  }

  printf("THE WINNERS FOR THIS MATCH: ");
  //Print the winners
  for(int i = 0; i < num_winners; i++){
    printf(ANSI_COLOR_RED "%s " ANSI_COLOR_RESET, winners[i].name);
  }
  printf("\nWITH A SCORE OF: " ANSI_COLOR_GREEN " %d " ANSI_COLOR_RESET "!!!\n",winners[0].score);  
}
