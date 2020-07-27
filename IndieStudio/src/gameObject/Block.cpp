/*
** EPITECH PROJECT, 2020
** Bomb.cpp
** File description:
** Bomb
*/

#include "Map.hpp"
#include "bombermanManager.hpp"
#include "IGameObject.hpp"
#include "Block.hpp"

Block::Block(irr::scene::ISceneManager *sceneManager, irr::scene::IAnimatedMesh *mesh, irr::video::ITexture *texture,
    irr::core::vector3df vector, block_type_e type)
{
    irr::f32 block_scaling = BLOCK_SIZE / 0.8;

    this->_blockType = type;
    this->_position = vector;
    if (type != NONE) {
        this->_blockMesh = sceneManager->addOctreeSceneNode(mesh);
        this->_blockMesh->setMaterialTexture(0, texture);
        this->_blockMesh->setPosition(vector);
        this->_blockMesh->setScale(irr::core::vector3df(block_scaling, block_scaling, block_scaling));
    }
    else
        this->_blockMesh = NULL;
    this->_objectType = BLOCK;
}

Block::~Block()
{
}

bool Block::update()
{
    return (0);
}

void Block::draw()
{

}

irr::core::vector3df Block::getPos(void)
{
    return (this->_position);
}

bool Block::destroyBlock(void)
{
    if (this->_blockType == BREAKABLE) {
        this->_blockMesh->remove();
        this->_blockMesh = NULL;
        this->_blockType = NONE;
        return (true);
    }
    return (false);
}

irr::scene::IMeshSceneNode *Block::getBlockMesh(void)
{
    return (this->_blockMesh);
}