#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

// Function to read the status of switches SW4 through SW1
int getsw(){
    // Read the status of switches SW4 through SW1 from bits 11 through 8 of Port D
    return ((PORTD >> 8) & 0x0f);
}

// Function to read the status of push-buttons BTN4, BTN3, and BTN2
int getbtns(void){
    // Read the status of push-buttons BTN4, BTN3, and BTN2
    // from bits 7, 6, and 5 of Port D and bit 1 of Port F
    return (((PORTD >> 5) & 0x07) << 1 | ((PORTF >> 1) & 0X1));
}


