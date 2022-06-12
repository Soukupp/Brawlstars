//作者 : 王鹏
//日期 : 2022-5-18

//修改 : 束赫
//日期 : 2022-6-3
//实现 : 新增判断变量和相应函数

#include "Panel.h"

USING_NS_CC;

/****************************
* Name ：Panel::init
* Summary ：初始化面板
* return ：
****************************/
void Panel::init(int maxHealthPoint, int attack, int defence, float skillRate, float attackRate, int maxMagicPoint)
{
	_maxHealthPoint = maxHealthPoint;
	_healthPoint = maxHealthPoint;
	_maxMagicPoint = maxMagicPoint;
	_magicPoint = maxMagicPoint;
	_attack = attack % (PANEL_MAX_ATTACK + 1);
	_defence = defence % (PANEL_MAX_DEFENCE + 1);
	_skillRate = skillRate;
	_attackRate = attackRate;

	_survive = true;
	_canBeSeen = true;
}

/*===============================================================================*/
/*============================以下是面板的直接读取===============================*/
/*===============================================================================*/

/****************************
* Name ：Panel::getHealthPoint()const
* Summary ：读取当前血量
* return ：血量
****************************/
int Panel::getHealthPoint()const
{
	return _healthPoint;
}

/****************************
* Name ：Panel::getMaxHealthPoint()const
* Summary ：读取最大血量
* return ：最大血量
****************************/
int Panel::getMaxHealthPoint()const
{
	return _maxHealthPoint;
}

/****************************
* Name ：Panel::getMagicPoint()const
* Summary ：读取当前蓝量
* return ：蓝量
****************************/
int Panel::getMagicPoint()const
{
	return _magicPoint;
}

/****************************
* Name ：Panel::getMaxMagicPoint()const
* Summary ：读取最大蓝量
* return ：最大蓝量
****************************/
int Panel::getMaxMagicPoint()const
{
	return _maxMagicPoint;
}

/****************************
* Name ：Panel::getSkillAttackRate()const
* Summary ：读取技能倍率
* return ：技能倍率
****************************/
float Panel::getSkillRate()const
{
	return _skillRate;
}

/****************************
* Name ：Panel::getAttackRate()const
* Summary ：读取普攻倍率
* return ：普攻倍率
****************************/
float Panel::getAttackRate()const
{
	return _attackRate;
}

/****************************
* Name ：Panel::getAttack()const
* Summary ：读取攻击力
* return ：攻击力
****************************/
int Panel::getAttack()const
{
	return _attack;
}

/****************************
* Name ：Panel::getDefence()const
* Summary ：读取防御力
* return ：防御力
****************************/
int Panel::getDefence()const
{
	return _defence;
}

/****************************
* Name ：getIsSurvive()const
* Summary ：获取是否存活 
* return ：true 存活, false 未存活 
****************************/
bool Panel::getIsSurvive()const
{
	return _survive;
}

/****************************
* Name ：getCanBeSeen()const
* Summary ：获取是否可视 
* return ：true 可视, false 不可视 
****************************/
bool Panel::getCanBeSeen()const
{
	return _canBeSeen;
}

/*===============================================================================*/
/*============================以下是面板的直接设置===============================*/
/*===============================================================================*/

/****************************
* Name ：Panel::setMaxHealthPoint
* Summary ：设置最大血量
* return ：
****************************/
void Panel::setMaxHealthPoint(int maxHealthPoint)
{
	_maxHealthPoint = maxHealthPoint;
}

/****************************
* Name ：Panel::setHealthPoint
* Summary ：设置当前血量
* return ：
****************************/
void Panel::setHealthPoint(int healthPoint)
{
	_healthPoint = healthPoint;
}

/****************************
* Name ：Panel::setMagicPoint
* Summary ：设置当前蓝量
* return ：
****************************/
void Panel::setMagicPoint(int magicPoint)
{
	_magicPoint = magicPoint;
}

/****************************
* Name ：Panel::setAttack
* Summary ：设置攻击力
* return ：
****************************/
void Panel::setAttack(int attack)
{
	_attack = attack;
	if (_attack > PANEL_MAX_ATTACK)
	{
		_attack = PANEL_MAX_ATTACK;
	}
}

/****************************
* Name ：Panel::setDefence
* Summary ：设置防御力
* return ：
****************************/
void Panel::setDefence(int defence)
{
	_defence = defence;
	if (_defence > PANEL_MAX_DEFENCE)
	{
		_defence = PANEL_MAX_DEFENCE;
	}
}

/****************************
* Name ：Panel::setAttackRate
* Summary ：设置普攻倍率
* return ：
****************************/
void Panel::setAttackRate(float attackRate)
{
	_attackRate = attackRate;
}

/****************************
* Name ：Panel::setSkillRate
* Summary ：设置普攻倍率
* return ：
****************************/
void Panel::setSkillRate(float skillRate)
{
	_skillRate = skillRate;
}

/****************************
* Name ：setIsSurvive
* Summary ：设置是否存活 
* return ：
****************************/
void Panel::setIsSurvive(bool survive)
{
	_survive = survive;
}

/****************************
* Name ：setCanBeSeen
* Summary ：设置是否可见 
* return ：
****************************/
void Panel::setCanBeSeen(bool canBeSeen)
{
	_canBeSeen = canBeSeen;
}

/*===============================================================================*/
/*=========================以下是发起攻击的伤害的结算============================*/
/*===============================================================================*/

/****************************
* Name ：Panel::doAttack()
* Summary ：结算普攻伤害
* return ：普攻伤害
****************************/
int Panel::doAttack()
{
	return static_cast<int>(_attack * _attackRate);
}

/****************************
* Name ：Panel::doSkillAttack()
* Summary ：结算技能伤害
* return ：技能伤害
****************************/
int Panel::doSkillAttack()
{
	return static_cast<int>(_attack * _skillRate);
}

/*===============================================================================*/
/*=========================以下是受攻击与受治疗的结算============================*/
/*===============================================================================*/

/****************************
* Name ：Panel::hit
* Summary ：受攻击
* return ：最终结算的伤害值
****************************/
int Panel::hit(int attack)
{
	//防御力的生效方式为百分比减伤
	int hitPoint = static_cast<int>(attack * (1.0f - _defence / PANEL_MAX_DEFENCE));
	_healthPoint -= hitPoint;
	if (_healthPoint <= 0) 
	{//伤害溢出或击杀
		_healthPoint = 0;
		_survive = false;
	}
	return hitPoint;//哪怕伤害溢出 也直接返回造成的伤害
}

/****************************
* Name ：Panel::treat
* Summary ：受治疗
* return ：受治疗量
****************************/
int Panel::treat(int healthPoint)
{
	_healthPoint += healthPoint;
	if (_healthPoint > _maxHealthPoint)
	{
		_healthPoint = _maxHealthPoint;//避免溢出
	}
	return healthPoint;//返回治疗量
}

/****************************
* Name ：Panel::restoreMagic
* Summary ：恢复蓝量
* return ：恢复的蓝量
****************************/
int Panel::restoreMagic(int magic)
{
	_magicPoint += magic;
	if (_magicPoint >= _maxMagicPoint)
	{
		_magicPoint = _maxMagicPoint;
	}
	return magic;
}

/****************************
* Name ：Panel::getPlayerState
* Summary ：获得player的状态（共五种）
* return ：状态对应的枚举量
*         具体状态和枚举量见Panel.h
****************************/
int Panel::getPlayerState()const
{
	return _playerstase;
}

/****************************
* Name ：Panel::setPlayerState
* Summary ：设置player的状态（共五种）
           具体状态和枚举量见Panel.h
* return ：
****************************/
void Panel::setPlayerState(int state)
{
	switch (state)
	{
		case NORMAL:
			_playerstase = NORMAL;
			break;
		case MOVING:
			_playerstase = MOVING;
			break;
		case ATTACK:
			_playerstase = ATTACK;
			break;
		case HURT:
			_playerstase = HURT;
			break;
		case SKILL:
			_playerstase = SKILL;
			break;
		case DEAD:
			_playerstase = DEAD;
			break;
	}
}

/****************************
* Name ：Panel::getIfPlayAttackAnimation
* Summary ：获得当前是否播放attack动画
* return ： _ifPlayAttackAnimation
****************************/
bool Panel::getIfPlayAttackAnimation()const
{
	return _ifPlayAttackAnimation;
}

/****************************
* Name ：Panel::setIfPlayAttackAnimation
* Summary : 设置当前是否播放攻击动画
* return ：
****************************/
void Panel::setIfPlayAttackAnimation(bool ifplay)
{
	_ifPlayAttackAnimation = ifplay;
}

/****************************
* Name ：Panel::getIfPlayNormalAnimationInUpdate2
* Summary ：获得当前是否在update2中播放normal动画
* return ：_ifPlayNormalAnimationInUpdate2
****************************/
bool Panel::getIfPlayNormalAnimationInUpdate2()const
{
	return _ifPlayNormalAnimationInUpdate2;
}

/****************************
* Name ：Panel::getIfPlayNormalAnimationInUpdate2
* Summary : 设置当前是否在update2中播放normal动画
* return ：
****************************/
void Panel::setIfPlayNormalAnimationInUpdate2(bool ifplay)
{
	_ifPlayNormalAnimationInUpdate2 = ifplay;

}

/****************************
* Name ：Panel::addHitnum
* Summary : 增加击杀数
* return ：
****************************/
void Panel::addHitnum()
{
	_hitnum++;
}

/****************************
* Name ：Panel::getHitnum
* Summary : 获取击杀数
* return ：
****************************/
int Panel::getHitnum()
{
	return _hitnum;
}