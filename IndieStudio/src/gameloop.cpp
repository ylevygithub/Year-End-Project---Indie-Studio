/*
** EPITECH PROJECT, 2020
** gameloop
** File description:
** gammeloop
*/

#ifdef __IRR_WINDOWS_
#pragram comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "game.h"
#include "audio.hpp"
#include "menu.hpp"
#include "save.hpp"
#include "HUD.hpp"
#include "catchEvent.hpp"
#include "bombermanManager.hpp"
#include <memory>

void setScreenTitle(irr::s16 fps, irr::s16 lastFPS, std::shared_ptr<BManager> manager)
{
    fps = manager->getdriver()->getFPS();
    if (lastFPS != fps) {
        irr::core::stringw tmp(L"!--BOMBERMAN--! - Irrlicht Engine [");
        tmp += manager->getdriver()->getName();
        tmp += L"] fps: ";
        tmp += fps;
        manager->getdevice()->setWindowCaption(tmp.c_str());
        lastFPS = fps;
    }
}

void draw2DImage(std::shared_ptr<HUD> hud, std::shared_ptr<BManager> manager)
{
    irr::core::position2d<irr::s32> sizeHead1;
    sizeHead1.X = hud->getpictureheadOne()->getSize().Width;
    sizeHead1.Y = hud->getpictureheadOne()->getSize().Height;

    manager->getdriver()->draw2DImage(hud->getpictureheadOne(), irr::core::position2d<irr::s32>(50,60), irr::core::rect<irr::s32>(0,0,sizeHead1.X,sizeHead1.Y), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpicturebomb(), irr::core::position2d<irr::s32>(159, 53), irr::core::rect<irr::s32>(0, 0, 20, 20), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpictureflame(), irr::core::position2d<irr::s32>(159, 78), irr::core::rect<irr::s32>(0, 0, 20, 18), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpicturespeed(), irr::core::position2d<irr::s32>(155, 100), irr::core::rect<irr::s32>(0, 0, 27, 25), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpicturehearth(), irr::core::position2d<irr::s32>(157, 126), irr::core::rect<irr::s32>(0, 0, 20, 20), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpicturewall(), irr::core::position2d<irr::s32>(157, 152), irr::core::rect<irr::s32>(0, 0, 20, 20), 0, irr::video::SColor(255,255,255,255), true);

    manager->getdriver()->draw2DImage(hud->getpictureheadTwo(), irr::core::position2d<irr::s32>(50,190), irr::core::rect<irr::s32>(0,0,sizeHead1.X,sizeHead1.Y), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpicturebomb(), irr::core::position2d<irr::s32>(159, 188), irr::core::rect<irr::s32>(0, 0, 20, 20), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpictureflame(), irr::core::position2d<irr::s32>(159, 213), irr::core::rect<irr::s32>(0, 0, 20, 18), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpicturespeed(), irr::core::position2d<irr::s32>(155, 236), irr::core::rect<irr::s32>(0, 0, 27, 25), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpicturehearth(), irr::core::position2d<irr::s32>(157, 263), irr::core::rect<irr::s32>(0, 0, 20, 20), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpicturewall(), irr::core::position2d<irr::s32>(157, 288), irr::core::rect<irr::s32>(0, 0, 20, 20), 0, irr::video::SColor(255,255,255,255), true);

    manager->getdriver()->draw2DImage(hud->getpictureheadThree(), irr::core::position2d<irr::s32>(50,330), irr::core::rect<irr::s32>(0,0,sizeHead1.X,sizeHead1.Y), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpicturebomb(), irr::core::position2d<irr::s32>(159, 323), irr::core::rect<irr::s32>(0, 0, 20, 20), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpictureflame(), irr::core::position2d<irr::s32>(159, 348), irr::core::rect<irr::s32>(0, 0, 20, 18), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpicturespeed(), irr::core::position2d<irr::s32>(155, 371), irr::core::rect<irr::s32>(0, 0, 27, 25), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpicturehearth(), irr::core::position2d<irr::s32>(157, 398), irr::core::rect<irr::s32>(0, 0, 20, 20), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpicturewall(), irr::core::position2d<irr::s32>(157, 423), irr::core::rect<irr::s32>(0, 0, 20, 20), 0, irr::video::SColor(255,255,255,255), true);

    manager->getdriver()->draw2DImage(hud->getpictureheadFour(), irr::core::position2d<irr::s32>(50,460), irr::core::rect<irr::s32>(0,0,sizeHead1.X,sizeHead1.Y), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpicturebomb(), irr::core::position2d<irr::s32>(159, 458), irr::core::rect<irr::s32>(0, 0, 20, 20), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpictureflame(), irr::core::position2d<irr::s32>(159, 483), irr::core::rect<irr::s32>(0, 0, 20, 18), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpicturespeed(), irr::core::position2d<irr::s32>(155, 501), irr::core::rect<irr::s32>(0, 0, 27, 25), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpicturehearth(), irr::core::position2d<irr::s32>(157, 533), irr::core::rect<irr::s32>(0, 0, 20, 20), 0, irr::video::SColor(255,255,255,255), true);
    manager->getdriver()->draw2DImage(hud->getpicturewall(), irr::core::position2d<irr::s32>(157, 558), irr::core::rect<irr::s32>(0, 0, 20, 20), 0, irr::video::SColor(255,255,255,255), true);
}

std::string createMenu(std::shared_ptr<BManager> manager, bool isIngame, std::shared_ptr<Map> map, std::string fileName)
{
    Data data;
    Menu *menu = new Menu(manager, isIngame);
    if (isIngame == false) {
        std::cout << "fileName: " << menu->getFileName() << std::endl;
        data.load(manager, map, menu->getFileName());
    }
    if (menu->getSave() == true){
        std::cout << "test save in if" << std::endl;
        data.save(manager->getplayer(), map, fileName);
        std::cout << "before return fileName: " << menu->getFileName() << std::endl;
    }
    menu->setSave(false);
    fileName = menu->getFileName();
    delete menu;
    return fileName;
}

void checkIngameMenu(std::shared_ptr<BManager> manager, ICatchEvent *catchEvent, std::shared_ptr<Map> map, std::string fileName)
{
    if (catchEvent->keyIsPressed(irr::KEY_KEY_P))
        createMenu(manager, true, map, fileName);
    else if (manager->getMenuAsk() == true)
        createMenu(manager, false, map, fileName);
}

int gameLoop(void)
{
    std::shared_ptr<BManager> manager = std::shared_ptr<BManager>(new BManager());
    std::shared_ptr<Map> map = std::shared_ptr<Map>(new Map());
    std::shared_ptr<sound_t> sound = std::shared_ptr<sound_t>(new sound_t);
    std::shared_ptr<music_t> music = std::shared_ptr<music_t>(new music_t);
    std::shared_ptr<ICatchEvent> catchEvent = std::shared_ptr<ICatchEvent>(new ICatchEvent());
    Data data;
    std::string fileName;
    irr::s16 lastFPS = -1;
    irr::s16 fps = 0;

    fileName = createMenu(manager, false, map, fileName);
    std::shared_ptr<HUD> hud = std::shared_ptr<HUD>(new HUD(manager->getplayer()));

    /* MUSIC */

    if (InGameMusic(music) == -1)
        exit(84);

    /* MUSIC */
    // data.load(manager, map, menu->getFileName());
    manager->initGame();
    map->createMap(manager);
    manager->initPlayers(map);
    map->addCollision(manager);
    hud->setTexture(manager);
    // printf("WSH LE SANG\n");
    //_blockMesh->remove();
    /* PRINT NB DE JOUEUR ET IA SELECTIONNER */
    // printf("NB PLAYER = %d\nNB IA = %d\n", manager->getnbPlayer(), manager->getnbIA()); // A RETIRER !!
    /* PRINT NB DE JOUEUR ET IA SELECTIONNER */
     while (manager->getdevice()->run() && manager->getMenuAsk() == false) {
        checkIngameMenu(manager, manager->getCatchEvent(), map, fileName);
        manager->playerMovement(map);
        manager->getdriver()->beginScene(true, true, irr::video::SColor(255, 113, 113, 133));
        manager->updateObjects(map);
        // draw objects
        hud->refreshHUD(manager, manager->getplayer(), hud->getFont());
        manager->drawObjects();
        manager->getsmgr()->drawAll();
        manager->getGUI()->drawAll();
        draw2DImage(hud, manager);
        manager->getdriver()->endScene();
        setScreenTitle(fps, lastFPS, manager);
    }
    music->ingame.stop();
    if (manager->getMenuAsk() == true)
        gameLoop();
    return (0);
}