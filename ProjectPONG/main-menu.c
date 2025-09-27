#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include "include/numbers.h"

/**
 * @brief Function to handle menu browsing and update the display accordingly.
 */
void menu_browsing() {
    // Display the main heading for the menu
    display_string(0, "  PONG!");

    // Switch based on the current menu browse position
    switch (menuBrowse) {
        case 0:
            // Display the options with "-" indicating the selected option
            display_string(1, "- Start");
            display_string(2, "  Choose mode");
            display_string(3, "  Highscore list");
            break;

        case 1:
            // Display the options with "-" indicating the selected option
            display_string(1, "  Start");
            display_string(2, "- Choose mode");
            display_string(3, "  Highscore list");
            break;

        case 2:
            // Display the options with "-" indicating the selected option
            display_string(1, "  Start");
            display_string(2, "  Choose mode");
            display_string(3, "- Highscore list");
            break;

        default:
            // Default case, no specific action
            break;
    }

    // Update the display with the changes
    display_update();
}

/**
 * @brief Function to handle menu selection logic.
 */
void menu_selection(void) {
    // Introduce a delay using quicksleep
    quicksleep(1 << 20); 

    // Check if button 1 is pressed
    if (getbtns() & 0x1) {
        switch (menuBrowse) {
            case 0:
                // Start the game
                menu = 0;
                menuBrowse = 0;
                gameN = 1;
                game = 1;
                LEDs = 0x000f;
                break;
            case 1:
                // Navigate to modes menu
                menu = 0;
                menuBrowse = 0;
                modes = 1;
                modesN = 1;
                break;
            case 2:
                // Navigate to highscore menu
                menu = 0;
                menuBrowse = 0;
                highscore = 1;
                highscoreN = 1;
                break;
            default:
                break;
        }
    } 
    // Check if button 2 is pressed and not at the last menu position
    else if ((getbtns() & 0x2) && menuBrowse != 2) {
        // Move to the next menu position
        menuBrowse++;
        menu_browsing();
    } 
    // Check if button 3 is pressed and not at the first menu position
    else if ((getbtns() & 0x4) && menuBrowse != 0) {
        // Move to the previous menu position
        menuBrowse--;
        menu_browsing();
    }
}

/**
 * @brief Function to handle highscores display.
 */
void highscores()
{
  // Introduce a delay using quicksleep
  quicksleep(1 << 20); 

  // Check if button 1 is pressed
  if (getbtns() & 0x1)
  {
    // Update game state to return to the main menu
    menu = 1;
    highscore = 0;
    menuN = 1;
  }
}

/**
 * @brief Function to handle modes browsing display.
 */
void modes_browsing() {
    // Display the main heading for modes
    display_string(0, "  Modes");

    // Switch based on the current mode browse position
    switch (modesBrowse) {
        case 0:
            // Display the options with "-" indicating the selected option
            display_string(1, "- Multiplayer");
            display_string(2, "  Single player");
            display_string(3, "  Beat the score");
            break;

        case 1:
            // Display the options with "-" indicating the selected option
            display_string(1, "  Multiplayer");
            display_string(2, "- Single player");
            display_string(3, "  Beat the score");
            break;

        case 2:
            // Display the options with "-" indicating the selected option
            display_string(1, "  Multiplayer");
            display_string(2, "  Single player");
            display_string(3, "- Beat the score");
            break;

        default:
            // Default case, no specific action
            break;
    }

    // Update the display with the changes
    display_update();
}

/**
 * @brief Function to handle modes selection based on button input.
 */
void modes_selection() {
    // Introduce a delay using quicksleep
    quicksleep(1 << 20); 

    // Check button states and update game state accordingly
    if (getbtns() & 0x1) { // Button 1 pressed
        switch (modesBrowse) {
            case 0:
                // Multiplayer mode selected
                menu = 1;
                modes = 0;
                modesBrowse = 0;
                multiplayer = 1;
                single_player = 0;
                highscore_mode = 0;
                menuN = 1;
                break;
            case 1:
                // Single player mode selected
                menu = 1;
                modes = 0;
                modesBrowse = 0;
                multiplayer = 0;
                single_player = 1;
                highscore_mode = 0;
                menuN = 1;
                break;
            case 2:
                // Highscore mode selected
                menu = 1;
                modes = 0;
                modesBrowse = 0;
                multiplayer = 0;
                single_player = 0;
                highscore_mode = 1;
                menuN = 1;
                break;
        }
    } else if ((getbtns() & 0x2) && modesBrowse != 2) { // Button 2 pressed and not at the last modes position
        // Move to the next modes position
        modesBrowse++;
        modes_browsing();
    } else if ((getbtns() & 0x4) && modesBrowse != 0) { // Button 3 pressed and not at the first modes position
        // Move to the previous modes position
        modesBrowse--;
        modes_browsing();
    }
}

/**
 * @brief Checks if the game is active and the SW1 button is pressed, then resets the game state and ends the game.
 */
void quit_game() {
    // Check if in game mode and SW1 is pressed
    if (game && getsw() & 0x1) {
        // Reset the game state
        reset_game();
        
        // End the game
        end_game();
    }
}

/**
 * @brief Adjusts the AI speed based on the position of the switches (SW2, SW3, SW4) in single-player mode.
 */
void ai_speed_difficulty() {
    // Check if in single-player mode
    if (single_player) {
        // Switch based on the position of the switches (SW2, SW3, SW4)
        switch (getsw()) {
            case 0x2:
                // Set AI speed to 0.65 and use default ball max speed
                ai_speed = 0.65;
                break;

            case 0x4:
                // Set AI speed to 0.85 and set ball max speed to 3.5
                ai_speed = 0.85;
                ball_max_speed = 3.5;
                break;

            case 0x8:
                // Set AI speed to 1.05 and set ball max speed to 4
                ai_speed = 1.05;
                ball_max_speed = 4;
                break;

            default:
                // Set default AI speed to 0.35
                ai_speed = 0.35;
                break;
        }
    }
}



