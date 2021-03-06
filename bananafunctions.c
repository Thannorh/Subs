/******************************************************************************
filename    bananaFunctions.c
author      Toby Klauder
DP email    toby.klauder@digipen.edu
course      GAM100

Brief Description:
This file defines the functions to create a specific item, the "banana".

******************************************************************************/
#include "stdafx.h" /* UNREFERENCED_PARAMETER, NULL*/
#include "bananaFunctions.h" /* Function declarations */
#include "GameState.h" /* struct GameState, GameState_ChangeScore */
#include "GameFlags.h" /* GameFlags_IsInList */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetItemList, Room_SetDescription */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Remove, ItemList_Add */
#include "Item.h" /* Item_Create */
#include "onetimekeycardFunctions.h"

void banana_Take(CommandContext context, GameState* gameState, WorldData* worldData) {
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(gameState);
	UNREFERENCED_PARAMETER(worldData);

	printf("the banana is frozen, could leave a mark . \n");
}

void banana_Use(CommandContext context, GameState* gameState, WorldData* worldData) {
	Room* room;
	ItemList** roomItemsPtr;
	Item* banana;

	if ((gameState == NULL) || (worldData == NULL)) {
		return;
	}

	if (context != CommandContext_Item_Inventory) {
		printf("try picking up the banana before using it. \n");
		return;
	}
	if (gameState->currentRoomIndex != 6) {
		printf("you cannot use that here. \n"); 
		return; 
	}

	if (GameFlags_IsInList(gameState->gameFlags, "henchiefakeout")) {
		printf("You've already duped the henchmen. \n");
		return;
	}
	else {
		/* get the current room */
		room = WorldData_GetRoom(worldData, gameState->currentRoomIndex);

		/* get the list of items in the current room */
		roomItemsPtr = Room_GetItemList(room);
		if (roomItemsPtr == NULL)
		{
			return; /* take no action, as something is wrong - we should always have an item list */
		}

		/* Find the brick in the player's inventory - it should be there, since we are in the Inventory context */
		banana = ItemList_FindItem(gameState->inventory, "banana");

		/* Tell the user what they did */
		printf("you pull out your frozen banana, the henchmen can't see what it is due to poor lighting, and pass out from shock. They both drop keycards. \n");
		*roomItemsPtr = ItemList_Add(*roomItemsPtr, Keycard_Build());
		*roomItemsPtr = ItemList_Add(*roomItemsPtr, Keycard_Build());
		/* Add to the player's score */
		GameState_ChangeScore(gameState, 10);
		gameState->inventory = ItemList_Remove(gameState->inventory, banana);
		/* Update the room description to reflect the change in the room */
		Room_SetDescription(room, "Room 6. You are in the hallway. There are two henchies on the floor. \n");

		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "henchiefakeout");

	}
}




Item* banana_Build() {
	return Item_Create("banana", "a banana, looks like it could really slice through things easily", true, banana_Use, banana_Take, NULL);
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