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
#include "players.h"

// Returns true if the player name matches one of the existing players
bool player_exists(player *players, int num_players, char *name)
{
	// loop through players
	for(int i=0; i<num_players; i++){
		// check for name match
		if(strcmp(players->name, name)==0){
			return true;
		}
	}

    return false;
}

// Updates the score for that player given their name
void update_score(player *players, int num_players, char *name, int score)
{
	// loop through players
    for(int i=0; i<num_players; i++){
    	// check for name match
		if(strcmp(players->name, name)==0){
			// add score to player's score
			players[i].score += score;
		}
	}
}