/*
** EPITECH PROJECT, 2020
** PowerUp.hpp
** File description:
** PowerUp
*/

#pragma once

#ifdef __linux__
    #include <irrlicht/irrlicht.h>
#elif _WIN64
    #include <irrlicht.h>
#endif

#include "IGameObject.hpp"

class PowerUp: public IGameObject
{
    public:
        PowerUp();
        ~PowerUp();
        bool update(){return (0);};
        void draw(){};
        // void setPos(irr::core::vector3df vector);
        // irr::core::vector3df getPos(void){};
        object_type_e getObjectType() {return (this->_objectType);};
    private:
        object_type_e _objectType;
        powerup_type_e _type;
};
