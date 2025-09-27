#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include "include/numbers.h"

/**
 * @brief Draw pixels within a specified rectangle on the display.
 * 
 * This function sets the pixels within the specified rectangle defined by 
 * (int x_position, int y_position, int x_length, int y_length) to 1.
 * 
 * @param x_position X-coordinate of the top-left corner of the rectangle.
 * @param y_position Y-coordinate of the top-left corner of the rectangle.
 * @param x_length Width of the rectangle.
 * @param y_length Height of the rectangle.
 */
void draw_pixel(int x_position, int y_position, int x_length, int y_length) 
{
    int row, column;

    // Iterate through each row in the display (display has dimensions 32x128)
    for (row = 0; row < DISPLAY_HEIGHT; row++) {
        // Iterate through each column in the display
        for (column = 0; column < DISPLAY_WIDTH; column++) {
            // Check if the current pixel is within the specified rectangle defined by (x_position, y_position, x_length, y_length)
            if (row >= y_position && row <= (y_position + y_length) && column >= x_position && column <= (x_position + x_length)) {
                // Set the pixel at the current position to 1 (turn it on)
                display[row][column] = 1;
            }
        }
    }
}

/**
 * @brief Convert the 2D pixel array to a format suitable for the OLED display.
 * 
 * This function converts the 2D pixel array ('display') into a 1D array ('oled_display') 
 * that is compatible with the OLED display. It processes each column and row, updating 
 * the 'oled_display' accordingly.
 */
void array_to_image() 
{
    int page, column, row, c;

    uint8_t power_of_two = 1;
    uint8_t number_of_oled = 0;

    // Loop through each "page" (vertical section) of the display
    for (page = 0; page < DISPLAY_PAGE; page++) {
        // Loop through each column in the display
        for (column = 0; column < DISPLAY_WIDTH; column++) {
            // Reset variables for each new column
            power_of_two = 1;
            number_of_oled = 0;

            // Loop through each "row" (8 rows make up a page)
            for (row = 0; row < 8; row++) {
                // Check if the pixel in the 2D array is turned on
                if (display[8 * page + row][column]) {
                    // Update the number_of_oled based on the turned-on pixel
                    number_of_oled |= power_of_two;
                }
                // Shift power_of_two to the left for the next bit position
                power_of_two <<= 1;
            }

            // Check conditions for handling highscore_mode and textbuffer
            if ((highscore_mode && page == 0) && (column % 8 == 0)) {
                c = textbuffer[page][column / 8];
            }

            if ((highscore_mode && page == 0) && !(c & 0x80)) {
                number_of_oled |= font[c * 8 + column % 8];
            }

            // Store the calculated number_of_oled in the 1D array
            oled_display[column + page * DISPLAY_WIDTH] = number_of_oled;
        }
    }
}

/**
 * @brief Clears a 2D array by setting all its elements to zero.
 * 
 * This function iterates through each element of the 2D array and sets its value to zero,
 * effectively clearing the content of the array.
 * 
 * @param array The 2D array to be cleared.
 * @param rows The number of rows in the array.
 * @param cols The number of columns in the array.
 */
void clear2DArray(uint8_t array[][DISPLAY_WIDTH], int rows, int cols) {
    // Iterate through each element of the 2D array
    int row, column;
    for (row = 0; row < rows; ++row) {
        for (column = 0; column < cols; ++column) {
            // Set the value of the current element to zero
            array[row][column] = 0;
        }
    }
}

/**
 * @brief Clears the display by resetting the content of the 2D array and OLED display buffer.
 * 
 * This function clears both the 2D array 'display' and the OLED display buffer 'oled_display'.
 * The 2D array represents the logical structure of the display, and the OLED display buffer
 * holds the pixel data sent to the actual display. After calling this function, the display
 * will be blank.
 * 
 * It sets all elements in both arrays to 0, preparing them for a fresh display.
 * 
 * @note The dimensions of the 'display' array are defined by 'DISPLAY_HEIGHT' and 'DISPLAY_WIDTH'.
 *       The 'oled_display' array has a size of 'DISPLAY_PAGE * DISPLAY_WIDTH' to accommodate
 *       the whole display content.
 */
void clear_display() {
    // Clear the logical structure of the display (2D array)
    clear2DArray(display, DISPLAY_HEIGHT, DISPLAY_WIDTH);

    // Clear the pixel data in the OLED display buffer
    int column;
    for (column = 0; column < DISPLAY_PAGE * DISPLAY_WIDTH; ++column) {
        oled_display[column] = 0;
    }
}


/**
 * @brief Reset the positions of paddles and the ball.
 */
void reset_positions() {
    // Reset the position of paddle 1
    padel1_xPos = 0;
    padel1_yPos = DISPLAY_HEIGHT / 2 - padel_height / 2;

    // Reset the position of paddle 2
    padel2_xPos = DISPLAY_WIDTH - padel_width - 1;
    padel2_yPos = DISPLAY_HEIGHT / 2 - padel_height / 2;

    // Reset the position of the ball
    ball_xPos = DISPLAY_WIDTH / 2 - size_of_ball / 2;
    ball_yPos = 16;
}

/**
 * @brief Reset the game state to initial conditions.
 * 
 * This function resets the positions of paddles and the ball, clears the display arrays, 
 * sets pixel arrays for paddles and the ball, and updates the OLED display.
 */
void reset_game() {
    // reset the positions of the paddles and the ball
    reset_positions();

    // Clear display and set pixel arrays for paddles and ball
    clear_display();
    draw_pixel(padel1_xPos, padel1_yPos, padel_width, padel_height);
    draw_pixel(padel2_xPos, padel2_yPos, padel_width, padel_height);
    draw_pixel(ball_xPos, ball_yPos, size_of_ball, size_of_ball);
    
    // Translate and display the pixel arrays
    array_to_image();
    display_image(0, oled_display);

    // Set the gameN flag to indicate that the game is active
    gameN = 1;
}

/**
 * @brief Handle the start of the game.
 * 
 * This function introduces a delay, resets the game state, generates a random number 
 * for the initial y-speed of the ball, and determines a random sign for the initial x-speed of the ball.
 */
void handleGameStart() 
{
  // Introduce a delay of 2^23 cycles (quicksleep is a function for a short delay)
  quicksleep(1 << 23); 

  // Reset the game state
  gameN = 0;

  // Generate a random number for the initial y-speed of the ball
  random_number();
  ball_y_speed = randomN;

  // Determine a random sign for the initial x-speed of the ball
  ball_x_speed = random_sign();
}

/**
 * @brief Handle the highscore mode.
 * 
 * Adjusts the position of paddle 2 based on the position of the ball. Stores and saves the score 
 * with a string and displays it on the OLED screen.
 */
void handle_highscore_mode()
{
  // Adjust the position of paddle 2 based on the position of the ball
  if (ball_yPos < padel_height / 2)
  {
    padel2_yPos = 0;
  }
  else if ((ball_yPos + size_of_ball) > (31 - padel_height / 2))
  {
    padel2_yPos = 31 - padel_height;
  }
  else
  {
    padel2_yPos = ball_yPos + size_of_ball / 2 - padel_height / 2;
  }

  // Store the score with a string and display it
  strcpy(number_of_score, save_score);
  strcat(number_of_score, itoaconv(score));
  display_string(0, number_of_score);
}

/**
 * @brief Handle the single-player mode logic for controlling paddle 2.
 * 
 * Checks the position of the ball and adjusts the paddle 2 position accordingly.
 * If the ball is on the right side, paddle 2 follows the ball vertically.
 * If the ball is on the left side, paddle 2 maintains a center position.
 */
void handle_single_player_mode()
{
  // Check if the ball is on the right side of the display
  if (ball_xPos > 127 / 2)
  {
    // If ball is below the center of paddle 2 and within display bounds, move paddle down
    if ((padel2_yPos + padel_height / 2) < (ball_yPos + size_of_ball / 2) && padel2_yPos < (31 - padel_height))
    {
      padel2_yPos += ai_speed;
    }
    // If ball is above the center of paddle 2 and within display bounds, move paddle up
    else if ((padel2_yPos + padel_height / 2) > (ball_yPos + size_of_ball / 2) && padel2_yPos > 0)
    {
      padel2_yPos -= ai_speed;
    }
  }
  else
  {
    // If ball is below the center of paddle 2, move paddle down
    if ((padel2_yPos + padel_height / 2) < 14.79)
    {
      padel2_yPos += 0.10;
    }
    // If ball is above the center of paddle 2, move paddle up
    else if ((padel2_yPos + padel_height / 2) > 15.19)
    {
      padel2_yPos -= 0.10;
    }
  }
}

/**
 * @brief Handle the main game logic.
 * 
 * Clears string display, sets pixels for paddles and ball, handles game mode-specific logic,
 * translates pixel arrays to a 1D array, and displays the image on the OLED display.
 * Performs various game-related operations such as movement, collision detection, and LED control.
 * Checks for game termination conditions and handles game start logic when necessary.
 */
void handleGame()
{
  // Clear the string display (assuming this clears some text-related display state)
  clear_string_display();

  // Set pixels for paddles
  draw_pixel(padel1_xPos, padel1_yPos, padel_width, padel_height);
  draw_pixel(padel2_xPos, padel2_yPos, padel_width, padel_height);

  // Depending on the game mode, handle specific logic
  if (highscore_mode)
  {
    handle_highscore_mode();
  }
  else if (single_player)
  {
    // Adjust AI speed based on difficulty and handle single-player mode logic
    ai_speed_difficulty();
    handle_single_player_mode();
  }

  // Set pixels for the ball and translate the pixel arrays to a 1D array
  draw_pixel(ball_xPos, ball_yPos, size_of_ball, size_of_ball);
  array_to_image();

  // Display the translated image on the OLED display if the game is not over
  if (!endGame)
  {
    display_image(0, oled_display);
  }

  // Perform various game-related operations
  movement();
  padel_collision();
  update_game();
  led_control();
  quit_game();

  // If the game state indicates that the game needs to start, handle game start logic
  if (gameN)
  {
    handleGameStart();
  }

  // Clear the display (resetting it for the next frame or update)
  clear_display();
}
