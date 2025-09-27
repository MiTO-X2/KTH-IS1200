# Project Pong - Chipkit Uno32

A pong game made with the Chipkit Uno32 microcontroller together with the Chipkit basic I/O shield as part of the KTH course Computer Hardware Engineering IS1200. We worked with the SPI (Serial Peripheral Interface) to communicate with the processor.

## Features

* Single player: You can play against an AI, and controll the speed (difficulty) of the AI 
with the switches (SWT 2-4).

* Multiplayer: You can play against a "foe" or your friend.

* Beat the score: This is a mode where you can set and/or beat the top 3 highscores that can be found in the highscore list. This mode works where you basically play against an AI, and every time you hit the ball the score increase with one. You lose when the AI scores against you and lit all the LEDs, that is you basically have 4 lives, because the game already starts with 4 lights ON (LEDs 1-4) and the remaining 4 (LEDs 5-8) are OFF.

## Controls 

* You control player 1 (player on the left side of the display) with BTN 3-4
* The second player (player on the right side of the display) is controlled with BTN 1-2
* You can scroll and navigate the menu with BTN 2-3 and you can select the current selection with BTN1
SWT 1 is used to quit the game (when a game is on)

### Install mcb32tools environment

Follow the steps for your OS specified [here](https://github.com/is1200-example-projects/mcb32tools/releases/).

### Flash to chipkit (uno32/uc32)

#### Windows

1. Open MSYS terminal.
1. Find the correct serial device. Run `ls /dev` both with and without the chipkit connected to see what serial device pops up. In this case it's `ttyS2`.
1. Enter MCB32 environment: `. /opt/mcb32tools/environment`.
1. Navigate to the correct path: `cd <path>/IS1500_project`.
1. Run: `make && make install TTYDEV=/dev/ttyS2`.

#### MacOS

1. Open MCB32Tools.app.
1. Find the correct serial device. Run `ls /dev` both with and without the chipkit connected to see what serial device pops up. In this case it's `tty.usbserial-A503WFTK`.
1. Navigate to the correct path: `cd <path>/IS1500_project`.
1. Run: `make && make install TTYDEV=/dev/tty.usbserial-A503WFTK`.
