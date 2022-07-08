#pragma once
//作者 : 王鹏
//日期 : 2022-6-2
#ifndef __HERO4_H__
#define __HERO4_H__

#include "Entity/Player/player.h"
#include "Entity/Weapon/Weapon.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d::ui;
using namespace cocos2d;

/*==============================以下是你需要修改的宏定义=================================*/

//面朝右时 武器的横向锚点
#define HERO4_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT (0.0f)
//武器的纵向锚点
#define HERO4_YOU_WEAPON_ANCHOR_POSITION_Y (0.5f)
//面朝右时 武器相对人物的横向位置
#define HERO4_YOU_WEAPON_POSITION_X ( - this->getContentSize().width / 2)
//武器相对人物的纵向位置
#define HERO4_YOU_WEAPON_POSITION_Y (this->getContentSize().height * 2 / 3)
//血条、蓝条相对人物的纵向位置
#define HERO4_YOU_BAR_POSITION (this->getContentSize().height / 2)
//动画时长、帧数
#define HERO4_YOU_ATTACK_TIME 0.5f
#define HERO4_YOU_ATTACK_FRAME 10
#define HERO4_YOU_SKILL_TIME 1.0f
#define HERO4_YOU_SKILL_FRAME 10
/*==============================以上是你需要修改的宏定义=================================*/

/*==============================!!!!!以下宏请勿修改!!!!!=================================*/
//武器锚点
#define HERO4_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT HERO4_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define HERO4_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT 1.0f - HERO4_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define HERO4_WEAPON_ANCHOR_POSITION_Y 1.0f
//武器位置
#define HERO4_WEAPON_POSITION_X (this->getPosition().x + HERO4_YOU_WEAPON_POSITION_X * _direct)
#define HERO4_WEAPON_POSITION_Y (this->getPosition().y + HERO4_YOU_WEAPON_POSITION_Y)
//血条 蓝条位置 this->getContentSize().width / 2
#define HERO4_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO4_YOU_BAR_POSITION + healthBar->getContentSize().height / 2)
#define HERO4_MAGICBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO4_YOU_BAR_POSITION)
//血、蓝百分比计算
#define HERO4_BLOOD_PERCENT static_cast<int>(100 * static_cast<float>(_panel.getHealthPoint()) / static_cast<float>(_panel.getMaxHealthPoint()))
#define HERO4_MAGIC_PERCENT static_cast<int>(100 * static_cast<float>(_panel.getMagicPoint()) / static_cast<float>(_panel.getMaxMagicPoint()))
//等级位置
#define HERO4_LEVELTEXT_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO4_YOU_BAR_POSITION + bar->getContentSize().height)
//初始面板
#define HERO4_INIT_MAXHEALTHPOINT 1000
#define HERO4_INIT_ATTACK 150
#define HERO4_INIT_DEFENCE 150
#define HERO4_INIT_SKILLRATE 2.5f
#define HERO4_INIT_ATTACKRATE 1.0f

/*==============================!!!!!以上宏请勿修改!!!!!=================================*/
class Hero1;
class Hero2;
class Hero3;
class Tools;
class Hero4 : public Player
{
public:
	const int _width = 26;
	const int _height = 44;

	float _weaponAnchorPositionX = HERO4_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT;
	float _weaponAnchorPositionY = HERO4_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT;

	static Hero4* create(const std::string& filename);
	static Hero4* create(const std::string& filename, const Rect& rect);

	void initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate);
	void initPlayer();

	void keepHealthBar(Slider* healthBar);
	void keepMagicBar(Slider* magicBar);
	void keepWeapon(Weapon* weapon);
	void keepLevelText(cocos2d::Label* levelText, Slider* bar);

	void runFlipxWithWeapon(bool flipx, Weapon* weapon);
	void setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon, Slider* healthBar, Slider* magicBar, cocos2d::Label* levelText);

	void upgrade(cocos2d::Label* levelText, Slider* bar);

	bool initWalkAction();
	bool initAttackAction();
	bool initNormalAction();
	bool initSkillAction();

	bool playerCollisionTest(Player* target, Weapon* weapon, bool ifPlayEffect);

	int getID();

	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _walkAction, WalkAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _normalAction, NormalAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _attackAction, AttackAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _skillAction, SkillAction);

private:
	int _ID = 4;

	float _targetX;//目标位置X
	float _targetY;//目标位置Y

	float _thisX;
	float _thisY;
};

#endif
