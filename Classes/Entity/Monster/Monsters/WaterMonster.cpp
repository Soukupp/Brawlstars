//作者 : 王鹏
//日期 : 2022-5-23

//修改 : 李元特
//日期 : 2022-5-25

//修改 : 王鹏
//日期 : 2022-6-8

#include "WaterMonster.h"

USING_NS_CC;

WaterMonster* WaterMonster::create(const std::string& filename)
{
	WaterMonster* player = new (std::nothrow) WaterMonster();
	if (player && player->initWithFile(filename))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

WaterMonster* WaterMonster::create(const std::string& filename, const Rect& rect)
{
	WaterMonster* player = new (std::nothrow) WaterMonster();
	if (player && player->initWithFile(filename, rect))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

void WaterMonster::initMonster(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
{
	//初始化面板
	_panel.init(maxHealthPoint, attack, defence, skillAttackRate, attackRate);
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
}

/****************************
* Name ：init
* Summary ：怪兽初始化
* return ：
****************************/
void WaterMonster::initMonster()
{
	_panel.init(1000, 0, 100, 0.0f, 0.0f, 0);
}
void WaterMonster::keepHealthBar(Slider* healthBar)
{
	healthBar->setPosition(WATERMONSTER_HEALTHBAR_POSITION);
	//_healthBar->setPosition(position);
}


