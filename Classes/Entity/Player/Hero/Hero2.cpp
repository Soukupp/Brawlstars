//作者 : 王鹏
//日期 : 2022-5-23
#include "Hero2.h"

USING_NS_CC;

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

void Hero2::initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
{
	//初始化面板
	_panel.init(maxHealthPoint, attack, defence, skillAttackRate, attackRate);
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
}

void Hero2::launchAnAttack(Weapon* weapon, const std::string& attackType)
{
	if (attackType == "attack")
	{
		if (weapon->launchAnAttack(_panel.doAttack()))
		{
			restoreMagic();
		}

		auto _animationAttack = CCAnimation::create();
		for (int loop = 1; loop <= 20; ++loop)
		{
			char szName[100] = { 0 };
			sprintf(szName, "Character/Hero2/attack/attack%02d.png", loop);
			_animationAttack->addSpriteFrameWithFile(szName);
		}
		_animationAttack->setDelayPerUnit(0.5f / 20.0f);
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
			for (int loop = 1; loop <= 7; ++loop)
			{
				char szName[100] = { 0 };
				sprintf(szName, "Character/Hero2/skill/skill%02d.png", loop);
				_animationAttack->addSpriteFrameWithFile(szName);
			}
			_animationAttack->setDelayPerUnit(1.0f / 7.0f);
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

void Hero2::keepHealthBar(Slider* healthBar)
{
	healthBar->setPosition(HERO2_HEALTHBAR_POSITION);
	//_healthBar->setPosition(position);
}

void Hero2::keepMagicBar(Slider* magicBar)
{
	magicBar->setPosition(HERO2_MAGICBAR_POSITION);
}


void Hero2::keepWeapon(Weapon* weapon)
{
	weapon->setPosition(HERO2_WEAPON_POSITION_X, HERO2_WEAPON_POSITION_Y);
}
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