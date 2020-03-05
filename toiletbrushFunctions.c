/******************************************************************************
filename    toiletbrushFunctions.c
author      Toby Klauder
DP email    toby.klauder@digipen.edu
course      GAM100

Brief Description:
This file defines the functions to create a specific item, the "toiletbrush".

******************************************************************************/
#include "stdafx.h" /* UNREFERENCED_PARAMETER, NULL*/
#include "toiletbrushFunctions.h" /* Function declarations */
#include "GameState.h" /* struct GameState, GameState_ChangeScore */
#include "GameFlags.h" /* GameFlags_IsInList */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetItemList, Room_SetDescription */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Remove, ItemList_Add */
#include "Item.h" /* Item_Create */
#include "onetimekeycardFunctions.h"

void toiletbrush_Take(CommandContext context, GameState* gameState, WorldData* worldData) {
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(gameState);
	UNREFERENCED_PARAMETER(worldData);

	printf("toiletbrush = forbidden backscratcher. \n");
}

void toiletbrush_Use(CommandContext context, GameState* gameState, WorldData* worldData) {
	Room* room;
	ItemList** roomItemsPtr;
	Item* toiletbrush;

	if ((gameState == NULL) || (worldData == NULL)) {
		return;
	}

	if (context != CommandContext_Item_Inventory) {
		printf("try picking up the toiletbrush before using it. \n");
		return;
	}
	if (GameFlags_IsInList(gameState->gameFlags, "bearscratched")) {
		printf("You've already used the toiletbrush. \n");
		return;
	}
	if (gameState->currentRoomIndex != 5) {
		printf("You cannot use the toilet brush here. \n"); 
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
		toiletbrush = ItemList_FindItem(gameState->inventory, "toiletbrush");

		/* Tell the user what they did */
		printf("you scratch the bears back with the toilet brush. The bear drops a keycard from between it's teeth. \n");
		*roomItemsPtr = ItemList_Add(*roomItemsPtr, Keycard_Build());
		/* Add to the player's score */
		GameState_ChangeScore(gameState, 10);

		/* Update the room description to reflect the change in the room */
		Room_SetDescription(room, "Room 5.  You are in the Bear's Den.  There is a keyswipe and obviously, a bear. \n");

		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "bearscratched");

	}
}




Item* toiletbrush_Build() {
	return Item_Create("toiletbrush", "a toiletbrush, looks like it would make for a good, but gross back-scratcher", true, toiletbrush_Use, toiletbrush_Take, NULL);
}