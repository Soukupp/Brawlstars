//���� : ����
//���� : 2022-5-23

//�޸� : ��Ԫ��
//���� : 2022-5-25

//�޸� : ����
//���� : 2022-6-8

#include "DesertMonster.h"

USING_NS_CC;

/****************************
* Name ��create
* Summary ����������
* return ������ָ��
****************************/
DesertMonster* DesertMonster::create(const std::string& filename)
{
	DesertMonster* player = new (std::nothrow) DesertMonster();
	if (player && player->initWithFile(filename))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

/****************************
* Name ��create
* Summary ����������
* return ������ָ��
****************************/
DesertMonster* DesertMonster::create(const std::string& filename, const Rect& rect)
{
	DesertMonster* player = new (std::nothrow) DesertMonster();
	if (player && player->initWithFile(filename, rect))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

/****************************
* Name ��init
* Summary �����޳�ʼ��
* return ��
****************************/
void DesertMonster::initMonster(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
{
	//��ʼ�����
	_panel.init(maxHealthPoint, attack, defence, skillAttackRate, attackRate);
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
}

/****************************
* Name ��init
* Summary �����޳�ʼ��
* return ��
****************************/
void DesertMonster::initMonster()
{
	_panel.init(1000, 100, 100, 1.0f, 1.0f, 100);
}

/****************************
* Name ��keepHealthBar()
* Summary ������Ѫ��λ��
* return ��
****************************/
void DesertMonster::keepHealthBar(Slider* healthBar)
{
	healthBar->setPosition(DESERTMONSTER_HEALTHBAR_POSITION);
	//_healthBar->setPosition(position);
}