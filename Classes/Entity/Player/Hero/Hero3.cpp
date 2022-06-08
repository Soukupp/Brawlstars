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
	/*healthBar->setPosition(HERO3_HEALTHBAR_POSITION);*/
	//_healthBar->setPosition(position);
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
	//magicBar->setPosition(HERO3_MAGICBAR_POSITION);
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
	//levelText->setPosition(HERO3_LEVELTEXT_POSITION);
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
	if (_level < PLAYER_MAX_GRADE) {
		_level++;
		levelText->setString((std::string("Lv.") + std::to_string(_level)));
		_panel.setMaxHealthPoint(HERO3_INIT_MAXHEALTHPOINT / 10 + _panel.getMaxHealthPoint());
		_panel.setAttack(HERO3_INIT_ATTACK / 10 + _panel.getAttack());
		_panel.setDefence(HERO3_INIT_DEFENCE / 10 + _panel.getDefence());
		_panel.setAttackRate(0.1f + _panel.getAttackRate());
		_panel.setSkillRate(0.1f + _panel.getSkillRate());
		_panel.setHealthPoint(HERO3_INIT_MAXHEALTHPOINT / 10 + _panel.getHealthPoint());
		this->keepLevelText(levelText, bar);
	}
}

bool Hero3::initWalkAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Character/Hero3/hero3_Run.plist", "Character/Hero3/hero3_Run.png");

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

bool Hero3::initNormalAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Character/Hero3/hero3_Start.plist", "Character/Hero3/hero3_Start.png");

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

bool Hero3::initAttackAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Character/Hero3/hero3_Attack.plist", "Character/Hero3/hero3_Attack.png");

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

bool Hero3::initSkillAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Character/Hero3/hero3_Skill.plist", "Character/Hero3/hero3_Skill.png");

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

bool Hero3::playerCollisionTest1(Player* target, Weapon* weapon)
{
	float targetX = target->getPosition().x;                           //Ŀ��λ��X
	float targetY = target->getPosition().y;                           //Ŀ��λ��Y
	float targetWidth = target->_width;         //Ŀ��Ŀ��
	float targetHeight = target->_height;        //Ŀ��ĸ߶�
	float weaponWidth = 50.0f;                //������Χ�Ŀ��

	float judgearea = 80;

	//log("**this->getPosition().x        %f", this->getPosition().x);
	//log("**this->getPosition().x-targetX        %f", this->getPosition().x - targetX);
	//log("**targetWidth / 2                      %f", targetWidth / 2);



	if (_direct == 1) {
		if ((targetX - this->getPosition().x) < judgearea && (this->getPosition().x - targetX) <= 0) {           //��Χ�ж�
			if (fabs(this->getPosition().y - targetY) < targetHeight / 4 + 10) {
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_2.mp3");
				return true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
			return false;
		}
		else {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
			return false;
		}
	}
	if (_direct == -1) {

		//log("this->getPosition().x-targetX        %f", this->getPosition().x - targetX);
		//log("targetWidth / 2                      %f", targetWidth / 2);

		if ((this->getPosition().x - targetX) < judgearea && (this->getPosition().x - targetX) >= 0) {           //��Χ�ж�
			if (fabs(this->getPosition().y - targetY) < targetHeight / 4 + 10) {

				return true;
			}
			return false;
		}
		else {
			return false;
		}
	}
}

bool Hero3::playerCollisionTest2(Player* target, Weapon* weapon)
{
	float targetX = target->getPosition().x;                           //Ŀ��λ��X
	float targetY = target->getPosition().y;                           //Ŀ��λ��Y
	float targetWidth = target->_width;         //Ŀ��Ŀ��
	float targetHeight = target->_height;        //Ŀ��ĸ߶�
	float weaponWidth = weapon->getContentSize().width;                //������Χ�Ŀ��

	float judgearea = 80;

	log("**this->getPosition().x        %f", this->getPosition().x);
	log("**this->getPosition().x-targetX        %f", this->getPosition().x - targetX);
	log("**targetWidth / 2                      %f", targetWidth / 2);



	if (_direct == 1) {
		if ((targetX - this->getPosition().x) < judgearea && (this->getPosition().x - targetX) <= 0) {           //��Χ�ж�
			if (fabs(this->getPosition().y - targetY) < targetHeight / 2) {
				return true;
			}
			return false;
		}
		else {
			return false;
		}
	}
	if (_direct == -1) {

		log("this->getPosition().x-targetX        %f", this->getPosition().x - targetX);
		log("targetWidth / 2                      %f", targetWidth / 2);

		if ((this->getPosition().x - targetX) < judgearea && (this->getPosition().x - targetX) >= 0) {           //��Χ�ж�
			if (fabs(this->getPosition().y - 16 - targetY) < targetHeight / 2) {

				return true;
			}
			return false;
		}
		else {
			return false;
		}
	}
}

int Hero3::getID()
{
	return ID;
}