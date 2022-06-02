//作者 : 王鹏
//日期 : 2022-5-23
#include "Hero2.h"

USING_NS_CC;
using namespace CocosDenshion;

/*===============================================================================*/
/*=============================以下是创建与初始化================================*/
/*===============================================================================*/

/****************************
* Name ：create
* Summary ：创建
* return ：hero指针
****************************/
Hero2* Hero2::create(const std::string& filename)
{
	Hero2* player = new (std::nothrow) Hero2();
	if (player && player->initWithFile(filename))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}
/****************************
* Name ：create
* Summary ：创建
* return ：hero指针
****************************/
Hero2* Hero2::create(const std::string& filename, const Rect& rect)
{
	Hero2* player = new (std::nothrow) Hero2();
	if (player && player->initWithFile(filename, rect))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}
/****************************
* Name ：initPlayer
* Summary ：初始化
* return ：
****************************/
void Hero2::initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
{
	//初始化面板
	_panel.init(maxHealthPoint, attack, defence, skillAttackRate, attackRate);
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
}
/****************************
* Name ：initPlayer
* Summary ：按默认值初始化
* return ：
****************************/
void Hero2::initPlayer()
{
	//初始化面板
	_panel.init(HERO2_INIT_MAXHEALTHPOINT, HERO2_INIT_ATTACK, HERO2_INIT_DEFENCE, HERO2_INIT_SKILLRATE, HERO2_INIT_ATTACKRATE);
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
}

/*===============================================================================*/
/*============================以下是发动攻击与动画===============================*/
/*===============================================================================*/

/****************************
* Name ：launchAnAttack
* Summary ：发动攻击 输入"attack" "skill" 调用
* return ：
****************************/
void Hero2::launchAnAttack(Weapon* weapon, const std::string& attackType, Slider* magicBar)
{
	if (attackType == "attack")
	{
		if (weapon->launchAnAttack(_panel.doAttack()))
		{
			restoreMagic();
		}

		auto _animationAttack = CCAnimation::create();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_2.mp3");
		for (int loop = 1; loop <= HERO2_YOU_ATTACK_FRAME; ++loop)
		{
			char szName[100] = { 0 };
			sprintf(szName, "Character/Hero2/attack/attack%02d.png", loop);
			_animationAttack->addSpriteFrameWithFile(szName);
		}
		_animationAttack->setDelayPerUnit(HERO2_YOU_ATTACK_TIME / HERO2_YOU_ATTACK_FRAME);
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
			weapon->launchAnSkill(_panel.doSkillAttack());

			auto _animationAttack = CCAnimation::create();
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_2.mp3");
			for (int loop = 1; loop <= HERO2_YOU_SKILL_FRAME; ++loop)
			{
				char szName[100] = { 0 };
				sprintf(szName, "Character/Hero2/skill/skill%02d.png", loop);
				_animationAttack->addSpriteFrameWithFile(szName);
				if (loop % 3 == 0)
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_2.mp3");
			}
			_animationAttack->setDelayPerUnit(HERO2_YOU_SKILL_TIME / HERO2_YOU_SKILL_FRAME);
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
/*=======================以下是UI、武器等的位置保持跟随==========================*/
/*===============================================================================*/

/****************************
* Name ：keepHealthBar
* Summary ：保持血条位置
* return ：
****************************/
void Hero2::keepHealthBar(Slider* healthBar)
{
	healthBar->setPosition(HERO2_HEALTHBAR_POSITION);
	//_healthBar->setPosition(position);
}
/****************************
* Name ：keepMagicBar
* Summary ：保持蓝条位置
* return ：
****************************/
void Hero2::keepMagicBar(Slider* magicBar)
{
	magicBar->setPosition(HERO2_MAGICBAR_POSITION);
}
/****************************
* Name ：keepWeapon
* Summary ：保持武器位置
* return ：
****************************/
void Hero2::keepWeapon(Weapon* weapon)
{
	weapon->setPosition(HERO2_WEAPON_POSITION_X, HERO2_WEAPON_POSITION_Y);
}
/****************************
* Name ：keepLevelText
* Summary ：保持等级位置
* return ：
****************************/
void Hero2::keepLevelText(cocos2d::Label* levelText, Slider* bar)
{
	levelText->setPosition(HERO2_LEVELTEXT_POSITION);
}
/****************************
* Name ：runFlipxWithWeapon
* Summary ：带着武器翻转
* return ：
****************************/
void Hero2::runFlipxWithWeapon(bool flipx, Weapon* weapon)
{

	_weaponAnchorPositionX = (flipx ?
		HERO2_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT :
		HERO2_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT);
	_direct = (flipx ? -1.0f : 1.0f);

	weapon->setAnchorPoint(Vec2(_weaponAnchorPositionX, _weaponAnchorPositionY));
	keepWeapon(weapon);

	this->runAction(FlipX::create(flipx));
	weapon->runAction(FlipX::create(flipx));
}
/****************************
* Name ：setPositionWithAll
* Summary ：整体移动
* return ：
****************************/
void Hero2::setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon, Slider* healthBar, Slider* magicBar, cocos2d::Label* levelText)
{
	this->setPosition(position);
	this->keepWeapon(weapon);
	this->refreshHealthBar(healthBar);
	this->refreshMagicBar(magicBar);
	this->keepLevelText(levelText, magicBar);
}

/*===============================================================================*/
/*==================================以下是升级===================================*/
/*===============================================================================*/

/****************************
* Name ：Hero2::upgrade()
* Summary ：人物升级
* return ：
****************************/
void Hero2::upgrade(cocos2d::Label* levelText, Slider* bar)
{
	if (_level < PLAYER_MAX_GRADE) {
		_level++;
		levelText->setString((std::string("Lv.") + std::to_string(_level)));
		_panel.setMaxHealthPoint(HERO2_INIT_MAXHEALTHPOINT / 10 + _panel.getMaxHealthPoint());
		_panel.setAttack(HERO2_INIT_ATTACK / 10 + _panel.getAttack());
		_panel.setDefence(HERO2_INIT_DEFENCE / 10 + _panel.getDefence());
		_panel.setAttackRate(0.1f + _panel.getAttackRate());
		_panel.setSkillRate(0.1f + _panel.getSkillRate());
		_panel.setHealthPoint(HERO2_INIT_MAXHEALTHPOINT / 10 + _panel.getHealthPoint());
		this->keepLevelText(levelText, bar);
	}
}