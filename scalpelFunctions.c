/******************************************************************************
filename    scalpelFunctions.c
author      Toby Klauder
DP email    toby.klauder@digipen.edu
course      GAM100

Brief Description:
This file defines the functions to create a specific item, the "scalpel".

******************************************************************************/
#include "stdafx.h" /* UNREFERENCED_PARAMETER, NULL*/
#include "scalpelFunctions.h" /* Function declarations */
#include "GameState.h" /* struct GameState, GameState_ChangeScore */
#include "GameFlags.h" /* GameFlags_IsInList */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetItemList, Room_SetDescription */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Remove, ItemList_Add */
#include "Item.h" /* Item_Create */

void Scalpel_Take(CommandContext context, GameState* gameState, WorldData* worldData) {
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(gameState);
	UNREFERENCED_PARAMETER(worldData);

	printf("the scalpel has one sharp edge, good for cutting through things. \n");
}

void Scalpel_Use(CommandContext context, GameState* gameState, WorldData* worldData) {
	Room* room;
	ItemList** roomItemsPtr;
	Item* scalpel;

	if ((gameState == NULL) || (worldData == NULL)) {
		return;
	}

	if (context != CommandContext_Item_Inventory) {
		printf("try picking up the scalpel before using it. \n");
	}
	if ((GameFlags_IsInList(gameState->gameFlags, "bondscutscored")) && (gameState->currentRoomIndex == 0)) {
		printf("You've already used the scalpel. \n");
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
		scalpel = ItemList_FindItem(gameState->inventory, "scalpel");

		/* Tell the user what they did */
		printf("you cut your bonds with the scalpel. You may now move about the room. \n");

		/* Add to the player's score */
		GameState_ChangeScore(gameState, 10);

		/* Update the room description to reflect the change in the room */
		Room_SetDescription(room, "Room 0.  You are in a interrogation room.  There is a keyswipe and a door going south. \n");

		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "bondscutscored");

	}
}




Item* Scalpel_Build() {
	return Item_Create("scalpel", "a scalpel, looks like it could really slice through things easily", true, Scalpel_Use, Scalpel_Take, NULL);
}