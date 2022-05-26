//作者 : 李元特
//日期 : 2022-5-14

#include "Monster.h"

USING_NS_CC;



/****************************
* Name ：Monster::init
* Summary ：人物初始化
* return ：
****************************/
void Monster::initMonster(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
{
	//初始化面板
	_panel.init(maxHealthPoint, attack, defence, skillAttackRate, attackRate);
}
/****************************
* Name ：Player::init
* Summary ：人物初始化
* return ：
****************************/
void Monster::initMonster(Panel& panel)
{
	_panel = panel;
}

/****************************
* Name ：Monster::create
* Summary ：创建怪兽
* return ：怪兽指针
****************************/
Monster* Monster::create(const std::string& filename)
{
	Monster* monster = new (std::nothrow) Monster();
	if (monster && monster->initWithFile(filename))
	{
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return nullptr;
}
// 存在问题，始终返回nullptr

/****************************
* Name ：Monster::getPanel()
* Summary ：获取面板
* return ：面板指针
****************************/
Panel* Monster::getPanel()
{
	return &_panel;
}




/****************************
* Name ：Monster::keepHealthBar()
* Summary ：保持血条位置
* return ：
****************************/
void Monster::keepHealthBar(Slider* healthBar)
{
	healthBar->setPosition(MONSTER_HEALTHBAR_POSITION);
}

/****************************
* Name ：Monster::setPositionWithAll
* Summary ：设置血条和人物位置，整体移动
* return ：
****************************/
void Monster::setPositionWithAll(cocos2d::Vec2& position, Slider* healthBar)
{
	this->setPosition(position);
	this->refreshHealthBar(healthBar);
}

/****************************
* Name ：Monster::refreshHealthBar()
* Summary ：更新血条
* return ：
****************************/
void Monster::refreshHealthBar(Slider* healthBar)
{
	healthBar->setPercent(int(MONSTER_BLOOD_PERCENT));
	keepHealthBar(healthBar);
}

/****************************
* Name ：Monster::refreshHealthBar()
* Summary ：更新怪兽血条
* return ：
****************************/
void Monster::refreshPlayer()
{

}