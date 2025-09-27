#include <stdint.h>
#include <stdbool.h>
#include <pic32mx.h>
#include "mipslab.h"
#include "include/numbers.h"

/**
 * @brief Update the game state by adjusting the position of the ball based on its speed.
 * Check if the ball has hit the roof or floor, and bounce it accordingly.
 */
void update_game() {
    // Update the position of the ball based on its speed
    ball_xPos += ball_x_speed;
    ball_yPos += ball_y_speed;

    // Check if the ball has hit the roof or floor, and bounce it accordingly
    ball_y_speed = (ball_yPos < 0 || ball_yPos > (DISPLAY_HEIGHT - size_of_ball - 1)) ? -ball_y_speed : ball_y_speed;
}

/**
 * @brief Update the scoring system by shifting the lights on PORTE based on the player's score.
 *
 * @param score Player's score.
 */
void scoring_system(int score) {
    // Set PORTE to 0x8 (binary 1000) - initializing some lights
    PORTE = 0x8;

    // Define the shift direction based on the player's score
    int dir = (score == 0) ? 1 : 0;

    int count;
    // Loop for a certain number of iterations (48 in this case)
    for (count = 0; count < 48; ++count) {
        // Adjust PORTE based on the shift_direction
        if (dir) {
            PORTE >>= 1; // Shift to the right
        } else {
            PORTE <<= 1; // Shift to the left
        }

        // Switch based on the current value of PORTE
        switch (PORTE) {
            case 0x10: // Binary 00010000
            case 0x1:  // Binary 00000001
                dir = !dir;
                break;
        }

        // Introduce a short delay
        quicksleep(1 << 10);
    }
}

/**
 * @brief Update labels and buffers to display the top three high scores.
 *
 * This function constructs labels and buffers for the first, second, and third
 * high scores, incorporating them into the corresponding strings. The updated
 * labels and buffers can be used for display purposes.
 */
void updateLabelsAndBuffers() {
    // Update labels and buffers based on the new high scores

    // Label and buffer for the first high score
    strcpy(first, " 1. "); // Initialize " 1. " label
    snprintf(buffer1, sizeof(int) * 3 + 2, "%d", highscore_list[0]); // Convert and store the first high score to buffer1
    strcat(first, buffer1); // Concatenate label and buffer

    // Label and buffer for the second high score
    strcpy(second, " 2. "); // Initialize " 2. " label
    snprintf(buffer2, sizeof(int) * 3 + 2, "%d", highscore_list[1]); // Convert and store the second high score to buffer2
    strcat(second, buffer2); // Concatenate label and buffer

    // Label and buffer for the third high score
    strcpy(third, " 3. "); // Initialize " 3. " label
    snprintf(buffer3, sizeof(int) * 3 + 2, "%d", highscore_list[2]); // Convert and store the third high score to buffer3
    strcat(third, buffer3); // Concatenate label and buffer
}


/**
 * @brief Update the high score list based on the current score.
 */
void updateHighScoreList() {
    int i, j;

    // Check if the current score is higher than any of the high scores
    for (i = 0; i < 3; ++i) {
        // Check if the current score is higher than the i-th high score
        if (highscore_list[i] < score) {
            // Move the old high scores down the list
            for (j = 2; j > i; --j) {
                highscore_list[j] = highscore_list[j - 1];
            }

            // Update the i-th high score with the current score
            highscore_list[i] = score;

            // Update the labels and buffers
            updateLabelsAndBuffers();

            // Reset the current score to 0
            score = 0;

            // Break out of the loop since we've updated the high score
            break;
        }
    }
}

/**
 * @brief End the game and display the winner or high score.
 */
void end_game(void) {
    // Clear specific lines on the display
    display_string(0, "");
    display_string(2, "");
    display_string(3, "");

    switch (LEDs) {
        case 0:
            if (single_player)
                display_string(1, "    You won!");
            else if (multiplayer) 
                display_string(1, " Player 1 won!");
            scoring_system(0); // Update the scoring system for Player 1 winning
            break;
        case 0xff:
            if (single_player)
                display_string(1, "    AI won!");
            else if (multiplayer)
                display_string(1, " Player 2 won!");
            else if (highscore_mode) {
                display_string(1, "   Your score:");
                display_string(2, number_of_score);
            }
            scoring_system(1); // Update the scoring system for Player 2 or AI winning
            break;
        default:
            break;
    }
    
    // If in highscore mode, update the high score list
    if (highscore_mode) {
        updateHighScoreList();
    }

    // Reset various game-related variables to their initial values
    game = 0;
    menu = 1;
    menuN = 1;
    gameN = 1;

    // Update the display after handling the game end
    display_update();
}

/**
 * @brief Handle the crossing of the left boundary by the ball.
 *
 * This function shifts the LEDs to the left and sets the rightmost bit to 1
 * and increments Player 2's score.
 */
void handleLeftBoundaryCrossing() {
    // Shift the LEDs to the left and set the rightmost bit to 1
    LEDs = ((LEDs << 1) | 0x1);
    // Increment Player 2's score
    player2_scores++;
}

/**
 * @brief Handle the crossing of the right boundary by the ball.
 *
 * This function shifts the LEDs to the right and increments Player 1's score.
 */
void handleRightBoundaryCrossing() {
    // Shift the LEDs to the right
    LEDs >>= 1;
    // Increment Player 1's score
    player1_scores++;
}


/**
 * @brief Update the scores, check boundaries, and handle game state accordingly.
 */
void scoring() {
    // Check if the ball has crossed the left or right boundary
    if (ball_xPos < 0) {
        // Ball crossed the left boundary
        handleLeftBoundaryCrossing();
    } 
    else if (ball_xPos > (DISPLAY_WIDTH - size_of_ball)) {
        // Ball crossed the right boundary
        handleRightBoundaryCrossing();
    }

    // Reset the game state
    reset_game();

    // Check if the game has ended based on the current LED configuration
    switch (LEDs) {
        case 0x0:
        case 0xFF:
            end_game();
            break;

        default:
            break;
    }
}

/**
 * @brief Clear the content of each line on the display by setting them to spaces.
 */
void clear_string_display()
{
  // Clear the content of each line on the display by setting them to spaces
  display_string(0, "              "); // Clear line 0
  display_string(1, "              "); // Clear line 1
  display_string(2, "              "); // Clear line 2
  display_string(3, "              "); // Clear line 3
}

/**
 * @brief Handle collision with paddle 1.
 *        Reverse the direction of the ball in the x-axis and adjust speed based on collision conditions.
 */
void handleCollisionPadel1() {
    // Reverse the direction of the ball in the x-axis
    ball_x_speed *= -1;

    // Increase the ball speed in the x-axis if it's below the maximum speed
    if (ball_x_speed < ball_max_speed) {
        ball_x_speed += 0.49;
    }

    // Check the vertical position of the ball relative to the paddle
    if ((ball_yPos + size_of_ball / 2) < padel1_yPos + padel_height / 2 && ball_y_speed > -1.5) {
        // Adjust the ball's vertical speed based on the conditions
        ball_y_speed -= (ball_x_speed < -2) ? 0.54 : 0.34;
    } else if ((ball_yPos + size_of_ball / 2) > padel1_yPos + 2 * padel_height / 2 && ball_y_speed < 1.5) {
        // Adjust the ball's vertical speed based on the conditions
        ball_y_speed += (ball_x_speed < -2) ? 0.54 : 0.34;
    }

    // Increment the score if in highscore mode
    if (highscore_mode) {
        score++;
    }
}

/**
 * @brief Handle collision with paddle 2.
 *        Reverse the direction of the ball in the x-axis and adjust speed based on collision conditions.
 */
void handleCollisionPadel2() {
    // Reverse the direction of the ball in the x-axis
    ball_x_speed *= -1;

    // Decrease the ball speed in the x-axis if it's above the negative maximum speed
    if (ball_x_speed > -ball_max_speed) {
        ball_x_speed -= 0.49;
    }

    // Check the vertical position of the ball relative to the paddle 
    if ((ball_yPos + size_of_ball / 2) < padel2_yPos + padel_height / 2 && ball_y_speed > -1.5) {
        // Adjust the ball's vertical speed based on the conditions
        ball_y_speed -= (ball_x_speed > 2) ? 0.54 : 0.34;
    } else if ((ball_yPos + size_of_ball / 2) > padel2_yPos + 2 * padel_height / 2 && ball_y_speed < 1.5) {
        // Adjust the ball's vertical speed based on the conditions
        ball_y_speed += (ball_x_speed > 2) ? 0.54 : 0.34;
    }
}

/**
 * @brief Handle ball goal condition.
 *        Check if the ball has crossed the left or right boundary, introduce a delay, and call scoring function.
 */
void handleGoalCondition() {
    // Check if the ball has crossed the left or right boundary
    if ((ball_xPos + size_of_ball) < 0 || ball_xPos > DISPLAY_WIDTH) {
        // Introduce a delay using quicksleep
        quicksleep(1 << 15);
        // Call the scoring function to update scores and reset the game
        scoring();
    }
}

/**
 * @brief Check if the ball has collided with paddle 1.
 *
 * This function returns true if the ball is moving towards the left (negative x_speed)
 * and its position overlaps with paddle 1.
 *
 * @return True if there is a collision with paddle 1, false otherwise.
 */
bool isCollisionWithPadel1() {
    return (ball_x_speed < 0) &&
           (ball_xPos >= padel1_xPos) && (ball_xPos <= (padel1_xPos + padel_width)) &&
           ((ball_yPos + size_of_ball) > padel1_yPos) && (ball_yPos < (padel1_yPos + padel_height));
}

/**
 * @brief Check if the ball has collided with paddle 2.
 *
 * This function returns true if the ball is moving towards the right (positive x_speed)
 * and its position overlaps with paddle 2.
 *
 * @return True if there is a collision with paddle 2, false otherwise.
 */
bool isCollisionWithPadel2() {
    return (ball_x_speed > 0) &&
           ((ball_xPos + size_of_ball) >= padel2_xPos) && ((ball_xPos + size_of_ball) <= padel2_xPos + padel_width) &&
           ((ball_yPos + size_of_ball) > padel2_yPos) && (ball_yPos < (padel2_yPos + padel_height));
}


/**
 * @brief Main function to handle paddle collisions.
 *        Checks collision with paddle 1 and paddle 2, and handles goal condition.
 */
void padel_collision() {
    // Check collision with Padel 1
    if (isCollisionWithPadel1()) {
        handleCollisionPadel1();
    }
    // Check collision with Padel 2
    else if (isCollisionWithPadel2()) {
        handleCollisionPadel2();
    }

    // Check if the ball has reached the goal
    handleGoalCondition();
}

/**
 * @brief Update the position of a paddle based on button inputs.
 *
 * This function adjusts the vertical position of a paddle based on button inputs.
 * If the down button is pressed and the paddle is within the lower bounds of the display,
 * it moves the paddle down. If the up button is pressed and the paddle is within the upper
 * bounds of the display, it moves the paddle up.
 *
 * @param yPos Pointer to the current vertical position of the paddle.
 * @param isDownButtonPressed Boolean indicating whether the down button is pressed.
 * @param isUpButtonPressed Boolean indicating whether the up button is pressed.
 */
void updatePadelPosition(float* yPos, bool isDownButtonPressed, bool isUpButtonPressed) {
    // Move the paddle down if the down button is pressed and within bounds
    if (isDownButtonPressed && (*yPos < (DISPLAY_HEIGHT - padel_height - 1))) {
        *yPos += padel_speed;
    }
    // Move the paddle up if the up button is pressed and within bounds
    else if (isUpButtonPressed && (*yPos > 0)) {
        *yPos -= padel_speed;
    }
}

/**
 * @brief Function to handle paddle movement based on button inputs.
 *        Controls the movement of Padel 1 in single-player mode and Padel 2 in multiplayer mode.
 */
void movement() {
    // Update Padel 1 position based on single player control
    updatePadelPosition(&padel1_yPos, (getbtns() & 0x4), (getbtns() & 0x8));

    // Update Padel 2 position based on multiplayer control
    if (multiplayer) {
        updatePadelPosition(&padel2_yPos, (getbtns() & 0x1), (getbtns() & 0x2));
    }
}