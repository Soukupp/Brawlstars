//作者 : 王鹏
//日期 : 2022-5-18
#include "Player.h"
#include "Entity/Weapon/Weapon.h"
#include <SimpleAudioEngine.h>


USING_NS_CC;

/*===============================================================================*/
/*==============================以下是创建与初始化===============================*/
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
}
/****************************
* Name ：Player::init
* Summary ：人物初始化
* return ：
****************************/
void Player::initPlayer(Panel& panel)
{
	_panel.init(panel.getMaxHealthPoint(), panel.getAttack(), panel.getDefence(), panel.getSkillRate(), panel.getAttackRate());
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
/*================================以下是角色行为==================================*/
/*===============================================================================*/

/****************************
* Name ：Player::launchAnAttack()
* Summary ：发起攻击(请传入 "attack" 或 "skill")
* return ：
****************************/
void Player::launchAnAttack(Weapon* weapon, const std::string& attackType, Slider* magicBar, Player* enemy, Slider* enemyHealthBar)
{
	if (enemy != nullptr) {
		if (attackType == "attack")
		{
			if (this->playerCollisionTest(enemy, weapon, true)) {
				if (weapon->launchAnAttack(this->_panel.doAttack(), enemy))
				{
					//成功造成伤害才回能
					restoreMagic();
					enemy->refreshHealthBar(enemyHealthBar);
				}
			}
		}
		else if (attackType == "skill")
		{
			if (useMagic())
			{
				if (this->playerCollisionTest(enemy, weapon, true)) {
					weapon->launchAnAttack(this->_panel.doSkillAttack(), enemy);
					enemy->refreshHealthBar(enemyHealthBar);
				}
			}
		}
		if (enemy->_panel.getHealthPoint() <= 0)
		{
			enemy->_panel.setIsSurvive(false);
		}
		this->refreshMagicBar(magicBar);
	}
	else
	{
		log("Player::launchAnAttack enemy == null");
	}
}

/****************************
* Name ：Player::hitPlayer
* Summary ：对角色进行攻击
* return ：造成的伤害
****************************/
int Player::hitPlayer(int attack)
{
	//结算伤害后可以通过panel的getIsSurvive获取是否存活
	return _panel.hit(attack);
}

/****************************
* Name ：Player::restoreMagic
* Summary ：补充蓝量
* return ：
****************************/
void Player::restoreMagic()
{
	//三次回满
	_panel.restoreMagic(34);
}

/****************************
* Name ：Player::magicIsFull()const
* Summary ：蓝量已满
* return ：true:满 false:未满
****************************/
bool Player::magicIsFull()const
{
	return _panel.getMagicPoint() == _panel.getMaxMagicPoint();
}

/****************************
* Name ：Player::useMagic
* Summary ：使用蓝
* return ：true:使用成功 false:使用失败
****************************/
bool Player::useMagic()
{
	if (magicIsFull()) 
	{
		_panel.setMagicPoint(0);
		return true;
	}
	return false;
}

/****************************
* Name ：Player::getHealthPercent
* Summary ：获取当前血量百分比
* return ：血量百分比
****************************/
int Player::getHealthPercent()
{
	return PLAYER_BLOOD_PERCENT;
}

/****************************
* Name ：Player::getMagicPercent
* Summary ：获取当前蓝量百分比
* return ：蓝量百分比
****************************/
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
	weapon->setPosition(
		this->getPosition().x+this->getContentSize().width+weapon->getContentSize().width,
		this->getPosition().y);
}

/****************************
* Name ：Player::runFlipxWithWeapon
* Summary ：带着武器翻转
* return ：
****************************/
void Player::runFlipxWithWeapon(bool flipx,Weapon* weapon)
{
	_weaponAnchorPositionX = (flipx ?
		PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT :
		PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT);
	_direct = (flipx ? -1 : 1);

	weapon->setAnchorPoint(Vec2(_weaponAnchorPositionX, _weaponAnchorPositionY));
	keepWeapon(weapon);

	this->runAction(FlipX::create(flipx));
	weapon->runAction(FlipX::create(flipx));
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

/****************************
* Name ：Player::keepMagicBar
* Summary ：保持蓝条位置
* return ：
****************************/
void Player::keepMagicBar(Slider* magicBar)
{
	magicBar->setPosition(PLAYER_MAGICBAR_POSITION);
}

/****************************
* Name ：Player::keepLevelText
* Summary ：保持等级位置
* return ：
****************************/
void Player::keepLevelText(cocos2d::Label* levelText, Slider* bar)
{
	levelText->setPosition(PLAYER_LEVELTEXT_POSITION);
}

/****************************
* Name ：Player::setPositionWithAll
* Summary ：整体移动
* return ：
****************************/
void Player::setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon, Slider* healthBar, Slider* magicBar, cocos2d::Label* levelText)
{
	
	this->setPosition(position);
	this->keepWeapon(weapon);
	this->refreshHealthBar(healthBar);
	this->refreshMagicBar(magicBar);
	this->keepLevelText(levelText, magicBar);

}

/*===============================================================================*/
/*==================================以下是状态相关===============================*/
/*===============================================================================*/

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

/****************************
* Name ：palyerCollisionTest1
* Summary ：近距离攻击碰撞检测
* 参数说明 : target : 攻击对象
*           weapon : 武器对象
****************************/
bool Player::playerCollisionTest(Player* target,Weapon* weapon, bool ifPlayEffect)
{
	return true;
}

/****************************
* Name ：Player::upgrade()
* Summary ：人物升级
* return ：
****************************/
void Player::upgrade(cocos2d::Label* levelText, Slider* bar)
{
}

/****************************
* Name ：Player::initWalkAction
* Summary ：初始化行走动作
* return ：是否初始化成功
****************************/
bool Player::initWalkAction()
{
	return true;
}

/****************************
* Name ：Player::initNormalAction
* Summary ：初始化静止动作
* return ：是否初始化成功
****************************/
bool Player::initNormalAction()
{
	return true;
}

/****************************
* Name ：Player::initAttackAction
* Summary ：初始化普攻动作
* return ：是否初始化成功
****************************/
bool Player::initAttackAction()
{
	return true;
}

/****************************
* Name ：Player::initSkillAction
* Summary ：初始化技能动作
* return ：是否初始化成功
****************************/
bool Player::initSkillAction()
{
	return true;
}

/****************************
* Name ：Player::getID
* Summary ：获取角色id
* return ：id
****************************/
int Player::getID()
{
	return _ID;
}
