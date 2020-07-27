/*
** EPITECH PROJECT, 2020
** Block.hpp
** File description:
** Block
*/

#pragma once

#ifdef __linux__
    #include <irrlicht/irrlicht.h>
#elif _WIN64
    #include <irrlicht.h>
#endif

#include "IGameObject.hpp"
#include "bombermanManager.hpp"
#include "structures.h"

class Block: public IGameObject
{
    public:
        Block(irr::scene::ISceneManager *sceneManager, irr::scene::IAnimatedMesh *mesh, irr::video::ITexture *texture,
            irr::core::vector3df vector, block_type_e type);
        ~Block();
        bool update();
        void draw();
        irr::core::vector3df getPos(void);
        irr::scene::IMeshSceneNode *getBlockMesh(void);
        bool destroyBlock(void);
        inline object_type_e getObjectType() {return (this->_objectType);};
        inline block_type_e getBlockType() {return (this->_blockType);};
    private:
        object_type_e _objectType;
        irr::core::vector3df _position;
        block_type_e _blockType;
        irr::scene::IMeshSceneNode *_blockMesh;
};