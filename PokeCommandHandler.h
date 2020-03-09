/******************************************************************************
filename    PokeCommandHandler.h
author      Toby and Jacob
DP email    toby.klauder@digipen.edu
course      GAM100

Brief Description:
This file declares functions that handle the "poke" command which is risky.

******************************************************************************/
#pragma once

typedef struct CommandData CommandData;
typedef struct GameState GameState;
typedef struct WorldData WorldData;


/* Handles the "speak" user command, which prints out some flavortext.*/
void HandlePokeCommand(CommandData* command, GameState* gameState, WorldData* worldData, CommandContext context);