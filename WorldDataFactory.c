/******************************************************************************
filename    WorldDataFactory.c
author      Justin Chambers
DP email    justin.chambers@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines the WorldData factory, which creates the WorldData objects used
in this game.

This could be used to create default states as well as loaded state.

******************************************************************************/
#include "WorldDataFactory.h" /* Function declarations */
#include "WorldData.h" /* WorldData_Create, WorldData_SetRoom */
#include "Room.h" /* Room_Create, Room_AddRoomExit, Room_GetItemList */
#include "ItemList.h" /* ItemList_Add */
#include "BrickFunctions.h" /* Brick_Build */
#include "GoldPieceFunctions.h" /* GoldPiece_Build */
#include "ExitDoorFunctions.h" /* ExitDoor_Build */
#include "malletFunctions.h"
#include "scalpelFunctions.h"
#include "snazzylabcoatFunctions.h"
#include "acidFunctions.h"
#include "toiletbrushFunctions.h"
#include "BananaFunctions.h"


/******************************************************************************
	Build room TEMPLATE
    Use this example function to build additional rooms
******************************************************************************/
Room* RoomN_Build()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room;

	/* Create the room
	   include an initial room description */
	room = Room_Create("DEBUG: This is a template - Include a description for the room here\n");

	/* Exits
	   add one or more exits to allow navigation between rooms */
	Room_AddRoomExit(room, "north", 1);  /* 1 = the room index this exit connects to */

	/* Items
	   add items to the room */
	ItemList_AddItem(Room_GetItemList(room), ExitDoor_Build());

	/* Return the new room */
	return room;
}


/* TODO REQUIRED: Build room 0 */
Room* Room0_Build()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room = NULL;

	/* TODO REQUIRED: Call Room_Create with the Room 1 description:
	"This is room 0. It is a display room with a cage in the middle. You can see a jeweled egg inside the cage.  There is a crack in the west wall, but you can't fit through it from this side.\n" */
	room = Room_Create("You are in what appears to be an interrogation room, you see a mallet and a scalpel. There is a keycard swipe by the door, indicating it is locked. You are tightly bound to a chair. \n");
	/* TODO REQUIRED: Add an Exit "north" to Room 1 */
	/* added it into MalletFunctions.c*/
	/* TODO BASIC: Add room exit shortcut for "n" */

	/* TODO REQUIRED: add an exit door to the list of items in the room, ExitDoor_Build() */
	ItemList_AddItem(Room_GetItemList(room), Mallet_Build()); 
	ItemList_AddItem(Room_GetItemList(room), Scalpel_Build()); 
	/* TODO ADVANCED: (not required) update the description and add a room exit to the "east" */

	/* return the new room */
	return room;
}


/* TODO REQUIRED: Build room 1 */
Room* Room1_Build()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room = NULL;

	/* TODO REQUIRED: Call Room_Create with the Room 1 description:
	"This is room 1.  There is a large mirror here, and it shimmers as you approach.\n" */
	room = Room_Create("You enter a long hallway. You see a man who shouts stop! You see an elevator at the end of the hallway. There is a keyswipe on the west wall. \n"); 
	/* TODO REQUIRED: Add an Exit "through the mirror" to Room 2 */
	/* TODO BASIC: Add exit shortcuts for "through mirror" and "mirror" */

	/* TODO REQUIRED: Add an Exit "north" back to Room 0 */
	Room_AddRoomExit(room, "north", 0);
	/* TODO BASIC: Add room exit shortcut for "s" */
	/* TODO REQUIRED: Add a brick to the list of items in the room */

	/* return the new room */
	return room;
}


/* TODO REQUIRED: Build room 2 */
Room* Room2_Build()
{
	/* TODO: Pre-declare a room pointer which we will use to build the new room */
	Room* room = NULL;

	/* TODO REQUIRED: Call Room_Create with the Room 2 description:
	"This is room 2.  The room is isolated from the others, but you can see a crack in the east wall, just large enough to get through.\n" */
	room = Room_Create("You enter a chemistry lab. You see a super slick lab coat, as well as some acid. \n "); 
	/* TODO REQUIRED: Add an Exit "east" to Room 0 */
	/* TODO BASIC: Add exit shortcuts for "e" and "crack" */
	Room_AddRoomExit(room, "east", 1); 
	/* TODO REQUIRED: Add a gold piece to the list of items in the room */
	ItemList_AddItem(Room_GetItemList(room), labcoat_Build()); 
	ItemList_AddItem(Room_GetItemList(room), acid_Build()); 
	/* return the new room */
	return room;
}


/* TODO ADVANCED: Build room 3 */
Room* Room3_Build() {
	Room* room = NULL; 
	/* add description here */
	room = Room_Create("You take the elevator up into a empty concrete room, you see no obvious exits. \n "); 
	/* add exits here*/
	Room_AddRoomExit(room, "south", 1); 

	/* add items here */
	return room; 
}

Room* Room4_Build() {
	Room* room = NULL; 

	room = Room_Create("You shimmy through the vent and drop into a bathroom, there is a man at the sink washing his hands. \n"); 

	Room_AddRoomExit(room, "west", 3); 
	Room_AddRoomExit(room, "north", 5); 

	ItemList_AddItem(Room_GetItemList(room), toiletbrush_Build()); 
	return room; 
}

Room* Room5_Build() {
	Room* room = NULL; 

	room = Room_Create("You head out of the bathroom and into a room with a bear in it! There is a keyswipe on the west wall. \n"); 

	Room_AddRoomExit(room, "south", 4); 


	return room; 
}

Room* Room6_Build() {
	Room* room = NULL; 

	room = Room_Create("You are in a long hallway. You spot two guards at the end of the hallway. There is a unlocked door to the east. \n"); 

	Room_AddRoomExit(room, "south", 5); 
	Room_AddRoomExit(room, "east", 7);
	return room; 

}

Room* Room7_Build() {
	Room* room = NULL; 

	room = Room_Create("You duck into the room to the right, it's a cafeteria, there is a banana and a pot of hot coffee. \n "); 

	Room_AddRoomExit(room, "west", 6); 

	ItemList_AddItem(Room_GetItemList(room), banana_Build()); 
	return room; 
}
/* TODO ADVANCED: Build room 4 */


/* ------------------------------------------------------- */
/* Create the world data for a new game */
/* ------------------------------------------------------- */
WorldData* CreateInitialWorldData()
{
	/* The new world data */
	WorldData* worldData;

	/* TODO REQUIRED: update room count to match the number of rooms you have created and added to the world
	   if this number doesn't match then your game will either crash or you will end up stuck in a broken room with no exits */
	int roomCount = 8;

	/* create the new WorldData object with 3 rooms */
	worldData = WorldData_Create("Welcome to my GAM100 Game!\n\n", roomCount);

	/* build each room and assign them to the world data */
	WorldData_SetRoom(worldData, 0, Room0_Build());
	WorldData_SetRoom(worldData, 1, Room1_Build()); 
	WorldData_SetRoom(worldData, 2, Room2_Build()); 
	WorldData_SetRoom(worldData, 3, Room3_Build()); 
	WorldData_SetRoom(worldData, 4, Room4_Build()); 
	WorldData_SetRoom(worldData, 5, Room5_Build()); 
	WorldData_SetRoom(worldData, 6, Room6_Build());
	WorldData_SetRoom(worldData, 7, Room7_Build()); 
	/* TODO REQUIRED: add rooms 1 and 2 to the world data */

	/* TODO ADVANCED: add additional advanced rooms */

	/* return the new object */
	return worldData;
}