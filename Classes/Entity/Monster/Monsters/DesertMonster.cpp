//���� : ����
//���� : 2022-5-23

//�޸� : ��Ԫ��
//���� : 2022-5-25

//�޸� : ����
//���� : 2022-6-8

#include "DesertMonster.h"

USING_NS_CC;

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
	_panel.init(2000, 0, 100, 0.0f, 0.0f, 0);
}
void DesertMonster::keepHealthBar(Slider* healthBar)
{
	healthBar->setPosition(DESERTMONSTER_HEALTHBAR_POSITION);
	//_healthBar->setPosition(position);
}


