//作者 : 王鹏
//日期 : 2022-5-20
#include "Weapon.h"

USING_NS_CC;

/****************************
* Name ：Weapon::create
* Summary ：武器初始化
* return ：武器指针
****************************/
Weapon* Weapon::create(const std::string& filename)
{
	Weapon* weapon = new (std::nothrow) Weapon();
	if (weapon && weapon->initWithFile(filename))
	{
		weapon->autorelease();
		return weapon;
	}
	CC_SAFE_DELETE(weapon);
	return nullptr;
}
/****************************
* Name ：Weapon::getWeapon()
* Summary ：获取武器指针
* return ：武器指针
****************************/
Weapon* Weapon::getWeapon()
{
	return this;
}

/****************************
* Name ：Weapon::launchAnAttack()
* Summary ：发起攻击
* return ：造成的伤害
****************************/
int Weapon::launchAnAttack(int attack)
{
	return attack;
}

/****************************
* Name ：Weapon::launchAnSkill()
* Summary ：发起技能攻击
* return ：造成的伤害
****************************/
int Weapon::launchAnSkill(int attack)
{
	return attack;
}