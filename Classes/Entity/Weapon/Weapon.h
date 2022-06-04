#pragma once
//���� : ����
//���� : 2022-5-20
#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "cocos2d.h"
#include "Entity/Entity.h"
/**
#include "Entity/Player/Hero/Hero1.h"
#include "Entity/Player/Hero/Hero2.h"
#include "Entity/Player/Hero/Hero3.h"
#include "Entity/Player/Hero/Hero4.h"
/**/
using namespace cocos2d;
using namespace cocos2d::ui;

class Player;
class Hero1;
class Hero2;
class Hero3;
class Hero4;
class Weapon : public Entity
{
public:
    static Weapon* create(const std::string& filename);
    Weapon* getWeapon();

    void createWeaponPhysicsBody();
    
    //template<typename Enemy>
    int launchAnAttack(int attack, Player* enemy);
};

#endif