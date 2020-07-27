/*
** EPITECH PROJECT, 2020
** bomberman Manager
** File description:
** bomberManager
*/

#ifndef __BMANAGER__
#define __BMANAGER__

#ifdef __linux__
    #include <irrlicht/irrlicht.h>
#elif _WIN64
    #include <irrlicht.h>
#endif

#include <vector>
#include <memory>
#include "structures.h"

class IGameObject;
class Map;
class Player;
class Bomb;
class PowerUp;
class ICatchEvent;

class BManager {
    public:
        BManager();
        ~BManager();
        void initGame();
        void initPlayers(std::shared_ptr<Map> map);
        irr::IrrlichtDevice *getdevice() {return (this->_device);};
        irr::video::IVideoDriver *getdriver() {return (this->_driver);};
        irr::scene::ISceneManager *getsmgr() {return (this->_smgr);};
        irr::gui::IGUIEnvironment *getGUI() {return (this->_GUI);};
        void playerMovement(std::shared_ptr<Map> map);
        void updateObjects(std::shared_ptr<Map> map);
        void drawObjects(void);
        void addPlayer(key_binding_t keyBinding, bool isBot);
        void load(key_binding_t keyBinding, irr::core::vector3df vec, statistics_t stat);
        void bombExplode(std::shared_ptr<Map> map, map_pos_t mapPosition, irr::u8 range);
        ICatchEvent *getCatchEvent() {return (this->_catchEvent);};
        void addGameObjects(IGameObject * gameObject);
        void setMenuAsk(bool isMenuAsk);
        void setloaded(bool isloaded);
        bool getMenuAsk() {return (this->_isMenuAsk);};
        bool getLoaded() {return (this->_isLoaded);};
        std::vector<Bomb *> getBombs(void) {return (this->_bombs);};
        std::vector<Player *> getplayer(void) {return (this->_players);};
        irr::u32 getnbPlayer() {return (this->_nbPlayerSelected);};
        irr::u32 getnbIA() {return (this->_nbIASelected);};
        void endGameDisplay(irr::u8 first, irr::u8 seg, irr::u8 third, irr::u8 last);
        void setNbPlayer(irr::u32 nbPlayer);
        void setNbIA(irr::u32 nbIA);
    private:
        std::vector<Player *> _players;
        std::vector<IGameObject *> _gameObjects;
        std::vector<Bomb *> _bombs;
        irr::core::aabbox3d<irr::f32> b1;
        irr::core::aabbox3d<irr::f32> b2;
        irr::IrrlichtDevice *_device;
        irr::video::IVideoDriver *_driver;
        irr::scene::ISceneManager *_smgr;
        irr::gui::IGUIEnvironment *_GUI;
        irr::gui::IGUIButton *_board[4];
        irr::u32 _nbPlayerSelected;
        irr::u32 _nbIASelected;
        ICatchEvent *_catchEvent;
        bool _isMenuAsk;
        bool _isLoaded;
};

#endif