//���� : ����
//���� : 2022-5-23

//�޸� : ����
//���� : 2022-6-3
//ʵ�� : ���ﶯ�����ܺ����ӿ�

#include "Hero2.h"

USING_NS_CC;
using namespace CocosDenshion;
/****************************
* Name ��create
* Summary ������
* return ��heroָ��
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
* Name ��create
* Summary ������
* return ��heroָ��
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
* Name ��initPlayer
* Summary ����ʼ��
* return ��
****************************/
void Hero2::initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
{
	//��ʼ�����
	_panel.init(maxHealthPoint, attack, defence, skillAttackRate, attackRate);
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
}
/****************************
* Name ��launchAnAttack
* Summary ���������� ����"attack" "skill" ����
* return ��
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
		for (int loop = 1; loop <= 20; ++loop)
		{
			char szName[100] = { 0 };
			sprintf(szName, "Character/Hero2/attack/attack%02d.png", loop);
			_animationAttack->addSpriteFrameWithFile(szName);
		}
		_animationAttack->setDelayPerUnit(0.3f / 20.0f);
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
			for (int loop = 1; loop <= 7; ++loop)
			{
				char szName[100] = { 0 };
				sprintf(szName, "Character/Hero2/skill/skill%02d.png", loop);
				_animationAttack->addSpriteFrameWithFile(szName);
				if (loop % 3 == 0)
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_2.mp3");
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
	this->refreshMagicBar(magicBar);
}
/****************************
* Name ��keepHealthBar
* Summary ������Ѫ��λ��
* return ��
****************************/
void Hero2::keepHealthBar(Slider* healthBar)
{
	healthBar->setPosition(HERO2_HEALTHBAR_POSITION);
	//_healthBar->setPosition(position);
}
/****************************
* Name ��keepMagicBar
* Summary ����������λ��
* return ��
****************************/
void Hero2::keepMagicBar(Slider* magicBar)
{
	magicBar->setPosition(HERO2_MAGICBAR_POSITION);
}
/****************************
* Name ��keepWeapon
* Summary ����������λ��
* return ��
****************************/
void Hero2::keepWeapon(Weapon* weapon)
{
	weapon->setPosition(HERO2_WEAPON_POSITION_X, HERO2_WEAPON_POSITION_Y);
}
/****************************
* Name ��runFlipxWithWeapon
* Summary ������������ת
* return ��
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
* Name ��initWalkAction
* Summary ����ʼ��_walkAction(Action�ͱ���)
****************************/
bool Hero2::initWalkAction()
{

	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Character/Hero1/hero1_Walk.plist", "Character/Hero1/hero1_Walk.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 0; i < 6; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("adventurer-run-0%d.png", i)->getCString());
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
* Summary ����ʼ��_normalAction(Action�ͱ���)
****************************/
bool Hero2::initNormalAction()
{

	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Character/Hero1/hero1_Idle.plist", "Character/Hero1/hero1_Idle.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 1; i < 5; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("adventurer-idle%d.png", i)->getCString());
		playerFrameArray.pushBack(frame);
	}

	auto* animation = Animation::createWithSpriteFrames(playerFrameArray, 1.0 / 12.0);
	this->setNormalAction(RepeatForever::create(Animate::create(animation)));

	if (_normalAction != nullptr)
		return true;
	else
		return false;

}
/****************************
* Name ��initAttackAction
* Summary ����ʼ��_attackAction(Action�ͱ���)
****************************/
bool Hero2::initAttackAction()
{

	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Character/Hero1/hero1_Attack.plist", "Character/Hero1/hero1_Attack.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 1; i < 13; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("adventurer-attack%d.png", i)->getCString());
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







