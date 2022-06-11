#pragma once
//���� : ����
//���� : 2022-5-18

//�޸� : ��Ԫ��
//���� : 2022-5-25

//�޸� : ����
//���� : 2022-6-8

#ifndef __GROUNDMONSTER_H__
#define __GROUNDMONSTER_H__

#include "Entity/Monster/Monster.h"

using namespace cocos2d::ui;
using namespace cocos2d;

/*==============================����������Ҫ�޸ĵĺ궨��=================================*/

//Ѫ����Թ��޵�����λ��
#define GROUNDMONSTER_YOU_BAR_POSITION (this->getContentSize().height / 2)

/*==============================����������Ҫ�޸ĵĺ궨��=================================*/

/*==============================!!!!!���º������޸�!!!!!=================================*/

//Ѫ��λ�� this->getContentSize().width / 2
#define GROUNDMONSTER_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + GROUNDMONSTER_YOU_BAR_POSITION + healthBar->getContentSize().height / 2)
//Ѫ�ٷֱȼ���
#define GROUNDMONSTER_BLOOD_PERCENT int(100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint()))

/*==============================!!!!!���Ϻ������޸�!!!!!=================================*/

class GroundMonster : public Monster
{
public:
	float _direct = 1.0f;//��ʾ����

	static GroundMonster* create(const std::string& filename);
	static GroundMonster* create(const std::string& filename, const Rect& rect);

	void initMonster(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate);
	void initMonster();

	void keepHealthBar(Slider* healthBar);
};

#endif
