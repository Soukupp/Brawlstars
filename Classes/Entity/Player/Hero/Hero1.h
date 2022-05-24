#pragma once
//作者 : 王鹏
//日期 : 2022-5-18
#ifndef __HERO1_H__
#define __HERO1_H__

#include "Entity/Player/player.h"

using namespace cocos2d::ui;
using namespace cocos2d;

/*==============================以下是你需要修改的宏定义=================================*/

//面朝右时 武器的横向锚点
#define HERO1_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT (0.0f)
//武器的纵向锚点
#define HERO1_YOU_WEAPON_ANCHOR_POSITION_Y (1.0f)
//面朝右时 武器相对人物的横向位置
#define HERO1_YOU_WEAPON_POSITION_X (this->getContentSize().width / 2)
//武器相对人物的纵向位置
#define HERO1_YOU_WEAPON_POSITION_Y (this->getContentSize().height/3)
//血条、蓝条相对人物的纵向位置
#define HERO1_YOU_BAR_POSITION (this->getContentSize().height / 2)

/*==============================以上是你需要修改的宏定义=================================*/

/*==============================!!!!!以下宏请勿修改!!!!!=================================*/
//武器锚点
#define HERO1_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT HERO1_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define HERO1_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT 1.0f - HERO1_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define HERO1_WEAPON_ANCHOR_POSITION_Y 1.0f
//武器位置
#define HERO1_WEAPON_POSITION_X (this->getPosition().x + HERO1_YOU_WEAPON_POSITION_X * _direct)
#define HERO1_WEAPON_POSITION_Y (this->getPosition().y + HERO1_YOU_WEAPON_POSITION_Y)
//血条 蓝条位置 this->getContentSize().width / 2
#define HERO1_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO1_YOU_BAR_POSITION + healthBar->getContentSize().height / 2)
#define HERO1_MAGICBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO1_YOU_BAR_POSITION)
//血、蓝百分比计算
#define HERO1_BLOOD_PERCENT int(100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint()))
#define HERO1_MAGIC_PERCENT int(100 * float(_panel.getMagicPoint()) / float(_panel.getMaxMagicPoint()))
//素材
#define HERO1_PNG_X (351.0f/7.0f)
#define HERO1_PNG_Y (592.0f/16.0f)

/*==============================!!!!!以上宏请勿修改!!!!!=================================*/

class Hero1 : public Player
{
public:
	float _direct = 1.0f;//表示方向

	float _weaponAnchorPositionX = HERO1_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT;
	float _weaponAnchorPositionY = HERO1_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT;

	static Hero1* create(const std::string& filename);
	static Hero1* create(const std::string& filename, const Rect& rect);

	void initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate);

	void launchAnAttack(Weapon* weapon, const std::string& attackType);

	void keepHealthBar(Slider* healthBar);
	void keepMagicBar(Slider* magicBar);

	void keepWeapon(Weapon* weapon);
	void runFlipxWithWeapon(bool flipx, Weapon* weapon);
};

#endif
