/*
** EPITECH PROJECT, 2020
** map
** File description:
** map
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "bombermanManager.hpp"
#include "Block.hpp"
#include "Player.hpp"
#include "Map.hpp"

Map::Map()
{
    this->_loaded = false;
}

Map::~Map()
{
}

void Map::load(std::shared_ptr<BManager> manager, std::vector<std::vector<irr::s16>> tab)
{
    irr::scene::IAnimatedMesh *mesh = manager->getsmgr()->getMesh("../assets/Mesh/Magma/UnbreakableBorder.3ds");
    irr::video::ITexture *border_texture = manager->getdriver()->getTexture("../assets/Mesh/Magma/Unreakable.T");
    irr::video::ITexture *unbreakable_block_texture = manager->getdriver()->getTexture("../assets/Mesh/Magma/Stories.TGA");
    irr::video::ITexture *breakable_block_texture = manager->getdriver()->getTexture("../assets/Mesh/Magma/Breakable.TG");
    irr::scene::IMeshSceneNode *tmp_new_object;
    std::vector<Block *> tmp_block_line;
    Block *tmp_block;
    this->_map_chunks.clear();
    /* background */
    for (irr::s16 index = tab.size() - 1; index >= 0; index--) {
        tmp_block_line.clear();
        for (irr::s16 line = 0; line < tab[index].size(); line++) {
            if (tab[index][line] == WALL) { // WALL BLOCKS
                tmp_block = new Block(manager->getsmgr(), mesh, border_texture,
                    irr::core::vector3df(-15 + BLOCK(line), 0, -3 + BLOCK(index)), WALL);
                tmp_block_line.push_back(tmp_block);
            }
            else if (tab[index][line] == UNBREAKABLE) { // UNBREAKABLE BLOCKS
                tmp_block = new Block(manager->getsmgr(), mesh, unbreakable_block_texture,
                    irr::core::vector3df(-15 + BLOCK(line), 0, -3 + BLOCK(index)), UNBREAKABLE);
                tmp_block_line.push_back(tmp_block);
            }
            else if (tab[index][line] == BREAKABLE) { // BREAKABLE BLOCKS
                tmp_block = new Block(manager->getsmgr(), mesh, breakable_block_texture,
                    irr::core::vector3df(-15 + BLOCK(line), 0, -3 + BLOCK(index)), BREAKABLE);
                tmp_block_line.push_back(tmp_block);
                manager->addGameObjects(static_cast<IGameObject *>(tmp_block));
            }
            else { // EMPTY CHUNK
                tmp_block = new Block(manager->getsmgr(), NULL, NULL,
                    irr::core::vector3df(-15 + BLOCK(line), 0, -3 + BLOCK(index)), NONE);
                tmp_block_line.push_back(tmp_block);
                manager->addGameObjects(static_cast<IGameObject *>(tmp_block));
            }
        }
        this->_map_chunks.push_back(tmp_block_line);
    }
    this->_loaded = true;
}

void Map::addCollision(std::shared_ptr<BManager> manager)
{
    irr::scene::IAnimatedMesh *meshMap = manager->getsmgr()->getMesh("../assets/Mesh/Magma/UnbreakableBorder.3ds");
    irr::scene::IAnimatedMesh *meshGround = manager->getsmgr()->getMesh("../assets/Mesh/Magma/Ground.3ds");
    irr::scene::ITriangleSelector *selector;
    irr::scene::ISceneNodeAnimator *anim;
    irr::u8 playerNb = manager->getplayer().size();

    for (irr::u32 indexZ = 0; indexZ < this->_map_chunks.size(); indexZ++) {
        for (irr::u32 indexX = 0; indexX < this->_map_chunks[indexZ].size(); indexX++) {
            selector = manager->getsmgr()->createOctreeTriangleSelector(meshMap,
                this->_map_chunks[indexZ][indexX]->getBlockMesh(), 128);
            for (irr::u8 index = 0; index < playerNb; index++) {
                anim = manager->getsmgr()->createCollisionResponseAnimator(selector, manager->getplayer()[index]->getPlayerMesh(),
                    irr::core::vector3df(0.5, 0.5, 0.5), irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
                manager->getplayer()[index]->getPlayerMesh()->addAnimator(anim);
            }
            selector->drop();
            anim->drop();
        }
    }
    for (irr::u32 index = 0; index < this->_ground.size(); index++) {
        selector = manager->getsmgr()->createOctreeTriangleSelector(meshGround,
            this->_ground[index]->getBlockMesh(), 128);
        for (irr::u8 index = 0; index < playerNb; index++) {
            anim = manager->getsmgr()->createCollisionResponseAnimator(selector, manager->getplayer()[index]->getPlayerMesh(),
                irr::core::vector3df(0.1, 0.1, 0.1), irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
            manager->getplayer()[index]->getPlayerMesh()->addAnimator(anim);
        }
        selector->drop();
        anim->drop();
    }
}

void Map::createWall(std::shared_ptr<BManager> manager)
{
    irr::scene::IAnimatedMesh *mesh = manager->getsmgr()->getMesh("../assets/Mesh/Magma/UnbreakableBorder.3ds");
    irr::video::ITexture *border_texture = manager->getdriver()->getTexture("../assets/Mesh/Magma/Unreakable.T");
    irr::video::ITexture *unbreakable_block_texture = manager->getdriver()->getTexture("../assets/Mesh/Magma/Stories.TGA");
    irr::video::ITexture *breakable_block_texture = manager->getdriver()->getTexture("../assets/Mesh/Magma/Breakable.TG");
    irr::scene::IMeshSceneNode *tmp_new_object;
    std::vector<Block *> tmp_block_line;
    Block *tmp_block;

    std::srand(std::time(0));

    /* background */
    for (irr::s16 indexZ = this->_height_size - 1; indexZ > -1; indexZ--) {
        tmp_block_line.clear();
        for (irr::s16 indexX = 0; indexX < this->_width_size; indexX++) {
            if (indexZ == this->_height_size - 1 || indexX == 0 || indexZ == 0 || indexX + 1 >= this->_width_size) { // WALL BLOCKS
                tmp_block = new Block(manager->getsmgr(), mesh, border_texture,
                    irr::core::vector3df(this->_width_off + BLOCK(indexX), 0, this->_height_off + BLOCK(indexZ)), WALL);
                tmp_block_line.push_back(tmp_block);
            }
            else if (!(indexZ % 2) && !(indexX % 2) && (std::rand() % 3)) { // UNBREAKABLE BLOCKS
                tmp_block = new Block(manager->getsmgr(), mesh, unbreakable_block_texture,
                    irr::core::vector3df(this->_width_off + BLOCK(indexX), 0, this->_height_off + BLOCK(indexZ)), UNBREAKABLE);
                tmp_block_line.push_back(tmp_block);
            }
            else if (std::rand() % 3) { // BREAKABLE BLOCKS
                tmp_block = new Block(manager->getsmgr(), mesh, breakable_block_texture,
                    irr::core::vector3df(this->_width_off + BLOCK(indexX), 0, this->_height_off + BLOCK(indexZ)), BREAKABLE);
                tmp_block_line.push_back(tmp_block);
                manager->addGameObjects(static_cast<IGameObject *>(tmp_block));
            }
            else { // EMPTY CHUNK
                tmp_block = new Block(manager->getsmgr(), NULL, NULL,
                    irr::core::vector3df(this->_width_off + BLOCK(indexX), 0, this->_height_off + BLOCK(indexZ)), NONE);
                tmp_block_line.push_back(tmp_block);
                manager->addGameObjects(static_cast<IGameObject *>(tmp_block));
            }
        }
        this->_map_chunks.push_back(tmp_block_line);
    }
    // TAKE OUT CORNERS
    /* up left */
    this->destroy_block(1, 1);
    this->destroy_block(1, 2);
    this->destroy_block(2, 1);
    /* up right */
    this->destroy_block(1, this->_width_size - 2);
    this->destroy_block(1, this->_width_size - 3);
    this->destroy_block(2, this->_width_size - 2);
    // /* down left */
    this->destroy_block(this->_height_size - 2, 1);
    this->destroy_block(this->_height_size - 3, 1);
    this->destroy_block(this->_height_size - 2, 2);
    // /* down right */
    this->destroy_block(this->_height_size - 2, this->_width_size - 2);
    this->destroy_block(this->_height_size - 3, this->_width_size - 2);
    this->destroy_block(this->_height_size - 2, this->_width_size - 3);
}

irr::u8 Map::destroy_block(irr::u8 z, irr::u8 x)
{
    if (z < this->_height_size && x < this->_width_size)
        return (this->_map_chunks[z][x]->destroyBlock());
    else
        return (false);
}

void Map::createGround(std::shared_ptr<BManager> manager)
{
    irr::scene::IAnimatedMesh *mesh = manager->getsmgr()->getMesh("../assets/Mesh/Magma/Ground.3ds");
    irr::video::ITexture *texture = manager->getdriver()->getTexture("../assets/Mesh/Magma/Ground.TGA");
    Block *tmp_block;

    for (irr::s16 indexZ = this->_height_size - 1; indexZ > -1; indexZ--) {
        for (irr::s16 indexX = 0; indexX < this->_width_size; indexX++) {
            tmp_block = new Block(manager->getsmgr(), mesh, texture,
                irr::core::vector3df(this->_width_off + BLOCK(indexX), 0, this->_height_off + BLOCK(indexZ)), GROUND);
            this->_ground.push_back(tmp_block);
        }
    }
}

void Map::createExteriorGround(std::shared_ptr<BManager> manager)
{
    irr::scene::IAnimatedMeshSceneNode *tmp_new_object;
    irr::scene::IAnimatedMesh *mesh = manager->getsmgr()->getMesh("../assets/Mesh/Magma/Ground.3ds");
    irr::video::ITexture *texture = manager->getdriver()->getTexture("../assets/Mesh/Magma/Exterior.TGA");
    // irr::f32 block_scaling = BLOCK_SIZE / 0.8;
    Block *tmp_block;

    // for (irr::s16 indexZ = 45; indexZ > -10; indexZ--) {
    //     for (irr::s16 indexX = -60; indexX < 60; indexX++) {
    //         tmp_block = Block *new Block(manager, mesh, texture,
    //             irr::core::vector3df(indexX, -2, indexZ), BACKGROUND));
    //         this->_ground.push_back(tmp_block);
    //         // tmp_new_object = manager->getsmgr()->addAnimatedMeshSceneNode(mesh);
    //         // tmp_new_object->setMaterialTexture(0, texture);
    //         // tmp_new_object->setPosition(irr::core::vector3df(indexX, -2, indexZ));
    //         // // tmp_new_object->setScale(irr::core::vector3df(block_scaling, block_scaling, block_scaling));
    //         // this->_exteriorGround.push_back(tmp_new_object);
    //     }
    // }

    tmp_new_object = manager->getsmgr()->addAnimatedMeshSceneNode(mesh);
    tmp_new_object->setMaterialTexture(0, texture);
    tmp_new_object->setScale(irr::core::vector3df(150, 0, 100));
    tmp_new_object->setPosition(irr::core::vector3df(0, -2, 0));
    // this->_exteriorGround.push_back(tmp_new_object);
}

void Map::setMapSize(irr::s16 width_off, irr::s16 height_off, irr::u16 width_size, irr::u16 height_size)
{
    this->_width_off = width_off;
    this->_height_off = height_off;
    if (width_size < 6)
        width_size = 6;
    if (height_size < 6)
        height_size = 6;
    this->_width_size = (width_size % 2) ? width_size : width_size + 1; 
    this->_height_size = (height_size % 2) ? height_size : height_size + 1;
}

void Map::createMap(std::shared_ptr<BManager> manager)
{
    this->setMapSize(-15, -3, 30, 20);
    this->createExteriorGround(manager);
    this->createGround(manager);

    if (this->_loaded != true) {
        this->createWall(manager);
            // irr::scene::IAnimatedMeshSceneNode *bomb = manager->getsmgr()->addAnimatedMeshSceneNode(
            //     manager->getsmgr()->getMesh("../assets/Mesh/bomb.3ds"));
            // bomb->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            // bomb->setPosition(irr::core::vector3df(
            //     this->getMapOffX() + 1.7 + 0.1, 0.5, this->getMapOffZ() + BLOCK(this->getMapZ() - 1) - 1.7 + 0.1));
            // bomb->setScale(irr::core::vector3df(1.5, 1.5, 1.5));
            // irr::scene::IAnimatedMeshSceneNode *bomb = manager->getsmgr()->addAnimatedMeshSceneNode(
            // manager->getsmgr()->getMesh("../assets/Mesh/bomb.3ds"));
            // bomb->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            // printf("%d    %d\n", this->getMapOffX(), this->_width_off);
            // exit(0);
            // bomb->setPosition(irr::core::vector3df(
            //     this->_width_off + 1.7 + 0.1, 0.5, this->_height_off + BLOCK(this->_height_size - 1) - 1.7 + 0.1));
            // bomb->setScale(irr::core::vector3df(1.5,1.5,1.5));
    }
}