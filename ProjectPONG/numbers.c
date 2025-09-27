#include "include/numbers.h"

// Modes
int multiplayer = 1;
int single_player;
int highscore_mode;

// AI difficulty variables
float ai_speed = 0.35;

int menu = 1;
int game;
int modes;
int highscore;
int menuBrowse;
int modesBrowse;

// Variables that are needed for (quicksleeps/delays) in the start and end of every screen
int menuN = 1;
int gameN = 1;
int modesN;
int highscoreN;
int endGame;

// Highscore specific variables
int score;
int highscore_list[3] = {0, 0, 0};
// Highscore int to char array
char first[10] = " 1. ";
char second[10] = " 2. ";
char third[10] = " 3. ";
char buffer1[sizeof(int) * 3 + 2];
char buffer2[sizeof(int) * 3 + 2];
char buffer3[sizeof(int) * 3 + 2];

char number_of_score[16];
char save_score[7] = "      ";

// Ball variables
float size_of_ball = 3;
float ball_x_speed = 1;
float ball_y_speed;
float ball_xPos = DISPLAY_WIDTH / 2 - 2;
float ball_yPos = 16;
float ball_max_speed = 3;

// Padel and player variables
float padel_height = 7;
float padel_width = 4;
float padel_speed = 1;
int LEDs = 0x000f;

float padel1_xPos;
float padel2_xPos = DISPLAY_WIDTH - 5;

float padel1_yPos = DISPLAY_HEIGHT / 2 - 5;
float padel2_yPos = DISPLAY_HEIGHT / 2 - 5;

int player1_scores;
int player2_scores;

float randomN;

void *stdout = (void *) 0; // this is used to prevent an error when running make on msys2

