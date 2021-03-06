/******************************************************************************
filename    YellCommandHandler.c
author      Toby and Jacob
DP email    toby.klauder@digipen.edu
course      GAM100

Brief Description:
This file defines functions that handle the "poke", for when you have the toiletbrush.

******************************************************************************/
#include "stdafx.h" /* NULL, printf, strnlen_s */
#include "PokeCommandHandler.h" /* Function declarations */
#include "CommandData.h" /* struct CommandData */
#include "GameState.h" /* struct GameState */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_Print, Room_GetItemList */
#include "ItemList.h" /* ItemList_FindItem */
#include "Item.h" /* Item_Print */
#include "GameFlags.h"
#include "onetimekeycardFunctions.h"

void HandleYellCommand(CommandData* command, GameState* gameState, WorldData* worldData) {
	UNREFERENCED_PARAMETER(worldData); 
	UNREFERENCED_PARAMETER(command); 
	UNREFERENCED_PARAMETER(gameState);
	printf("AHHHHHHHHH\n"); 
	if (gameState->currentRoomIndex == 0) {
		printf("You hear someone in the next room yell ""SHUT UP"". \n");
	}
	if (gameState->currentRoomIndex == 1) {
		printf("The guard hears you he may or may not be awake. \n");
	}
	if (gameState->currentRoomIndex == 2) {
		printf("The glass beakers shatter you get fluids all over your face.... good thing it was just water. \n");
	}
	if (gameState->currentRoomIndex == 3) {
		printf("Nothing happens. \n");
	}
	if (gameState->currentRoomIndex == 4) {
		printf("Nothing was heard was heard because the water was on. \n");
	}
	if (gameState->currentRoomIndex == 5) {
		printf("The bear looks at and he's like ""what the heck I'm trying to vibe here"" he didn't but you could see it in his face. \n");
	}
	if (gameState->currentRoomIndex == 6) {
		printf("quietly yell so the henchies dont hear you. \n");
	}
	if (gameState->currentRoomIndex == 7) {
		printf("After yelling you think to yourself ""I could really  go for a cup of joe"" . \n");
	}
	if (gameState->currentRoomIndex == 8) {
		printf("You think to youself: Coca Cola from McDonalds is better. \n");
	}
	if (gameState->currentRoomIndex == 9){
		printf("You hear your yell echo across the sub bay. \n");
	}
	if (gameState->currentRoomIndex == 10) {
		printf("You think to youself: Coca Cola from McDonalds is better. \n");
	}
}


/******************************************************************************
Copyrights, Logos, and EULAs

All DigiPen projects must include a DigiPen copyright notice, the DigiPen logo, and the DigiPen EULA (if they have an installer). DigiPen holds the copyright to all your classwork done while enrolled at DigiPen.

The DigiPen copyright notice has exactly the following form (except with the current year, of course):

All content � 2020 DigiPen (USA) Corporation, all rights reserved.

The copyright notice must be clearly placed in all your work at DigiPen.

At the top of every code file.

In the footer of every page of all design documents.

On the main screen or the credits of all games or other projects.

On all secondary materials (boxes, sell sheets, press releases, CDs, etc.).

If you are allowed to use various tools and libraries for your project (DirectX, FMod, etc.), you must follow the rules those tools and libraries have for displaying their copyrights and logos. This can be different for each one--you are responsible for following their restrictions.

All projects and videos must display the DigiPen logo for at least two seconds in the beginning.

All projects with installers must require the user to agree to the DigiPen EULA before the project is actually installed.

******************************************************************************/