#ifndef NUMBERS_H
#define NUMBERS_H

#include <stdint.h>

#define DISPLAY_WIDTH 128   // the display has 128 columns
#define DISPLAY_HEIGHT 32   // each page has 8 rows ---> that's 32 rows in total
#define DISPLAY_PAGE 4      // the display has 4 pages

// display = a matrix for the pixel dimensions is 32 pixels in height (y) and 128 pixels in width (x)
uint8_t display[DISPLAY_HEIGHT][DISPLAY_WIDTH];
// oled_display = a matrix that can be interpreted by the hardware
uint8_t oled_display[DISPLAY_PAGE * DISPLAY_WIDTH];


// Modes
extern int multiplayer;
extern int single_player;
extern int highscore_mode;

// AI difficulty variables
extern float ai_speed;

extern int menu;
extern int game;
extern int modes;
extern int highscore;
extern int menuBrowse;
extern int modesBrowse;

// Variables that are needed for (quicksleeps/delays) in the start and end of every screen
extern int menuN;
extern int modesN;
extern int highscoreN;
extern int gameN;
extern int endGame;

// Highscore specific variables
extern int score;
extern int highscore_list[3];
// Highscore int to char array
extern char first[10];
extern char second[10];
extern char third[10];
extern char buffer1[sizeof(int) * 3 + 2];
extern char buffer2[sizeof(int) * 3 + 2];
extern char buffer3[sizeof(int) * 3 + 2];

extern char save_score[7];
extern char number_of_score[16];

// Padel and player variables
extern float padel_height;
extern float padel_width;
extern float padel_speed;
extern int LEDs;

extern float padel1_xPos;
extern float padel1_yPos;
extern int player1_scores;

extern float padel2_xPos;
extern float padel2_yPos;
extern int player2_scores;

// Ball variables
extern float size_of_ball;
extern float ball_x_speed;
extern float ball_y_speed;
extern float ball_xPos;
extern float ball_yPos;
extern float ball_max_speed;

extern float randomN;

#endif