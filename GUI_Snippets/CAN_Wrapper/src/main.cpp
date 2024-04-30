// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 Michael Bauer <mike.bauer@fau.de>

//============================================================================
// Name        : main.cpp
// Author      : Michael Bauer
// Version     : 0.1
// Copyright   : MIT
// Description : Main to test interaction with CAN Wrapper
//============================================================================

#if defined(_Windows) || defined(_MSC_VER) || defined (__GNUC__)
 #define  STRICT
 #include <windows.h>
#endif

#include <stdio.h>
#include "can_wrapper.hpp"

//============================================================================
// global variables
//============================================================================

int g_silent = 0;

//============================================================================
// console help
//============================================================================

void help(void){

	printf("\n----------------------------------------------------------\n");
	printf("- Keyboard commands:                                     -\n");
	printf("- 't'      Transmit a message                            -\n");
	printf("- '+'      Select transmit Id  (up)                      -\n");
	printf("- '-'      Select transmit Id  (down)                    -\n");
	printf("- 'v'      Toggle logging to screen                      -\n");
	printf("- 'h'      Help                                          -\n");
	printf("- 'ESC'    Exit                                          -\n");
	printf("----------------------------------------------------------\n\n");
}


//============================================================================
// main
//============================================================================

int main() {

	int stop = 0;
	int c;
	unsigned int txID = 0x01;

	// Print help at startup
	help();

	CAN_Wrapper can = CAN_Wrapper(500000);

	while (stop == 0){

		unsigned long n;
		INPUT_RECORD ir;

		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &ir, 1, &n);

		if ((n == 1) && (ir.EventType == KEY_EVENT) && (ir.Event.KeyEvent.bKeyDown)) {
			c = ir.Event.KeyEvent.uChar.AsciiChar;
			switch (c) {
				case 't': // transmit a message
					can.txCAN(new byte[0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8], 8);
					break;

				case '+': // Increase id
					txID++;
					can.setID(txID);
					break;

				case '-': // Decrease id
					txID--;
					can.setID(txID);
					break;

				case 'v': // toggle logging mode
					g_silent = !g_silent;
					if (g_silent)
						printf(">> Logging off\n");
					else
						printf(">> Logging on\n");
					break;

				case 'h': // show help
					help();
					break;

				case 27: // end application
					stop=1;
					break;

				default:
					break;
			}
		}
	}

	return 0;
}
