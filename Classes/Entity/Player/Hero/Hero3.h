#pragma once
//作者 : 王鹏
//日期 : 2022-6-2
#ifndef __HERO3_H__
#define __HERO3_H__

#include "Entity/Player/player.h"
#include "SimpleAudioEngine.h"
#include "Entity/Weapon/Weapon.h"

using namespace cocos2d::ui;
using namespace cocos2d;

/*==============================以下是你需要修改的宏定义=================================*/

//面朝右时 武器的横向锚点
#define HERO3_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT (0.0f)
//武器的纵向锚点
#define HERO3_YOU_WEAPON_ANCHOR_POSITION_Y (0.5f)
//面朝右时 武器相对人物的横向位置
#define HERO3_YOU_WEAPON_POSITION_X (0)
//武器相对人物的纵向位置
#define HERO3_YOU_WEAPON_POSITION_Y (this->getContentSize().height * 2 / 3)
//血条、蓝条相对人物的纵向位置
#define HERO3_YOU_BAR_POSITION (this->getContentSize().height / 2)
//动画时长、帧数
#define HERO3_YOU_ATTACK_TIME 0.5f
#define HERO3_YOU_ATTACK_FRAME 10
#define HERO3_YOU_SKILL_TIME 1.0f
#define HERO3_YOU_SKILL_FRAME 10

/*==============================以上是你需要修改的宏定义=================================*/

/*==============================!!!!!以下宏请勿修改!!!!!=================================*/
//武器锚点
#define HERO3_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT HERO3_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define HERO3_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT 1.0f - HERO3_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define HERO3_WEAPON_ANCHOR_POSITION_Y 1.0f
//武器位置
#define HERO3_WEAPON_POSITION_X (this->getPosition().x + HERO3_YOU_WEAPON_POSITION_X * _direct)
#define HERO3_WEAPON_POSITION_Y (this->getPosition().y + HERO3_YOU_WEAPON_POSITION_Y)
//血条 蓝条位置 this->getContentSize().width / 2
#define HERO3_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO3_YOU_BAR_POSITION + healthBar->getContentSize().height / 2)
#define HERO3_MAGICBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO3_YOU_BAR_POSITION)
//血、蓝百分比计算
#define HERO3_BLOOD_PERCENT int(100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint()))
#define HERO3_MAGIC_PERCENT int(100 * float(_panel.getMagicPoint()) / float(_panel.getMaxMagicPoint()))
//等级位置
#define HERO3_LEVELTEXT_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO3_YOU_BAR_POSITION + bar->getContentSize().height)
//初始面板
#define HERO3_INIT_MAXHEALTHPOINT 800
#define HERO3_INIT_ATTACK 200
#define HERO3_INIT_DEFENCE 50
#define HERO3_INIT_SKILLRATE 3.0f
#define HERO3_INIT_ATTACKRATE 0.9f

/*==============================!!!!!以上宏请勿修改!!!!!=================================*/
class Hero1;
class Hero2;
class Hero4;
//class Weapon;
class Hero3 : public Player
{
public:
	float _direct = 1.0f;//表示方向

	float _weaponAnchorPositionX = HERO3_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT;
	float _weaponAnchorPositionY = HERO3_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT;

	static Hero3* create(const std::string& filename);
	static Hero3* create(const std::string& filename, const Rect& rect);

	void initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate);
	void initPlayer();

	void launchAnAttack(Weapon* weapon, const std::string& attackType, Slider* magicBar, Player* enemy, Slider* enemyHealthBar);

	void keepHealthBar(Slider* healthBar);
	void keepMagicBar(Slider* magicBar);
	void keepWeapon(Weapon* weapon);
	void keepLevelText(cocos2d::Label* levelText, Slider* bar);

	void runFlipxWithWeapon(bool flipx, Weapon* weapon);
	void setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon, Slider* healthBar, Slider* magicBar, cocos2d::Label* levelText);

	void upgrade(cocos2d::Label* levelText, Slider* bar);

	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _walkAction, WalkAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _normalAction, NormalAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _attackAction, AttackAction);

	bool initWalkAction();
	bool initNormalAction();
	bool initAttackAction();

	bool playerCollisionTest1(Player* target, Weapon* weapon);
	const int _width = 26;
	const int _height = 44;

	int getID();
private:
	int ID = 3;
};

#endif
