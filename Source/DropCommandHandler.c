/******************************************************************************
filename    DropCommandHandler.c
author      Matthew Picioccio
DP email    mattpic@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines functions that handle the "drop" user command, which removes
the specified item from the user's inventory and adds it to the current room.

******************************************************************************/
#include "stdafx.h" /* NULL */
#include "DropCommandHandler.h" /* Function declarations */
#include "CommandData.h" /* struct CommandData, CommandContext */
#include "WorldData.h" /* WorldData_GetRoom, */
#include "GameState.h" /* struct GameState */
#include "Room.h" /* Room_GetItemList */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Remove, ItemList_Add */
#include "Item.h" /* ItemFunc, Item_GetDropFunc */


/* Handles the "drop" user command, which drops an item in inventory to the current room.*/
void HandleDropCommand(CommandData *command, GameState* gameState, WorldData* worldData)
{
	Item* droppedItem; /* The item that is removed from inventory and added to the room */
	Room* room; /* The room that the item is being added to */
	ItemList** roomItemPtr; /* A pointer to the item-list pointer held by the room */
	ItemFunc dropFunc; /* The function to be called for the given item when it is dropped */

	/* safety check on the parameters */
	if ((command == NULL) || (command->noun == NULL) || (gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters aren't valid */
	}

	/* get the current room */
	room = WorldData_GetRoom(worldData, gameState->currentRoomIndex);
	/* get the item list from the current room */
	roomItemPtr = Room_GetItemList(room);
	if (roomItemPtr == NULL)
	{
		return; /* take no action if the room has no item list - this should never happen, though */
	}

	/* find the dropped item in the player's inventory */
	droppedItem = ItemList_FindItem(gameState->inventory, command->noun);
	if (droppedItem == NULL)
	{
		/* if the item wasn't found, then the player doesn't have it so they can't drop it */
		printf("You do not have a %s.\n", command->noun);
		return;
	}

	/* remove the item from inventory and assign the inventory pointer back to the game state */
	gameState->inventory = ItemList_Remove(gameState->inventory, droppedItem);

	/* add the item to the room's item list */
	*roomItemPtr = ItemList_Add(*roomItemPtr, droppedItem);

	/* everything has succeeded, so output the result */
	printf("You have dropped the %s.\n", command->noun);

	/* get the "drop" function for this item, if any (it is optional) */
	dropFunc = Item_GetDropFunc(droppedItem);
	if (dropFunc != NULL)
	{
		/* call the drop function with the Inventory context, since that's where the item was */
		dropFunc(CommandContext_Item_Inventory, gameState, worldData);
	}
}
/******************************************************************************
Copyrights, Logos, and EULAs

All DigiPen projects must include a DigiPen copyright notice, the DigiPen logo, and the DigiPen EULA (if they have an installer). DigiPen holds the copyright to all your classwork done while enrolled at DigiPen.

The DigiPen copyright notice has exactly the following form (except with the current year, of course):

All content © 2020 DigiPen (USA) Corporation, all rights reserved.

The copyright notice must be clearly placed in all your work at DigiPen.

At the top of every code file.

In the footer of every page of all design documents.

On the main screen or the credits of all games or other projects.

On all secondary materials (boxes, sell sheets, press releases, CDs, etc.).

If you are allowed to use various tools and libraries for your project (DirectX, FMod, etc.), you must follow the rules those tools and libraries have for displaying their copyrights and logos. This can be different for each one--you are responsible for following their restrictions.

All projects and videos must display the DigiPen logo for at least two seconds in the beginning.

All projects with installers must require the user to agree to the DigiPen EULA before the project is actually installed.

******************************************************************************/