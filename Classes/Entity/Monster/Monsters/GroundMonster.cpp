//作者 : 王鹏
//日期 : 2022-5-23

//修改 : 李元特
//日期 : 2022-5-25

//修改 : 王鹏
//日期 : 2022-6-8

#include "GroundMonster.h"

USING_NS_CC;

/****************************
* Name ：create
* Summary ：创建怪兽
* return ：怪兽指针
****************************/
GroundMonster* GroundMonster::create(const std::string& filename)
{
	GroundMonster* player = new (std::nothrow) GroundMonster();
	if (player && player->initWithFile(filename))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

/****************************
* Name ：create
* Summary ：创建怪兽
* return ：怪兽指针
****************************/
GroundMonster* GroundMonster::create(const std::string& filename, const Rect& rect)
{
	GroundMonster* player = new (std::nothrow) GroundMonster();
	if (player && player->initWithFile(filename, rect))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

/****************************
* Name ：init
* Summary ：怪兽初始化
* return ：
****************************/
void GroundMonster::initMonster(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
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
void GroundMonster::initMonster()
{
	_panel.init(1000, 100, 200, 1.0f, 1.0f, 100);
}

/****************************
* Name ：keepHealthBar()
* Summary ：保持血条位置
* return ：
****************************/
void GroundMonster::keepHealthBar(Slider* healthBar)
{
	healthBar->setPosition(GROUNDMONSTER_HEALTHBAR_POSITION);
	//_healthBar->setPosition(position);
}