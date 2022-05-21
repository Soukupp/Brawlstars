//作者 : 王鹏
//日期 : 2022-5-18
#include "Player.h"

USING_NS_CC;

/*===============================================================================*/
/*==========================以下是初始化与面板直接调用===========================*/
/*===============================================================================*/

/****************************
* Name ：Player::init
* Summary ：人物初始化
* return ：
****************************/
void Player::initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
{
	//初始化面板
	_panel.init(maxHealthPoint, attack, defence, skillAttackRate, attackRate);

	_healthBar = Slider::create();
	_healthBar->setPercent(PLAYER_BLOOD_PERCENT);
	_healthBar->loadBarTexture("/ui/playerHealthbarFrame.png");
	_healthBar->loadProgressBarTexture("/ui/playerHealthbarBlock.png");
	_healthBar->setScale(0.5);
	_healthBar->setPosition(PLAYER_HEALTHBAR_POSITION);
	this->addChild(_healthBar);
}
/****************************
* Name ：Player::init
* Summary ：人物初始化
* return ：
****************************/
void Player::initPlayer(Panel& panel)
{
	_panel = panel;

	_healthBar = Slider::create();
	_healthBar->setPercent(PLAYER_BLOOD_PERCENT);
	_healthBar->loadBarTexture("/ui/playerHealthbarFrame.png");
	_healthBar->loadProgressBarTexture("/ui/playerHealthbarBlock.png");
	_healthBar->setScale(0.5);
	_healthBar->setPosition(PLAYER_HEALTHBAR_POSITION);
	this->addChild(_healthBar);
}

/****************************
* Name ：Player::create
* Summary ：创建人物
* return ：人物指针
****************************/
Player* Player::create(const std::string& filename)
{
	Player* player = new (std::nothrow) Player();
	if (player && player->initWithFile(filename))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}
/****************************
* Name ：Player::getPanel()
* Summary ：获取面板
* return ：面板指针
****************************/
Panel* Player::getPanel()
{
	return &_panel;
}

/*===============================================================================*/
/*=====================================以下是行为================================*/
/*===============================================================================*/

/****************************
* Name ：Player::launchAnAttack()
* Summary ：发起攻击(请传入 "attack" 或 "skill")
* return ：
****************************/
void Player::launchAnAttack(Weapon* weapon, const std::string& attackType)
{
	if (attackType == "attack")
	{
		weapon->launchAnAttack(_panel.doAttack());
	}
	else if (attackType == "skill")
	{
		weapon->launchAnSkill(_panel.doSkillAttack());
	}
}
/****************************
* Name ：Player::hitPlayer
* Summary ：对角色进行攻击
* return ：造成的伤害
****************************/
int Player::hitPlayer(int attack)
{
	return _panel.hit(attack);
}

/*===============================================================================*/
/*==================================以下是移动相关===============================*/
/*===============================================================================*/

/****************************
* Name ：Player::keepWeapon
* Summary ：保持武器位置
* return ：
****************************/
void Player::keepWeapon(Weapon* weapon)
{
	weapon->setPosition(this->getPosition());
}
/****************************
* Name ：Player::runFlipxWithWeapon
* Summary ：带着武器翻转
* return ：
****************************/
void Player::runFlipxWithWeapon(bool flipx,Weapon* weapon)
{
	this->runAction(FlipX::create(flipx));
	weapon->runAction(FlipX::create(flipx));

	float anchorPointX = 
		flipx ? 
		PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT : 
		PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT;

	weapon->setAnchorPoint(Vec2(anchorPointX, PLAYER_WEAPON_ANCHOR_POSITION_Y));
}
/****************************
* Name ：Player::setPositionWithWeapon
* Summary ：带着武器移动
* return ：
****************************/
void Player::setPositionWithWeapon(cocos2d::Vec2& position, Weapon* weapon)
{
	this->setPosition(position);
	this->keepWeapon(weapon);
}

/****************************
* Name ：Player::keepHealthBar()
* Summary ：保持血条位置
* return ：
****************************/
void Player::keepHealthBar()
{
	_healthBar->setPosition(PLAYER_HEALTHBAR_POSITION);
}
/****************************
* Name ：Player::setPositionWithAll
* Summary ：整体移动
* return ：
****************************/
void Player::setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon)
{
	this->setPosition(position);
	this->keepWeapon(weapon);
	this->refreshHealthBar();
}
/****************************
* Name ：Player::refreshHealthBar()
* Summary ：更新血条
* return ：
****************************/
void Player::refreshHealthBar()
{
	_healthBar->setPercent(PLAYER_BLOOD_PERCENT);
	keepHealthBar();
}
/****************************
* Name ：Player::refreshHealthBar()
* Summary ：更新人物
* return ：
****************************/
void Player::refreshPlayer()
{

}