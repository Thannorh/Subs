/******************************************************************************
filename    SpeakCommandHandler.c
author      Toby and Jacob
DP email    mattpic@digipen.edu
course      GAM100 

Brief Description:
This file defines functions that handle the "speak" user command, which outputs some flavortext

******************************************************************************/
#include "stdafx.h" /* NULL, printf, strnlen_s */
#include "SpeakCommandHandler.h" /* Function declarations */
#include "CommandData.h" /* struct CommandData */
#include "GameState.h" /* struct GameState */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_Print, Room_GetItemList */
#include "ItemList.h" /* ItemList_FindItem */
#include "Item.h" /* Item_Print */

void HandleSpeakCommand(CommandData* command, GameState* gameState, WorldData* worldData) {
	UNREFERENCED_PARAMETER(command); 
	UNREFERENCED_PARAMETER(gameState);
	UNREFERENCED_PARAMETER(worldData);
	if (gameState->currentRoomIndex == 0) {
		printf("You think to youself: Coca Cola from McDonalds is better. \n");
	}
	if (gameState->currentRoomIndex == 1) {
		printf("Merry Christmas you filthy animal. \n"); 
	}
	if (gameState->currentRoomIndex == 2) {
		printf("aw fantastic, if i was smarter i could use some of this. \n"); 
	}
	if (gameState->currentRoomIndex == 3) {
		printf("Did I ever tell you the definition of insanity? it starts with talking to yourself in a concrete room. \n"); 
	}
	if (gameState->currentRoomIndex == 4) {
		printf("Hey, can you pass me a roll. \n");
	}
	if (gameState->currentRoomIndex == 5) {
		printf("beary wanna cracker?. \n");
	}
	if (gameState->currentRoomIndex == 6) {
		printf("I'm not the fugitive you're looking for *waves hand*. \n");
	}
	if (gameState->currentRoomIndex == 7) {
		printf("These prices are astronomically  OUTRAGEOUS. \n");
	}
	if (gameState->currentRoomIndex == 8) {
		printf("eenie meenie miney mo catch a tiger by the toe..... \n ");
	}
	if (gameState->currentRoomIndex == 9) {
		printf("imagine typing ""go submerge"" \n");
	}
	if (gameState->currentRoomIndex == 10) {
		printf("DING DING \n");
	}
}
