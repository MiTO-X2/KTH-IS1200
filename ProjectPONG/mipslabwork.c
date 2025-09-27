/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   Modified by Mostafa Faik and Stefan Neskovic 2024

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include "include/numbers.h"

int timeoutcount = 0;

/**
 * 
 * @brief Interrupt Service Routine (ISR) for handling timeout interrupts.
 * 
 * This function is called when the interrupt flag bit for interrupt source 0x100 is set.
 * It increments the timeout count variable, clears the interrupt flag, and resets the timeout count
 * to 0 when it reaches 10.
 */
void user_isr(void)
{
  // Check if the interrupt flag bit for interrupt source 0x100 is set
  if (IFS(0) & 0x100)
  {
    // Increment the timeout count variable
    timeoutcount++;

    // Clear the interrupt flag bit for interrupt source 0x100
    IFSCLR(0) = 0x100;

    // Check if the timeout count has reached 10
    if (timeoutcount == 10)
    { 
      // Reset the timeout count to 0 when it reaches 10
      timeoutcount = 0;
    }
  }
}

/**
 * 
 * @brief Lab-specific initialization function.
 * 
 * This function is responsible for initializing the specific hardware configuration for the lab.
 * It sets the lower 8 bits of the TRISE register to 0 (output mode) for controlling LEDs,
 * sets bits 5 through 11 of the TRISD register to 1 (input mode) for BTN 2-4 and SW 1-4,
 * and sets bit 1 of the TRISF register to 1 (input mode) for BTN 1.
 * Additionally, it initializes the PORTE register to 0 to turn off LEDs.
 */
void labinit(void)
{
  // Set the lower 8 bits of the TRISE register to 0 (output mode) for LEDs
  TRISECLR = 0xff;  // Set as output (LEDs)

  // Set bits 5 through 11 of the TRISD register to 1 (input mode) for BTN 2-4 and SW 1-4
  TRISDSET = 0xfe0; // Set as input (BTN 2-4, SW 1-4)

  // Set bit 1 of the TRISF register to 1 (input mode) for BTN 1
  TRISFSET = 0x2;   // Set as input (BTN 1)

  // Initialize the PORTE register to 0 (turn off LEDs)
  PORTE = 0x0;      // LEDs
}

/**
 * @brief Control function to update the state of LEDs.
 * 
 * This function sets the value of the PORTE register to the value stored in the variable LEDs,
 * controlling the state of LEDs based on the variable's value.
 */
void led_control()
{
  // Set the value of PORTE register to the value stored in the variable LEDs
  PORTE = LEDs;
}

/**
 * @brief Main function to handle different states of the game and menu.
 * 
 * This function checks the current state of the game and menu and performs corresponding actions.
 * It includes handling in-game logic, menu selection, modes selection, and high score display.
 */
void labwork()
{
  // Introduce a delay of 2^15 cycles (quicksleep is  a function for a short delay)
  quicksleep(1 << 10); // 15

  // Check if the game state is active
  if (game)
  {
    // If in-game, handle the game logic
    handleGame();
  }
  // Check if the menu state is active
  else if (menu)
  {
    // Handle menu selection logic
    menu_selection();

    // Check if menuN flag is set
    if (menuN)
    {
      // Configure PORTE and display menu options
      PORTE = 0x0;
      display_string(0, "  PONG!");
      display_string(1, "- Start");
      display_string(2, "  Choose mode");
      display_string(3, "  Highscore list");
      display_update();

      // Reset menuN flag to avoid repetitive display updates
      menuN = 0;
    }
  }
  // Check if the modes state is active
  else if (modes)
  {
    // Handle modes selection logic
    modes_selection();

    // Check if modesN flag is set
    if (modesN)
    {
      // Display mode options
      display_string(0, "  Modes");
      display_string(1, "- Multiplayer");
      display_string(2, "  Single player");
      display_string(3, "  Beat the score");
      display_update();

      // Reset modesN flag to avoid repetitive display updates
      modesN = 0;
    }
  }
  // Check if the highscore state is active
  else if (highscore)
  {
    // Display high scores
    highscores();

    // Check if highscoreN flag is set
    if (highscoreN)
    {
      // Display high score information
      display_string(0, first);  // Convert elements to string!
      display_string(1, second);
      display_string(2, third);
      display_string(3, "- Back to menu");
      display_update();

      // Reset highscoreN flag to avoid repetitive display updates
      highscoreN = 0;
    }
  }
}

