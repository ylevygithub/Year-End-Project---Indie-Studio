/*
** EPITECH PROJECT, 2020
** game 
** File description:
** game
*/

#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include "bombermanManager.hpp"
#include "Map.hpp"
#include <memory>

int gameLoop(void);
void playerMovement(std::shared_ptr<BManager> manager, Map *map);
void setScreenTitle(irr::s16 fps, irr::s16 lastFPS, std::shared_ptr<BManager> manager);

#endif