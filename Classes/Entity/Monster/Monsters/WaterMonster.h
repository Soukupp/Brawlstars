#pragma once
//作者 : 王鹏
//日期 : 2022-5-18

//修改 : 李元特
//日期 : 2022-5-25

//修改 : 王鹏
//日期 : 2022-6-8

#ifndef __WATERMONSTER_H__
#define __WATERMONSTER_H__

#include "Entity/Monster/Monster.h"

using namespace cocos2d::ui;
using namespace cocos2d;

/*==============================以下是你需要修改的宏定义=================================*/

//血条相对怪兽的纵向位置
#define WATERMONSTER_YOU_BAR_POSITION (this->getContentSize().height / 2)

/*==============================以上是你需要修改的宏定义=================================*/

/*==============================!!!!!以下宏请勿修改!!!!!=================================*/

//血条位置 this->getContentSize().width / 2
#define WATERMONSTER_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + WATERMONSTER_YOU_BAR_POSITION + healthBar->getContentSize().height / 2)
//血百分比计算
#define WATERMONSTER_BLOOD_PERCENT int(100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint()))

/*==============================!!!!!以上宏请勿修改!!!!!=================================*/

class WaterMonster : public Monster
{
public:
	float _direct = 1.0f;//表示方向

	static WaterMonster* create(const std::string& filename);
	static WaterMonster* create(const std::string& filename, const Rect& rect);

	void initMonster(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate);
	void initMonster();
	//void launchAnAttack(Weapon* weapon, const std::string& attackType);

	void keepHealthBar(Slider* healthBar);

};

#endif
