#pragma once
//作者 : 王鹏
//日期 : 2022-6-8
#ifndef __THEMONSTER_H__
#define __THEMONSTER_H__

#include "Entity/Monster/Monster.h"
#include "Entity/Monster/Monsters/DesertMonster.h"
#include "Entity/Monster/Monsters/GroundMonster.h"
#include "Entity/Monster/Monsters/WaterMonster.h"
#include "Entity/Weapon/Weapon.h"
//#include "Entity/Monster/Monster.h"

struct TheMonster
{
    Monster* _monster;
    Slider* _healthBar;
    bool _isCollidedByPlayer = false;
};

#endif

