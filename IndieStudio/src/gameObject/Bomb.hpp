/*
** EPITECH PROJECT, 2020
** Bomb.hpp
** File description:
** Bomb
*/

#pragma once

#include <chrono>
#ifdef __linux__
    #include <irrlicht/irrlicht.h>
#elif _WIN64
    #include <irrlicht.h>
#endif

#include <memory>
#include "Map.hpp"
#include "IGameObject.hpp"
#include "Player.hpp"

#define BOMB_COOLDOWN 3
#define SEC_TO_MILLI(x) ((x) * 1000)

class Bomb: public IGameObject
{
    public:
        Bomb(BManager *manager, std::shared_ptr<Map> map, Player *player);
        ~Bomb();
        bool update();
        void draw(){};
        irr::core::vector3df getPos(void) {return (this->_mesh->getPosition());};
        map_pos_t getMapPos(void) {return (this->_position);};
        bool isDestroyed() {return (this->_destroyed);};
        irr::u8 getBombRange(void) {return (this->bombRange);};
        object_type_e getObjectType() {return (this->_objectType);};
    private:
        object_type_e _objectType;
        map_pos_t _position;
        irr::scene::IAnimatedMeshSceneNode *_mesh;
        std::chrono::steady_clock::time_point _startTime;
        // irr::ITimer *_timer;
        // irr::IrrlichtDevice *_bombDevice;

        bool _destroyed;
        irr::u8 bombRange;
};