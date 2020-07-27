/*
** EPITECH PROJECT, 2020
** menu
** File description:
** menu
*/

#include "audio.hpp"
#include "game.h"
#include "menu.hpp"
#include <fstream>
#include <string>
#include <iostream>

irr::s16 countFiles()
{
    std::ifstream outfile;
    irr::s16 fileNbr = 0;
    std::string input;
    outfile.open("save/saveList.txt");
    for (fileNbr; std::getline(outfile, input); fileNbr++);
    outfile.close();
    return fileNbr;
}

Menu::Menu(std::shared_ptr<BManager> manager, bool isIngame)
{
    this->_isPlayPressed = false;
    this->_isMenu = true;
    this->_isQuitPressed = false;
    this->_isLoadSelected = false;
    this->_isNewGameSelected = false;
    this->_isSettingsRemoved = false;
    this->_saveStatus = true;
    manager->setNbPlayer(1);
    manager->setNbIA(1);
    this->fileNbr = countFiles();

    if (isIngame == false) {
        this->_gui = manager->getsmgr()->getGUIEnvironment();
        this->_gui->getSkin()->setFont(this->_gui->getFont("../assets/fontcourier.bmp"));
        this->_introBackground = manager->getdriver()->getTexture("../assets/indiestudio.png");
        // this->box = this->_gui->addComboBox(irr::core::rect<irr::s32>(20,20,320,70));
        // this->_saves.push_back(box->addItem(L"NEW SAVE"));

        /* SET BUTTON */
        this->_bouton[PLAY] = this->_gui->addButton(irr::core::rect<irr::s32>(600,180,740,220),
        0, -1, L"PLAY");
        this->_bouton[LOAD] = this->_gui->addButton(irr::core::rect<irr::s32>(600,260,740,300),
        0, -1, L"LOAD");
        this->_bouton[SETTINGS] = this->_gui->addButton(irr::core::rect<irr::s32>(600,340,740,380),
        0, -1, L"SETTINGS");
        this->_bouton[QUIT] = this->_gui->addButton(irr::core::rect<irr::s32>(600,420,740,460),
        0, -1, L"QUIT");

        /* ADD COLOR */
        this->_bouton[PLAY]->setPressedImage(manager->getdriver()->getTexture("../assets/green.png"));
        this->_bouton[LOAD]->setPressedImage(manager->getdriver()->getTexture("../assets/green.png"));
        this->_bouton[QUIT]->setPressedImage(manager->getdriver()->getTexture("../assets/green.png"));

        /* LAUNCH MENU LOOP */
        this->launchIntro(manager);
        this->_menuBackground = manager->getdriver()->getTexture("../assets/menu_back.jpg");
        this->Menuloop(manager);
    }
    else  {
        this->_gui = manager->getsmgr()->getGUIEnvironment();
        this->_gui->getSkin()->setFont(this->_gui->getFont("../assets/fontcourier.bmp"));
        /* SET BUTTON */
        this->_bouton[PLAY] = this->_gui->addButton(irr::core::rect<irr::s32>(600,180,740,220),
        0, -1, L"RESUME");
        this->_bouton[LOAD] = this->_gui->addButton(irr::core::rect<irr::s32>(600,260,740,300),
        0, -1, L"SAVE");
        this->_bouton[QUIT] = this->_gui->addButton(irr::core::rect<irr::s32>(600,340,740,380),
        0, -1, L"MENU");

        /* ADD COLOR */
        this->_bouton[PLAY]->setPressedImage(manager->getdriver()->getTexture("../assets/green.png"));
        this->_bouton[LOAD]->setPressedImage(manager->getdriver()->getTexture("../assets/green.png"));
        this->_bouton[QUIT]->setPressedImage(manager->getdriver()->getTexture("../assets/green.png"));
        this->ingameMenuLoop(manager);
    }
}

void Menu::ingameMenuLoop(std::shared_ptr<BManager> manager)
{
    irr::s16 lastFPS = -1;
    irr::s16 fps = 0;

    while (this->_isMenu && manager->getdevice()->run() && manager->getMenuAsk() == false) {
        manager->getdriver()->beginScene(true, true, irr::video::SColor (150,150,255,255));
        manager->getsmgr()->drawAll();
        this->MenuAction(manager, true);
        this->_gui->drawAll();
        manager->getdriver()->endScene();
        setScreenTitle(fps, lastFPS, manager);
    }
    if (!manager->getdevice()->run() || this->_isQuitPressed == true)
        exit(0);
    this->_isNewGameSelected = false;
    this->_isSettingsRemoved = true;
    this->_isLoadSelected = false;
}

Menu::~Menu()
{
    this->_bouton[PLAY]->remove();
    this->_bouton[LOAD]->remove();
    this->_bouton[QUIT]->remove();
    if (this->_isNewGameSelected == true) {
        this->boxNewGame->remove();
    }
    if (this->_isSettingsRemoved == false)
        this->_bouton[SETTINGS]->remove();
    if (this->_isLoadSelected == true)
        this->box->remove();
}

void Menu::loadSplashScreen(std::shared_ptr<BManager> manager)
{
    this->_splashScreen = manager->getsmgr()->addAnimatedMeshSceneNode(
        manager->getsmgr()->getMesh("../assets/Mesh/SplashScreen/SplashScreen.3ds"));
    this->_splashScreen->setMaterialFlag(irr::video::EMF_LIGHTING, false);    
    this->_splashScreen->setMaterialTexture(0, manager->getdriver()->getTexture("../assets/Mesh/SplashScreen/AllBombermanColorPattern.png"));
    this->_splashScreen->setPosition(irr::core::vector3df(-500, -0.2, 0));
    this->_splashScreen->setScale(irr::core::vector3df(0.08, 0.08, 0.08));
}

void Menu::setPipper(std::shared_ptr<BManager> manager, irr::scene::IAnimatedMeshSceneNode *pipper)
{
    pipper = manager->getsmgr()->addAnimatedMeshSceneNode(
        manager->getsmgr()->getMesh("../assets/Mesh/PlayersTextures/PlayerBasic/PlayerOne.b3d"));
    pipper->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    pipper->setMaterialTexture(0, manager->getdriver()->getTexture("../assets/Mesh/PlayersTextures/PlayerYellow/PlayerColorSetYellow.png"));
    pipper->setScale(irr::core::vector3df(0.20, 0.20, 0.20));
    pipper->setPosition(irr::core::vector3df(-0.05,-0.50,-0.3));
    pipper->setFrameLoop(171, 201);
    pipper->setAnimationSpeed(20);
}

void Menu::setActor(std::shared_ptr<BManager> manager)
{
    irr::f32 indexX = 0.45;
    irr::f32 speed = 20;

    for (irr::s16 index = 0; index != 5; index++) {
        this->_player[index] = manager->getsmgr()->addAnimatedMeshSceneNode(
        manager->getsmgr()->getMesh("../assets/Mesh/PlayersTextures/PlayerDarker/PlayerTwo.b3d"));
        this->_player[index]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        this->_player[index]->setMaterialTexture(0, manager->getdriver()->getTexture("../assets/Mesh/PlayersTextures/PlayerDarker/PlayerColorSetTwo.png"));
        this->_player[index]->setScale(irr::core::vector3df(0.25, 0.25, 0.25));
        this->_player[index]->setPosition(irr::core::vector3df(indexX,-0.40,0));
        this->_player[index]->setFrameLoop(91, 131);
        this->_player[index]->setAnimationSpeed(speed);
        speed -= 3;
        indexX -= 0.25;
    }
    this->setPipper(manager, this->_player[5]);
}

void Menu::cleanIntro(std::shared_ptr<BManager> manager)
{
    for (irr::s16 index = 0; index != 5; index++)
        manager->getsmgr()->addToDeletionQueue(this->_player[index]);
}

void Menu::launchIntro(std::shared_ptr<BManager> manager)
{
    std::shared_ptr<music_t> music = std::shared_ptr<music_t>(new music_t);
    irr::s16 lastFPS = -1;
    irr::s16 fps = 0;

    if (introMusic(music) == -1)
        exit(84);

    this->loadSplashScreen(manager);
    this->setActor(manager);
    this->setBackgroundImage(this->_introBackground);
    playIntro(music);
    while (isIntroPlay(music) && manager->getdevice()->run()) {
        manager->getdriver()->beginScene(true, true, irr::video::SColor (0,0,0,0));
        manager->getsmgr()->drawAll();
        manager->getdriver()->draw2DImage(this->_introBackground, this->_positionA,
        this->_rectangle, 0, irr::video::SColor(255,255,255,255), true);
        manager->getdriver()->endScene();
        setScreenTitle(fps, lastFPS, manager);
    }
    if (!manager->getdevice()->run()) {
        exit(0);
    }
    cleanIntro(manager);
}

void Menu::loadMenu(std::shared_ptr<BManager> manager)
{
    std::wstring save;
    
    for (irr::s16 index = 1; index <= this->fileNbr; index++) {
        save = L"SAVE " + std::to_wstring(index);
        this->_saves.push_back(box->addItem(save.c_str()));
    }
    this->_isLoadSelected = true;
    this->_saveStatus = false;
}
void Menu::selected()
{
    this->fileName = "save/save";
    if (this->_saveStatus == false) {
        if (this->box->getSelected() == 0)
            this->fileName += std::to_string(this->fileNbr + 1) + ".txt";
        else
            this->fileName += std::to_string(this->box->getSelected()) + ".txt";
    }
    else
        this->fileName += std::to_string(this->fileNbr + 1) + ".txt";
}
void Menu::newGame(void)
{
    this->boxNewGame = this->_gui->addComboBox(irr::core::rect<irr::s32>(920,20,1220,70));
    this->_numberPlayer.push_back(this->boxNewGame->addItem(L"ONE PLAYER"));
    this->_numberPlayer.push_back(this->boxNewGame->addItem(L"TWO PLAYERS"));
    this->_numberPlayer.push_back(this->boxNewGame->addItem(L"THREE PLAYERS"));
    this->_numberPlayer.push_back(this->boxNewGame->addItem(L"FOUR PLAYERS"));
    this->_isNewGameSelected = true;
}

void Menu::MenuAction(std::shared_ptr<BManager> manager, bool isIngame)
{
    if (isIngame == false) {
        if (this->_bouton[SETTINGS]->isPressed() && this->_isNewGameSelected == false)
            newGame();
        else if (this->_bouton[PLAY]->isPressed()) {
            this->_isPlayPressed = true;
            this->selected();
            if (this->_isLoadSelected == true) {
                if (this->box->getSelected() == 0 && this->_isNewGameSelected == true) {
                    manager->setNbPlayer(this->boxNewGame->getSelected() + 1);
                }
            }
            else if (this->_isNewGameSelected == true) {
                manager->setNbPlayer(this->boxNewGame->getSelected() + 1);
            }
            this->_isMenu = false;
        }
        else if (this->_bouton[PLAY]->isPressed())
            this->_isMenu = false;
        else if (this->_bouton[QUIT]->isPressed()) {
            this->_isMenu = false;
            this->_isQuitPressed = true;
        }
        else if (this->_bouton[LOAD]->isPressed() && this->_isLoadSelected == false) {
            this->box = this->_gui->addComboBox(irr::core::rect<irr::s32>(20,20,320,70));
            this->_saves.push_back(box->addItem(L"NEW SAVE"));
            this->loadMenu(manager);
            this->_isNewGame = true;
        }
    }
    else {
        if (this->_bouton[PLAY]->isPressed())
            this->_isMenu = false;
        else if (this->_bouton[QUIT]->isPressed()) {
            this->_isSettingsRemoved = true;
            manager->setMenuAsk(true);
        }
        else if (this->_bouton[LOAD]->isPressed() && this->_isLoadSelected == false) {
            this->_save = true;
        }
    }
}

void Menu::setBackgroundImage(irr::video::ITexture *background)
{
    irr::core::dimension2d<irr::u32> size = background->getSize();
    this->_positionA.X = 0;
    this->_positionA.Y = 0;
    this->_positionB.X = size.Width;
    this->_positionB.Y = size.Height;
    this->_rectangle.UpperLeftCorner = this->_positionA;
    this->_rectangle.LowerRightCorner = this->_positionB;
}

void Menu::launchSplashScreen(void)
{
    this->_splashScreen->setPosition(irr::core::vector3df(0,0,0));
    this->_positionA.X = -50;
    this->_positionB.Y = -50;
    this->_rectangle.UpperLeftCorner = this->_positionA;
    this->_rectangle.LowerRightCorner = this->_positionB;
    this->_bouton[PLAY]->setRelativePosition(irr::core::position2di(-50));
    this->_bouton[SETTINGS]->setRelativePosition(irr::core::position2di(-50));
    this->_bouton[LOAD]->setRelativePosition(irr::core::position2di(-50));
    this->_bouton[QUIT]->setRelativePosition(irr::core::position2di(-50));
    if (this->_isLoadSelected == true)
        this->box->setRelativePosition(irr::core::position2di(-50));
    if (this->_isNewGameSelected == true) {
        this->boxNewGame->setRelativePosition(irr::core::position2di(-50));
    }
}

void Menu::Menuloop(std::shared_ptr<BManager> manager)
{
    std::shared_ptr<music_t> music = std::shared_ptr<music_t>(new music_t);
    irr::s16 lastFPS = -1;
    irr::s16 fps = 0;
    if (MenuMusic(music) == -1)
        exit(84);

    this->setBackgroundImage(this->_menuBackground);
    while (this->_isMenu && manager->getdevice()->run()) {
        this->MenuAction(manager, false);
        if (this->_isPlayPressed == true)
            this->launchSplashScreen();
        manager->getdriver()->beginScene(true, true, irr::video::SColor (0,0,0,0));
        manager->getsmgr()->drawAll();
        manager->getdriver()->draw2DImage(this->_menuBackground, this->_positionA,
        this->_rectangle, 0, irr::video::SColor(255,255,255,255), true);
        this->_gui->drawAll();
        manager->getdriver()->endScene();
        setScreenTitle(fps, lastFPS, manager);
    }
    if (!manager->getdevice()->run() || this->_isQuitPressed == true) {
        exit(0);
    }
    music->menu.stop();
} 