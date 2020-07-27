/*
** EPITECH PROJECT, 2020
** Bomb.cpp
** File description:
** Bomb
*/

#include <chrono>
#include <iostream>
#include "structures.h"
#include "IGameObject.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Bomb.hpp"

Bomb::Bomb(BManager *manager, std::shared_ptr<Map> map, Player *player)
{
    irr::s32 mapSizeZ = map->getMapZ();
    irr::s32 mapSizeX = map->getMapX();
    irr::core::vector3df bomb_position;
    map_pos_t playerMapPos = player->getMapPos(map);

    if (map->getMap()[playerMapPos.z][playerMapPos.x]->getBlockType() == NONE) {
        this->_mesh = manager->getsmgr()->addAnimatedMeshSceneNode(manager->getsmgr()->getMesh(
            "../assets/Mesh/bomb.3ds"));
        this->_mesh->setMaterialTexture(0, manager->getdriver()->getTexture("../assets/Mesh/bomb.png"));
        bomb_position = map->getBlockPosition(playerMapPos.z, playerMapPos.x);
        bomb_position.Y = 0.5;

        this->_mesh->setPosition(bomb_position);
        this->_mesh->setScale(irr::core::vector3df(1.5, 1.5, 1.5));
        this->_objectType = BOMB;
        this->_destroyed = false;
        this->bombRange = player->getStatistics().bombRange;
        this->_startTime = std::chrono::steady_clock::now();
    }
    else
        this->_destroyed = true;
}

Bomb::~Bomb()
{
    
}

bool Bomb::update()
{
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    // printf("on test le temps: %d\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - this->_startTime).count());
    if (std::chrono::duration_cast<std::chrono::milliseconds>(end - this->_startTime).count() < SEC_TO_MILLI(BOMB_COOLDOWN)) {
        this->_mesh->setAnimationSpeed(80);
    }
    else {
        this->_mesh->remove();
        this->_destroyed = true;
        return (true);
    }
    return (0);
}