//作者 : 王鹏
//日期 : 2022-5-23
#include "Hero1.h"

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
* Summary ：自定义值初始化
* return ：
****************************/
void Hero1::initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
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
void Hero1::initPlayer()
{
	//初始化面板
	_panel.init(HERO1_INIT_MAXHEALTHPOINT, HERO1_INIT_ATTACK, HERO1_INIT_DEFENCE, HERO1_INIT_SKILLRATE, HERO1_INIT_ATTACKRATE);
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
void Hero1::launchAnAttack(Weapon* weapon, const std::string& attackType, Slider* magicBar)
{
	if (attackType == "attack")
	{
		if (weapon->launchAnAttack(_panel.doAttack()))
		{
			//成功造成伤害才回能
			restoreMagic();
		}

		auto _animationAttack = CCAnimation::create();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
		for (int loop = 1; loop <= HERO1_YOU_ATTACK_FRAME; ++loop)
		{
			char szName[100] = { 0 };
			sprintf(szName, "Character/Hero1/attack/attack%d.png", loop);
			_animationAttack->addSpriteFrameWithFile(szName);
		}
		_animationAttack->setDelayPerUnit(HERO1_YOU_ATTACK_TIME / HERO1_YOU_ATTACK_FRAME);
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
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
			for (int loop = 1; loop <= HERO1_YOU_SKILL_FRAME; ++loop)
			{
				char szName[100] = { 0 };
				sprintf(szName, "Character/Hero1/skill/skill%02d.png", loop);
				_animationAttack->addSpriteFrameWithFile(szName);
				if (loop % 7 == 0)
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
				}
			}
			_animationAttack->setDelayPerUnit(HERO1_YOU_SKILL_TIME / HERO1_YOU_SKILL_FRAME);
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
* Name ：keepLevelText
* Summary ：保持等级位置
* return ：
****************************/
void Hero1::keepLevelText(cocos2d::Label* levelText,Slider* bar)
{
	levelText->setPosition(HERO1_LEVELTEXT_POSITION);
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

//bool Hero1::initWalkAction()
//{
//
//	auto* frameCache = CCSpriteFrameCache::getInstance();
//	frameCache->addSpriteFramesWithFile("Character/Hero1/hero1_Walk.plist", "Character/Hero1/hero1_Walk.png");
//
//	Vector<CCSpriteFrame*> playerFrameArray;
//	for (int i = 0; i < 6; i++)
//	{
//		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("adventurer-run-0%d.png", i)->getCString());
//		playerFrameArray.pushBack(frame);
//	}
//
//	auto* animation = Animation::createWithSpriteFrames(playerFrameArray, 1.0 / 12.0);
//	this->setwalkAction(RepeatForever::create(Animate::create(animation)));
//
//	if (_walkAction != nullptr)
//	{
//		log("flase");
//		return true;
//	}
//	else
//	{
//		log("true");
//		return false;
//	}
//}

/****************************
* Name ：setPositionWithAll
* Summary ：整体移动
* return ：
****************************/
void Hero1::setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon, Slider* healthBar, Slider* magicBar, cocos2d::Label* levelText)
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
* Name ：Hero1::upgrade()
* Summary ：人物升级
* return ：
****************************/
void Hero1::upgrade(cocos2d::Label* levelText, Slider* bar)
{
	if (_level < PLAYER_MAX_GRADE) {
		_level++;
		levelText->setString((std::string("Lv.") + std::to_string(_level)));
		_panel.setMaxHealthPoint(HERO1_INIT_MAXHEALTHPOINT / 10 + _panel.getMaxHealthPoint());
		_panel.setAttack(HERO1_INIT_ATTACK / 10 + _panel.getAttack());
		_panel.setDefence(HERO1_INIT_DEFENCE / 10 + _panel.getDefence());
		_panel.setAttackRate(0.1f + _panel.getAttackRate());
		_panel.setSkillRate(0.1f + _panel.getSkillRate());
		_panel.setHealthPoint(HERO1_INIT_MAXHEALTHPOINT / 10 + _panel.getHealthPoint());
		this->keepLevelText(levelText, bar);
	}
}

/****************************
* Name ：initWalkAction
* Summary ：初始化_walkAction(Action型变量)
****************************/
bool Hero1::initWalkAction()
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
* Name ：initNormalAction
* Summary ：初始化_normalAction(Action型变量)
****************************/
bool Hero1::initNormalAction()
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
* Name ：initAttackAction
* Summary ：初始化_attackAction(Action型变量)
****************************/
bool Hero1::initAttackAction()
{

	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Character/Hero1/hero1_Attack.plist", "Character/Hero1/hero1_Attack.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 1; i < 13; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("adventurer-attack%d.png", i)->getCString());
		playerFrameArray.pushBack(frame);
	}

	auto* animation = Animation::createWithSpriteFrames(playerFrameArray, 1.0 / 24.0);
	animation->setLoops(1);
	auto* animate = Animate::create(animation);
	this->setAttackAction(animate);

	if (_normalAction != nullptr)
		return true;
	else
		return false;
}

bool Hero1::initSkillAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Character/Hero1/hero1_Skill.plist", "Character/Hero1/hero1_Skill.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 0; i < 4; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("skill1-%d.png", i)->getCString());
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

bool Hero1::playerCollisionTest1(Player* target, Weapon* weapon)
{
	float targetX = target->getPosition().x;                           //目标位置X
	float targetY = target->getPosition().y;                           //目标位置Y
	float targetWidth = target->_width;         //目标的宽度
	float targetHeight = target->_height;        //目标的高度
	float weaponWidth = weapon->getContentSize().width;                //攻击范围的宽度

	float judgearea = 45;

	log("**this->getPosition().x        %f", this->getPosition().x);
	log("**this->getPosition().x-targetX        %f", this->getPosition().x - targetX);
	log("**targetWidth / 2                      %f", targetWidth / 2);



	if (_direct == 1) {
		if ((targetX - this->getPosition().x) < judgearea && (this->getPosition().x - targetX) <= 0) {           //范围判定
			if (fabs(this->getPosition().y - targetY) < targetHeight / 2) {
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_2.mp3");
				log("true++++++++++++++++++++++++++++++++++++++++++");
				return true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
			log("true----------------------------------------");
			return false;
		}
		else {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
			log("true----------------------------------------");
			return false;
		}
	}
	if (_direct == -1) {

		log("this->getPosition().x-targetX        %f", this->getPosition().x - targetX);
		log("targetWidth / 2                      %f", targetWidth / 2);

		if ((this->getPosition().x - targetX) < judgearea && (this->getPosition().x - targetX) >= 0) {           //范围判定
			if (fabs(this->getPosition().y - 16 - targetY) < targetHeight / 2) {
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_2.mp3");
				log("true++++++++++++++++++++++++++++++++++++++++++");

				return true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
			log("true----------------------------------------");
			return false;
		}
		else {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
			log("true----------------------------------------");
			return false;
		}
	}
}

int Hero1::getID()
{
	return ID;
}