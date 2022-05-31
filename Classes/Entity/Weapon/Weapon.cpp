//作者 : 王鹏
//日期 : 2022-5-20


//修改 :李元特
//日期 : 2033-5-31
//内容 : 增加了武器需要的物理碰撞，但不确定你具体想怎么实现，可以参考

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


/****************************
* Name ：Weapon::createWeaponPhysicsBody()
* Summary ：设置武器的物理碰撞区域
* return ：无
****************************/
void Weapon::createWeaponPhysicsBody()
{
	auto WeaponPhysicsBody = cocos2d::PhysicsBody::createBox(this->getContentSize(), cocos2d::PhysicsMaterial(0.1f, 0.1f, 0.0f));
	// Material 三个参数表示：density，friction和restitution
	WeaponPhysicsBody->setDynamic(false);
	WeaponPhysicsBody->setContactTestBitmask(0XFFFFFFFF);
	this->setPhysicsBody(WeaponPhysicsBody);
}
// https://blog.csdn.net/cheyiliu/article/details/43560685