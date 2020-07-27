/*
** EPITECH PROJECT, 2020
** IGameObject.hpp
** File description:
** IGameObject
*/

#pragma once

#ifdef __linux__
    #include <irrlicht/irrlicht.h>
#elif _WIN64
    #include <irrlicht.h>
#endif


#include "structures.h"

class IGameObject
{
    public:
        IGameObject(){};
        virtual ~IGameObject(){};
        virtual bool update() = 0;
        virtual void draw() = 0;
        // virtual void setPos(irr::core::vector3df vector) = 0;
        virtual irr::core::vector3df getPos(void) = 0;
        virtual object_type_e getObjectType() = 0;
};