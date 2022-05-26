//���� : ��Ԫ��
//���� : 2022-5-14

#include "Monster.h"

USING_NS_CC;



/****************************
* Name ��Monster::init
* Summary �������ʼ��
* return ��
****************************/
void Monster::initMonster(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
{
	//��ʼ�����
	_panel.init(maxHealthPoint, attack, defence, skillAttackRate, attackRate);
}
/****************************
* Name ��Player::init
* Summary �������ʼ��
* return ��
****************************/
void Monster::initMonster(Panel& panel)
{
	_panel = panel;
}

/****************************
* Name ��Monster::create
* Summary ����������
* return ������ָ��
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
// �������⣬ʼ�շ���nullptr

/****************************
* Name ��Monster::getPanel()
* Summary ����ȡ���
* return �����ָ��
****************************/
Panel* Monster::getPanel()
{
	return &_panel;
}




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
* Summary ������Ѫ��������λ�ã������ƶ�
* return ��
****************************/
void Monster::setPositionWithAll(cocos2d::Vec2& position, Slider* healthBar)
{
	this->setPosition(position);
	this->refreshHealthBar(healthBar);
}

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
* Summary �����¹���Ѫ��
* return ��
****************************/
void Monster::refreshPlayer()
{

}