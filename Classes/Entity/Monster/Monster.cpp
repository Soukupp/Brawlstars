//作者 : 李元特
//日期 : 2022-5-14

#include "Monster.h"

USING_NS_CC;

/*===============================================================================*/
/*============================以下是初始化与面板直接调用===========================*/
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

	_healthBar = Slider::create();
	_healthBar->setPercent(MONSTER_BLOOD_PERCENT);
	_healthBar->loadBarTexture("/ui/playerHealthbarFrame.png");
	_healthBar->loadProgressBarTexture("/ui/playerHealthbarBlock.png");
	_healthBar->setScale(0.5);
	_healthBar->setPosition(MONSTER_HEALTHBAR_POSITION);
	this->addChild(_healthBar);
}
/****************************
* Name ：Monster::init
* Summary ：怪兽初始化
* return ：
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
* Name ：Monster::create
* Summary ：创建怪兽
* return ：怪兽指针
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
 // 存在问题，始终返回nullptr


/****************************
* Name ：Monster::getPanel()
* Summary ：获取面板
* return ：面板指针
****************************/
Panel* Monster::getPanel()
{
	return &_panel;
}
