/* header file for main.cpp file */
/* contains function definitions */

#include "microcontroller.h"

void displayApplicationPrompt();
char inputOption();
void switchOption(char, mcontroller::Microcontroller**);
void displayConnectPrompt();
void optionErrorHandler();
void optionHelpHandler();
void optionConnectHandler(mcontroller::Microcontroller**);
void optionResetHandler(mcontroller::Microcontroller**);
