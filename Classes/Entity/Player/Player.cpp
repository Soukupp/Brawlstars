//���� : ����
//���� : 2022-5-18
#include "Player.h"

USING_NS_CC;

/*===============================================================================*/
/*==========================�����ǳ�ʼ�������ֱ�ӵ���===========================*/
/*===============================================================================*/

/****************************
* Name ��Player::init
* Summary �������ʼ��
* return ��
****************************/
void Player::initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
{
	//��ʼ�����
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
* Name ��Player::init
* Summary �������ʼ��
* return ��
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
* Name ��Player::create
* Summary ����������
* return ������ָ��
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
* Name ��Player::getPanel()
* Summary ����ȡ���
* return �����ָ��
****************************/
Panel* Player::getPanel()
{
	return &_panel;
}

/*===============================================================================*/
/*=====================================��������Ϊ================================*/
/*===============================================================================*/

/****************************
* Name ��Player::launchAnAttack()
* Summary �����𹥻�(�봫�� "attack" �� "skill")
* return ��
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
* Name ��Player::hitPlayer
* Summary ���Խ�ɫ���й���
* return ����ɵ��˺�
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
/*==================================�������ƶ����===============================*/
/*===============================================================================*/

/****************************
* Name ��Player::keepWeapon
* Summary ����������λ��
* return ��
****************************/
void Player::keepWeapon(Weapon* weapon)
{
	weapon->setPosition(this->getPosition());
}
/****************************
* Name ��Player::runFlipxWithWeapon
* Summary ������������ת
* return ��
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
* Name ��Player::keepHealthBar()
* Summary ������Ѫ��λ��
* return ��
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
* Name ��Player::setPositionWithAll
* Summary �������ƶ�
* return ��
****************************/
void Player::setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon, Slider* healthBar, Slider* magicBar)
{
	this->setPosition(position);
	this->keepWeapon(weapon);
	this->refreshHealthBar(healthBar);
	this->refreshMagicBar(magicBar);
}
/****************************
* Name ��Player::refreshHealthBar()
* Summary ������Ѫ��
* return ��
****************************/
void Player::refreshHealthBar(Slider* healthBar)
{
	healthBar->setPercent(int(PLAYER_BLOOD_PERCENT));
	keepHealthBar(healthBar);
}
/****************************
* Name ��Player::refreshMagicBar()
* Summary ����������
* return ��
****************************/
void Player::refreshMagicBar(Slider* magicBar)
{
	magicBar->setPercent(int(PLAYER_MAGIC_PERCENT));
	keepMagicBar(magicBar);
}
/****************************
* Name ��Player::refreshHealthBar()
* Summary ����������
* return ��
****************************/
void Player::refreshPlayer()
{

}