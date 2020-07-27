/*
** EPITECH PROJECT, 2020
** menu
** File description:
** menu
*/

#ifndef __MENU__H__
#define __MENU__H__

#ifdef __linux__
    #include <irrlicht/irrlicht.h>
#elif _WIN64
    #include <irrlicht.h>
#endif

#include <string>
#include <memory>
#include "../bombermanManager/bombermanManager.hpp"

typedef enum options_e {
    PLAY,
    LOAD,
    QUIT,
    SETTINGS,
} options_e;

class Menu {
    public:
        Menu(std::shared_ptr<BManager> manager, bool isIngame);
        ~Menu();
        void Menuloop(std::shared_ptr<BManager> manager);
        void MenuAction(std::shared_ptr<BManager> manager, bool isIngame);
        void setBackgroundImage(irr::video::ITexture *background);
        void launchIntro(std::shared_ptr<BManager> manager);
        void setActor(std::shared_ptr<BManager> manager);
        void setPipper(std::shared_ptr<BManager> manager, irr::scene::IAnimatedMeshSceneNode *pipper);
        void loadMenu(std::shared_ptr<BManager> manager);
        void cleanIntro(std::shared_ptr<BManager> manager);
        void selected();
        std::string getFileName() const {return this->fileName;}
        void ingameMenuLoop(std::shared_ptr<BManager> manager);
        void checkIngameMenu(std::shared_ptr<BManager> manager, ICatchEvent *catchEvent);
        void newGame(void);
        void loadSplashScreen(std::shared_ptr<BManager> manager);
        void launchSplashScreen(void);
        bool getSave(){return this->_save;}
        void setSave(bool set){this->_save = set;}
    private:
        irr::gui::IGUIEnvironment *_gui;
        irr::gui::IGUIFont *_font;
        irr::gui::IGUIButton *_bouton[4];
        irr::video::ITexture *_menuBackground;
        irr::video::ITexture *_introBackground;
        irr::core::rect<irr::s32> _rectangle;
        irr::core::position2d<irr::s32> _positionB;
        irr::core::position2d<irr::s32> _positionA;
        irr::scene::IAnimatedMeshSceneNode *_player[6];
        std::string fileName;
        irr::gui::IGUIComboBox *box;
        irr::gui::IGUIComboBox *boxNewGame;
        std::vector<irr::u32> _saves;
        std::vector<irr::u32> _numberPlayer;
        irr::scene::IAnimatedMeshSceneNode *_splashScreen;
        irr::s16 fileNbr;
        bool _isSettingsRemoved;
        bool _isMenu;
        bool _isQuitPressed;
        bool _isLoadSelected;
        bool _isNewGameSelected;
        bool _isNewGame;
        bool _saveStatus;
        bool _save;
        bool _isPlayPressed;
};

#endif