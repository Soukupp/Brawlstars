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

    int killedNum = 0;

    int direct = 0;//需要保存原方向 所以static
    bool backDirectChanged = 0;
    int searchTimes = 0;

    bool ifOpenUpdate = false;
    bool isCollidedByPlayer= false;

};

#endif

