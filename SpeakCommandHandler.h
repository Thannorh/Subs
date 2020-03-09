/******************************************************************************
filename    SpeakCommandHandler.h
author      Toby and Jacob 
DP email    toby.klauder@digipen.edu
course      GAM100 

Brief Description:
This file declares functions that handle the "speak" command which randomly says some flavortext.

******************************************************************************/
#pragma once

typedef struct CommandData CommandData;
typedef struct GameState GameState;
typedef struct WorldData WorldData;


/* Handles the "speak" user command, which prints out some flavortext.*/
void HandleSpeakCommand(CommandData* command, GameState* gameState, WorldData* worldData);