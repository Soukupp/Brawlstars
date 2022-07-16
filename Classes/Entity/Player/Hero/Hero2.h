#pragma once
//作者 : 王鹏
//日期 : 2022-5-18
#ifndef __HERO2_H__
#define __HERO2_H__

#include "Entity/Player/player.h"
#include "SimpleAudioEngine.h"
#include "Entity/Weapon/Weapon.h"
using namespace cocos2d::ui;
using namespace cocos2d;

/*==============================以下是你需要修改的宏定义=================================*/

//面朝右时 武器的横向锚点
#define HERO2_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT (0.0f)
//武器的纵向锚点
#define HERO2_YOU_WEAPON_ANCHOR_POSITION_Y (0.5f)
//面朝右时 武器相对人物的横向位置
#define HERO2_YOU_WEAPON_POSITION_X ( - this->getContentSize().width / 2)
//武器相对人物的纵向位置
#define HERO2_YOU_WEAPON_POSITION_Y (this->getContentSize().height * 2 / 3)
//血条、蓝条相对人物的纵向位置
#define HERO2_YOU_BAR_POSITION (this->getContentSize().height / 2)
//动画时长、帧数
#define HERO2_YOU_ATTACK_TIME 0.3f
#define HERO2_YOU_ATTACK_FRAME 20
#define HERO2_YOU_SKILL_TIME 1.0f
#define HERO2_YOU_SKILL_FRAME 7

/*==============================以上是你需要修改的宏定义=================================*/

/*==============================!!!!!以下宏请勿修改!!!!!=================================*/
//武器锚点
#define HERO2_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT HERO2_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define HERO2_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT 1.0f - HERO2_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define HERO2_WEAPON_ANCHOR_POSITION_Y 1.0f
//武器位置
#define HERO2_WEAPON_POSITION_X (this->getPosition().x + HERO2_YOU_WEAPON_POSITION_X * _direct)
#define HERO2_WEAPON_POSITION_Y (this->getPosition().y + HERO2_YOU_WEAPON_POSITION_Y)
//血条 蓝条位置 this->getContentSize().width / 2
#define HERO2_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO2_YOU_BAR_POSITION + healthBar->getContentSize().height / 2)
#define HERO2_MAGICBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO2_YOU_BAR_POSITION)
//血、蓝百分比计算
#define HERO2_BLOOD_PERCENT static_cast<int>(100 * static_cast<float>(_panel.getHealthPoint()) / static_cast<float>(_panel.getMaxHealthPoint()))
#define HERO2_MAGIC_PERCENT static_cast<int>(100 * static_cast<float>(_panel.getMagicPoint()) / static_cast<float>(_panel.getMaxMagicPoint()))
//等级位置
#define HERO2_LEVELTEXT_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO2_YOU_BAR_POSITION + bar->getContentSize().height)
//初始面板
#define HERO2_INIT_MAXHEALTHPOINT 1050
#define HERO2_INIT_ATTACK 140
#define HERO2_INIT_DEFENCE 150
#define HERO2_INIT_SKILLRATE 2.7f
#define HERO2_INIT_ATTACKRATE 1.2f

/*==============================!!!!!以上宏请勿修改!!!!!=================================*/
class Hero1;
class Hero3;
class Hero4;
class Tools;
class Hero2 : public Player
{
public:
	const int _width = 26;
	const int _height = 44;
	float _weaponAnchorPositionX = HERO2_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT;
	float _weaponAnchorPositionY = HERO2_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT;

	static Hero2* create(const std::string& filename);	
	static Hero2* create(const std::string& filename, const Rect& rect);

	void initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate);
	void initPlayer();

	void keepHealthBar(Slider* healthBar);
	void keepMagicBar(Slider* magicBar);
	void keepWeapon(Weapon* weapon);
	void keepLevelText(cocos2d::Label* levelText, Slider* bar);

	void runFlipxWithWeapon(bool flipx, Weapon* weapon);
  
	//CC_SYTHESIZE_RETAIN相当于同时得到getxxxAction和setxxxAction两个函数
	//在hero1~hero4中都需要添加
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _walkAction, WalkAction);       
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _normalAction, NormalAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _attackAction, AttackAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _skillAction, SkillAction);

	bool initWalkAction();
	bool initNormalAction();
	bool initAttackAction();
	bool initSkillAction();

	void setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon, Slider* healthBar, Slider* magicBar, cocos2d::Label* levelText);

	void upgrade(cocos2d::Label* levelText, Slider* bar);

	bool playerCollisionTest(Player* target, Weapon* weapon, bool ifPlayEffect);

	int getID();

private:
	int _ID = 2;

	float _targetX;//目标位置X
	float _targetY;//目标位置Y

	float _thisX;
	float _thisY;
};

#endif
