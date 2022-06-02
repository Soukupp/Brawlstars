#pragma once
//���� : ����
//���� : 2022-5-18
#ifndef __HERO1_H__
#define __HERO1_H__

#include "Entity/Player/player.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d::ui;
using namespace cocos2d;

/*==============================����������Ҫ�޸ĵĺ궨��=================================*/

//�泯��ʱ �����ĺ���ê��
#define HERO1_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT (0.0f)
//����������ê��
#define HERO1_YOU_WEAPON_ANCHOR_POSITION_Y (0.5f)
//�泯��ʱ �����������ĺ���λ��
#define HERO1_YOU_WEAPON_POSITION_X ( - this->getContentSize().width / 2)
//����������������λ��
#define HERO1_YOU_WEAPON_POSITION_Y (this->getContentSize().height * 2 / 3)
//Ѫ��������������������λ��
#define HERO1_YOU_BAR_POSITION (this->getContentSize().height / 2)
//����ʱ����֡��
#define HERO1_YOU_ATTACK_TIME 0.2f
#define HERO1_YOU_ATTACK_FRAME 7
#define HERO1_YOU_SKILL_TIME 1.5f
#define HERO1_YOU_SKILL_FRAME 18

/*==============================����������Ҫ�޸ĵĺ궨��=================================*/

/*==============================!!!!!���º������޸�!!!!!=================================*/
//����ê��
#define HERO1_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT HERO1_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define HERO1_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT 1.0f - HERO1_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define HERO1_WEAPON_ANCHOR_POSITION_Y 1.0f
//����λ��
#define HERO1_WEAPON_POSITION_X (this->getPosition().x + HERO1_YOU_WEAPON_POSITION_X * _direct)
#define HERO1_WEAPON_POSITION_Y (this->getPosition().y + HERO1_YOU_WEAPON_POSITION_Y)
//Ѫ�� ����λ�� this->getContentSize().width / 2
#define HERO1_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO1_YOU_BAR_POSITION + healthBar->getContentSize().height / 2)
#define HERO1_MAGICBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO1_YOU_BAR_POSITION)
//Ѫ�����ٷֱȼ���
#define HERO1_BLOOD_PERCENT int(100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint()))
#define HERO1_MAGIC_PERCENT int(100 * float(_panel.getMagicPoint()) / float(_panel.getMaxMagicPoint()))
//�ȼ�λ��
#define HERO1_LEVELTEXT_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO1_YOU_BAR_POSITION + bar->getContentSize().height)
//��ʼ���
#define HERO1_INIT_MAXHEALTHPOINT 950
#define HERO1_INIT_ATTACK 160
#define HERO1_INIT_DEFENCE 100
#define HERO1_INIT_SKILLRATE 2.3f
#define HERO1_INIT_ATTACKRATE 1.2f

/*==============================!!!!!���Ϻ������޸�!!!!!=================================*/

class Hero1 : public Player
{
public:
	float _direct = 1.0f;//��ʾ����

	float _weaponAnchorPositionX = HERO1_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT;
	float _weaponAnchorPositionY = HERO1_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT;

	static Hero1* create(const std::string& filename);
	static Hero1* create(const std::string& filename, const Rect& rect);

	void initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate);
	void initPlayer();

	void launchAnAttack(Weapon* weapon, const std::string& attackType, Slider* magicBar);

	void keepHealthBar(Slider* healthBar);
	void keepMagicBar(Slider* magicBar);
	void keepWeapon(Weapon* weapon);
	void keepLevelText(cocos2d::Label* levelText, Slider* bar);

	void runFlipxWithWeapon(bool flipx, Weapon* weapon);
	void setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon, Slider* healthBar, Slider* magicBar, cocos2d::Label* levelText);

	void upgrade(cocos2d::Label* levelText, Slider* bar);
};

#endif
