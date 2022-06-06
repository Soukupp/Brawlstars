#pragma once
//���� : ����
//���� : 2022-6-2
#ifndef __HERO4_H__
#define __HERO4_H__

#include "Entity/Player/player.h"
#include "Entity/Weapon/Weapon.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d::ui;
using namespace cocos2d;

/*==============================����������Ҫ�޸ĵĺ궨��=================================*/

//�泯��ʱ �����ĺ���ê��
#define HERO4_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT (0.0f)
//����������ê��
#define HERO4_YOU_WEAPON_ANCHOR_POSITION_Y (0.5f)
//�泯��ʱ �����������ĺ���λ��
#define HERO4_YOU_WEAPON_POSITION_X ( - this->getContentSize().width / 2)
//����������������λ��
#define HERO4_YOU_WEAPON_POSITION_Y (this->getContentSize().height * 2 / 3)
//Ѫ��������������������λ��
#define HERO4_YOU_BAR_POSITION (this->getContentSize().height / 2)

/*==============================����������Ҫ�޸ĵĺ궨��=================================*/

/*==============================!!!!!���º������޸�!!!!!=================================*/
//����ê��
#define HERO4_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT HERO4_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define HERO4_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT 1.0f - HERO4_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define HERO4_WEAPON_ANCHOR_POSITION_Y 1.0f
//����λ��
#define HERO4_WEAPON_POSITION_X (this->getPosition().x + HERO4_YOU_WEAPON_POSITION_X * _direct)
#define HERO4_WEAPON_POSITION_Y (this->getPosition().y + HERO4_YOU_WEAPON_POSITION_Y)
//Ѫ�� ����λ�� this->getContentSize().width / 2
#define HERO4_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO4_YOU_BAR_POSITION + healthBar->getContentSize().height / 2)
#define HERO4_MAGICBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO4_YOU_BAR_POSITION)
//Ѫ�����ٷֱȼ���
#define HERO4_BLOOD_PERCENT int(100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint()))
#define HERO4_MAGIC_PERCENT int(100 * float(_panel.getMagicPoint()) / float(_panel.getMaxMagicPoint()))
//�ȼ�λ��
#define HERO4_LEVELTEXT_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO4_YOU_BAR_POSITION + bar->getContentSize().height)
//��ʼ���
#define HERO4_INIT_MAXHEALTHPOINT 1000
#define HERO4_INIT_ATTACK 150
#define HERO4_INIT_DEFENCE 150
#define HERO4_INIT_SKILLRATE 2.5f
#define HERO4_INIT_ATTACKRATE 1.0f
//����ʱ����֡��
#define HERO4_YOU_ATTACK_TIME 0.5f
#define HERO4_YOU_ATTACK_FRAME 10
#define HERO4_YOU_SKILL_TIME 1.0f
#define HERO4_YOU_SKILL_FRAME 10

/*==============================!!!!!���Ϻ������޸�!!!!!=================================*/
class Hero1;
class Hero2;
class Hero3;
//class Weapon;
class Hero4 : public Player
{
public:
	float _direct = 1.0f;//��ʾ����

	float _weaponAnchorPositionX = HERO4_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT;
	float _weaponAnchorPositionY = HERO4_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT;

	static Hero4* create(const std::string& filename);
	static Hero4* create(const std::string& filename, const Rect& rect);

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

	const int _width = 26;
	const int _height = 44;
	int getID();

private:
	int ID = 4;
};

#endif
