/*
** EPITECH PROJECT, 2020
** HUD.cpp
** File description:
** HUD
*/

#include "bombermanManager.hpp"
#include "Player.hpp"
#include "HUD.hpp"

HUD::HUD(std::vector<Player *> player)
{
    this->_player = player;
}

HUD::~HUD()
{
}

void HUD::setTexture(std::shared_ptr<BManager> manager)
{
    this->_headPicOne = manager->getdriver()->getTexture("../assets/Mesh/PlayersTextures/PlayerBasic/headHUD.png");
    this->_headPicTwo = manager->getdriver()->getTexture("../assets/Mesh/PlayersTextures/PlayerDarker/headPurple.png");
    this->_headPicThree = manager->getdriver()->getTexture("../assets/Mesh/PlayersTextures/PlayerGreen/headGreen.png");
    this->_headPicFour = manager->getdriver()->getTexture("../assets/Mesh/PlayersTextures/PlayerYellow/headYellow.png");
    this->_flamePic = manager->getdriver()->getTexture("../assets/Mesh/flame.png");
    this->_bombPic = manager->getdriver()->getTexture("../assets/Mesh/bomb.png");
    this->_speedPic = manager->getdriver()->getTexture("../assets/Mesh/speed.png");
    this->_hearthPic = manager->getdriver()->getTexture("../assets/Mesh/hearth.png");
    this->_wallPic = manager->getdriver()->getTexture("../assets/Mesh/wallpass.png");

    this->_font = manager->getGUI()->getFont("../assets/fontcourier.bmp");
    this->bombTextOne = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,50, 185, 75), true, true, 0, -1, true);
    this->flameTextOne = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,75, 185, 100), true, true, 0, -1, true);
    this->speedTextOne = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,100, 185, 125), true, true, 0, -1, true);
    this->hearthTextOne = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,125, 185, 150), true, true, 0, -1, true);
    this->wallTextOne = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,150, 185, 175), true, true, 0, -1, true);

    this->bombTextTwo = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,185, 185, 210), true, true, 0, -1, true);
    this->flameTextTwo = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,210, 185, 235), true, true, 0, -1, true);
    this->speedTextTwo = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,235, 185, 260), true, true, 0, -1, true);
    this->hearthTextTwo = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,260, 185, 285), true, true, 0, -1, true);
    this->wallTextTwo = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,285, 185, 310), true, true, 0, -1, true);

    this->bombTextThree = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,320, 185, 345), true, true, 0, -1, true);
    this->flameTextThree = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,345, 185, 370), true, true, 0, -1, true);
    this->speedTextThree = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,370, 185, 395), true, true, 0, -1, true);
    this->hearthTextThree = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,395, 185, 420), true, true, 0, -1, true);
    this->wallTextThree = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,420, 185, 445), true, true, 0, -1, true);

    this->bombTextFour = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,455, 185, 480), true, true, 0, -1, true);
    this->flameTextFour = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,480, 185, 505), true, true, 0, -1, true);
    this->speedTextFour = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,505, 185, 530), true, true, 0, -1, true);
    this->hearthTextFour = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,530, 185, 555), true, true, 0, -1, true);
    this->wallTextFour = manager->getGUI()->addStaticText(L"", irr::core::rect<irr::s32>(135,555, 185, 580), true, true, 0, -1, true);

}

void HUD::txtHUDPlayerFour(irr::gui::IGUIFont *font, std::shared_ptr<BManager> manager, std::vector<Player *> player)
{
    this->bombTextFour->setText(irr::core::stringw(player[3]->getStatistics().bombNumber).c_str());
    this->flameTextFour->setText(irr::core::stringw(player[3]->getStatistics().bombRange).c_str());
    this->speedTextFour->setText(irr::core::stringw(player[3]->getStatistics().speed).c_str());
    this->hearthTextFour->setText(irr::core::stringw(player[3]->getStatistics().life).c_str());
    this->wallTextFour->setText(irr::core::stringw(player[3]->getStatistics().wallPass).c_str());
    this->bombTextFour->setOverrideFont(this->_font);
    this->flameTextFour->setOverrideFont(this->_font);
    this->speedTextFour->setOverrideFont(this->_font);
    this->hearthTextFour->setOverrideFont(this->_font);
    this->wallTextFour->setOverrideFont(this->_font);
}

void HUD::txtHUDPlayerThree(irr::gui::IGUIFont *font, std::shared_ptr<BManager> manager, std::vector<Player *> player)
{
    this->bombTextThree->setText(irr::core::stringw(player[2]->getStatistics().bombNumber).c_str());
    this->flameTextThree->setText(irr::core::stringw(player[2]->getStatistics().bombRange).c_str());
    this->speedTextThree->setText(irr::core::stringw(player[2]->getStatistics().speed).c_str());
    this->hearthTextThree->setText(irr::core::stringw(player[2]->getStatistics().life).c_str());
    this->wallTextThree->setText(irr::core::stringw(player[2]->getStatistics().wallPass).c_str());
    this->bombTextThree->setOverrideFont(this->_font);
    this->flameTextThree->setOverrideFont(this->_font);
    this->speedTextThree->setOverrideFont(this->_font);
    this->hearthTextThree->setOverrideFont(this->_font);
    this->wallTextThree->setOverrideFont(this->_font);
    txtHUDPlayerFour(this->_font, manager, player);
}


void HUD::txtHUDPlayerTwo(irr::gui::IGUIFont *font, std::shared_ptr<BManager> manager, std::vector<Player *> player)
{
    this->bombTextTwo->setText(irr::core::stringw(player[1]->getStatistics().bombNumber).c_str());
    this->flameTextTwo->setText(irr::core::stringw(player[1]->getStatistics().bombRange).c_str());
    this->speedTextTwo->setText(irr::core::stringw(player[1]->getStatistics().speed).c_str());
    this->hearthTextTwo->setText(irr::core::stringw(player[1]->getStatistics().life).c_str());
    this->wallTextTwo->setText(irr::core::stringw(player[1]->getStatistics().wallPass).c_str());
    this->bombTextTwo->setOverrideFont(this->_font);
    this->flameTextTwo->setOverrideFont(this->_font);
    this->speedTextTwo->setOverrideFont(this->_font);
    this->hearthTextTwo->setOverrideFont(this->_font);
    txtHUDPlayerThree(this->_font, manager, player);
}

void HUD::refreshHUD(std::shared_ptr<BManager> manager, std::vector<Player *> player, irr::gui::IGUIFont *_font)
{
    this->bombTextOne->setText(irr::core::stringw(player[0]->getStatistics().bombNumber).c_str());
    this->flameTextOne->setText(irr::core::stringw(player[0]->getStatistics().bombRange).c_str());
    this->speedTextOne->setText(irr::core::stringw(player[0]->getStatistics().speed).c_str());
    this->hearthTextOne->setText(irr::core::stringw(player[0]->getStatistics().life).c_str());
    this->wallTextOne->setText(irr::core::stringw(player[0]->getStatistics().wallPass).c_str());
    this->bombTextOne->setOverrideFont(this->_font);
    this->flameTextOne->setOverrideFont(this->_font);
    this->speedTextOne->setOverrideFont(this->_font);
    this->hearthTextOne->setOverrideFont(this->_font);
    this->wallTextOne->setOverrideFont(this->_font);
    txtHUDPlayerTwo(this->_font, manager, player);
}

irr::video::ITexture* HUD::getpictureheadOne()
{
    return (this->_headPicOne);
}

irr::video::ITexture* HUD::getpictureheadTwo()
{
    return (this->_headPicTwo);
}

irr::video::ITexture* HUD::getpictureheadThree()
{
    return (this->_headPicThree);
}

irr::video::ITexture* HUD::getpictureheadFour()
{
    return (this->_headPicFour);
}

irr::video::ITexture* HUD::getpictureflame()
{
    return (this->_flamePic);
}

irr::video::ITexture* HUD::getpicturebomb()
{
    return (this->_bombPic);
}

irr::video::ITexture* HUD::getpicturespeed()
{
    return (this->_speedPic);
}

irr::video::ITexture* HUD::getpicturehearth()
{
    return (this->_hearthPic);
}

irr::video::ITexture* HUD::getpicturewall()
{
    return (this->_wallPic);
}

irr::gui::IGUIFont* HUD::getFont()
{
    return (this->_font);
}