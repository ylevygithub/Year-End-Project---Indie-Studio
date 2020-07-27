/*
** EPITECH PROJECT, 2020
** IPowerUp.cpp
** File description:
** IPowerUp
*/

#include "PowerUp.hpp"
#include "IGameObject.hpp"

PowerUp::PowerUp()
{
    this->_objectType = POWER_UP;
}

PowerUp::~PowerUp()
{
    
}

// ICatchEvent::ICatchEvent()
// {
//     for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
//         this->_keyIsPressed[i] = false;
// }

// bool ICatchEvent::OnEvent(const irr::SEvent& event)
// {
//     if (event.EventType == irr::EET_KEY_INPUT_EVENT)
//         this->_keyIsPressed[event.KeyInput.Key] = event.KeyInput.PressedDown;
//     return (false);
// }

// bool ICatchEvent::keyIsPressed(irr::EKEY_CODE keyCode) const
// {
//     return (this->_keyIsPressed[keyCode]);
// }