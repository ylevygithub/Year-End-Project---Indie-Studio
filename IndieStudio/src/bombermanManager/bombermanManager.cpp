/*
** EPITECH PROJECT, 2020
** bomberman Manger
** File description:
** bomber manager
*/

#include "IGameObject.hpp"
#include "Bomb.hpp"
#include "IGameObject.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "catchEvent.hpp"
#include "Map.hpp"
#include "bombermanManager.hpp"
#include <iostream>
#include <string>
#include <memory>

BManager::BManager()
{
    this->_isMenuAsk = false;
    this->_isLoaded = false;
    this->_catchEvent = new ICatchEvent();
    this->_device = createDevice(irr::video::EDT_OPENGL,
    irr::core::dimension2d<irr::u32>(1280, 640), 16, false, false, false, this->_catchEvent);

    if (this->_device == 0)
        exit(84);
    this->_driver = this->_device->getVideoDriver();
    this->_smgr = this->_device->getSceneManager();
    this->_GUI = this->_device->getGUIEnvironment();
}

BManager::~BManager(void)
{
    this->_device->drop();
}

void BManager::load(key_binding_t keyBinding, irr::core::vector3df vec, statistics_t stat)
{
    Player *player;
    if (keyBinding.back == 0 && keyBinding.front == 0)
        player = new Player((this), keyBinding, this->_players.size(), true); // <- le dernier argument pour set si c est un bot
    else
        player = new Player((this), keyBinding, this->_players.size(), false); // <- le dernier argument pour set si c est un bot
    player->setPos(vec);
    player->setStatistics(stat.bombNumber, stat.bombRange, stat.life, stat.speed, stat.wallPass);
    this->_players.push_back(player);
    this->_gameObjects.push_back(static_cast<IGameObject *>(player));
    this->_isLoaded = true;
}

void BManager::addPlayer(key_binding_t keyBinding, bool isBot)
{
    Player *player = new Player((this), keyBinding, this->_players.size(), isBot);

    this->_players.push_back(player);
    this->_gameObjects.push_back(static_cast<IGameObject *>(player));
}

void BManager::playerMovement(std::shared_ptr<Map> map)
{
    irr::u8 playersNumber = this->_players.size();
    // new Bomb();

    for (irr::u16 index = 0; index < playersNumber; index++) {
        if (this->_players[index]->movement((this), map, index)) {
            Bomb *tmp_bomb = new Bomb((this), map, this->_players[index]);
            this->_bombs.push_back(tmp_bomb);
            this->_gameObjects.push_back(static_cast<IGameObject *>(tmp_bomb));
        }
    }
}

void BManager::bombExplode(std::shared_ptr<Map> map, map_pos_t mapPosition, irr::u8 range)
{
    // bool break_a_wall[4] = {false, false, false, false};

    // for (irr::u8 index = 1; index < range; index++) {
        
    //     if (mapPosition.z + index < map->getMapZ() && !break_a_wall[0]) {
    //         break_a_wall[0] = (map->getMap()[mapPosition.z + index][mapPosition.x]->getBlockType() == BREAKABLE);
    //         map->destroy_block(mapPosition.z + index, mapPosition.x);
    //     }
    //     if (mapPosition.z - index >= 0 && !break_a_wall[1]) {
    //         break_a_wall[1] = (map->getMap()[mapPosition.z - index][mapPosition.x]->getBlockType() == BREAKABLE);
    //         map->destroy_block(mapPosition.z - index, mapPosition.x);
    //     }
    //     if (mapPosition.x + index < map->getMapX() && !break_a_wall[2]) {
    //         break_a_wall[2] = (map->getMap()[mapPosition.z][mapPosition.x + index]->getBlockType() == BREAKABLE);
    //         map->destroy_block(mapPosition.z, mapPosition.x + index);
    //     }
    //     if (mapPosition.x - index >= 0  && !break_a_wall[3]) {
    //         break_a_wall[3] = (map->getMap()[mapPosition.z][mapPosition.x - index]->getBlockType() == BREAKABLE);
    //         map->destroy_block(mapPosition.z, mapPosition.x - index);
    //     }
    // }
    return ;
}

void BManager::updateObjects(std::shared_ptr<Map> map)
{
    irr::u16 objectStackSize = this->_gameObjects.size();

    for (irr::s16 index = 0; index < objectStackSize; index++) {
        if (this->_gameObjects[index]->update()) {
            if (this->_gameObjects[index]->getObjectType() == BOMB) {
                this->bombExplode(map, static_cast<Bomb *>(this->_gameObjects[index])->getMapPos(),
                    static_cast<Bomb *>(this->_gameObjects[index])->getBombRange());
                this->_gameObjects.erase(this->_gameObjects.begin() + index);
                index -= 1;
                objectStackSize -= 1;
            }
        }
    }
    for (irr::s16 index = 0; index < this->_bombs.size(); index++) {
        if (this->_bombs[index]->isDestroyed()) {
            this->_bombs.erase(this->_bombs.begin() + index);
            index -= 1;
        }
    }
}

void BManager::drawObjects(void)
{
    irr::u16 objectStackSize = this->_gameObjects.size();

    for (irr::u16 index = 0; index < objectStackSize; index++)
        this->_gameObjects[index]->draw();
}

void BManager::initPlayers(std::shared_ptr<Map> map)
{
    key_binding_t mainPlayerKeys;
    mainPlayerKeys.front = irr::EKEY_CODE::KEY_KEY_Z;
    mainPlayerKeys.back = irr::EKEY_CODE::KEY_KEY_S;
    mainPlayerKeys.left = irr::EKEY_CODE::KEY_KEY_Q;
    mainPlayerKeys.right = irr::EKEY_CODE::KEY_KEY_D;
    mainPlayerKeys.bomb = irr::EKEY_CODE::KEY_KEY_F;
    key_binding_t secPlayerKeys;
    secPlayerKeys.front = irr::EKEY_CODE::KEY_KEY_I;
    secPlayerKeys.back = irr::EKEY_CODE::KEY_KEY_K;
    secPlayerKeys.left = irr::EKEY_CODE::KEY_KEY_J;
    secPlayerKeys.right = irr::EKEY_CODE::KEY_KEY_L;
    secPlayerKeys.bomb = irr::EKEY_CODE::KEY_KEY_M;

    if (this->_isLoaded != true) {
        this->addPlayer(mainPlayerKeys, false);
        this->addPlayer(secPlayerKeys, false);
        this->addPlayer(mainPlayerKeys, true);
        this->addPlayer(mainPlayerKeys, true);
        this->getplayer()[0]->setPos(irr::core::vector3df(
            map->getMapOffX() + 1.7 + 0.1, 0.1, map->getMapOffZ() + BLOCK(map->getMapZ() - 1) - 1.7 + 0.1));
        this->getplayer()[1]->setPos(irr::core::vector3df(
            map->getMapOffX() + 1.7 + 0.1, 0.1, map->getMapOffZ() + BLOCK(1)));
        this->getplayer()[2]->setPos(irr::core::vector3df(
            map->getMapOffX() + BLOCK(map->getMapX() - 1) - 1.7 - 0.1, 0.1, map->getMapOffZ() + BLOCK(map->getMapZ() - 1) - 1.7 + 0.1));
        this->getplayer()[3]->setPos(irr::core::vector3df(
            map->getMapOffX() + BLOCK(map->getMapX() - 1) - 1.7 - 0.1, 0.1, map->getMapOffZ() + BLOCK(1)));
    }
}

void BManager::initGame()
{
    /* LIGHT */

    irr::scene::ILightSceneNode *lumiere = this->_smgr->addLightSceneNode(0, irr::core::vector3df(0, 50, -15),
    irr::video::SColorf(0.4f, 0.4f, 0.6f, 0.0f));
    lumiere->getLightData().DiffuseColor = irr::video::SColorf(0.6, 1.0, 1.0, 1);
    lumiere->getLightData().SpecularColor = irr::video::SColorf(0.6, 0.0, 0.0, 1);
    lumiere->setRadius(250);
    
    /* LIGHT */
    // irr::gui::IGUIStaticText *text = this->_GUI->addStaticText(L"Tsb frangin ahahahaha\n" "le sang azeeee\n", irr::core::rect<irr::s32>(100,20,400,60), true, true, 0, -1, true);
    // irr::gui::IGUIFont *font = this->_GUI->getFont("../assets/fontlucida.png");
    // text->setOverrideFont(font);
    this->_smgr->addCameraSceneNode(0, irr::core::vector3df(0, 20, -5), irr::core::vector3df(0, 100, 200))->setTarget(irr::core::vector3df(0, 10, 0));
}

void BManager::addGameObjects(IGameObject * gameObject)
{
    this->_gameObjects.push_back(gameObject);
}

void BManager::setMenuAsk(bool isMenuAsk)
{
    this->_isMenuAsk = isMenuAsk;
}
void BManager::setloaded(bool isLoaded)
{
    this->_isLoaded = isLoaded;
}

void BManager::setNbPlayer(irr::u32 nbPlayer)
{
    this->_nbPlayerSelected = nbPlayer;
}
void BManager::setNbIA(irr::u32 nbIA)
{
    this->_nbIASelected = nbIA;
}

void BManager::endGameDisplay(irr::u8 first, irr::u8 seg, irr::u8 third, irr::u8 last)
{
    std::string name = "WINNER : PLAYER " + std::to_string(first);
    std::wstring wname[4];
    const wchar_t* result[4];

    for (irr::u8 i = 0; i < name.length(); ++i)
        wname[0] += wchar_t(name[i]);
    result[0] = wname[0].c_str();

    name = "SECOND : PLAYER " + std::to_string(seg);
    for (irr::u8 i = 0; i < name.length(); ++i)
        wname[1] += wchar_t(name[i]);
    result[1] = wname[1].c_str();

    name = "THIRD : PLAYER " + std::to_string(third);
    for (irr::u8 i = 0; i < name.length(); ++i)
        wname[2] += wchar_t(name[i]);
    result[2] = wname[2].c_str();

    name = "LAST : PLAYER " + std::to_string(last);
    for (irr::u8 i = 0; i < name.length(); ++i)
        wname[3] += wchar_t(name[i]);
    result[3] = wname[3].c_str();

    this->_board[0] = this->_GUI->addButton(irr::core::rect<irr::s32>(600,180,740,220),
        0, -1, result[0]);
        this->_board[1] = this->_GUI->addButton(irr::core::rect<irr::s32>(600,260,740,300),
        0, -1, result[1]);
        this->_board[2] = this->_GUI->addButton(irr::core::rect<irr::s32>(600,340,740,380),
        0, -1, result[2]);
        this->_board[3] = this->_GUI->addButton(irr::core::rect<irr::s32>(600,420,740,460),
        0, -1, result[3]);

        /* ADD COLOR */
        this->_board[0]->setImage(this->_driver->getTexture("../assets/green.png"));
        this->_board[1]->setImage(this->_driver->getTexture("../assets/red.png"));
        this->_board[2]->setImage(this->_driver->getTexture("../assets/red.png"));
        this->_board[3]->setImage(this->_driver->getTexture("../assets/red.png"));
}