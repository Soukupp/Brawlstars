#pragma once
//作者 : 王鹏
//日期 : 2022-6-7
#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Entity/Player/Hero/Hero1.h"
#include "Entity/Player/Hero/Hero2.h"
#include "Entity/Player/Hero/Hero3.h"
#include "Entity/Player/Hero/Hero4.h"
#include "Entity/Weapon/Weapon.h"
//#include "Entity/Monster/Monster.h"

struct Character
{
    Player* _player;
    Weapon* _weapon;
    Slider* _healthBar;
    Slider* _magicBar;
    cocos2d::Label* _levelText;

    int _killedNum = 0;

    int _direct = 0;
    bool _backDirectChanged = 0;
    int _searchTimes = 0;

    bool _ifOpenUpdate = false;
    bool _isCollidedByPlayer= false;

};

#endif

