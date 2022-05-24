//���� : ��Ԫ��
//���� : 2022-5-14

#include "Monster.h"

USING_NS_CC;

/*===============================================================================*/
/*============================�����ǳ�ʼ�������ֱ�ӵ���===========================*/
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

	_healthBar = Slider::create();
	_healthBar->setPercent(MONSTER_BLOOD_PERCENT);
	_healthBar->loadBarTexture("/ui/playerHealthbarFrame.png");
	_healthBar->loadProgressBarTexture("/ui/playerHealthbarBlock.png");
	_healthBar->setScale(0.5);
	_healthBar->setPosition(MONSTER_HEALTHBAR_POSITION);
	this->addChild(_healthBar);
}
/****************************
* Name ��Monster::init
* Summary �����޳�ʼ��
* return ��
****************************/
void Monster::initMonster(Panel& panel)
{
	_panel = panel;

	_healthBar = Slider::create();
	_healthBar->setPercent(MONSTER_BLOOD_PERCENT);
	_healthBar->loadBarTexture("/ui/playerHealthbarFrame.png");
	_healthBar->loadProgressBarTexture("/ui/playerHealthbarBlock.png");
	_healthBar->setScale(0.5);
	_healthBar->setPosition(MONSTER_HEALTHBAR_POSITION);
	this->addChild(_healthBar);
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
