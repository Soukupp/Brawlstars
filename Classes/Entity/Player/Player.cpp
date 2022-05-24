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

	/**
	_healthBar = Slider::create();
	_healthBar->setPercent(int(PLAYER_BLOOD_PERCENT));
	_healthBar->loadBarTexture("/ui/playerHealthbarFrame.png");
	_healthBar->loadProgressBarTexture("/ui/playerHealthbarBlock.png");
	_healthBar->setScale(0.5);
	_healthBar->setPosition(PLAYER_HEALTHBAR_POSITION);
	this->addChild(_healthBar);

	_magicBar = Slider::create();
	_magicBar->setPercent(int(PLAYER_MAGIC_PERCENT));
	_magicBar->loadBarTexture("/ui/playerMagicbarFrame.png");
	_magicBar->loadProgressBarTexture("/ui/playerMagicbarBlock.png");
	_magicBar->setScale(0.5);
	_magicBar->setPosition(PLAYER_MAGICBAR_POSITION);
	this->addChild(_magicBar);
	/**/
}
/****************************
* Name ：Player::init
* Summary ：人物初始化
* return ：
****************************/
void Player::initPlayer(Panel& panel)
{
	_panel = panel;

	/**
	_healthBar = Slider::create();
	_healthBar->setPercent(int(PLAYER_BLOOD_PERCENT));
	_healthBar->loadBarTexture("/ui/playerHealthbarFrame.png");
	_healthBar->loadProgressBarTexture("/ui/playerHealthbarBlock.png");
	_healthBar->setScale(0.5);
	_healthBar->setPosition(PLAYER_HEALTHBAR_POSITION);
	this->addChild(_healthBar);

	_magicBar = Slider::create();
	_magicBar->setPercent(int(PLAYER_MAGIC_PERCENT));
	_magicBar->loadBarTexture("/ui/playerMagicbarFrame.png");
	_magicBar->loadProgressBarTexture("/ui/playerMagicbarBlock.png");
	_magicBar->setScale(0.5);
	_magicBar->setPosition(PLAYER_MAGICBAR_POSITION);
	this->addChild(_magicBar);
	/**/
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
		if (weapon->launchAnAttack(_panel.doAttack()))
		{
			restoreMagic();
		}
	}
	else if (attackType == "skill")
	{
		if (useMagic()) 
		{
			weapon->launchAnSkill(_panel.doSkillAttack());
		}
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

void Player::restoreMagic()
{
	_panel.restoreMagic(34);
}

bool Player::magicIsFull()const
{
	return _panel.getMagicPoint() == _panel.getMaxMagicPoint();
}

bool Player::useMagic()
{
	if (magicIsFull()) 
	{
		_panel.setMagicPoint(0);
		return true;
	}
	else 
	{
		return false;
	}
}

int Player::getHealthPercent()
{
	return PLAYER_BLOOD_PERCENT;
}
int Player::getMagicPercent()
{
	return PLAYER_MAGIC_PERCENT;
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

	_weaponAnchorPositionX = 
		flipx ? 
		PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT : 
		PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT;

	weapon->setAnchorPoint(Vec2(_weaponAnchorPositionX, _weaponAnchorPositionY));
}

/****************************
* Name ：Player::keepHealthBar()
* Summary ：保持血条位置
* return ：
****************************/
void Player::keepHealthBar(Slider* healthBar)
{
	healthBar->setPosition(PLAYER_HEALTHBAR_POSITION);
}

void Player::keepMagicBar(Slider* magicBar)
{
	magicBar->setPosition(PLAYER_MAGICBAR_POSITION);
}
/****************************
* Name ：Player::setPositionWithAll
* Summary ：整体移动
* return ：
****************************/
void Player::setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon, Slider* healthBar, Slider* magicBar)
{
	this->setPosition(position);
	this->keepWeapon(weapon);
	this->refreshHealthBar(healthBar);
	this->refreshMagicBar(magicBar);
}
/****************************
* Name ：Player::refreshHealthBar()
* Summary ：更新血条
* return ：
****************************/
void Player::refreshHealthBar(Slider* healthBar)
{
	healthBar->setPercent(int(PLAYER_BLOOD_PERCENT));
	keepHealthBar(healthBar);
}
/****************************
* Name ：Player::refreshMagicBar()
* Summary ：更新蓝条
* return ：
****************************/
void Player::refreshMagicBar(Slider* magicBar)
{
	magicBar->setPercent(int(PLAYER_MAGIC_PERCENT));
	keepMagicBar(magicBar);
}
/****************************
* Name ：Player::refreshHealthBar()
* Summary ：更新人物
* return ：
****************************/
void Player::refreshPlayer()
{

}