//���� : ����
//���� : 2022-6-2

//�޸� : ����
//���� : 2022-6-3
//ʵ�� : ���ﶯ�����ܺ����ӿ�

#include "Hero1.h"
#include "Hero2.h"
#include "Hero3.h"
#include "Hero4.h"

USING_NS_CC;
using namespace CocosDenshion;

/*===============================================================================*/
/*=============================�����Ǵ������ʼ��================================*/
/*===============================================================================*/

/****************************
* Name ��create
* Summary ������
* return ��heroָ��
****************************/
Hero3* Hero3::create(const std::string& filename)
{
	Hero3* player = new (std::nothrow) Hero3();
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
* Summary ������
* return ��heroָ��
****************************/
Hero3* Hero3::create(const std::string& filename, const Rect& rect)
{
	Hero3* player = new (std::nothrow) Hero3();
	if (player && player->initWithFile(filename, rect))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

/****************************
* Name ��initPlayer
* Summary ���Զ���ֵ��ʼ��
* return ��
****************************/
void Hero3::initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
{
	//��ʼ�����
	_panel.init(maxHealthPoint, attack, defence, skillAttackRate, attackRate);
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
}

/****************************
* Name ��initPlayer
* Summary ����Ĭ��ֵ��ʼ��
* return ��
****************************/
void Hero3::initPlayer()
{
	//��ʼ�����
	_panel.init(HERO3_INIT_MAXHEALTHPOINT, HERO3_INIT_ATTACK, HERO3_INIT_DEFENCE, HERO3_INIT_SKILLRATE, HERO3_INIT_ATTACKRATE);
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
}

/*===============================================================================*/
/*=======================������UI�������ȵ�λ�ñ��ָ���==========================*/
/*===============================================================================*/

/****************************
* Name ��keepHealthBar
* Summary ������Ѫ��λ��
* return ��
****************************/
void Hero3::keepHealthBar(Slider* healthBar)
{
	float x = this->getPosition().x;
	float y = this->getPosition().y + 30;

	healthBar->setPosition(Vec2::Vec2(x, y));
}

/****************************
* Name ��keepMagicBar
* Summary ����������λ��
* return ��
****************************/
void Hero3::keepMagicBar(Slider* magicBar)
{
	float x = this->getPosition().x;
	float y = this->getPosition().y + 25;

	magicBar->setPosition(Vec2::Vec2(x, y));
}

/****************************
* Name ��keepWeapon
* Summary ����������λ��
* return ��
****************************/
void Hero3::keepWeapon(Weapon* weapon)
{
	weapon->setPosition(HERO3_WEAPON_POSITION_X, HERO3_WEAPON_POSITION_Y);
}

/****************************
* Name ��keepLevelText
* Summary �����ֵȼ�λ��
* return ��
****************************/
void Hero3::keepLevelText(cocos2d::Label* levelText, Slider* bar)
{
	float x = this->getPosition().x;
	float y = this->getPosition().y + 35;

	levelText->setPosition(Vec2::Vec2(x, y));
}

/****************************
* Name ��runFlipxWithWeapon
* Summary ������������ת
* return ��
****************************/
void Hero3::runFlipxWithWeapon(bool flipx, Weapon* weapon)
{

	_weaponAnchorPositionX = (flipx ?
		HERO3_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT :
		HERO3_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT);
	_direct = (flipx ? -1.0f : 1.0f);

	weapon->setAnchorPoint(Vec2(_weaponAnchorPositionX, _weaponAnchorPositionY));
	keepWeapon(weapon);

	this->runAction(FlipX::create(flipx));
	weapon->runAction(FlipX::create(flipx));
}

/****************************
* Name ��setPositionWithAll
* Summary �������ƶ�
* return ��
****************************/
void Hero3::setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon, Slider* healthBar, Slider* magicBar, cocos2d::Label* levelText)
{
	this->setPosition(position);
	this->keepWeapon(weapon);
	this->refreshHealthBar(healthBar);
	this->refreshMagicBar(magicBar);
	this->keepLevelText(levelText, magicBar);
}

/*===============================================================================*/
/*==================================����������===================================*/
/*===============================================================================*/

/****************************
* Name ��Hero3::upgrade()
* Summary ����������
* return ��
****************************/
void Hero3::upgrade(cocos2d::Label* levelText, Slider* bar)
{
	if (_level < PLAYER_MAX_GRADE) 
	{
		_level++;
		levelText->setString((std::string("Lv.") + std::to_string(_level)));
		_panel.setMaxHealthPoint(HERO3_INIT_MAXHEALTHPOINT / 10 + _panel.getMaxHealthPoint());
		_panel.setAttack(HERO3_INIT_ATTACK / 10 + _panel.getAttack());
		_panel.setDefence(HERO3_INIT_DEFENCE / 10 + _panel.getDefence());
		_panel.setAttackRate(0.1f + _panel.getAttackRate());
		_panel.setSkillRate(0.1f + _panel.getSkillRate());
		_panel.setHealthPoint(HERO3_INIT_MAXHEALTHPOINT / 10 + _panel.getHealthPoint());
		_panel.treat(HERO3_INIT_MAXHEALTHPOINT / 2);
		this->keepLevelText(levelText, bar);
	}
}

/*===============================================================================*/
/*==================================�����Ƕ���===================================*/
/*===============================================================================*/

/****************************
* Name ��initWalkAction
* Summary ����ʼ�����߶���
* return ���Ƿ��ʼ���ɹ�
****************************/
bool Hero3::initWalkAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("character/Hero3/hero3_Run.plist", "character/Hero3/hero3_Run.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 0; i < 6; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("Run-%d.png", i)->getCString());
		playerFrameArray.pushBack(frame);
	}

	auto* animation = Animation::createWithSpriteFrames(playerFrameArray, 1.0 / 12.0);

	this->setWalkAction(RepeatForever::create(Animate::create(animation)));

	if (_walkAction != nullptr)
		return true;
	else
		return false;
}

/****************************
* Name ��initNormalAction
* Summary ����ʼ����ֹ����
* return ���Ƿ��ʼ���ɹ�
****************************/
bool Hero3::initNormalAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("character/Hero3/hero3_Start.plist", "character/Hero3/hero3_Start.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 0; i < 6; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("Idle3-%d.png", i)->getCString());
		playerFrameArray.pushBack(frame);
	}

	auto* animation = Animation::createWithSpriteFrames(playerFrameArray, 1.0 / 9.0);
	this->setNormalAction(RepeatForever::create(Animate::create(animation)));

	if (_normalAction != nullptr)
		return true;
	else
		return false;
}

/****************************
* Name ��initAttackAction
* Summary ����ʼ���չ�����
* return ���Ƿ��ʼ���ɹ�
****************************/
bool Hero3::initAttackAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("character/Hero3/hero3_Attack.plist", "character/Hero3/hero3_Attack.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 0; i < 8; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("Attack2-%d.png", i)->getCString());
		playerFrameArray.pushBack(frame);
	}

	auto* animation = Animation::createWithSpriteFrames(playerFrameArray, 1.0 / 12.0);
	animation->setLoops(1);
	auto* animate = Animate::create(animation);
	this->setAttackAction(animate);

	if (_normalAction != nullptr)
		return true;
	else
		return false;
}

/****************************
* Name ��initSkillAction
* Summary ����ʼ�����ܶ���
* return ���Ƿ��ʼ���ɹ�
****************************/
bool Hero3::initSkillAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("character/Hero3/hero3_Skill.plist", "character/Hero3/hero3_Skill.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 1; i < 9; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("skill1- (%d).png", i)->getCString());
		playerFrameArray.pushBack(frame);
	}

	auto* animation = Animation::createWithSpriteFrames(playerFrameArray, 1.0 / 12.0);
	auto* animate = Animate::create(animation);
	this->setSkillAction(animate);

	if (_normalAction != nullptr)
		return true;
	else
		return false;
}

/*===============================================================================*/
/*================================��������ײ���=================================*/
/*===============================================================================*/

/****************************
* Name ��palyerCollisionTest1
* Summary �������빥����ײ���
* ����˵�� : target : ��������
*           weapon : ��������
****************************/
bool Hero3::playerCollisionTest1(Player* target, Weapon* weapon)
{
	if (target == nullptr)
		return false;
	_targetX = target->getPosition().x;                           //Ŀ��λ��X
	_targetY = target->getPosition().y;                           //Ŀ��λ��Y
	_targetWidth = target->_width;                                //Ŀ��Ŀ��
	_targetHeight = target->_height;                              //Ŀ��ĸ߶�
	_weaponWidth = weapon->getContentSize().width;                //������Χ�Ŀ��
	_weaponHeight = weapon->getContentSize().height;              //������Χ�ĸ߶�

	_thisX = this->getPosition().x;
	_thisY = this->getPosition().y;

	if (_direct == 1)
	{
		if ((_targetX - _thisX) < (_weaponWidth + _targetWidth / 2) && (_thisX - _targetX) <= 0)
		{           //��Χ�ж�
			if (fabs(_thisY - _targetY) < (_weaponHeight / 2 + _targetHeight / 2))
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_2.mp3");
				return true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
			return false;
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
			return false;
		}
	}
	if (_direct == -1)
	{
		if ((_thisX - _targetX) < (_weaponWidth + _targetWidth / 2) && (_thisX - _targetX) >= 0)
		{           //��Χ�ж�
			if (fabs(_thisY - _targetY) < (_weaponHeight / 2 + _targetHeight / 2))
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_2.mp3");
				return true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
			return false;
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
			return false;
		}
	}
}

/****************************
* Name ��palyerCollisionTest2
* Summary �������빥����ײ���
* ����˵�� : target : ��������
*           weapon : ��������
****************************/
bool Hero3::playerCollisionTest2(Player* target, Weapon* weapon)
{
	_targetX = target->getPosition().x;                           //Ŀ��λ��X
	_targetY = target->getPosition().y;                           //Ŀ��λ��Y
	_targetWidth = target->_width;         //Ŀ��Ŀ��
	_targetHeight = target->_height;        //Ŀ��ĸ߶�
	_weaponWidth = weapon->getContentSize().width;                //������Χ�Ŀ��
	_weaponHeight = weapon->getContentSize().height;              //������Χ�ĸ߶�

	_thisX = this->getPosition().x;
	_thisY = this->getPosition().y;

	if (_direct == 1)
	{
		if ((_targetX - _thisX) < (_weaponWidth + _targetWidth / 2) && (_thisX - _targetX) <= 0)
		{           //��Χ�ж�
			if (fabs(_thisY - _targetY) < (_weaponHeight / 2 + _targetHeight / 2))
			{
				return true;
			}
			return false;
		}
		else
		{
			return false;
		}
	}
	if (_direct == -1)
	{
		if ((_thisX - _targetX) < (_weaponWidth + _targetWidth / 2) && (_thisX - _targetX) >= 0)
		{           //��Χ�ж�
			if (fabs(_thisY - _targetY) < (_weaponHeight / 2 + _targetHeight / 2))
			{
				return true;
			}
			return false;
		}
		else
		{
			return false;
		}
	}
}

/****************************
* Name ��getID
* Summary ����ȡ��ɫid
* return ��id
****************************/
int Hero3::getID()
{
	return _ID;
}