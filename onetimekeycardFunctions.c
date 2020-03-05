/******************************************************************************
filename    snazzylabcoatFunctions.c
author      Toby Klauder
DP email    toby.klauder@digipen.edu
course      GAM100

Brief Description:
This file defines the functions to create a specific item, the "keycard".

******************************************************************************/
#include "stdafx.h" /* UNREFERENCED_PARAMETER, NULL*/
#include "onetimekeycardFunctions.h" /* Function declarations */
#include "GameState.h" /* struct GameState, GameState_ChangeScore */
#include "GameFlags.h" /* GameFlags_IsInList */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetItemList, Room_SetDescription */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Remove, ItemList_Add */
#include "Item.h" /* Item_Create */

void Keycard_Take(CommandContext context, GameState* gameState, WorldData* worldData) {
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(gameState);
	UNREFERENCED_PARAMETER(worldData);

	printf("the keycard is slim, could come in handy later. \n");
}

void Keycard_Use(CommandContext context, GameState* gameState, WorldData* worldData) {
	Room* room;
	ItemList** roomItemsPtr;
	Item* keycard;

	if ((gameState == NULL) || (worldData == NULL)) {
		return;
	}

	if (context != CommandContext_Item_Inventory) {
		printf("try picking up the keycard before using it. \n");
	}
	if (gameState->currentRoomIndex != 1 && gameState->currentRoomIndex != 5) {
		printf("You can't use that here.");
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
		keycard = ItemList_FindItem(gameState->inventory, "keycard");

		gameState->inventory = ItemList_Remove(gameState->inventory, keycard);

		/* Tell the user what they did */
		printf("You use the keycard on the keyswipe. A door appears. \n");
		if (gameState->currentRoomIndex == 1) {
			Room_AddRoomExit(room, "west", 2);
			Room_SetDescription(room, "Room 1. You have unlocked the door to the west. \n");
		}
		if (gameState->currentRoomIndex == 5) {
			Room_AddRoomExit(room, "west", 6); 
			Room_SetDescription(room, "Room 5. Unlocked Elevator to the west. \n"); 
		}
		/* Add to the player's score */
		GameState_ChangeScore(gameState, 10);

		/* Update the room description to reflect the change in the room */

	}
}




Item* Keycard_Build() {
	return Item_Create("keycard", "a Keycard, looks like it matches with the keyswipe", true, Keycard_Use, Keycard_Take, NULL);
}

