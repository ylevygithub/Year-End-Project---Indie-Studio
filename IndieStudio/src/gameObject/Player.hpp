/*
** EPITECH PROJECT, 2020
** Player.hpp
** File description:
** Player
*/

#pragma once

class BManager;

#include "IGameObject.hpp"
#ifdef __linux__
    #include <irrlicht/irrlicht.h>
#elif _WIN64
    #include <irrlicht.h>
#endif

#include "catchEvent.hpp"
#include "structures.h"
#include "bombermanManager.hpp"
#include <memory>

#define PLAYER_SPEED 10.f

class Map;

class Player: public IGameObject
{
    public:
        Player(BManager *manager, key_binding_t keyBinding, irr::u8 ID, bool isBot);
        ~Player();
        bool update();
        void draw();
        irr::scene::IAnimatedMeshSceneNode *getPlayerMesh(void);
        irr::core::vector3df getPos(void) {return (this->_mesh->getPosition());};
        map_pos_t getMapPos(std::shared_ptr<Map> map);
        void setPos(const irr::core::vector3df newpos) {this->_mesh->setPosition(newpos);};
        void setKeys(key_binding_t key_binding) {this->_key_binding = key_binding;};
        key_binding_t getKeys(void) {return (this->_key_binding);};
        bool movement(BManager *manager, std::shared_ptr<Map> map, irr::u8 playerID);
        void runPlayer(void);
        void iddlePlayer(void);
        inline const statistics_t getStatistics(void) {return (this->_statistics);};
        void setStatistics(irr::s16 bombNumber, irr::s16 bombRange, irr::s16 life, irr::s16 speed, bool wallPass) {this->_statistics.bombNumber = bombNumber;this->_statistics.bombRange = bombRange; this->_statistics.life = life; this->_statistics.speed = speed; this->_statistics.wallPass = wallPass;};
        inline object_type_e getObjectType(void) {return (this->_objectType);};
        bool getStatus(){return this->_isBot;}
    private:
        irr::core::vector3df getBotNodePath(BManager *manager, std::shared_ptr<Map> map, irr::u8 playerID);
        object_type_e _objectType;
        irr::scene::IAnimatedMeshSceneNode *_mesh;
        irr::s64 _prevMoveTime;
        key_binding_t _key_binding;
        bool _is_running;
        bool _moving_state_change;
        irr::core::vector3df _nextPosition;
        irr::u8 _ID;
        statistics_t _statistics;
        bool _isBot;
};