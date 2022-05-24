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

#define PLAYER_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + this->getContentSize().height / 2 + healthBar->getContentSize().height / 2)
#define PLAYER_MAGICBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + this->getContentSize().height / 2)

#define PLAYER_BLOOD_PERCENT 100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint())
#define PLAYER_MAGIC_PERCENT 100 * float(_panel.getMagicPoint()) / float(_panel.getMaxMagicPoint())

class Player : public Entity
{
private:
    float _weaponAnchorPositionX = PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT;
    float _weaponAnchorPositionY = PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT;
public:
    Panel _panel;
    //Slider* _healthBar;
    //Slider* _magicBar;

    static Player* create(const std::string& filename);
    virtual void initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate);
    virtual void initPlayer(Panel& panel);
    Panel* getPanel();

    virtual void launchAnAttack(Weapon* weapon, const std::string& attackType);
    int hitPlayer(int attack);

    void restoreMagic();
    bool magicIsFull()const;
    bool useMagic();

    virtual void keepWeapon(Weapon* weapon);
    virtual void runFlipxWithWeapon(bool flipx,Weapon* weapon);

    virtual void keepHealthBar(Slider* healthBar);
    virtual void keepMagicBar(Slider* magicBar);

    int getHealthPercent();
    int getMagicPercent();

    void setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon, Slider* healthBar, Slider* magicBar);
    void refreshHealthBar(Slider* healthBar);
    void refreshMagicBar(Slider* magicBar);
    void refreshPlayer();
};

#endif
