//���� : ����
//���� : 2022-6-2
#include "Hero1.h"
#include "Hero2.h"
#include "Hero3.h"
#include "Hero4.h"
//#include "Entity/Weapon/Weapon.h"
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
Hero4* Hero4::create(const std::string& filename)
{
	Hero4* player = new (std::nothrow) Hero4();
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
Hero4* Hero4::create(const std::string& filename, const Rect& rect)
{
	Hero4* player = new (std::nothrow) Hero4();
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
* Summary ����ʼ��
* return ��
****************************/
void Hero4::initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
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
void Hero4::initPlayer()
{
	//��ʼ�����
	_panel.init(HERO4_INIT_MAXHEALTHPOINT, HERO4_INIT_ATTACK, HERO4_INIT_DEFENCE, HERO4_INIT_SKILLRATE, HERO4_INIT_ATTACKRATE);
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
}

/*===============================================================================*/
/*============================�����Ƿ��������붯��===============================*/
/*===============================================================================*/

/****************************
* Name ��launchAnAttack
* Summary ���������� ����"attack" "skill" ����
* return ��
****************************/
template<typename Enemy>
void Hero4::launchAnAttack(Weapon* weapon, const std::string& attackType, Slider* magicBar, Enemy* enemy, Slider* enemyHealthBar)
{
	if (attackType == "attack")
	{
		if (weapon->launchAnAttack(_panel.doAttack(), enemy))
		{
			restoreMagic();
			enemy->refreshHealthBar(enemyHealthBar);
		}

		auto _animationAttack = CCAnimation::create();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_2.mp3");
		for (int loop = 1; loop <= HERO4_YOU_ATTACK_FRAME; ++loop)
		{
			char szName[100] = { 0 };
			sprintf(szName, "Character/Hero4/attack/attack%02d.png", loop);
			_animationAttack->addSpriteFrameWithFile(szName);
		}
		_animationAttack->setDelayPerUnit(HERO4_YOU_ATTACK_TIME / HERO4_YOU_ATTACK_FRAME);
		_animationAttack->setRestoreOriginalFrame(true);
		auto _animateAttack = CCAnimate::create(_animationAttack);
		//this->runAction(Hide::create());
		this->setAnchorPoint(Vec2(0.5f - _direct * 0.1f, 0.5f));
		this->runAction(_animateAttack);
		this->setAnchorPoint(Vec2(0.5f, 0.5f));
		//this->runAction(Show::create());
	}
	else if (attackType == "skill")
	{
		if (useMagic())
		{
			weapon->launchAnAttack(_panel.doSkillAttack(), enemy);
			enemy->refreshHealthBar(enemyHealthBar);

			auto _animationAttack = CCAnimation::create();
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_2.mp3");
			for (int loop = 1; loop <= HERO4_YOU_SKILL_FRAME; ++loop)
			{
				char szName[100] = { 0 };
				sprintf(szName, "Character/Hero4/skill/skill%02d.png", loop);
				_animationAttack->addSpriteFrameWithFile(szName);
				if (loop % 3 == 0)
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_2.mp3");
			}
			_animationAttack->setDelayPerUnit(HERO4_YOU_SKILL_TIME / HERO4_YOU_SKILL_FRAME);
			_animationAttack->setRestoreOriginalFrame(true);
			auto _animateAttack = CCAnimate::create(_animationAttack);
			//this->runAction(Hide::create());
			this->setAnchorPoint(Vec2(0.5f - _direct * 0.1f, 0.5f));
			this->runAction(_animateAttack);
			this->setAnchorPoint(Vec2(0.5f, 0.5f));
			//this->runAction(Show::create());
		}
	}
	this->refreshMagicBar(magicBar);
}

/*===============================================================================*/
/*=======================������UI�������ȵ�λ�ñ��ָ���==========================*/
/*===============================================================================*/

/****************************
* Name ��keepHealthBar
* Summary ������Ѫ��λ��
* return ��
****************************/
void Hero4::keepHealthBar(Slider* healthBar)
{
	healthBar->setPosition(HERO4_HEALTHBAR_POSITION);
	//_healthBar->setPosition(position);
}
/****************************
* Name ��keepMagicBar
* Summary ����������λ��
* return ��
****************************/
void Hero4::keepMagicBar(Slider* magicBar)
{
	magicBar->setPosition(HERO4_MAGICBAR_POSITION);
}
/****************************
* Name ��keepWeapon
* Summary ����������λ��
* return ��
****************************/
void Hero4::keepWeapon(Weapon* weapon)
{
	weapon->setPosition(HERO4_WEAPON_POSITION_X, HERO4_WEAPON_POSITION_Y);
}
/****************************
* Name ��keepLevelText
* Summary �����ֵȼ�λ��
* return ��
****************************/
void Hero4::keepLevelText(cocos2d::Label* levelText, Slider* bar)
{
	levelText->setPosition(HERO4_LEVELTEXT_POSITION);
}
/****************************
* Name ��runFlipxWithWeapon
* Summary ������������ת
* return ��
****************************/
void Hero4::runFlipxWithWeapon(bool flipx, Weapon* weapon)
{

	_weaponAnchorPositionX = (flipx ?
		HERO4_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT :
		HERO4_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT);
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
void Hero4::setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon, Slider* healthBar, Slider* magicBar, cocos2d::Label* levelText)
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
* Name ��Hero4::upgrade()
* Summary ����������
* return ��
****************************/
void Hero4::upgrade(cocos2d::Label* levelText, Slider* bar)
{
	if (_level < PLAYER_MAX_GRADE) {
		_level++;
		levelText->setString((std::string("Lv.") + std::to_string(_level)));
		_panel.setMaxHealthPoint(HERO4_INIT_MAXHEALTHPOINT / 10 + _panel.getMaxHealthPoint());
		_panel.setAttack(HERO4_INIT_ATTACK / 10 + _panel.getAttack());
		_panel.setDefence(HERO4_INIT_DEFENCE / 10 + _panel.getDefence());
		_panel.setAttackRate(0.1f + _panel.getAttackRate());
		_panel.setSkillRate(0.1f + _panel.getSkillRate());
		_panel.setHealthPoint(HERO4_INIT_MAXHEALTHPOINT / 10 + _panel.getHealthPoint());
		this->keepLevelText(levelText, bar);
	}
}

int Hero4::getID()
{
	return ID;
}