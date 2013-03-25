/* header file for main.cpp file */
/* contains function definitions */

#include "microcontroller.h"

// CUSTOM DATATYPE DECLARATIONS

// My defined function type for those functions that handle option
typedef void optionHandler(mcontroller::Microcontroller**);

// FUNCTION DEFINITIONS

// Functions to display prompt
void displayApplicationPrompt();
void displayConnectPrompt();
void displayLocationPrompt();

// Utility function
char inputOption();
void switchOption(char, mcontroller::Microcontroller**);
void executeOptionIfConnected(mcontroller::Microcontroller**, optionHandler*);

// Functions for handling option
void optionErrorHandler();
void optionHelpHandler();
void optionConnectHandler(mcontroller::Microcontroller**);
void optionResetHandler(mcontroller::Microcontroller**);
void optionLookAtMemoryHandler(mcontroller::Microcontroller**);
void optionModifyMemoryHandler(mcontroller::Microcontroller**);
void optionDisplayAllMemoryHandler(mcontroller::Microcontroller**);
void optionExecuteHandler(mcontroller::Microcontroller**);
void optionExecuteFromSpecificLocationHandler(mcontroller::Microcontroller**);
void optionDisplayStatusHandler(mcontroller::Microcontroller**);
