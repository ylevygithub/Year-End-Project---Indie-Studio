/*
** EPITECH PROJECT, 2020
** catchEvent
** File description:
** catchEvent
*/


#ifndef __EVENT__
#define __EVENT__

#ifdef __linux__
    #include <irrlicht/irrlicht.h>
#elif _WIN64
    #include <irrlicht.h>
#endif


class ICatchEvent : public irr::IEventReceiver {
    public:
        virtual bool OnEvent(const irr::SEvent& event);
        virtual bool keyIsPressed(irr::EKEY_CODE keyCode) const;
        ICatchEvent();
    private:
        bool _keyIsPressed[irr::KEY_KEY_CODES_COUNT];
};

#endif