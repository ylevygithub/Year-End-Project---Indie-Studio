/*
** EPITECH PROJECT, 2020
** Map
** File description:
** map
*/

#ifndef __MAP__H__
#define __MAP__H__

#ifdef __linux__
    #include <irrlicht/irrlicht.h>
#elif _WIN64
    #include <irrlicht.h>
#endif

#include <vector>
#include <memory>
#include "structures.h"
#include "Block.hpp"

class BManager;
class Block;

#define BLOCK_SIZE 1.25
#define BLOCK(x) ((x) * BLOCK_SIZE)

class Map {
    public:
        Map();
        ~Map();
        void createMap(std::shared_ptr<BManager> manager);
        void createGround(std::shared_ptr<BManager> manager);
        void createWall(std::shared_ptr<BManager> manager);
        void addCollision(std::shared_ptr<BManager> manager);
        void createExteriorGround(std::shared_ptr<BManager> manager);
        irr::u8 destroy_block(irr::u8 z, irr::u8 x);
        void setMapSize(irr::s16 width_off, irr::s16 height_off, irr::u16 width_size, irr::u16 height_size);
        irr::u8 checkCollision(std::shared_ptr<BManager> manager);
        std::vector<std::vector<Block *>> getMap() {return this->_map_chunks;};
        void load(std::shared_ptr<BManager> manager, std::vector<std::vector<irr::s16>> tab);
        inline irr::core::vector3df getBlockPosition(irr::u16 z, irr::u16 x) {return (this->_map_chunks[z][x]->getPos());};
        inline irr::s32 getMapZ(){return (this->_height_size);};
        inline irr::s32 getMapX(){return (this->_width_size);};
        inline irr::s32 getMapOffZ(){return (this->_height_off);};
        inline irr::s32 getMapOffX(){return (this->_width_off);};
    private:
        std::vector<Block *> _ground;
        std::vector<Block *> _exteriorGround;
        std::vector<std::vector<Block *>> _map_chunks;
        irr::s16 _width_off;
        irr::s16 _height_off;
        irr::u16 _width_size;
        bool _loaded;
        irr::u16 _height_size;
};

#endif