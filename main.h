/* header file for main.cpp file */
/* contains function definitions */

#include "microcontroller.h"

void displayApplicationPrompt();
void displayConnectPrompt();
void displayLocationPrompt();

char inputOption();
void switchOption(char, mcontroller::Microcontroller**);

void optionErrorHandler();
void optionHelpHandler();
void optionConnectHandler(mcontroller::Microcontroller**);
void optionResetHandler(mcontroller::Microcontroller**);
void optionLookAtMemoryHandler(mcontroller::Microcontroller**);
