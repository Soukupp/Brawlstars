//���� : ��Ԫ��
//���� : 2022-5-14

//���� : ����
//���� : 2022-6-6
#include "Monster.h"
#include "Entity/Player/Hero/Hero1.h"
#include "Entity/Player/Hero/Hero2.h"
#include "Entity/Player/Hero/Hero3.h"
#include "Entity/Player/Hero/Hero4.h"
#include <SimpleAudioEngine.h>

USING_NS_CC;

/*===============================================================================*/
/*==============================�����Ǵ������ʼ��===============================*/
/*===============================================================================*/

/****************************
* Name ��Monster::init
* Summary �����޳�ʼ��
* return ��
****************************/
void Monster::initMonster(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
{
	//��ʼ�����
	_panel.init(maxHealthPoint, attack, defence, skillAttackRate, attackRate);
}

/****************************
* Name ��Monster::init
* Summary �����޳�ʼ��
* return ��
****************************/
void Monster::initMonster(Panel& panel)
{
	_panel.init(panel.getMaxHealthPoint(), panel.getAttack(), panel.getDefence(), panel.getSkillRate(), panel.getAttackRate());
}

/****************************
* Name ��Monster::init
* Summary �����޳�ʼ��
* return ��
****************************/
void Monster::initMonster()
{

}

/****************************
* Name ��Monster::create
* Summary ����������
* return ������ָ��
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
* Name ��Monster::getPanel()
* Summary ����ȡ���
* return �����ָ��
****************************/
Panel* Monster::getPanel()
{
	return &_panel;
}

/*===============================================================================*/
/*================================�����ǹ�����Ϊ==================================*/
/*===============================================================================*/

/****************************
* Name ��Monster::launchAnAttack()
* Summary �����𹥻�
* return ��
****************************/
void Monster::launchAnAttack(Player* enemy, Slider* enemyHealthBar)
{

}

/****************************
* Name ��Monster::hitMonster
* Summary ���Թ��޽��й���
* return ����ɵ��˺�
****************************/
int Monster::hitMonster(int attack)
{
	//�����˺������ͨ��panel��getIsSurvive��ȡ�Ƿ���
	return _panel.hit(attack);
}

/****************************
* Name ��Monster::getHealthPercent
* Summary ����ȡ��ǰѪ���ٷֱ�
* return ��Ѫ���ٷֱ�
****************************/
int Monster::getHealthPercent()
{
	return MONSTER_BLOOD_PERCENT;
}

/*===============================================================================*/
/*==================================�������ƶ����===============================*/
/*===============================================================================*/

/****************************
* Name ��Monster::keepHealthBar()
* Summary ������Ѫ��λ��
* return ��
****************************/
void Monster::keepHealthBar(Slider* healthBar)
{
	healthBar->setPosition(MONSTER_HEALTHBAR_POSITION);
}

/****************************
* Name ��Monster::setPositionWithAll
* Summary �������ƶ�
* return ��
****************************/
void Monster::setPositionWithAll(cocos2d::Vec2& position, Slider* healthBar)
{
	this->setPosition(position);
	this->refreshHealthBar(healthBar);
}

/*===============================================================================*/
/*==================================������״̬���===============================*/
/*===============================================================================*/

/****************************
* Name ��Monster::refreshHealthBar()
* Summary ������Ѫ��
* return ��
****************************/
void Monster::refreshHealthBar(Slider* healthBar)
{
	healthBar->setPercent(int(MONSTER_BLOOD_PERCENT));
	keepHealthBar(healthBar);
}

/****************************
* Name ��Monster::refreshHealthBar()
* Summary �����¹���
* return ��
****************************/
void Monster::refreshMonster()
{

}

/****************************
* Name ��palyerCollisionTest1
* Summary �������빥����ײ���
* ����˵�� : target : ��������
*           weapon : ��������
* return ��
****************************/
bool Monster::playerCollisionTest1(Monster* target)
{
	return true;
}
