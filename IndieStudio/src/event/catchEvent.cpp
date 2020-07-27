/*
** EPITECH PROJECT, 2020
** catch event
** File description:
** catch event
*/

#include "catchEvent.hpp"

ICatchEvent::ICatchEvent()
{
    for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
        this->_keyIsPressed[i] = false;
}

bool ICatchEvent::OnEvent(const irr::SEvent& event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        this->_keyIsPressed[event.KeyInput.Key] = event.KeyInput.PressedDown;
    return (false);
}

bool ICatchEvent::keyIsPressed(irr::EKEY_CODE keyCode) const
{
    return (this->_keyIsPressed[keyCode]);
}