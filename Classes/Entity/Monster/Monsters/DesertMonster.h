#pragma once
//���� : ����
//���� : 2022-5-18

//�޸� : ��Ԫ��
//���� : 2022-5-25

//�޸� : ����
//���� : 2022-6-8

#ifndef __DESERTMONSTER_H__
#define __DESERTMONSTER_H__

#include "Entity/Monster/Monster.h"

using namespace cocos2d::ui;
using namespace cocos2d;

/*==============================����������Ҫ�޸ĵĺ궨��=================================*/

//Ѫ����Թ��޵�����λ��
#define DESERTMONSTER_YOU_BAR_POSITION (this->getContentSize().height / 2)

/*==============================����������Ҫ�޸ĵĺ궨��=================================*/

/*==============================!!!!!���º������޸�!!!!!=================================*/

//Ѫ��λ�� this->getContentSize().width / 2
#define DESERTMONSTER_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + DESERTMONSTER_YOU_BAR_POSITION + healthBar->getContentSize().height / 2)
//Ѫ�ٷֱȼ���
#define DESERTMONSTER_BLOOD_PERCENT int(100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint()))

/*==============================!!!!!���Ϻ������޸�!!!!!=================================*/

class DesertMonster : public Monster
{
public:
	float _direct = 1.0f;//��ʾ����

	static DesertMonster* create(const std::string& filename);
	static DesertMonster* create(const std::string& filename, const Rect& rect);

	void initMonster(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate);
	void initMonster();
	//void launchAnAttack(Weapon* weapon, const std::string& attackType);

	void keepHealthBar(Slider* healthBar);

};

#endif
