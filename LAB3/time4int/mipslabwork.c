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

int mytime = 0x5957;  // Initialize mytime with a hexadecimal value 0x5957

char textstring[] = "text, more text, and even more text!";

int timeoutcount = 0; // Initialize timeout counter

int prime = 1234567;  // Initialize a variable with a prime number

/* Interrupt Service Routine */
void user_isr( void ){

  // Check the timeout event flag for Timer 2
  if (IFS(0) & 0x0100) {
    timeoutcount++; 

    // If the timeoutcount reaches 10, execute the following
    if (timeoutcount == 10){ 
    time2string( textstring, mytime );  // Convert mytime to string
    display_string( 3, textstring );    // Display the string on the screen
    display_update();                   // Update the display
    tick( &mytime );                    // Increment the time variable

    // reset the timeout counter
    timeoutcount = 0;
    }

    // Reset the flag
    IFSCLR(0) = 0x100;  // Clear the Timer 2 interrupt flag, bit 8
  }

  // Check the interrupt flag for external interrupt 2 (SW2)
    if (IFS(0) & 0x0800) {
        mytime += 2;  // Increment mytime by 3 to simulate 3 seconds
        IFSCLR(0) = 0x0800;  // Clear the INT2 interrupt flag
    }
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int *trisE = (volatile int*) 0xbf886100; // Address of TRISE
  //volatile int *portE = (volatile int*) 0xbf886110; // Address of PORTE

  *trisE &= ~0xff; // Set bits 7-0 of TRISE as outputs 
  //*portE = 0x0;  // Set the initial value of PORTE to 0

  // Set bits 11 through 5 of Port D as inputs
  TRISD = TRISD | 0x0fe0;

  // Initialize Timer 2 for timeouts every 100 ms
  T2CON = 0x0;                  // Clear Timer 2 control register
  //T2CONSET = 0x70;            // Set prescaler to 1:256 (bits 6-4)
  TMR2 = 0x0;                   // Clear Timer 2 counter
  PR2 = 31250; // ((80000000 / 256) / 10) Set period register for 100 ms (80 MHz clock)

  //T2CONSET = 0x8000;          // Start Timer 2 with prescaler 1:1 (bit 15 set)
  T2CON = 0x8070;
  // Enable Timer 2 interrupts
  IECSET(0) = 0x100;          // IEC(0) = IEC(0) | 0x100;

  // Enable INT2 interrupts
  IECSET(0) = 0x0800;

  // Clear Timer 2 interrupt flag
  IFSCLR(0) = 0x100;

  // Clear INT2 interrupt flag
  IFSCLR(0) = 0x0800;

  // Set Timer 2 interrupt priority
  IPCSET(2) = 0x1f;           // IPC(2) = (IPC(2) & 0xFFFFFF00) | 0x1C;

  // Set INT2 interrupt priority
  IPCSET(2) = 0x1f00; 

  // Enable global interrupts
  enable_interrupt();

  // Configure INT2 using external interrupt control registers
  //INTCONSET = 0x1000;  // Set bit 12 to enable INT2

  return;
}

/* This function is called repetitively from the main program */
void labwork( void ){
  prime = nextprime( prime );             // Update prime to the next prime number     
  display_string( 0, itoaconv( prime ));  // Display the updated prime number on the screen
  display_update();                       // Update the display
}
