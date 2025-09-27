#include <pic32mx.h>
#include "include/numbers.h"

/**
 * 
 * @brief Generates a random sign (-1 or 1) based on the lower digit of TMR2.
 *
 * @return -1 if the lower digit of TMR2 is less than 5, otherwise 1.
 */
int random_sign()
{
    // Check if the lower digit of TMR2 is less than 5
    // If true, return -1; otherwise, return 1
    return (TMR2 % 10 < 5)? -1 : 1;
}

/**
 * 
 * @brief Generates a random number in the range [0.5, 0.9] with a random sign.
 */
void random_number()
{
    // Generate a random number in the range [0.0, 0.4]
    // by taking the remainder when TMR2 is divided by 5
    // and dividing the result by 10.0 and Shift the 
    // range to [0.5, 0.9] by adding 0.5
    randomN = (TMR2 % 5) / 10.0 + 0.5;

    // Determine the sign of the random number using random_sign()
    // and multiply it with the previously obtained value
    randomN *= random_sign();
}

