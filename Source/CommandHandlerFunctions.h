/******************************************************************************
filename    CommandHandlerFunctions.h
author      Toby Klauder
DP email    justin.chambers@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file declares functions that handle the various user commands
which are already implemented in the library

******************************************************************************/
#pragma once

typedef struct CommandData CommandData;
typedef struct GameState GameState;
typedef struct WorldData WorldData;


/* Handles the "help" command, whic outputs a list of available verbs */
void HandleHelpCommand(CommandData* command, GameState *gameState, WorldData *worldData);

/* Handles the "quit" command, which immediately exits the game */
void HandleQuitCommand(CommandData* command, GameState *gameState, WorldData *worldData);

/* Handles the "go" command, which moves the user to another room */
void HandleGoCommand(CommandData* command, GameState *gameState, WorldData *worldData);

/* Handles the "drop" user command, which drops an item in inventory to the current room.*/
void HandleDropCommand(CommandData* command, GameState *gameState, WorldData *worldData);

/* Handles the "inventory" command, which outputs a list of the items in the player's inventory */
void HandleInventoryCommand(CommandData* command, GameState *gameState, WorldData *worldData);

/* Handles the "look" command, which outputs a description of an item or the current room */
void HandleLookCommand(CommandData* command, GameState *gameState, WorldData *worldData);

/* Handles the "take" command, which removes an item from the current room and adds it to the user's inventory */
void HandleTakeCommand(CommandData* command, GameState *gameState, WorldData *worldData);

/* Handles the "use" command, which calls an item-specific function on a given item */
void HandleUseCommand(CommandData* command, GameState *gameState, WorldData *worldData);

void HandleSpeakCommand(CommandData* command, GameState* gameState, WorldData* worldData); 
void HandlePokeCommand(CommandData* command, GameState* gameState, WorldData* worldData); 
void HandleYellCommand(CommandData* command, GameState* gameState, WorldData* worldData); 
/* TODO ADVANCED: create aditional commands (add handler function declarations here)
   this may require the creation of additional .c files to implement the command functions */

   /******************************************************************************
   Copyrights, Logos, and EULAs

   All DigiPen projects must include a DigiPen copyright notice, the DigiPen logo, and the DigiPen EULA (if they have an installer). DigiPen holds the copyright to all your classwork done while enrolled at DigiPen.

   The DigiPen copyright notice has exactly the following form (except with the current year, of course):

   All content © 2020 DigiPen (USA) Corporation, all rights reserved.

   The copyright notice must be clearly placed in all your work at DigiPen.

   At the top of every code file.

   In the footer of every page of all design documents.

   On the main screen or the credits of all games or other projects.

   On all secondary materials (boxes, sell sheets, press releases, CDs, etc.).

   If you are allowed to use various tools and libraries for your project (DirectX, FMod, etc.), you must follow the rules those tools and libraries have for displaying their copyrights and logos. This can be different for each one--you are responsible for following their restrictions.

   All projects and videos must display the DigiPen logo for at least two seconds in the beginning.

   All projects with installers must require the user to agree to the DigiPen EULA before the project is actually installed.

   ******************************************************************************/