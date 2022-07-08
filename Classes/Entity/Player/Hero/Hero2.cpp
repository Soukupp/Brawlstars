//作者 : 王鹏
//日期 : 2022-5-23

//修改 : 束赫
//日期 : 2022-6-3
//实现 : 人物动画功能函数接口

#include "Hero1.h"
#include "Hero2.h"
#include "Hero3.h"
#include "Hero4.h"
#include "Tools.h"
//#include "Entity/Weapon/Weapon.h"
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
/*=======================以下是UI、武器等的位置保持跟随==========================*/
/*===============================================================================*/

/****************************
* Name ：keepHealthBar
* Summary ：保持血条位置
* return ：
****************************/
void Hero2::keepHealthBar(Slider* healthBar)
{
	float x = this->getPosition().x;
	float y = this->getPosition().y + 30;

	healthBar->setPosition(Vec2::Vec2(x, y));
}

/****************************
* Name ：keepMagicBar
* Summary ：保持蓝条位置
* return ：
****************************/
void Hero2::keepMagicBar(Slider* magicBar)
{
	float x = this->getPosition().x;
	float y = this->getPosition().y + 25;

	magicBar->setPosition(Vec2::Vec2(x, y));
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
	float x = this->getPosition().x;
	float y = this->getPosition().y + 35;

	levelText->setPosition(Vec2::Vec2(x, y));
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
	_direct = (flipx ? -1 : 1);

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
/*==================================以下是动画===================================*/
/*===============================================================================*/

/****************************
* Name ：initWalkAction
* Summary ：初始化_walkAction(Action型变量)
* return ：
****************************/
bool Hero2::initWalkAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("character/Hero2/hero2_Run.plist", "character/Hero2/hero2_Run.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 1; i < 9; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("Run_0%d.png", i)->getCString());
		playerFrameArray.pushBack(frame);
	}

	auto* animation = Animation::createWithSpriteFrames(playerFrameArray, 1.0f / 12.0f);

	this->setWalkAction(RepeatForever::create(Animate::create(animation)));

	if (_walkAction != nullptr)
		return true;
	else
		return false;
}

/****************************
* Name ：initNormalAction
* Summary ：初始化_normalAction(Action型变量)
* return ：
****************************/
bool Hero2::initNormalAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("character/Hero2/hero2_Normal.plist", "character/Hero2/hero2_Normal.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 0; i < 8; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("Idle-%d.png", i)->getCString());
		playerFrameArray.pushBack(frame);
	}

	auto* animation = Animation::createWithSpriteFrames(playerFrameArray, 1.0f / 12.0f);
	this->setNormalAction(RepeatForever::create(Animate::create(animation)));

	if (_normalAction != nullptr)
		return true;
	else
		return false;
}

/****************************
* Name ：initAttackAction
* Summary ：初始化_attackAction(Action型变量)
* return ：
****************************/
bool Hero2::initAttackAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("character/Hero2/hero2_Attack.plist", "character/Hero2/hero2_Attack.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 1; i < 5; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("Attack-%d.png", i)->getCString());
		playerFrameArray.pushBack(frame);
	}

	auto* animation = Animation::createWithSpriteFrames(playerFrameArray, 1.0f / 8.0f);
	animation->setLoops(1);
	auto* animate = Animate::create(animation);
	this->setAttackAction(animate);

	if (_attackAction != nullptr)
		return true;
	else
		return false;
}

/****************************
* Name ：initSkillAction
* Summary ：初始化技能动作
* return ：是否初始化成功
****************************/
bool Hero2::initSkillAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("character/Hero2/hero2_Skill.plist", "character/Hero2/hero2_Skill.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 0; i < 4; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("skill2-%d.png", i)->getCString());
		playerFrameArray.pushBack(frame);
	}

	auto* animation = Animation::createWithSpriteFrames(playerFrameArray, 1.0f / 12.0f);
	auto* animate = Animate::create(animation);
	this->setSkillAction(animate);

	if (_skillAction != nullptr)
		return true;
	else
		return false;
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
	if (_level < PLAYER_MAX_GRADE) 
	{
		_level++;
		levelText->setString((std::string("Lv.") + std::to_string(_level)));
		_panel.setMaxHealthPoint(HERO2_INIT_MAXHEALTHPOINT / 10 + _panel.getMaxHealthPoint());
		_panel.setAttack(HERO2_INIT_ATTACK / 10 + _panel.getAttack());
		_panel.setDefence(HERO2_INIT_DEFENCE / 10 + _panel.getDefence());
		_panel.setAttackRate(0.1f + _panel.getAttackRate());
		_panel.setSkillRate(0.1f + _panel.getSkillRate());
		_panel.setHealthPoint(HERO2_INIT_MAXHEALTHPOINT / 10 + _panel.getHealthPoint());
		_panel.treat(HERO2_INIT_MAXHEALTHPOINT / 2);
		this->keepLevelText(levelText, bar);
	}
}

/*===============================================================================*/
/*================================以下是碰撞检测=================================*/
/*===============================================================================*/

/****************************
* Name ：palyerCollisionTest1
* Summary ：近距离攻击碰撞检测
* 参数说明 : target : 攻击对象
*           weapon : 武器对象
* return ：
****************************/
bool Hero2::playerCollisionTest(Player* target, Weapon* weapon, bool ifPlayerEffect)
{
	if (target == nullptr)
		return false;
	_targetX = target->getPosition().x;                           //目标位置X
	_targetY = target->getPosition().y;                           //目标位置Y
	_thisX = this->getPosition().x;
	_thisY = this->getPosition().y;

	if (
		(_targetX - _thisX) * _direct < (weapon->getContentSize().width + target->_width / 2)
		&& (_targetX - _thisX) * _direct >= 0
		&& fabs(_targetY - _thisY) < (weapon->getContentSize().height / 2 + target->_height / 2)
		)
	{           //范围判定
		if (ifPlayerEffect)
		{//命中音效
			Tools::playEffect("music/knife_attack_2.mp3");
		}
		return true;
	}
	else
	{
		if (ifPlayerEffect)
		{//击空音效
			Tools::playEffect("music/knife_attack_1.mp3");
		}
		return false;
	}
}

/****************************
* Name ：getID
* Summary ：获取角色id
* return ：id
****************************/
int Hero2::getID()
{
	return _ID;
}