/*
** EPITECH PROJECT, 2020
** HUD.hpp
** File description:
** HUD
*/

#ifndef __HUD__
#define __HUD__

#ifdef __linux__
    #include <irrlicht/irrlicht.h>
#elif _WIN64
    #include <irrlicht.h>
#endif

#include <vector>
#include <memory>

class BManager;
class Player;

class HUD {
    public:
        HUD(std::vector<Player *> player);
        ~HUD();
        irr::video::ITexture* getpictureheadOne();
        irr::video::ITexture* getpictureheadTwo();
        irr::video::ITexture* getpictureheadThree();
        irr::video::ITexture* getpictureheadFour();
        irr::video::ITexture* getpicturebomb();
        irr::video::ITexture* getpicturespeed();
        irr::video::ITexture* getpictureflame();
        irr::video::ITexture* getpicturehearth();
        irr::video::ITexture* getpicturewall();
        irr::gui::IGUIFont * getFont();
        void txtHUDPlayerTwo(irr::gui::IGUIFont *font, std::shared_ptr<BManager> manager, std::vector<Player *> player);
        void txtHUDPlayerThree(irr::gui::IGUIFont *font, std::shared_ptr<BManager> manager, std::vector<Player *> player);
        void txtHUDPlayerFour(irr::gui::IGUIFont *font, std::shared_ptr<BManager> manager, std::vector<Player *> player);
        void setTexture(std::shared_ptr<BManager> manager);
        void refreshHUD(std::shared_ptr<BManager> manager, std::vector<Player *>, irr::gui::IGUIFont *font);
    private:
        std::vector<Player *> _player;
        irr::video::ITexture* _headPicOne;
        irr::video::ITexture* _headPicTwo;
        irr::video::ITexture* _headPicThree;
        irr::video::ITexture* _headPicFour;
        irr::video::ITexture* _speedPic;
        irr::video::ITexture* _bombPic;
        irr::video::ITexture* _flamePic;
        irr::video::ITexture* _hearthPic;
        irr::video::ITexture* _wallPic;
        irr::gui::IGUIStaticText *bombTextOne;
        irr::gui::IGUIStaticText *flameTextOne;
        irr::gui::IGUIStaticText *speedTextOne;
        irr::gui::IGUIStaticText *hearthTextOne;
        irr::gui::IGUIStaticText *wallTextOne;
        irr::gui::IGUIStaticText *bombTextTwo;
        irr::gui::IGUIStaticText *flameTextTwo;
        irr::gui::IGUIStaticText *speedTextTwo;
        irr::gui::IGUIStaticText *hearthTextTwo;
        irr::gui::IGUIStaticText *wallTextTwo;
        irr::gui::IGUIStaticText *bombTextThree;
        irr::gui::IGUIStaticText *flameTextThree;
        irr::gui::IGUIStaticText *speedTextThree;
        irr::gui::IGUIStaticText *hearthTextThree;
        irr::gui::IGUIStaticText *wallTextThree;
        irr::gui::IGUIStaticText *bombTextFour;
        irr::gui::IGUIStaticText *flameTextFour;
        irr::gui::IGUIStaticText *speedTextFour;
        irr::gui::IGUIStaticText *hearthTextFour;
        irr::gui::IGUIStaticText *wallTextFour;
        irr::gui::IGUIFont *_font;
};
#endif