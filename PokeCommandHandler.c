/******************************************************************************
filename    PokeCommandHandler.c
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
#include "onetimekeycardFunctions.h"

void HandlePokeCommand(CommandData* command, GameState* gameState, WorldData* worldData, CommandContext context) {
	Room* room;
	ItemList** roomItemsPtr;
	Item* toiletbrush;

	if ((gameState == NULL) || (worldData == NULL)) {
		return;
	}
	toiletbrush = ItemList_FindItem(gameState->inventory, "toiletbrush");
	if (toiletbrush == NULL) {
		printf("Error 404: poking tool not found. \n");
	}
	/*this is first room, one henchman*/
	if (gameState->currentRoomIndex == 1) {
		if (GameFlags_IsInList(gameState->gameFlags, "knockedlvl5mob")) {
			printf("you poke the knocked out henchman. \n"); 
		}
		else {
			printf("You poke the henchmen with the poker, the smell is overpowering, the henchman passes out and drops a keycard. \n");
			*roomItemsPtr = ItemList_Add(*roomItemsPtr, Keycard_Build());
			Room_SetDescription(room, "Room 1. You are in a hallway. There is a henchman on the floor, there is a keyswipe to the east. \n");
			Room_AddRoomExit(room, "south", 3);
			gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "knockedlvl5mob");
		}
	}
	/*this is bathroom, one henchman*/
	if (gameState->currentRoomIndex == 4) {
		if (GameFlags_IsInList(gameState->gameFlags, "lvl4mobhit")) {
			printf("you poke the knocked out henchman. \n"); 
		}
		else {
			printf("You poke the henchman with the poker, the smell is overpowering, he hurls and passes out on the floor, he drops nothing. \n");
			Room_SetDescription(room, "Room 4. You are in a bathroom, there is a knocked out henchman on the floor, there is an exit to the north. \n"); 
			gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "lvl4mobhit");
		}
	}
	/*this is bear room, one bear*/
	if (gameState->currentRoomIndex == 5) {
		if (GameFlags_IsInList(gameState->gameFlags, "bearscratched")) {
			printf("you've already given the bear a backscratch \n"); 
		}
		else {
			printf("You use the toiletbrush to give the bear a lovely backscratch. \n");  
			*roomItemsPtr = ItemList_Add(*roomItemsPtr, Keycard_Build()); 
			Room_SetDescription(room, "Room 5. You are in a hallway, a bear is laying on the floor, you see a keycard, as well as a keyswipe on the wall.\n"); 
			gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "bearscratched");
		}
	}
	/* this is hallway, two henchmen*/
	if (gameState->currentRoomIndex == 6) {
		if (GameFlags_IsInList(gameState->gameFlags, "henchiefakeout")) {
			printf("you poke the henchies with the poker. \n"); 
		}
		else {
			printf("You use the toiletbrush, the smell overpowers the henchman, they both fall to the ground and drop keycards. \n"); 
			*roomItemsPtr = ItemList_Add(*roomItemsPtr, Keycard_Build()); 
			*roomItemsPtr = ItemList_Add(*roomItemsPtr, Keycard_Build()); 
			Room_SetDescription(room, "Room 6. You are in a hallway, there are two henchies on the floor. You see two keycards. \n"); 
			gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "henchiefakeout"); 
		}
	}

}