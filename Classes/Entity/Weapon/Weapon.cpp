//���� : ����
//���� : 2022-5-20


//�޸� :��Ԫ��
//���� : 2033-5-31
//���� : ������������Ҫ��������ײ������ȷ�����������ôʵ�֣����Բο�

#include "Weapon.h"
#include "Entity/Player/Player.h"
#include "Entity/Player/Hero/Hero1.h"
#include "Entity/Player/Hero/Hero2.h"
#include "Entity/Player/Hero/Hero3.h"
#include "Entity/Player/Hero/Hero4.h"

USING_NS_CC;

/****************************
* Name ��Weapon::create
* Summary ��������ʼ��
* return ������ָ��
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
* Name ��Weapon::getWeapon()
* Summary ����ȡ����ָ��
* return ������ָ��
****************************/
Weapon* Weapon::getWeapon()
{
	return this;
}

/****************************
* Name ��Weapon::launchAnAttack()
* Summary �����𹥻�
* return ����ɵ��˺�
****************************/
//template<typename Enemy>
int Weapon::launchAnAttack(int attack, Player* enemy)
{
	//pz
	return enemy->hitPlayer(attack);
}


/****************************
* Name ��Weapon::createWeaponPhysicsBody()
* Summary ������������������ײ����
* return ����
****************************/
void Weapon::createWeaponPhysicsBody()
{
	auto WeaponPhysicsBody = cocos2d::PhysicsBody::createBox(this->getContentSize(), cocos2d::PhysicsMaterial(0.1f, 0.1f, 0.0f));
	// Material ����������ʾ��density��friction��restitution
	WeaponPhysicsBody->setDynamic(false);
	WeaponPhysicsBody->setContactTestBitmask(0XFFFFFFFF);
	this->setPhysicsBody(WeaponPhysicsBody);
}
// https://blog.csdn.net/cheyiliu/article/details/43560685