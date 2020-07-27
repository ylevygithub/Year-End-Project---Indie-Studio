/*
** EPITECH PROJECT, 2020
** game 
** File description:
** game
*/

#pragma once

#ifdef __linux__
    #include <irrlicht/irrlicht.h>
#elif _WIN64
    #include <irrlicht.h>
#endif

#define FRONT 1
#define BACK 2
#define LEFT 4
#define RIGHT 8
#define IDDLE 16

typedef struct key_binding_s {
    irr::EKEY_CODE front;
    irr::EKEY_CODE back;
    irr::EKEY_CODE left;
    irr::EKEY_CODE right;
    irr::EKEY_CODE bomb;
} key_binding_t;

typedef struct statistics_s {
    irr::u8 speed;
    irr::u8 bombRange;
    irr::u8 bombNumber;
    bool wallPass;
    irr::u8 life;
} statistics_t;

typedef struct map_pos_s {
     irr::u16 z;
     irr::u16 x;
} map_pos_t;

typedef enum object_type_e {
    BLOCK,
    POWER_UP,
    PLAYER,
    BOMB
} object_type_e;

typedef enum block_type_e {
    NONE,
    WALL,
    UNBREAKABLE,
    BREAKABLE,
    GROUND,
    BACKGROUND
} block_type_e;

typedef enum powerup_type_e {
    BOMB_UP,
    SPEED_UP,
    FIRE_UP,
    WALL_PASS
} powerup_type_e;