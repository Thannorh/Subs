/******************************************************************************
filename    hotcoffeeFunctions.c
author      Toby Klauder
DP email    tobyklauder@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines the functions to create a specific item, the "hotcoffee".

******************************************************************************/
#include "stdafx.h" /* UNREFERENCED_PARAMETER, NULL*/
#include "hotcoffeepotFunctions.h" /* Function declarations */
#include "GameState.h" /* struct GameState, GameState_ChangeScore */
#include "GameFlags.h" /* GameFlags_IsInList */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetItemList, Room_SetDescription */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Remove, ItemList_Add */
#include "Item.h" /* Item_Create */
#include "BrickFunctions.h"


/* Helper: The action performed when the hotcoffee is taken. */
void hotcoffee_Take(CommandContext context, GameState* gameState, WorldData* worldData)
{
	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(gameState);
	UNREFERENCED_PARAMETER(worldData);

	/* Give the user a hint about how the hotcoffee might be used, whenever it is picked up. */
	printf("The hotcoffee sizzles in your hand. \n");
}


/* Helper: The action performed when the hotcoffee is used. */
void hotcoffee_Use(CommandContext context, GameState* gameState, WorldData* worldData)
{
	Room* room; /* The current room */
	ItemList** roomItemsPtr; /* The list of items in the current room */
	Item* hotcoffee; /* The hotcoffee in the player's inventory */

	/* safety check on the parameters */
	if ((gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters are invalid */
	}

	/* check if the user is using the hotcoffee out of their inventory */
	if (context != CommandContext_Item_Inventory)
	{
		/* the user doesn't have the hotcoffee - inform the user of the problem and take no action */
		printf("You must have the hotcoffee before you can use it. \n");
		return;
	}

	/* check if we're in the right room to use the item */
	if (gameState->currentRoomIndex != 8)
	{
		/* we are not in the right room - inform the user of the problem and take no action */
		printf("You cannot use the hotcoffee here. \n");
		return;
	}

	/* check if the cage has already been broken and scored */
	if (GameFlags_IsInList(gameState->gameFlags, "meltoccured"))
	{
		/* the player already used the hotcoffee - inform the user of the problem and take no action */
		printf("You already used the hotcoffee here. \n");
		return;
	}
	else
	{
		/* get the current room */
		room = WorldData_GetRoom(worldData, gameState->currentRoomIndex);

		/* get the list of items in the current room */
		roomItemsPtr = Room_GetItemList(room);
		if (roomItemsPtr == NULL)
		{
			return; /* take no action, as something is wrong - we should always have an item list */
		}

		/* Find the hotcoffee in the player's inventory - it should be there, since we are in the Inventory context */
		hotcoffee = ItemList_FindItem(gameState->inventory, "hotcoffee");

		/* Remove the hotcoffee from the user's inventory - they won't need it again */
		gameState->inventory = ItemList_Remove(gameState->inventory, hotcoffee);

		/* Tell the user what they did */
		printf("You drip hotcoffee onto the ice cube, and the ice cube melts, revealing a keycard.  You can now pickup the keycard. \n");

		/* Add to the player's score */
		GameState_ChangeScore(gameState, 10);
		*roomItemsPtr = ItemList_Add(*roomItemsPtr, Keycard_Build());
		/* Update the room description to reflect the change in the room */
		Room_SetDescription(room, "You are in the break room, there is nothing and nobody in this room, only you, yourself and you. \n");

		/* the gold piece has not been scored, so mark the flag */
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "ventrevealed");
	}
}


/* Build a "hotcoffee" object */
Item* hotcoffee_Build()
{
	/* Create a "hotcoffee" item, using the functions defined in this file */
	return Item_Create("hotcoffee", "A small vial of hotcoffee of indeterminate origin, but probably the coffee machine", true, hotcoffee_Use, hotcoffee_Take, NULL);
}