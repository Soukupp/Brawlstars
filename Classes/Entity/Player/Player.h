#pragma once
//作者 : 王鹏
//日期 : 2022-5-18
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Entity/Entity.h"
#include "Panel.h"
#include "Entity/Weapon/Weapon.h"
#include "../ui/UISlider.h"
//#include "HealthBar.h"

using namespace cocos2d::ui;

#define PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT 0.0f
#define PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT 1.0f
#define PLAYER_WEAPON_ANCHOR_POSITION_Y 1.0f
#define PLAYER_HEALTHBAR_POSITION Vec2(this->getContentSize().width / 2, this->getContentSize().height * 4 / 5)

#define PLAYER_BLOOD_PERCENT 100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint())

class Player : public Entity
{
public:
    Panel _panel;
    Slider* _healthBar;

    static Player* create(const std::string& filename);
    //static Player* createWithObject(ValueMap valueMap);
    void initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate);
    void initPlayer(Panel& panel);
    Panel* getPanel();

    void launchAnAttack(Weapon* weapon, const std::string& attackType);
    int hitPlayer(int attack);

    void keepWeapon(Weapon* weapon);
    void runFlipxWithWeapon(bool flipx,Weapon* weapon);
    void setPositionWithWeapon(cocos2d::Vec2& position, Weapon* weapon);

    void keepHealthBar();

    void setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon);
    void refreshHealthBar();
    void refreshPlayer();
};

#endif
