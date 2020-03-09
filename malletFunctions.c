/******************************************************************************
filename    malletFunctions.c
author      Toby Klauder
DP email    toby.klauder@digipen.edu
course      GAM100

Brief Description:
This file defines the functions to create a specific item, the "mallet".

******************************************************************************/
#include "stdafx.h" /* UNREFERENCED_PARAMETER, NULL*/
#include "malletFunctions.h" /* Function declarations */
#include "GameState.h" /* struct GameState, GameState_ChangeScore */
#include "GameFlags.h" /* GameFlags_IsInList */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetItemList, Room_SetDescription */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Remove, ItemList_Add */
#include "Item.h" /* Item_Create */
#include "onetimekeycardFunctions.h"

void Mallet_Take(CommandContext context, GameState* gameState, WorldData* worldData) {
	UNREFERENCED_PARAMETER(context); 
	UNREFERENCED_PARAMETER(gameState);
	UNREFERENCED_PARAMETER(worldData);

	printf("the mallet feels suprising light and agile in your hand. \n"); 
}

void Mallet_Use(CommandContext context, GameState* gameState, WorldData* worldData) {
	Room* room; 
	ItemList** roomItemsPtr; 
	Item* mallet; 

	if ((gameState == NULL) || (worldData == NULL)) {
		return; 
	}

	if (context != CommandContext_Item_Inventory) {
		printf("try picking up the mallet before using it. \n"); 
		return; 
	}
	if ((GameFlags_IsInList(gameState->gameFlags, "keyswipebrokenscored")) && (gameState->currentRoomIndex == 0)) {
		printf("You've already used the mallet. \n"); 
		return; 
	}
	if ((gameState->currentRoomIndex == 1) && (GameFlags_IsInList(gameState->gameFlags, "knockedlvl5mob"))) {
		printf("You've already used the mallet here. \n"); 
	}
	if (!(GameFlags_IsInList(gameState->gameFlags, "bondscutscored"))) {
		printf("looks like you're a little tied up at the moment, try finding something to escape \n.");
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
		mallet = ItemList_FindItem(gameState->inventory, "mallet");

		/* Tell the user what they did */
		if (gameState->currentRoomIndex == 0) {
			printf("You smash the keyswipe open with the mallet, it sparks and the light turns green.  You can now leave your interrogation room: to the south. \n");
			Room_AddRoomExit(room, "south", 1);
			Room_SetDescription(room, "Room 0.  You are in a interrogation room.  There is a broken keyswipe and a door going south. \n");
			gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "keyswipebrokenscored");
		}
		else if (gameState->currentRoomIndex == 1) {
			printf("You bonk the henchie over the head with the mallet, the small handle the mallet snaps. You have lost the mallet. Henchie drops a keycard. \n"); 
			gameState->inventory = ItemList_Remove(gameState->inventory, mallet);
			*roomItemsPtr = ItemList_Add(*roomItemsPtr, Keycard_Build());
			Room_SetDescription(room, "Room 1. You are in a hallway. There is a henchman on the floor, there is a keyswipe to the east. \n");
			Room_AddRoomExit(room, "south", 3); 
			gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "knockedlvl5mob");
		}
		/* Add to the player's score */
		GameState_ChangeScore(gameState, 10);


	}
}




Item* Mallet_Build() {
	return Item_Create("mallet", "a small mallet, looks like it could leave a mark", true, Mallet_Use, Mallet_Take, NULL);
}