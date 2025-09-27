/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957; // Initialize a variable mytime with the value 0x5957 (hexadecimal)

char textstring[] = "text, more text, and even more text!";

int timeoutcount = 0; // Initialize a timeout counter

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int *trisE = (volatile int*) 0xbf886100; // Address of TRISE
  //volatile int *portE = (volatile int*) 0xbf886110; // Address of PORTE

  *trisE &= ~0xff; // Configure bits 7-0 of TRISE as outputs
  //*portE = 0x0;   // Set PORTE to 0 (initialization)

  // Set bits 11 through 5 of Port D as inputs
  TRISD = TRISD | 0x0fe0;

  // Initialize Timer 2 for timeouts every 100 ms
  T2CON = 0;                  // Clear Timer 2 control register
  T2CONSET = 0x70;            // Use the set-register for t2con to set prescaling to 1:256 (70 = 0111 0000)
                              // Bit 6-4 are the TCKPS that controls prescaling. 2^3 = 8 configurations.
  TMR2 = 0;                   // Clear Timer 2 counter
  PR2 = ((80000000 / 256) / 10); // Set period register for 100 ms (assuming an 80 MHz clock) 31250

  T2CONSET = 0x8000;          // Start Timer 2 with prescaler 1:1 (bit 15 set)

  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  // Read the status of buttons BTN4, BTN3, and BTN2
  int buttons = getbtns(); // Read button states 
  int switches = getsw();  // Read switche states

  // If BTN4 is pressed, update the first digit of mytime
  if (buttons & 0x04) {
    mytime = mytime & 0x0fff;           // Clear the first digit
    mytime = (switches << 12) | mytime; // Update with new switch value
  }

  // If BTN3 is pressed, update the second digit of mytime
  if (buttons & 0x02) {
    mytime = mytime & 0xf0ff;           // Clear the second digit
    mytime = (switches << 8) | mytime;  // Update with new switch value
  }

  // If BTN2 is pressed, update the third digit of mytime
  if (buttons & 0x01) {
    mytime = mytime & 0xff0f;           // Clear the third digit
    mytime = (switches << 4) | mytime;  // Update with new switch value
  }

  // Check the timeout event flag for Timer 2
  if (IFS(0) & 0x100) {
    timeoutcount++;   // Increment timeout counter

    // Reset the flag
    IFSCLR(0) = 0x100;  // Clear the Timer 2 interrupt flag
  }  

  if (timeoutcount == 10){ 
  //delay( 1000 );                    // Potentially add a delay (commented out)
  time2string( textstring, mytime );  // Convert mytime to string
  display_string( 3, textstring );    // Display the string on the screen
  display_update();                   // Update the display
  tick( &mytime );                    // Increment the time variable
  display_image(96, icon);            // Display an image at position (96, icon)

  // reset the timeout counter
  timeoutcount = 0;
  }

  // Increment the binary value on 8 green LEDs
  volatile int *portE = (volatile int *) 0xbf886110;  // Port E address for LEDs

  // Read the current value from PORTE
  int currentVal = *portE;

  // Increment the value (up to 255, assuming 8 LEDs)
  currentVal = (currentVal + 1) & 0xFF;

  // Write the updated value back to PORTE
  *portE = currentVal;

  // *portE += 0x00000001; // Increment the value with every tick
                           // Alternative way to increment the value (commented out)
}