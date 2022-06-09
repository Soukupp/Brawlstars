#pragma once
//作者 : 王鹏
//日期 : 2022-5-18
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Entity/Entity.h"
#include "Panel.h"
#include "Entity/Define/Definitions.h"


//#include "HealthBar.h"

using namespace cocos2d::ui;

/**
#define PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT 0.0f
#define PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT 1.0f
#define PLAYER_WEAPON_ANCHOR_POSITION_Y 1.0f

#define PLAYER_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + this->getContentSize().height / 2 + healthBar->getContentSize().height / 2)
#define PLAYER_MAGICBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + this->getContentSize().height / 2)

#define PLAYER_BLOOD_PERCENT 100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint())
#define PLAYER_MAGIC_PERCENT 100 * float(_panel.getMagicPoint()) / float(_panel.getMaxMagicPoint())
/**/

/*==============================以下是你需要修改的宏定义=================================*/

//面朝右时 武器的横向锚点
#define PLAYER_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT (0.0f)
//武器的纵向锚点
#define PLAYER_YOU_WEAPON_ANCHOR_POSITION_Y (1.0f)
//面朝右时 武器相对人物的横向位置
#define PLAYER_YOU_WEAPON_POSITION_X (this->getContentSize().width / 2)
//武器相对人物的纵向位置
#define PLAYER_YOU_WEAPON_POSITION_Y (this->getContentSize().height/3)
//血条、蓝条相对人物的纵向位置
#define PLAYER_YOU_BAR_POSITION (this->getContentSize().height / 2)

/*==============================以上是你需要修改的宏定义=================================*/

/*==============================!!!!!以下宏请勿修改!!!!!=================================*/
//武器锚点
#define PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT PLAYER_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT 1.0f - PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define PLAYER_WEAPON_ANCHOR_POSITION_Y 1.0f
//武器位置
#define PLAYER_WEAPON_POSITION_X (this->getPosition().x + PLAYER_YOU_WEAPON_POSITION_X * _direct)
#define PLAYER_WEAPON_POSITION_Y (this->getPosition().y + PLAYER_YOU_WEAPON_POSITION_Y)
//血条 蓝条位置 this->getContentSize().width / 2
#define PLAYER_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + PLAYER_YOU_BAR_POSITION + healthBar->getContentSize().height / 2)
#define PLAYER_MAGICBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + PLAYER_YOU_BAR_POSITION)
//血、蓝百分比计算
#define PLAYER_BLOOD_PERCENT int(100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint()))
#define PLAYER_MAGIC_PERCENT int(100 * float(_panel.getMagicPoint()) / float(_panel.getMaxMagicPoint()))
//等级位置
#define PLAYER_LEVELTEXT_POSITION Vec2(this->getPosition().x, this->getPosition().y + PLAYER_YOU_BAR_POSITION + bar->getContentSize().height)
//最高等级
#define PLAYER_MAX_GRADE 10
/*==============================!!!!!以上宏请勿修改!!!!!=================================*/
class Weapon;
class Player : public Entity
{
private:
    float _weaponAnchorPositionX = PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT;
    float _weaponAnchorPositionY = PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT;
public:
    Panel _panel;
    
    float _direct = 1.0f;//表示方向
    int _level = 0;

    static Player* create(const std::string& filename);
    virtual void initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate);
    virtual void initPlayer(Panel& panel);
    Panel* getPanel();

    virtual void launchAnAttack(Weapon* weapon, const std::string& attackType, Slider* magicBar, Player* enemy, Slider* enemyHealthBar);
    
    int hitPlayer(int attack);
    void restoreMagic();
    bool magicIsFull()const;
    bool useMagic();
    int getHealthPercent();
    int getMagicPercent();

    virtual void keepWeapon(Weapon* weapon);
    virtual void keepHealthBar(Slider* healthBar);
    virtual void keepMagicBar(Slider* magicBar);
    virtual void keepLevelText(cocos2d::Label* levelText, Slider* bar);

    virtual void runFlipxWithWeapon(bool flipx, Weapon* weapon);

    virtual void setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon, Slider* healthBar, Slider* magicBar,cocos2d::Label* levelText);

    void refreshHealthBar(Slider* healthBar);
    void refreshMagicBar(Slider* magicBar);
    void refreshPlayer();

    virtual bool playerCollisionTest1(Player* target, Weapon* weapon);
    virtual bool playerCollisionTest2(Player* target, Weapon* weapon);

    virtual void upgrade(cocos2d::Label* levelText, Slider* bar);


    virtual bool initWalkAction();
    virtual bool initNormalAction();
    virtual bool initAttackAction();
    virtual bool initSkillAction();

    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _walkAction, WalkAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _normalAction, NormalAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _attackAction, AttackAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _skillAction, SkillAction);
    const int _width = 26;
    const int _height = 44;

    virtual int getID();

private:
    int ID = 0;
};

#endif
