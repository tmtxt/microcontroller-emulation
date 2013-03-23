/* header file for main.cpp file */
/* contains function definitions */

#include "microcontroller.h"

void displayApplicationPrompt();
char inputOption();
void switchOption(char, microcontroller::Microcontroller**);
void displayConnectPrompt();
void optionErrorHandler();
void optionHelpHandler();
void optionConnectHandler(microcontroller::Microcontroller**);
