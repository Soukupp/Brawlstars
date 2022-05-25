//作者 : 王鹏
//日期 : 2022-5-23
#include "Hero1.h"

USING_NS_CC;

/****************************
* Name ：create
* Summary ：创建
* return ：hero指针
****************************/
Hero1* Hero1::create(const std::string& filename)
{
	Hero1* player = new (std::nothrow) Hero1();
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
Hero1* Hero1::create(const std::string& filename, const Rect& rect)
{
	Hero1* player = new (std::nothrow) Hero1();
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
void Hero1::initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
{
	//初始化面板
	_panel.init(maxHealthPoint, attack, defence, skillAttackRate, attackRate);
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
}
/****************************
* Name ：launchAnAttack
* Summary ：发动攻击 输入"attack" "skill" 调用
* return ：
****************************/
void Hero1::launchAnAttack(Weapon* weapon, const std::string& attackType)
{
	if (attackType == "attack")
	{
		if (weapon->launchAnAttack(_panel.doAttack()))
		{
			restoreMagic();
		}

		auto _animationAttack = CCAnimation::create();
		for (int loop = 1; loop <= 7; ++loop)
		{
			char szName[100] = { 0 };
			sprintf(szName, "Character/Hero1/attack/attack%d.png", loop);
			_animationAttack->addSpriteFrameWithFile(szName);
		}
		_animationAttack->setDelayPerUnit(0.2f / 7.0f);
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
			for (int loop = 1; loop <= 18; ++loop)
			{
				char szName[100] = { 0 };
				sprintf(szName, "Character/Hero1/skill/skill%02d.png", loop);
				_animationAttack->addSpriteFrameWithFile(szName);
			}
			_animationAttack->setDelayPerUnit(1.5f / 18.0f);
			_animationAttack->setRestoreOriginalFrame(true);
			auto _animateAttack = CCAnimate::create(_animationAttack);
			//this->runAction(Hide::create());
			this->setAnchorPoint(Vec2(0.5f - _direct * 0.1f, 0.5f));
			this->runAction(_animateAttack);
			this->setAnchorPoint(Vec2(0.5f, 0.5f));
			//this->runAction(Show::create());
		}
	}
}
/****************************
* Name ：keepHealthBar
* Summary ：保持血条位置
* return ：
****************************/
void Hero1::keepHealthBar(Slider* healthBar)
{
	healthBar->setPosition(HERO1_HEALTHBAR_POSITION);
	//_healthBar->setPosition(position);
}
/****************************
* Name ：keepMagicBar
* Summary ：保持蓝条位置
* return ：
****************************/
void Hero1::keepMagicBar(Slider* magicBar)
{
	magicBar->setPosition(HERO1_MAGICBAR_POSITION);
}
/****************************
* Name ：keepWeapon
* Summary ：保持武器位置
* return ：
****************************/
void Hero1::keepWeapon(Weapon* weapon)
{
	weapon->setPosition(HERO1_WEAPON_POSITION_X, HERO1_WEAPON_POSITION_Y);
}
/****************************
* Name ：runFlipxWithWeapon
* Summary ：带着武器翻转
* return ：
****************************/
void Hero1::runFlipxWithWeapon(bool flipx, Weapon* weapon)
{

	_weaponAnchorPositionX = (flipx ?
		HERO1_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT :
		HERO1_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT);
	_direct = (flipx ? -1.0f : 1.0f);

	weapon->setAnchorPoint(Vec2(_weaponAnchorPositionX, _weaponAnchorPositionY));
	keepWeapon(weapon);

	this->runAction(FlipX::create(flipx));
	weapon->runAction(FlipX::create(flipx));
}