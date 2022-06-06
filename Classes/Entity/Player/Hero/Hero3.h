#pragma once
//���� : ����
//���� : 2022-6-2
#ifndef __HERO3_H__
#define __HERO3_H__

#include "Entity/Player/player.h"
#include "SimpleAudioEngine.h"
#include "Entity/Weapon/Weapon.h"

using namespace cocos2d::ui;
using namespace cocos2d;

/*==============================����������Ҫ�޸ĵĺ궨��=================================*/

//�泯��ʱ �����ĺ���ê��
#define HERO3_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT (0.0f)
//����������ê��
#define HERO3_YOU_WEAPON_ANCHOR_POSITION_Y (0.5f)
//�泯��ʱ �����������ĺ���λ��
#define HERO3_YOU_WEAPON_POSITION_X (0)
//����������������λ��
#define HERO3_YOU_WEAPON_POSITION_Y (this->getContentSize().height * 2 / 3)
//Ѫ��������������������λ��
#define HERO3_YOU_BAR_POSITION (this->getContentSize().height / 2)
//����ʱ����֡��
#define HERO3_YOU_ATTACK_TIME 0.5f
#define HERO3_YOU_ATTACK_FRAME 10
#define HERO3_YOU_SKILL_TIME 1.0f
#define HERO3_YOU_SKILL_FRAME 10

/*==============================����������Ҫ�޸ĵĺ궨��=================================*/

/*==============================!!!!!���º������޸�!!!!!=================================*/
//����ê��
#define HERO3_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT HERO3_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define HERO3_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT 1.0f - HERO3_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define HERO3_WEAPON_ANCHOR_POSITION_Y 1.0f
//����λ��
#define HERO3_WEAPON_POSITION_X (this->getPosition().x + HERO3_YOU_WEAPON_POSITION_X * _direct)
#define HERO3_WEAPON_POSITION_Y (this->getPosition().y + HERO3_YOU_WEAPON_POSITION_Y)
//Ѫ�� ����λ�� this->getContentSize().width / 2
#define HERO3_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO3_YOU_BAR_POSITION + healthBar->getContentSize().height / 2)
#define HERO3_MAGICBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO3_YOU_BAR_POSITION)
//Ѫ�����ٷֱȼ���
#define HERO3_BLOOD_PERCENT int(100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint()))
#define HERO3_MAGIC_PERCENT int(100 * float(_panel.getMagicPoint()) / float(_panel.getMaxMagicPoint()))
//�ȼ�λ��
#define HERO3_LEVELTEXT_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO3_YOU_BAR_POSITION + bar->getContentSize().height)
//��ʼ���
#define HERO3_INIT_MAXHEALTHPOINT 800
#define HERO3_INIT_ATTACK 200
#define HERO3_INIT_DEFENCE 50
#define HERO3_INIT_SKILLRATE 3.0f
#define HERO3_INIT_ATTACKRATE 0.9f

/*==============================!!!!!���Ϻ������޸�!!!!!=================================*/
class Hero1;
class Hero2;
class Hero4;
//class Weapon;
class Hero3 : public Player
{
public:
	float _direct = 1.0f;//��ʾ����

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
