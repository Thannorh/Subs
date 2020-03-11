/******************************************************************************
filename    CommandFactory.c
author      Justin Chambers
DP email    justin.chambers@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file implements the CommandList factory, creating the commands used 
in this game.

******************************************************************************/
#include "stdafx.h" /* NULL */
#include "CommandListFactory.h" /* Function declarations */
#include "CommandList.h" /* CommandList and CommandList_Add */
#include "CommandHandlerFunctions.h" /* all Handle___Command functions */


/* Create the command list with all commands used in this game.*/
CommandList* CreateCommandList()
{
	/* The command list to be returned, starting empty */
	CommandList* commandList = NULL; 
	CommandList** cmdListPtr = &commandList;
	
	/*
	* NOTES: - Add the commands in the reverse of the order they'll be used, to reduce searching.
	*		 - Short alias commands do not show up in help.
	*/

	/* EXAMPLE: This is how you create the "help" command
				and add it to the list of commands for the game
	   NOTICE:  It uses a function called HandleHelpCommand, you can find
				additional command handler functions by looking here: CommandHandlerFunctions.h */
	CommandList_Add(cmdListPtr, "help", HandleHelpCommand, true);
	/* TODO BASIC: add support for a short alias "h" */
	CommandList_Add(cmdListPtr, "h", HandleHelpCommand, false); 
	/* TODO REQUIRED: create the "quit" command
	TODO BASIC: add a short alias "q" */
	CommandList_Add(cmdListPtr, "quit", HandleQuitCommand, true); 
	CommandList_Add(cmdListPtr, "q", HandleQuitCommand, false);
	/* TODO REQUIRED: create the "drop" command
	TODO BASIC: add a short alias "d" */
	CommandList_Add(cmdListPtr, "drop", HandleDropCommand, true); 
	CommandList_Add(cmdListPtr, "d", HandleDropCommand, false);
	/* TODO REQUIRED: create the "take" command
	TODO BASIC: add a short alias "t" */
	CommandList_Add(cmdListPtr, "take", HandleTakeCommand, true); 
	CommandList_Add(cmdListPtr, "t", HandleTakeCommand, false); 
	/* TODO REQUIRED: create the "use" command
	TODO BASIC: add a short alias "u" */
	CommandList_Add(cmdListPtr, "use", HandleUseCommand, true); 
	CommandList_Add(cmdListPtr, "u", HandleUseCommand, false); 
	/* TODO REQUIRED: create the "look" command
	TODO BASIC: add a short alias "l" */
	CommandList_Add(cmdListPtr, "look", HandleLookCommand, true); 
	CommandList_Add(cmdListPtr, "l", HandleLookCommand, false); 
	/* TODO REQUIRED: create the "inventory" command
	TODO BASIC: add a short alias "i" */
	CommandList_Add(cmdListPtr, "inventory", HandleInventoryCommand, true); 
	CommandList_Add(cmdListPtr, "i", HandleInventoryCommand, false); 
	/* TODO REQUIRED: create the "go" command
	TODO BASIC: add a short alias "g" */
	CommandList_Add(cmdListPtr, "go", HandleGoCommand, true); 
	CommandList_Add(cmdListPtr, "g", HandleGoCommand, false); 
	/* TODO ADVANCED: create aditional commands
	this should require the creation of additional .c files to implement the command functions */
	CommandList_Add(cmdListPtr, "speak", HandleSpeakCommand, true); 
	CommandList_Add(cmdListPtr, "s", HandleSpeakCommand, false); 

	CommandList_Add(cmdListPtr, "poke", HandlePokeCommand, true); 
	CommandList_Add(cmdListPtr, "yell", HandleYellCommand, true); 
	/* return the newly created command list */
	return commandList;
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