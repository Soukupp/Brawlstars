//作者 : 李元特
//日期 : 2022-5-14

//作者 : 王鹏
//日期 : 2022-6-6
#include "Monster.h"
#include "Entity/Player/Hero/Hero1.h"
#include "Entity/Player/Hero/Hero2.h"
#include "Entity/Player/Hero/Hero3.h"
#include "Entity/Player/Hero/Hero4.h"
#include <SimpleAudioEngine.h>

USING_NS_CC;

/*===============================================================================*/
/*==============================以下是创建与初始化===============================*/
/*===============================================================================*/

/****************************
* Name ：Monster::init
* Summary ：怪兽初始化
* return ：
****************************/
void Monster::initMonster(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
{
	//初始化面板
	_panel.init(maxHealthPoint, attack, defence, skillAttackRate, attackRate);
}

/****************************
* Name ：Monster::init
* Summary ：怪兽初始化
* return ：
****************************/
void Monster::initMonster(Panel& panel)
{
	_panel.init(panel.getMaxHealthPoint(), panel.getAttack(), panel.getDefence(), panel.getSkillRate(), panel.getAttackRate());
}

/****************************
* Name ：Monster::init
* Summary ：怪兽初始化
* return ：
****************************/
void Monster::initMonster()
{

}

/****************************
* Name ：Monster::create
* Summary ：创建怪兽
* return ：怪兽指针
****************************/
Monster* Monster::create(const std::string& filename)
{
	Monster* player = new (std::nothrow) Monster();
	if (player && player->initWithFile(filename))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

/****************************
* Name ：Monster::getPanel()
* Summary ：获取面板
* return ：面板指针
****************************/
Panel* Monster::getPanel()
{
	return &_panel;
}

/*===============================================================================*/
/*================================以下是怪兽行为==================================*/
/*===============================================================================*/

/****************************
* Name ：Monster::launchAnAttack()
* Summary ：发起攻击
* return ：
****************************/
void Monster::launchAnAttack(Player* enemy, Slider* enemyHealthBar)
{

}

/****************************
* Name ：Monster::hitMonster
* Summary ：对怪兽进行攻击
* return ：造成的伤害
****************************/
int Monster::hitMonster(int attack)
{
	//结算伤害后可以通过panel的getIsSurvive获取是否存活
	return _panel.hit(attack);
}

/****************************
* Name ：Monster::getHealthPercent
* Summary ：获取当前血量百分比
* return ：血量百分比
****************************/
int Monster::getHealthPercent()
{
	return MONSTER_BLOOD_PERCENT;
}

/*===============================================================================*/
/*==================================以下是移动相关===============================*/
/*===============================================================================*/

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
* Summary ：整体移动
* return ：
****************************/
void Monster::setPositionWithAll(cocos2d::Vec2& position, Slider* healthBar)
{
	this->setPosition(position);
	this->refreshHealthBar(healthBar);
}

/*===============================================================================*/
/*==================================以下是状态相关===============================*/
/*===============================================================================*/

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
* Summary ：更新怪兽
* return ：
****************************/
void Monster::refreshMonster()
{

}

/****************************
* Name ：palyerCollisionTest1
* Summary ：近距离攻击碰撞检测
* 参数说明 : target : 攻击对象
*           weapon : 武器对象
* return ：
****************************/
bool Monster::playerCollisionTest1(Monster* target)
{
	return true;
}
