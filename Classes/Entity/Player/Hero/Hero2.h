#pragma once
//���� : ����
//���� : 2022-5-18
#ifndef __HERO2_H__
#define __HERO2_H__

#include "Entity/Player/player.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d::ui;
using namespace cocos2d;

/*==============================����������Ҫ�޸ĵĺ궨��=================================*/

//�泯��ʱ �����ĺ���ê��
#define HERO2_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT (0.0f)
//����������ê��
#define HERO2_YOU_WEAPON_ANCHOR_POSITION_Y (0.5f)
//�泯��ʱ �����������ĺ���λ��
#define HERO2_YOU_WEAPON_POSITION_X ( - this->getContentSize().width / 2)
//����������������λ��
#define HERO2_YOU_WEAPON_POSITION_Y (this->getContentSize().height * 2 / 3)
//Ѫ��������������������λ��
#define HERO2_YOU_BAR_POSITION (this->getContentSize().height / 2)

/*==============================����������Ҫ�޸ĵĺ궨��=================================*/

/*==============================!!!!!���º������޸�!!!!!=================================*/
//����ê��
#define HERO2_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT HERO2_YOU_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define HERO2_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT 1.0f - HERO2_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT
#define HERO2_WEAPON_ANCHOR_POSITION_Y 1.0f
//����λ��
#define HERO2_WEAPON_POSITION_X (this->getPosition().x + HERO2_YOU_WEAPON_POSITION_X * _direct)
#define HERO2_WEAPON_POSITION_Y (this->getPosition().y + HERO2_YOU_WEAPON_POSITION_Y)
//Ѫ�� ����λ�� this->getContentSize().width / 2
#define HERO2_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO2_YOU_BAR_POSITION + healthBar->getContentSize().height / 2)
#define HERO2_MAGICBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO2_YOU_BAR_POSITION)
//Ѫ�����ٷֱȼ���
#define HERO2_BLOOD_PERCENT int(100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint()))
#define HERO2_MAGIC_PERCENT int(100 * float(_panel.getMagicPoint()) / float(_panel.getMaxMagicPoint()))
//�ȼ�λ��
#define HERO2_LEVELTEXT_POSITION Vec2(this->getPosition().x, this->getPosition().y + HERO2_YOU_BAR_POSITION + bar->getContentSize().height)
//��ʼ���
#define HERO2_INIT_MAXHEALTHPOINT 1050
#define HERO2_INIT_ATTACK 140
#define HERO2_INIT_DEFENCE 150
#define HERO2_INIT_SKILLRATE 2.7f
#define HERO2_INIT_ATTACKRATE 1.2f
//����ʱ����֡��
#define HERO2_YOU_ATTACK_TIME 0.3f
#define HERO2_YOU_ATTACK_FRAME 20
#define HERO2_YOU_SKILL_TIME 1.0f
#define HERO2_YOU_SKILL_FRAME 7

/*==============================!!!!!���Ϻ������޸�!!!!!=================================*/

class Hero2 : public Player
{
public:
	float _direct = 1.0f;//��ʾ����

	float _weaponAnchorPositionX = HERO2_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT;
	float _weaponAnchorPositionY = HERO2_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT;

	static Hero2* create(const std::string& filename);
	static Hero2* create(const std::string& filename, const Rect& rect);

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
