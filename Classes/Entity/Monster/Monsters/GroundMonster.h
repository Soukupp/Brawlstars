#pragma once
//作者 : 王鹏
//日期 : 2022-5-18

//修改 : 李元特
//日期 : 2022-5-25

//修改 : 王鹏
//日期 : 2022-6-8

#ifndef __GROUNDMONSTER_H__
#define __GROUNDMONSTER_H__

#include "Entity/Monster/Monster.h"

using namespace cocos2d::ui;
using namespace cocos2d;

/*==============================以下是你需要修改的宏定义=================================*/

//血条相对怪兽的纵向位置
#define GROUNDMONSTER_YOU_BAR_POSITION (this->getContentSize().height / 2)

/*==============================以上是你需要修改的宏定义=================================*/

/*==============================!!!!!以下宏请勿修改!!!!!=================================*/

//血条位置 this->getContentSize().width / 2
#define GROUNDMONSTER_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + GROUNDMONSTER_YOU_BAR_POSITION + healthBar->getContentSize().height / 2)
//血百分比计算
#define GROUNDMONSTER_BLOOD_PERCENT int(100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint()))

/*==============================!!!!!以上宏请勿修改!!!!!=================================*/

class GroundMonster : public Monster
{
public:
	float _direct = 1.0f;//表示方向

	static GroundMonster* create(const std::string& filename);
	static GroundMonster* create(const std::string& filename, const Rect& rect);

	void initMonster(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate);
	void initMonster();

	void keepHealthBar(Slider* healthBar);
};

#endif
