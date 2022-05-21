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

	_healthBar = Slider::create();
	_healthBar->setPercent(PLAYER_BLOOD_PERCENT);
	_healthBar->loadBarTexture("/ui/playerHealthbarFrame.png");
	_healthBar->loadProgressBarTexture("/ui/playerHealthbarBlock.png");
	_healthBar->setScale(0.5);
	_healthBar->setPosition(PLAYER_HEALTHBAR_POSITION);
	this->addChild(_healthBar);
}
/****************************
* Name ��Player::init
* Summary �������ʼ��
* return ��
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
		weapon->launchAnAttack(_panel.doAttack());
	}
	else if (attackType == "skill")
	{
		weapon->launchAnSkill(_panel.doSkillAttack());
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

	float anchorPointX = 
		flipx ? 
		PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT : 
		PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT;

	weapon->setAnchorPoint(Vec2(anchorPointX, PLAYER_WEAPON_ANCHOR_POSITION_Y));
}
/****************************
* Name ��Player::setPositionWithWeapon
* Summary �����������ƶ�
* return ��
****************************/
void Player::setPositionWithWeapon(cocos2d::Vec2& position, Weapon* weapon)
{
	this->setPosition(position);
	this->keepWeapon(weapon);
}

/****************************
* Name ��Player::keepHealthBar()
* Summary ������Ѫ��λ��
* return ��
****************************/
void Player::keepHealthBar()
{
	_healthBar->setPosition(PLAYER_HEALTHBAR_POSITION);
}
/****************************
* Name ��Player::setPositionWithAll
* Summary �������ƶ�
* return ��
****************************/
void Player::setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon)
{
	this->setPosition(position);
	this->keepWeapon(weapon);
	this->refreshHealthBar();
}
/****************************
* Name ��Player::refreshHealthBar()
* Summary ������Ѫ��
* return ��
****************************/
void Player::refreshHealthBar()
{
	_healthBar->setPercent(PLAYER_BLOOD_PERCENT);
	keepHealthBar();
}
/****************************
* Name ��Player::refreshHealthBar()
* Summary ����������
* return ��
****************************/
void Player::refreshPlayer()
{

}