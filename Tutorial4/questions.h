/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#ifndef QUESTIONS_H_
#define QUESTIONS_H_

#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 256

// List of 3 categories as array of strings
static char categories[3][MAX_LEN] = {"nothing", "nothing", "nothing"};

// Questions struct for each question
typedef struct {
    char category[MAX_LEN];
    char question[MAX_LEN];
    char answer[MAX_LEN];
    int value;
    bool answered;
} question;

// An array of 12 questions (4 for each category), initialized in initialize_game
// this may need to be a pointer if you want it set dynamically
question questions[12];

// Initializes the array of questions for the game
extern void initialize_game(int round);

// Displays each of the remaining categories and question dollar values that have not been answered
extern void display_categories(void);

// Displays the question for the category and dollar value
extern void display_question(char *category, int value);

extern void display_answer(char *categorty, int value);

// Returns true if the answer is correct for the question for that category and dollar value
extern bool valid_answer(char *category, int value, char *answer);

// Returns true if the question has already been answered
extern bool already_answered(char *category, int value);

//marks the category and value as completed
void mark_completed(char *category, int value);

//checks to see if there are still atleast one available question that have not been answered
bool questions_left(void);

int get_column_width(int console_width, int num_columns);

int get_row_height(int console_height, int num_rows);

void print_top_line(int line_length, int column_width);

void print_line(int line_length, char *color);

//marks all the questions as answered
void test_answer_all(void);
#endif /* QUESTIONS_H_ */
