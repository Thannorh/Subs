/******************************************************************************
filename    acidFunctions.c
author      Toby Klauder
DP email    tobyklauder@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines the functions to create a specific item, the "acid".

******************************************************************************/
#include "stdafx.h" /* UNREFERENCED_PARAMETER, NULL*/
#include "acidFunctions.h" /* Function declarations */
#include "GameState.h" /* struct GameState, GameState_ChangeScore */
#include "GameFlags.h" /* GameFlags_IsInList */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetItemList, Room_SetDescription */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Remove, ItemList_Add */
#include "Item.h" /* Item_Create */
#include "BrickFunctions.h"


/* Helper: The action performed when the acid is taken. */
void acid_Take(CommandContext context, GameState* gameState, WorldData* worldData)
{
	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(gameState);
	UNREFERENCED_PARAMETER(worldData);

	/* Give the user a hint about how the acid might be used, whenever it is picked up. */
	printf("The acid sizzles in your hand. \n");
}


/* Helper: The action performed when the acid is used. */
void acid_Use(CommandContext context, GameState* gameState, WorldData* worldData)
{
	Room* room; /* The current room */
	ItemList** roomItemsPtr; /* The list of items in the current room */
	Item* acid; /* The acid in the player's inventory */

	/* safety check on the parameters */
	if ((gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters are invalid */
	}

	/* check if the user is using the acid out of their inventory */
	if (context != CommandContext_Item_Inventory)
	{
		/* the user doesn't have the acid - inform the user of the problem and take no action */
		printf("You must have the acid before you can use it. \n");
		return;
	}

	/* check if we're in the right room to use the item */
	if (gameState->currentRoomIndex != 3)
	{
		/* we are not in the right room - inform the user of the problem and take no action */
		printf("You cannot use the acid here. \n");
		return;
	}

	/* check if the cage has already been broken and scored */
	if (GameFlags_IsInList(gameState->gameFlags, "ventrevealed"))
	{
		/* the player already used the acid - inform the user of the problem and take no action */
		printf("You already used the acid here. \n");
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

		/* Find the acid in the player's inventory - it should be there, since we are in the Inventory context */
		acid = ItemList_FindItem(gameState->inventory, "acid");

		/* Remove the acid from the user's inventory - they won't need it again */
		gameState->inventory = ItemList_Remove(gameState->inventory, acid);

		/* Tell the user what they did */
		printf("You drip acid onto the brick, and the brick crumbles, revealing a vent.  You can now move through the wall to the east. A whole brick drops to the ground. \n");

		/* Add to the player's score */
		GameState_ChangeScore(gameState, 10);

		Room_AddRoomExit(room, "east", 4);
		*roomItemsPtr = ItemList_Add(*roomItemsPtr, Brick_Build());
		/* Update the room description to reflect the change in the room */
		Room_SetDescription(room, "This is room 4.  You are in a concrete/brick room.  There is a hole in the wall, that you created, going west . \n");

		/* the gold piece has not been scored, so mark the flag */
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "ventrevealed");
	}
}


/* Build a "acid" object */
Item* acid_Build()
{
	/* Create a "acid" item, using the functions defined in this file */
	return Item_Create("acid", "A small vial of acid of indeterminate origin", true, acid_Use, acid_Take, NULL);
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