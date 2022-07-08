//作者 : 李元特
//日期 : 2022-5-20

//修改 : 李元特
//日期 : 2022-5-22
//修改 : 增加键盘功能

//修改 : 王鹏
//日期 : 2022-5-25
//修改 : 人物初始化函数 解决冲突

//修改 : 束赫
//日期 : 2022-5-28
//实现 : 实现和HeroScene的对接，英雄初始化玩家可以进行选择

//修改 : 李元特
//日期 : 2022-6-4
//实现 : 烟雾（安全区）、传送阵

//修改 : 王鹏
//日期 : 2022-6-5
//实现 : ai

//修改 : 束赫
//日期 : 2022-6-7
//实现 : 攻击效果

/*==============================================
	对象所在层数：
	_tileMap 0层
	_tree, _collidable 在_tileMap 上 （一部分）
	_portal, _portalDetermination 系列 1层
	*hero, *weapon （包括AI） 4层
	* monster 3层
	_SafeArea 100层

=============================================*/

#include "MapLayer.h"
using namespace CocosDenshion;

/****************************
* Name ：MapLayer::createScene
* Summary ：创建MapLayer
* return ：MapLayer
****************************/
Scene* MapLayer::createScene()
{
	auto mapLayer = Scene::create();
	auto layer = MapLayer::create();
	mapLayer->addChild(layer);
	return mapLayer;
}

/****************************
* Name ：MapLayer::init
* Summary ：地图层初始化
* return ：初始化成功与否
****************************/
bool MapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	srand(static_cast<unsigned int>(time(0)));

	/*===================Tilemap相关设置开始==================*/
	initTilemap();
	/*===================Tilemap相关设置结束===================*/

	/*====================键盘操纵设置开始==========================*/

	auto keyboardListener = EventListenerKeyboard::create();// 建立键盘监听器keyboardListener

	keyboardListener->onKeyPressed = CC_CALLBACK_2(MapLayer::onKeyPressed, this);  // 按键盘操作
	// 没有设置成持续按压，持续前进
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MapLayer::onKeyReleased, this); // 释放键盘操作
	
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->schedule(schedule_selector(MapLayer::update), 0.05f); 
	//每一帧都进入 update 函数，判断键盘有没有被按压住 参数（也可以控制行走速度）

	/*=====================键盘操控设置结束===========================*/

	/*=====================控制毒圈开始===========================*/

	memset(_fogIsPlaced, 0, sizeof(_fogIsPlaced));

	this->schedule(schedule_selector(MapLayer::updateForFog), MAP_SAFEAREA_INTERVAL_LAST, MAP_SAFEAREA_APPEAR_TIMES, MAP_SAFEAREA_DELAY_LAST); // 持续到结束
	//this->schedule(schedule_selector(MapLayer::updateOutsideFog));
	this->schedule(schedule_selector(MapLayer::updatePlayerHurtByFog), 0.01f);
	this->schedule(schedule_selector(MapLayer::updateForPortal));

	/*=====================控制毒圈结束===========================*/

	/*====================初始化数据开始==========================*/

	_numOfPlayer = allCharacter.size();
	Tools::setUserInt("PlayerRank", this->getPlayerRank());
	Tools::setUserInt("HitNum", this->getHitNum());

	/*====================初始化数据结束==========================*/

	return true;

}

bool MapLayer::initTilemap()
{
	/*===================Tilemap相关设置开始==================*/
	log("Map begin");
	int selectedMap = Tools::getUserInt("selectedMap");
	switch (selectedMap)
	{
		case 0:
			_tileMap = TMXTiledMap::create("map/Mapupdated1.tmx");
			break;
		case 1:
			_tileMap = TMXTiledMap::create("map/Mapupdated3.tmx");  //Mapupdated2是Mapupdated3的材料，不可删去
			break;
	}

	addChild(_tileMap, 0, 100);
	log("Map finished");

	//场景初始化
	_collidable = _tileMap->getLayer("collidable");  //障碍物collidable
	_collidable->setVisible(false);                  // 对应collidable图层是否可见
	_tree = _tileMap->getLayer("tree");
	/*=====================创建角色开始========================*/
	initCharacter();
	/*====================创建安全区开始=======================*/
	initSafeArea();
	/*======================AI创建开始=========================*/
	initAICharacter();
	/*======================创建怪兽开始=======================*/
	initAllMonster();
	/*=====================传送阵创建开始======================*/
	initPortal();
	/*=====================死亡点创建开始=====================*/
	initDeathPosition();

	setTouchEnabled(true);  // 开启触摸，必须继承于layer
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	/*===================Tilemap相关设置结束===================*/
	return true;
}

bool MapLayer::initCharacter()
{
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	log("Get Player finished");
	ValueMap spawnPoint = group->getObject("player");
	/*=====================创建角色开始========================*/

	float _playerX = static_cast<float>(spawnPoint["x"].asInt());
	float _playerY = static_cast<float>(spawnPoint["y"].asInt());        //创建英雄的位置

	int selectedHero = Tools::getUserInt("selectedHero");   //selectedHero表示玩家选择的英雄

	switch (selectedHero)
	{
		case 1:
			createHero(&_player1, &_weapon, &_healthBar, &_magicBar, &_levelText,
				Vec2(_playerX, _playerY), "character/Hero1/hero.png", "character/Hero1/emptyWeapon.png");
			tempCharacter = { _player1,_weapon,_healthBar,_magicBar,_levelText };
			allCharacter.push_back(tempCharacter);
			break;
		case 2:
			createHero(&_player2, &_weapon, &_healthBar, &_magicBar, &_levelText,
				Vec2(_playerX, _playerY), "character/Hero2/hero.png", "character/Hero2/emptyWeapon.png");
			tempCharacter = { _player2,_weapon,_healthBar,_magicBar,_levelText };
			allCharacter.push_back(tempCharacter);
			break;
		case 3:
			createHero(&_player3, &_weapon, &_healthBar, &_magicBar, &_levelText,
				Vec2(_playerX, _playerY), "character/Hero3/hero.png", "character/Hero3/emptyWeapon.png");
			tempCharacter = { _player3,_weapon,_healthBar,_magicBar,_levelText };
			allCharacter.push_back(tempCharacter);
			break;
		case 4:
			createHero(&_player4, &_weapon, &_healthBar, &_magicBar, &_levelText,
				Vec2(_playerX, _playerY), "character/Hero4/hero.png", "character/Hero4/emptyWeapon.png");
			tempCharacter = { _player4,_weapon,_healthBar,_magicBar,_levelText };
			allCharacter.push_back(tempCharacter);
			break;
	}

	//角色相关数据初始化
	PLAYER->initWalkAction();
	PLAYER->initNormalAction();
	PLAYER->initAttackAction();
	PLAYER->initSkillAction();
	PLAYER->setScale(1.3f);

	log("%d ID", PLAYER->getID());

	setViewpointCenter(PLAYER->getPosition());

	PLAYER->runAction(PLAYER->getNormalAction());
	/*=====================创建角色结束========================*/
	return true;
}

bool MapLayer::initSafeArea()
{
	/*====================创建安全区开始=======================*/

	log("Safe Area added");
	_SafeArea = Sprite::create("ui/SafeAreaLarge.png");
	_SafeArea->setAnchorPoint(Vec2(0.5, 0.5));
	_SafeArea->setPosition(MAP_SAFEAREA_POSITION);
	//_SafeArea->setVisible(false);
	this->addChild(_SafeArea, 100);

	/*====================创建安全区结束=======================*/
	return true;
}

bool MapLayer::initAICharacter()
{
	/*======================AI创建开始=========================*/

	float _aiX[MAP_AI_NUMBER + 1];
	float _aiY[MAP_AI_NUMBER + 1];              //设置AI位置

	memset(_aiX, 0, sizeof(_aiX));
	memset(_aiY, 0, sizeof(_aiY));

	//获取用户选择的AI人数
	int AINumber = Tools::getUserInt("selectedAINUmber");
	_invincibleMode = Tools::getUserInt("invincibleMode"); // 0表示normal，1表示无敌
	log("invincibleMode %d", _invincibleMode);

	//AI位置
	for (int i = 1; i <= AINumber; ++i)
	{
		std::string aiNumber = "ai" + std::to_string(i);
		_aiX[i] = static_cast<float>(_tileMap->getObjectGroup("AI")->getObject(aiNumber).at("x").asInt());
		_aiY[i] = static_cast<float>(_tileMap->getObjectGroup("AI")->getObject(aiNumber).at("y").asInt());
	}

	//AI随机生成
	for (int i = 1; i <= AINumber; ++i)
	{
		int tempHeroType = rand() % 4;
		//log("tempHeroType %d", tempHeroType);
		if (tempHeroType == 1) {
			createHero(&_player1, &_weapon, &_healthBar, &_magicBar, &_levelText,
				Vec2(_aiX[i], _aiY[i]), "character/Hero1/hero.png", "character/Hero1/emptyWeapon.png");
			tempCharacter = { _player1,_weapon,_healthBar,_magicBar,_levelText };
			allCharacter.push_back(tempCharacter);
		}
		if (tempHeroType == 2) {
			createHero(&_player2, &_weapon, &_healthBar, &_magicBar, &_levelText,
				Vec2(_aiX[i], _aiY[i]), "character/Hero2/hero.png", "character/Hero2/emptyWeapon.png");
			tempCharacter = { _player2,_weapon,_healthBar,_magicBar,_levelText };
			allCharacter.push_back(tempCharacter);
		}
		if (tempHeroType == 3) {
			createHero(&_player3, &_weapon, &_healthBar, &_magicBar, &_levelText,
				Vec2(_aiX[i], _aiY[i]), "character/Hero3/hero.png", "character/Hero3/emptyWeapon.png");
			tempCharacter = { _player3,_weapon,_healthBar,_magicBar,_levelText };
			allCharacter.push_back(tempCharacter);
		}
		if (tempHeroType == 0) {
			createHero(&_player4, &_weapon, &_healthBar, &_magicBar, &_levelText,
				Vec2(_aiX[i], _aiY[i]), "character/Hero4/hero.png", "character/Hero4/emptyWeapon.png");
			tempCharacter = { _player4,_weapon,_healthBar,_magicBar,_levelText };
			allCharacter.push_back(tempCharacter);
		}
	}
	(*HEALTHBAR).loadProgressBarTexture("/ui/playerGreenHealthbarBlock.png");
	//各个AI相关数据初始化
	for (unsigned int i = 1; i < allCharacter.size(); ++i)
	{
		CHARACTER(i)._player->_panel.setPlayerState(ATTACK);
		CHARACTER(i)._player->_panel.setIfPlayAttackAnimation(false);
		CHARACTER(i)._player->initWalkAction();
		CHARACTER(i)._player->initAttackAction();
		CHARACTER(i)._player->initSkillAction();
		CHARACTER(i)._player->initNormalAction();
		CHARACTER(i)._player->setScale(1.3f);
		CHARACTER(i)._player->_panel.setIsSurvive(true);
		setCharacterVisible(true, CHARACTER(i));
	}

	//schedule调用
	this->schedule(schedule_selector(MapLayer::updateAIMove), 0.05f);   //每0.05s检测AI的移动状况
	this->schedule(schedule_selector(MapLayer::updateAIAttack), 1.0f);  //每1s检测AI的攻击状况

	/*======================AI创建结束=========================*/
	return true;
}

bool MapLayer::initAllMonster()
{
	/*=======================创建怪兽开始=======================*/

	float _gmX[MAP_GM_NUMBER + 1];
	float _gmY[MAP_GM_NUMBER + 1];

	float _wmX[MAP_WM_NUMBER + 1];
	float _wmY[MAP_WM_NUMBER + 1];

	float _dmX[MAP_DM_NUMBER + 1];
	float _dmY[MAP_DM_NUMBER + 1];

	memset(_gmX, 0, sizeof(_gmX));
	memset(_gmY, 0, sizeof(_gmY));
	memset(_wmX, 0, sizeof(_wmX));
	memset(_wmY, 0, sizeof(_wmY));
	memset(_dmX, 0, sizeof(_dmX));
	memset(_dmY, 0, sizeof(_dmY));

	//三种monster的出生地选择

	for (int i = 1; i < MAP_GM_NUMBER + 1; ++i)
	{
		std::string moNumber = "gm" + std::to_string(i);
		_gmX[i] = static_cast<float>(_tileMap->getObjectGroup("groundmonster")->getObject(moNumber).at("x").asInt());
		_gmY[i] = static_cast<float>(_tileMap->getObjectGroup("groundmonster")->getObject(moNumber).at("y").asInt());
	}
	for (int i = 1; i < MAP_WM_NUMBER + 1; ++i)
	{
		std::string moNumber = "wm" + std::to_string(i);
		_wmX[i] = static_cast<float>(_tileMap->getObjectGroup("watermonster")->getObject(moNumber).at("x").asInt());
		_wmY[i] = static_cast<float>(_tileMap->getObjectGroup("watermonster")->getObject(moNumber).at("y").asInt());
	}
	for (int i = 1; i < MAP_DM_NUMBER + 1; ++i)
	{
		std::string moNumber = "dm" + std::to_string(i);
		_dmX[i] = static_cast<float>(_tileMap->getObjectGroup("desertmonster")->getObject(moNumber).at("x").asInt());
		_dmY[i] = static_cast<float>(_tileMap->getObjectGroup("desertmonster")->getObject(moNumber).at("y").asInt());
	}
	//  !!!!!注意！！以下三个 顺序 不可调换!!!!!
	for (int i = 1; i < MAP_GM_NUMBER + 1; ++i)
	{
		createMonster(&_monsterG, &_healthBar, Vec2(_gmX[i], _gmY[i]), "monster/groundmonster.png");
		tempMonster = { _monsterG,_healthBar };
		allMonster.push_back(tempMonster);
	}
	for (int i = 1; i < MAP_WM_NUMBER + 1; ++i)
	{
		createMonster(&_monsterW, &_healthBar, Vec2(_wmX[i], _wmY[i]), "monster/watermonster.png");
		tempMonster = { _monsterW,_healthBar };
		allMonster.push_back(tempMonster);
	}
	for (int i = 1; i < MAP_DM_NUMBER + 1; ++i)
	{
		createMonster(&_monsterD, &_healthBar, Vec2(_dmX[i], _dmY[i]), "monster/desertmonster.png");
		tempMonster = { _monsterD,_healthBar };
		allMonster.push_back(tempMonster);
	}

	/*=======================创建怪兽结束=======================*/
	return true;
}

bool MapLayer::initPortal()
{
	/*===================传送阵起点创建开始===================*/

	TMXObjectGroup* portalGroup = _tileMap->getObjectGroup("portal");
	log("Get Portal Finished");
	ValueMap portal_1_Position = portalGroup->getObject("portal1");
	ValueMap portal_2_Position = portalGroup->getObject("portal2");
	ValueMap portal_3_Position = portalGroup->getObject("portal3");
	ValueMap portal_4_Position = portalGroup->getObject("portal4");

	_portal_1 = Sprite::create("ui/scrap.png");
	_portal_1->setPosition(static_cast<float>(portal_1_Position["x"].asInt()), static_cast<float>(portal_1_Position["y"].asInt()));
	this->addChild(_portal_1, 1);

	_portal_2 = Sprite::create("ui/scrap.png");
	_portal_2->setPosition(static_cast<float>(portal_2_Position["x"].asInt()), static_cast<float>(portal_2_Position["y"].asInt()));
	this->addChild(_portal_2, 1);

	_portal_3 = Sprite::create("ui/scrap.png");
	_portal_3->setPosition(static_cast<float>(portal_3_Position["x"].asInt()), static_cast<float>(portal_3_Position["y"].asInt()));
	this->addChild(_portal_3, 1);

	_portal_4 = Sprite::create("ui/scrap.png");
	_portal_4->setPosition(static_cast<float>(portal_4_Position["x"].asInt()), static_cast<float>(portal_4_Position["y"].asInt()));
	this->addChild(_portal_4, 1);

	/*===================传送阵起点创建结束===================*/

	/*===================传送阵终点创建开始===================*/

	TMXObjectGroup* portalDeterminationGroup = _tileMap->getObjectGroup("portalDetermination");
	log("Get Portal Determination Finished");
	ValueMap portal_Determination_1_Position = portalDeterminationGroup->getObject("portalDetermination1");
	ValueMap portal_Determination_2_Position = portalDeterminationGroup->getObject("portalDetermination2");
	ValueMap portal_Determination_3_Position = portalDeterminationGroup->getObject("portalDetermination3");
	ValueMap portal_Determination_4_Position = portalDeterminationGroup->getObject("portalDetermination4");

	_portal_Determination_1 = Sprite::create("ui/scrapDetermination.png");
	_portal_Determination_1->setPosition(static_cast<float>(portal_Determination_1_Position["x"].asInt()),
		static_cast<float>(portal_Determination_1_Position["y"].asInt()));
	this->addChild(_portal_Determination_1, 1);

	_portal_Determination_2 = Sprite::create("ui/scrapDetermination.png");
	_portal_Determination_2->setPosition(static_cast<float>(portal_Determination_2_Position["x"].asInt()),
		static_cast<float>(portal_Determination_2_Position["y"].asInt()));
	this->addChild(_portal_Determination_2, 1);

	_portal_Determination_3 = Sprite::create("ui/scrapDetermination.png");
	_portal_Determination_3->setPosition(static_cast<float>(portal_Determination_3_Position["x"].asInt()),
		static_cast<float>(portal_Determination_3_Position["y"].asInt()));
	this->addChild(_portal_Determination_3, 1);

	_portal_Determination_4 = Sprite::create("ui/scrapDetermination.png");
	_portal_Determination_4->setPosition(static_cast<float>(portal_Determination_4_Position["x"].asInt()),
		static_cast<float>(portal_Determination_4_Position["y"].asInt()));
	this->addChild(_portal_Determination_4, 1);

	/*===================传送阵终点创建结束===================*/
	return true;
}

bool MapLayer::initDeathPosition()
{
	/*=====================死亡点创建开始=====================*/

	TMXObjectGroup* deathPositionGroup = _tileMap->getObjectGroup("DiePoint");
	ValueMap deathMapPosition = deathPositionGroup->getObject("diePoint");
	deathPosition = Vec2(static_cast<float>(deathMapPosition["x"].asInt()), static_cast<float>(deathMapPosition["y"].asInt()));

	/*=====================死亡点创建结束=====================*/
	return true;
}

/****************************
* Name ：MapLayer::onKeyPressed
* Summary ：按下键盘后分别带来的操作
* return ：无
****************************/
void MapLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (
		keyCode == EventKeyboard::KeyCode:: KEY_RIGHT_ARROW ||                 //忽略其他非功能按键
		keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_W ||
		keyCode == EventKeyboard::KeyCode::KEY_S ||
		keyCode == EventKeyboard::KeyCode::KEY_A ||
		keyCode == EventKeyboard::KeyCode::KEY_D 
		)
	{
		keyMap[keyCode] = true;
        if (PLAYER->_panel.getPlayerState() != MOVING)
		{

			PLAYER->_panel.setPlayerState(MOVING);

		}

		PLAYER->_panel.setIfPlayNormalAnimationInUpdate2(false);         //调用normal动画有两个函数，为此函数和update2函数
			                                                             //为避免 攻击->移动->（调用onKeyReleased）停下 这一过程和
			                                                             //攻击->（调用update2）停下 这两个过程发生冲突，用_ifPlayNormalAnimationInUpdate2
			                                                             //判断是否还要调用update2
		PLAYER->stopAllActions();
		PLAYER->runAction(PLAYER->getWalkAction());
	}
}

/****************************
* Name ：MapLayer::onKeyReleased
* Summary ：按下键盘后分别带来的操作
* return ：无
****************************/
void MapLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	//log("Key with keycode %d released", keyCode);
	if (
		keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW ||                   //忽略其他非功能按键
		keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_W ||
		keyCode == EventKeyboard::KeyCode::KEY_S ||
		keyCode == EventKeyboard::KeyCode::KEY_A ||
		keyCode == EventKeyboard::KeyCode::KEY_D
		)
	{
		keyMap[keyCode] = false;

		if (                                  
			PLAYER->_panel.getPlayerState() != NORMAL                          //当从其他状态将要转成NORAL时
			&& keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] == false         //当所有功能按键都释放时
			&& keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] == false
	    	&& keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW] == false
			&& keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW] == false
			&& keyMap[EventKeyboard::KeyCode::KEY_W] == false
			&& keyMap[EventKeyboard::KeyCode::KEY_S] == false
			&& keyMap[EventKeyboard::KeyCode::KEY_A] == false
			&& keyMap[EventKeyboard::KeyCode::KEY_D] == false
			)
		{
			PLAYER->stopAllActions();
			PLAYER->_panel.setPlayerState(NORMAL);
			PLAYER->_panel.setIfPlayAttackAnimation(true);
			PLAYER->runAction(PLAYER->getNormalAction());
		}
	}
}

/****************************
* Name ：MapLayer::update
* Summary ：更新函数，改变player实时动态
* return ：无
****************************/
void MapLayer::update(float delta)
{

	Vec2 playerPos = PLAYER->getPosition();  // 获取玩家位置坐标

	Tools::getDirtFromKey(keyMap, CHARACTER(0)._direct);
	Tools::getNextPosByDirt(playerPos, CHARACTER(0));

	this->setPlayerPosition(playerPos);
	this->setTreeOpacity(playerPos);
}

/****************************
* Name ：MapLayer::onTouchBegan
* Summary ：触摸开始
* return ：是否执行
****************************/
bool MapLayer::onTouchBegan(Touch* touch, Event* event)
{
	//log("onTouchBegan"); //日志
	if (PLAYER->_panel.getIfPlayAttackAnimation() && PLAYER->_panel.getPlayerState() != MOVING)
	{        //保证不会实现连续攻击，不会实现一边位移一边攻击

		if (PLAYER->_panel.getPlayerState() != ATTACK)
		{
			PLAYER->_panel.setPlayerState(ATTACK);
			PLAYER->stopAllActions();

			Tools::playEffect("music/knife_attack_1.mp3");
			Tools::setEffectsVolume("musicVolume");
			if (!PLAYER->magicIsFull())
			{
				PLAYER->runAction(PLAYER->getAttackAction());
			}
			else
			{
				PLAYER->runAction(PLAYER->getSkillAction());
			}
			PLAYER->_panel.setIfPlayAttackAnimation(false);                                          //保证不会实现连续攻击
																									  //检测攻击时是否碰到PLAYER1

			PLAYER->_panel.setIfPlayNormalAnimationInUpdate2(true);                                  //使得可以调用update2

			bool ifAttackEnemy = false;                                           //ifAttackEnemy用于判断player是否攻击可monster或者AI

			for (unsigned int i = 1; i < allCharacter.size(); i++)
			{
				if (PLAYER->playerCollisionTest(AI_PLAYER(i), WEAPON, true))
				{
					CHARACTER(i)._isCollidedByPlayer = true;
					ifAttackEnemy = true;
					break;                                //一旦检测到和AI发生碰撞，进行：1.被碰撞的AI进行标记  2.ifAttackEnemy设置为true  
					                                      //3.停止for循环防止标记多人，实现只对单一对象攻击
				}
			}

			if (PLAYER->magicIsFull())
			{
				if (PLAYER->magicIsFull() && !ifAttackEnemy)                //处理如果发动skill而没有击中目标的情况
				{
					PLAYER->useMagic();                                     //使用蓝条

					PLAYER->launchAnAttack(WEAPON, "skill", MAGICBAR, nullptr, nullptr);   //传入空指针
				}
			}

			if (!ifAttackEnemy)                          //如果没有击中AI，那么对monster进行进行碰撞monster
			{
				for (unsigned int i = 0; i < allMonster.size(); i++)    
				{
					if (PLAYER->playerCollisionTest(allMonster[i]._monster,WEAPON, true))
					{
						allMonster[i]._isCollidedByPlayer = true;
						ifAttackEnemy = true;
						break;
					}
				}
			}

			//根据player的身份调用相应的schedule，延时的时间表示人物的技能发动时间

			if (PLAYER->getID() == 1)
				this->scheduleOnce(schedule_selector(MapLayer::updatePlayerDoAttack), 0.5f);  //1.0f是动画时间，1.0f后进入update2执行一次normal动画
			else if (PLAYER->getID() == 2)
				this->scheduleOnce(schedule_selector(MapLayer::updatePlayerDoAttack), 0.5f);
			else if (PLAYER->getID() == 3)
				this->scheduleOnce(schedule_selector(MapLayer::updatePlayerDoAttack), 0.67f);
			else if (PLAYER->getID() == 4)
				this->scheduleOnce(schedule_selector(MapLayer::updatePlayerDoAttack), 0.167f);
		}
	}
	return true;
}

/****************************
* Name ：MapLayer::onTouchMoved
* Summary ：触摸移动
* return ：是否执行
****************************/
void MapLayer::onTouchMoved(Touch* touch, Event* event)
{
}

/****************************
* Name ：MapLayer::onTouchEnded
* Summary ：触摸结束
* return ：是否执行
****************************/
void MapLayer::onTouchEnded(Touch* touch, Event* event)
{

	/*================获取触摸点的坐标，并转化为当前层模型坐标系==================*/

	Vec2 touchLocation = touch->getLocation();  //获得在OpenGL坐标
	touchLocation = this->convertToNodeSpace(touchLocation);  //转换为当前层的模型坐标系

	Vec2 playerPos = PLAYER->getPosition();  // 获取玩家位置坐标

	Vec2 diff = touchLocation - playerPos;    // 获取上述两者坐标差 

	/*=============================坐标获取结束================================*/

	/*=============================角度获取开始================================*/

	float playerWeaponAngle;
	if (fabs(touchLocation.x - playerPos.x) < 1e-6 && touchLocation.y > playerPos.y)      //横坐标相等，纵坐标不等，向上90°
		playerWeaponAngle = 0.5f * static_cast<float>(M_PI);
	else if (fabs(touchLocation.x - playerPos.x) < 1e-6 && touchLocation.y <= playerPos.y)  //横坐标相等，纵坐标不等，向下90°
		playerWeaponAngle = -0.5f * static_cast<float>(M_PI);
	else
		playerWeaponAngle = atan((touchLocation.y - playerPos.y) / (touchLocation.x - playerPos.x));

	/*=============================角度获取结束================================*/
}

/****************************
* Name ：MapLayer::setPlayerPosition
* Summary ：是否走动
* return ：无
****************************/
void MapLayer::setPlayerPosition(Vec2 position)
{
	// 读取坐标
	Vec2 tileCoord = this->tileCoordFromPosition(position);  //从像素点坐标转化为瓦片坐标

	int tileGid = _collidable->getTileGIDAt(tileCoord);   //获得瓦片的GID

	// 碰撞检测
	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();
		// 元素+true
		if (collision == "true") { //碰撞检测成功
			return;
		}
	}

	PLAYER->setPositionWithAll(position, WEAPON, HEALTHBAR, MAGICBAR, LEVELTEXT);

	//滚动地图
	if (PLAYER->_panel.getPlayerState() != ATTACK)
	{
		this->setViewpointCenter(PLAYER->getPosition());
	}
}

/****************************
* Name ：MapLayer::setTreeOpacity
* Summary ：树的透明度
* return ：无
****************************/
void MapLayer::setTreeOpacity(Vec2 pos)
{
	static std::vector<Vec2> playerVisionArea = {};

	int count = 0;

	for (unsigned int i = 0; i < playerVisionArea.size(); ++i)
	{
		Vec2 treetileCoord = this->tileCoordFromPosition(playerVisionArea[i]);
		if (_tree->getTileAt(treetileCoord))
		{
			count++;
			_treecell = _tree->getTileAt(treetileCoord); //通过tile坐标访问指定草丛单元格
			_treecell->setOpacity(255);  //不透明
		}
	}

	if (count == 5)  //周围都不透明
	{
		playerOpacity = MAP_PLAYER_NOT_IN_TREE;
		count = 0;
	}
	else
	{
		if (playerOpacity != MAP_PLAYER_IN_TREE_AND_AROUND_AI)
			playerOpacity = MAP_PLAYER_IN_TREE_AND_NOT_AROUND_AI;
		count = 0;
	}

	Vec2 cellsize = _tileMap->getTileSize();

	playerVisionArea = {
		pos,
		Vec2(pos.x + cellsize.x,pos.y),
		Vec2(pos.x - cellsize.x,pos.y),
		Vec2(pos.x,pos.y + cellsize.y),
		Vec2(pos.x,pos.y - cellsize.y),
	};

	for (unsigned int i = 1; i < allCharacter.size(); ++i)
	{
		if (AI_PLAYER(i)->_panel.getIsSurvive())
		{
			Vec2 treetileCoord = this->tileCoordFromPosition(AI_PLAYER(i)->getPosition());
			if (_tree->getTileAt(treetileCoord))// AI的位置有树丛
			{
				if (playerOpacity == MAP_PLAYER_IN_TREE_AND_NOT_AROUND_AI && aroundPlayer[i] == false)
				{
					setCharacterVisible(false, CHARACTER(i));  // 不可见
				}
				else if (playerOpacity == MAP_PLAYER_IN_TREE_AND_AROUND_AI)  // 有AI在玩家旁边
				{
					if (aroundPlayer[i] == true)   // 如果这个AI在玩家旁边，则可见
					{
						AI_PLAYER(i)->setVisible(true);
						allCharacter[i]._healthBar->setVisible(true);
						allCharacter[i]._magicBar->setVisible(true);
						allCharacter[i]._levelText->setVisible(true);
					}

				}
			}
			else   // AI 的位置没有草丛
			{
				aroundPlayer[i] = false;  // 无需考虑AI在不在玩家旁边，回到默认值false，且AI可见
				AI_PLAYER(i)->setVisible(true);
				allCharacter[i]._healthBar->setVisible(true);
				allCharacter[i]._magicBar->setVisible(true);
				allCharacter[i]._levelText->setVisible(true);
			}
		}
	}

	for (unsigned int i = 0; i < playerVisionArea.size(); ++i) // 玩家周围区域若有草丛，则变透明
	{
		Vec2 treetileCoord = this->tileCoordFromPosition(playerVisionArea[i]);
		if (_tree->getTileAt(treetileCoord))
		{
			count++;
			_treecell = _tree->getTileAt(treetileCoord); //通过tile坐标访问指定草丛单元格
			_treecell->setOpacity(100);  //透明
		}
	}

	if (count != 0)   // 周围至少有一处草丛变透明
	{
		playerOpacity = MAP_PLAYER_IN_TREE_AND_NOT_AROUND_AI;  // 表示人一定在树丛中，但不一定周围没AI，后续代码判断
		count = 0;
	}

	for (unsigned int i = 1; i < allCharacter.size(); ++i)
	{
		if (AI_PLAYER(i)->_panel.getIsSurvive())
		{
			if (playerOpacity != MAP_PLAYER_NOT_IN_TREE)   // 玩家在草丛的话
			{
				if (AI_PLAYER(i)->getPositionX() <= (pos.x + MAP_PLAYER_TO_AI_VISIBLE_SIZE) &&
					AI_PLAYER(i)->getPositionX() >= (pos.x - MAP_PLAYER_TO_AI_VISIBLE_SIZE) &&
					AI_PLAYER(i)->getPositionY() <= (pos.y + MAP_PLAYER_TO_AI_VISIBLE_SIZE) &&
					AI_PLAYER(i)->getPositionY() >= (pos.y - MAP_PLAYER_TO_AI_VISIBLE_SIZE))   // 这个AI在玩家的周围
					//				&&((playerOpacity == 1) || (playerOpacity = 2)))
				{
					aroundPlayer[i] = true;   // 这个AI在玩家的周围
					AI_PLAYER(i)->setVisible(true);   // 这个AI可见
					allCharacter[i]._healthBar->setVisible(true);
					allCharacter[i]._magicBar->setVisible(true);
					allCharacter[i]._levelText->setVisible(true);
					playerOpacity = MAP_PLAYER_IN_TREE_AND_AROUND_AI;   // 有AI在玩家的周围
				}
				else    // 不在玩家的周围
					aroundPlayer[i] = false;
			}
		}
	}
}

/****************************
* Name ：MapLayer::tileCoordFromPosition
* Summary ：从像素点坐标转化为瓦片坐标
* return ：Vec2(x,y)
****************************/
Vec2 MapLayer::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x, y);
}

/****************************
* Name ：MapLayer::setViewpointCenter
* Summary ：滚动地图
* return ：无
****************************/
void MapLayer::setViewpointCenter(Vec2 position)
{

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//可以防止，视图左边超出屏幕之外。
	float visible_x = MAX(position.x, visibleSize.width / 2);
	float visible_y = MAX(position.y, visibleSize.height / 2);

	//可以防止，视图右边超出屏幕之外。
	visible_x = MIN(visible_x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
		- visibleSize.width / 2.0f);
	visible_y = MIN(visible_y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
		- visibleSize.height / 2.0f);

	visible_x = position.x;
	visible_y = position.y;
	//log("===========================");
	//log("visible %f %f", visible_x, visible_y);
	//屏幕中心点
	Vec2 pointA = Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	//log("pointA %f %f", pointA.x, pointA.y);
	//使精灵处于屏幕中心，移动地图目标位置
	Vec2 pointB = Vec2(visible_x, visible_y);
	//log("pointB %f %f", pointB.x, pointB.y);
	//地图移动偏移量
	Vec2 offset = pointA - pointB;
	//log("offset %f %f", offset.x, offset.y);
	//log("===========================");
	this->setPosition(offset);
}

/****************************
* Name ：MapLayer::createHero
* Summary ：创建角色
* return ：
****************************/
template<typename Hero>
void MapLayer::createHero(Hero** hero, Weapon** weapon, Slider** healthBar, Slider** magicBar, Label** levelText,
	                      Vec2& position, const std::string& filenameHero, const std::string& filenameWeapon)
{
	*hero = Hero::create(filenameHero);
	(**hero).initPlayer();
	addChild(*hero, 4, 200);

	*weapon = Weapon::create(filenameWeapon);
	(**weapon).setAnchorPoint(
		Vec2((**hero)._weaponAnchorPositionX,
			(**hero)._weaponAnchorPositionY));
	addChild(*weapon, 2, 100);

	*healthBar = Slider::create();
	(**healthBar).setPercent((**hero).getHealthPercent());
	(**healthBar).loadBarTexture("/ui/playerHealthbarFrame.png");
	(**healthBar).loadProgressBarTexture("/ui/playerHealthbarBlock.png");
	(**healthBar).setScale(0.5);
	(**healthBar).setAnchorPoint(Vec2(0.5f, 0.0f));
	addChild(*healthBar, 2);

	*magicBar = Slider::create();
	(**magicBar).setPercent((**hero).getMagicPercent());
	(**magicBar).loadBarTexture("/ui/playerMagicbarFrame.png");
	(**magicBar).loadProgressBarTexture("/ui/playerMagicbarBlock.png");
	(**magicBar).setScale(0.5);
	(**magicBar).setAnchorPoint(Vec2(0.5f, 0.0f));
	addChild(*magicBar, 2);
  	*levelText = Label::createWithTTF("Lv.0","fonts/Marker Felt.ttf", 24);
	(**levelText).setString((std::string("Lv.") + std::to_string((**hero)._level)));
	(**levelText).setScale(0.5);
	(**levelText).setAnchorPoint(Vec2(0.5f, 0.0f));
	addChild(*levelText, 2);

	(**hero).setPositionWithAll(position, *weapon, *healthBar, *magicBar, *levelText);
}


/****************************
* Name ：MapLayer::createMonster
* Summary ：初始化怪兽
* return ：
****************************/
template<typename Monsters>
void MapLayer::createMonster(Monsters** monster, Slider** healthBar,
	Vec2& position, const std::string& filenameMonster)
{
	*monster = Monsters::create(filenameMonster);
	(**monster).initMonster();
	addChild(*monster, 3, 200);

	*healthBar = Slider::create();
	(**healthBar).setPercent((**monster).getHealthPercent());
	(**healthBar).loadBarTexture("/ui/playerHealthbarFrame.png");
	(**healthBar).loadProgressBarTexture("/ui/playerHealthbarBlock.png");
	(**healthBar).setScale(0.5);
	(**healthBar).setAnchorPoint(Vec2(0.5f, 0.0f));
	addChild(*healthBar, 3);

	(**monster).setPositionWithAll(position, *healthBar);
}

/****************************
* Name ：MapLayer::update2
* Summary ：实现在attack动画执行后可以执行normal动画
* return ：
****************************/
/*解释：由于执行normal动画如果只添加在onKeyRealeased，
     而鼠标点击开始执行attack动画，如果在鼠标结束后加入normal动画
	   会屏蔽attack动画。如果attack和normal都放在onTouchEnded也
	   会造成attack动画被屏蔽为了。解决这个问题，只能延时调用update2*/
void MapLayer::updatePlayerDoAttack(float delta)
{
	int times = 0;
	if (PLAYER->_panel.getIfPlayNormalAnimationInUpdate2()) 
	{
		for (int i = 1; i < allCharacter.size(); i++) 
		{
			if (CHARACTER(i)._isCollidedByPlayer)
			{
				times++;
				if (PLAYER->_panel.getIfPlayNormalAnimationInUpdate2())
				{
					if (!PLAYER->magicIsFull() || times > 1)
					{
						//log("attack!");
						PLAYER->launchAnAttack(WEAPON, "attack", MAGICBAR, AI_PLAYER(i), AI_HEALTHBAR(i));
					}
					else
					{
						//log("skill!");
						PLAYER->launchAnAttack(WEAPON, "skill", MAGICBAR, AI_PLAYER(i), AI_HEALTHBAR(i));
					}
					if (!AI_PLAYER(i)->_panel.getIsSurvive())  // 如果AI死亡
					{
						PLAYER->upgrade(LEVELTEXT, HEALTHBAR);
						setCharacterVisible(false, CHARACTER(i));
						setCharacterPosition(deathPosition, CHARACTER(i));
						savePlayerKill();

						//log("attack %d", PLAYER->_panel.getAttack());
						//log("attackrate %d", PLAYER->_panel.getAttackRate());
						//log("player kill ai %d", i);

						if (PLAYER->getID() == 1)
							Tools::playEffect("music/gun2_kill.mp3");
						else if (PLAYER->getID() == 2)
							Tools::playEffect("music/sword_kill.mp3");
						else if (PLAYER->getID() == 3)
							Tools::playEffect("music/knife_kill.mp3");
						else if (PLAYER->getID() == 4)
							Tools::playEffect("music/hero4_kill.mp3");
						Tools::setEffectsVolume("musicVolume");
					}
					else
					{
						AI_PLAYER(i)->runAction(Shake::create(0.1f, 5));
					}
				}
				CHARACTER(i)._isCollidedByPlayer = false;     //重新标记为未碰撞
			}
		}
		
		times = 0;
		//player和monster的碰撞结果处理

		for (int i = 0; i < allMonster.size(); i++)
		{
			if (allMonster[i]._isCollidedByPlayer)
			{
				times++;
				if (PLAYER->_panel.getIfPlayNormalAnimationInUpdate2())
				{
					if (!PLAYER->magicIsFull() || times > 1)
					{
						//log("attack!");
						PLAYER->launchAnAttack(WEAPON,"attack",MAGICBAR, MONSTER(i), MONSTER_HEALTHBAR(i));
					}
					else
					{
						//log("skill!");
						PLAYER->launchAnAttack(WEAPON,"skill", MAGICBAR, MONSTER(i), MONSTER_HEALTHBAR(i));
					}
					if (!MONSTER(i)->_panel.getIsSurvive())  // 如果怪兽死亡
					{
						PLAYER->upgrade(LEVELTEXT, HEALTHBAR);
						getBuff(CHARACTER(0), i);
						MONSTER(i)->setVisible(false);
						MONSTER_HEALTHBAR(i)->setVisible(false);
						MONSTER(i)->setPosition(deathPosition);
						MONSTER_HEALTHBAR(i)->setPosition(deathPosition);
						//log("attack %d", PLAYER->_panel.getAttack());
						//log("attackrate %f", PLAYER->_panel.getAttackRate());
						//log("skillrate %f", PLAYER->_panel.getSkillRate());

						Tools::playEffect("music/update.mp3");
						Tools::setEffectsVolume("musicVolume");
					}
					else
					{
						MONSTER(i)->runAction(Shake::create(0.1f, 5));
					}
				}
				allMonster[i]._isCollidedByPlayer = false;
			}
		}

		//player相关数据的重置
		PLAYER->_panel.setPlayerState(NORMAL);
		PLAYER->_panel.setIfPlayAttackAnimation(true);
		if (PLAYER->_panel.getPlayerState() == NORMAL)
		{
			PLAYER->stopAllActions();
			PLAYER->runAction(PLAYER->getNormalAction());
		}
	}

	//可能会出现误标记的情况，保证update2后人物的状态均为未标记
	else
	{
		for (int i = 1; i < allCharacter.size(); i++)
		{
			CHARACTER(i)._isCollidedByPlayer = false;
		}
	}

}

/****************************
* Name ：MapLayer::updateForPortal
* Summary ：探测英雄/AI有无走进传送阵
* return ：
****************************/
void MapLayer::updateForPortal(float delta)
{
	if (PLAYER->getPositionX()<= (_portal_1->getPositionX() + MAP_PORTAL_SIZE)&&
		PLAYER->getPositionX() >= (_portal_1->getPositionX() - MAP_PORTAL_SIZE)&&
		PLAYER->getPositionY() <= (_portal_1->getPositionY() + MAP_PORTAL_SIZE) &&
		PLAYER->getPositionY() >= (_portal_1->getPositionY() - MAP_PORTAL_SIZE))
	{
		PLAYER->setPosition(_portal_Determination_1->getPosition());
	}

	if (PLAYER->getPositionX() <= (_portal_2->getPositionX() + MAP_PORTAL_SIZE) &&
		PLAYER->getPositionX() >= (_portal_2->getPositionX() - MAP_PORTAL_SIZE) &&
		PLAYER->getPositionY() <= (_portal_2->getPositionY() + MAP_PORTAL_SIZE) &&
		PLAYER->getPositionY() >= (_portal_2->getPositionY() - MAP_PORTAL_SIZE))
	{
		PLAYER->setPosition(_portal_Determination_2->getPosition());
	}
	if (PLAYER->getPositionX() <= (_portal_3->getPositionX() + MAP_PORTAL_SIZE) &&
		PLAYER->getPositionX() >= (_portal_3->getPositionX() - MAP_PORTAL_SIZE) &&
		PLAYER->getPositionY() <= (_portal_3->getPositionY() + MAP_PORTAL_SIZE) &&
		PLAYER->getPositionY() >= (_portal_3->getPositionY() - MAP_PORTAL_SIZE))
	{
		PLAYER->setPosition(_portal_Determination_3->getPosition());
	}

	if (PLAYER->getPositionX() <= (_portal_4->getPositionX() + MAP_PORTAL_SIZE) &&
		PLAYER->getPositionX() >= (_portal_4->getPositionX() - MAP_PORTAL_SIZE) &&
		PLAYER->getPositionY() <= (_portal_4->getPositionY() + MAP_PORTAL_SIZE) &&
		PLAYER->getPositionY() >= (_portal_4->getPositionY() - MAP_PORTAL_SIZE))
	{
		PLAYER->setPosition(_portal_Determination_4->getPosition());
	}

	for (int i = 1; i < allCharacter.size(); ++i)
	{
		if (AI_PLAYER(i)->_panel.getIsSurvive()) 
		{
			if (AI_PLAYER(i)->getPositionX() <= (_portal_1->getPositionX() + MAP_PORTAL_SIZE) &&
		  	AI_PLAYER(i)->getPositionX() >= (_portal_1->getPositionX() - MAP_PORTAL_SIZE) &&
			  AI_PLAYER(i)->getPositionY() <= (_portal_1->getPositionY() + MAP_PORTAL_SIZE) &&
		  	AI_PLAYER(i)->getPositionY() >= (_portal_1->getPositionY() - MAP_PORTAL_SIZE))
		  {
			  AI_PLAYER(i)->setPosition(_portal_Determination_1->getPosition());
		  }
		  if (AI_PLAYER(i)->getPositionX() <= (_portal_2->getPositionX() + MAP_PORTAL_SIZE) &&
		  	AI_PLAYER(i)->getPositionX() >= (_portal_2->getPositionX() - MAP_PORTAL_SIZE) &&
		  	AI_PLAYER(i)->getPositionY() <= (_portal_2->getPositionY() + MAP_PORTAL_SIZE) &&
		  	AI_PLAYER(i)->getPositionY() >= (_portal_2->getPositionY() - MAP_PORTAL_SIZE))
		  {
		  	AI_PLAYER(i)->setPosition(_portal_Determination_2->getPosition());
		  }
	  	if (AI_PLAYER(i)->getPositionX() <= (_portal_3->getPositionX() + MAP_PORTAL_SIZE) &&
		  	AI_PLAYER(i)->getPositionX() >= (_portal_3->getPositionX() - MAP_PORTAL_SIZE) &&
		  	AI_PLAYER(i)->getPositionY() <= (_portal_3->getPositionY() + MAP_PORTAL_SIZE) &&
		  	AI_PLAYER(i)->getPositionY() >= (_portal_3->getPositionY() - MAP_PORTAL_SIZE))
		  {
		  	AI_PLAYER(i)->setPosition(_portal_Determination_3->getPosition());
		  }
		  if (AI_PLAYER(i)->getPositionX() <= (_portal_4->getPositionX() + MAP_PORTAL_SIZE) &&
		  	AI_PLAYER(i)->getPositionX() >= (_portal_4->getPositionX() - MAP_PORTAL_SIZE) &&
		  	AI_PLAYER(i)->getPositionY() <= (_portal_4->getPositionY() + MAP_PORTAL_SIZE) &&
		  	AI_PLAYER(i)->getPositionY() >= (_portal_4->getPositionY() - MAP_PORTAL_SIZE))
		  {
		  	AI_PLAYER(i)->setPosition(_portal_Determination_4->getPosition());
      }
    }
	}
}

/****************************
* Name ：MapLayer::updateForFog
* Summary ：安全区不断缩小
* return ：
****************************/
void MapLayer::updateForFog(float delta)
{
	_fogTurn++;
	if (_fogTurn == 1)
	{
		Tools::playEffect("music/first_takedown.mp3");
	}
	else if (_fogTurn == 2)
	{
		Tools::playEffect("music/double_takedown.mp3");
	}
	Tools::setEffectsVolume("musicVolume");
	_SafeArea->runAction(ScaleBy::create(2.0f, 0.8f));
	this->schedule(schedule_selector(MapLayer::updateOutsideFog), 0.1, 2.0f / 0.1, 0.0f);

}

/****************************
* Name ：MapLayer::updateOutsideFog
* Summary ：外部毒气实时生成
* return ：
****************************/
void MapLayer::updateOutsideFog(float delta)
{
	for (int position_x = 0; position_x <= MAP_SAFEAREA_SIZE; position_x += MAP_FOG_DENSITY)
	{
		for (int position_y = 0; position_y <= MAP_SAFEAREA_SIZE; position_y += MAP_FOG_DENSITY)
		{
			if ((!_SafeArea->boundingBox().containsPoint(Vec2(position_x, position_y))) && (_fogIsPlaced[position_x][position_y] == false))
			{
				if (rand() % 6 == 0)
				{
					auto FogFullfill = Sprite::create("ui/purple_fog3.png");
					FogFullfill->setAnchorPoint(Vec2(0.5, 0.5));
					FogFullfill->setPosition(position_x, position_y);
					this->addChild(FogFullfill, 100);
				}
				_fogIsPlaced[position_x][position_y] = true;
			}
		}
	}
}

/****************************
* Name ：MapLayer::updatePlayerHurtByFog
* Summary ：英雄/AI扣血
* return ：
****************************/
void MapLayer::updatePlayerHurtByFog(float delta)
{
	if (PLAYER->_panel.getIsSurvive()
		&& !_SafeArea->boundingBox().containsPoint(Vec2(PLAYER->getPosition())))
	{
		if (Tools::getUserInt("invincibleMode") == 0)
		{
			//扣血
			PLAYER->_panel.hit(MAP_FOG_DAMAGE_TO_PLAYER);
			PLAYER->refreshHealthBar(HEALTHBAR);
			if (!PLAYER->_panel.getIsSurvive())  // player死亡==>GameOverScene
			{
				setCharacterVisible(false, CHARACTER(0));
				setCharacterPosition(deathPosition, CHARACTER(0));

				//log("player died fog");
				saveData();
				gameOver();
			}
		}
	}

	for (int i = 1; i < allCharacter.size(); ++i)
	{
		if (AI_PLAYER(i)->_panel.getIsSurvive() 
			&& !_SafeArea->boundingBox().containsPoint(Vec2(AI_PLAYER(i)->getPosition())))
		{
			AI_PLAYER(i)->_panel.hit(MAP_FOG_DAMAGE_TO_PLAYER);
			AI_PLAYER(i)->refreshHealthBar(AI_HEALTHBAR(i));
			if (!AI_PLAYER(i)->_panel.getIsSurvive())  // AI死亡
			{
				setCharacterVisible(false, CHARACTER(i));
				setCharacterPosition(deathPosition, CHARACTER(i));

				saveAIKill();//毒圈毒死ai被视为ai击杀
				//log("ai %d died fog",i);
				if (_numOfPlayer == 1)
				{
					//log("win bec ai died fog");
					gameOver();
				}
			}
		}
	}
}

/****************************
* Name ：MapLayer::updateAIMove
* Summary ：全体ai移动
* return ：
****************************/
void MapLayer::updateAIMove(float delta)
{
	int tempNum = 1;
	/**/
	for (int i = 1; i < allCharacter.size(); ++i)
	{
		if (AI_PLAYER(i)->_panel.getIsSurvive())
		{
			updateAIMoveOne(CHARACTER(i));
			setCharacterVisible(true, CHARACTER(i));
			++tempNum;
		}
		else
		{
			//setCharacterVisible(false, CHARACTER(i));
			//setCharacterPosition(deathPosition, CHARACTER(i));
		}
	}
	/**/
	_numOfPlayer = tempNum;
	Tools::setUserInt("_numOfPlayer", _numOfPlayer);
	Tools::setUserInt("_hitNum", PLAYER->_panel.getHitnum());
	if (_numOfPlayer == 1)
	{
		gameOver();
	}
}

/****************************
* Name ：MapLayer::updateAIMoveOne
* Summary ：一个ai移动
* return ：
****************************/
void MapLayer::updateAIMoveOne(Character& character)
{
	if (character._player->_panel.getIfPlayAttackAnimation() == false)//没有执行攻击动画
	{
		//动画处理开始
		if (character._player->_panel.getPlayerState() != MOVING)//不是移动状态
		{
			character._player->stopAllActions();//停止所有动作
			character._player->runAction(character._player->getWalkAction());//执行移动动画
		}
		//动画处理结束

		//方向抉择开始
		Tools::getDirtForAI(character, _SafeArea);
		//方向抉择结束

		//移动开始
		/*=====================以下由键盘操作改写=====================*/
		
		Vec2 playerPos = character._player->getPosition();  // 获取位置坐标
		Tools::getNextPosByDirt(playerPos, character);

		/*=====================以上由键盘操作改写=====================*/

		/*=====================以下由位置移动改写=====================*/

		// 读取坐标
		Vec2 tileCoord = this->tileCoordFromPosition(playerPos);  //从像素点坐标转化为瓦片坐标

		int tileGid = _collidable->getTileGIDAt(tileCoord);   //获得瓦片的GID

		// 碰撞检测
		if (tileGid > 0)
		{
			Value prop = _tileMap->getPropertiesForGID(tileGid);
			ValueMap propValueMap = prop.asValueMap();

			std::string collision = propValueMap["Collidable"].asString();
			// 元素+true
			if (collision == "true")
			{ //碰撞检测成功
				character._direct = rand() % 8;//当ai撞墙 每一帧有3/4概率转向 一秒有几十帧 则基本可以做到撞墙即转向
				return;
			}
		}

		character._player->setPositionWithAll(playerPos, character._weapon, character._healthBar, character._magicBar, character._levelText);

		/*=====================以上由位置移动改写=====================*/
	    //移动结束

	}//end of if(没有执行攻击动画)
}

/****************************
* Name ：MapLayer::updateAIAttack
* Summary ：ai攻击
* return ：
****************************/
void MapLayer::updateAIAttack(float delta)
{
	for (int active = 1; active < allCharacter.size(); ++active) {
		for (int passive = 0; passive < allCharacter.size(); ++passive)
		{
			if (active != passive && CHARACTER(passive)._player->_panel.getIsSurvive()
				&& AI_PLAYER(active)->playerCollisionTest(CHARACTER(passive)._player, AI_WEAPON(active), false))
			{

				if (AI_PLAYER(active)->_panel.getPlayerState() != ATTACK && !AI_PLAYER(active)->_panel.getIfPlayAttackAnimation())
				{         // active对passive造成伤害
					AI_PLAYER(active)->stopAllActions();

					if (!AI_PLAYER(active)->magicIsFull()) 
					{
						AI_PLAYER(active)->runAction(AI_PLAYER(active)->getAttackAction());
						if (passive == 0 && Tools::getUserInt("invincibleMode") == 1)
						{
							CHARACTER(passive)._player->runAction(Shake::create(0.1f, passive == 0 ? 4 : 5));
						}
						else
						{
							CHARACTER(passive)._player->runAction(Shake::create(0.1f, passive == 0 ? 4 : 5));
							AI_PLAYER(active)->launchAnAttack(AI_WEAPON(active), "attack", AI_MAGICBAR(active), CHARACTER(passive)._player, CHARACTER(passive)._healthBar);
						}
					}
					else
					{
						AI_PLAYER(active)->runAction(AI_PLAYER(active)->getSkillAction());
						if (passive == 0 && Tools::getUserInt("invincibleMode") == 1)
						{
							CHARACTER(passive)._player->runAction(Shake::create(0.1f, passive == 0 ? 4 : 5));
						}
						else
						{
							CHARACTER(passive)._player->runAction(Shake::create(0.1f, passive == 0 ? 4 : 5));
							AI_PLAYER(active)->launchAnAttack(AI_WEAPON(active), "skill", AI_MAGICBAR(active), CHARACTER(passive)._player, CHARACTER(passive)._healthBar);
						}
					}

					if (!AI_PLAYER(passive)->_panel.getIsSurvive() && passive != 0)   // 如果AI死亡
					{
						AI_PLAYER(active)->upgrade(AI_LEVELTEXT(active), AI_HEALTHBAR(active));
						setCharacterVisible(false, CHARACTER(passive));
						setCharacterPosition(deathPosition, CHARACTER(passive));
						saveAIKill();
						//log("ai %d kill ai %d", active, passive);
					}

					else if (!PLAYER->_panel.getIsSurvive())   // 如果玩家死亡
					{
						AI_PLAYER(active)->upgrade(AI_LEVELTEXT(active), AI_HEALTHBAR(active));
						//log("ai %d kill player", active);
						saveData();
						gameOver();
					}

					//AI数据重置
					AI_PLAYER(active)->_panel.setPlayerState(ATTACK);
					AI_PLAYER(active)->_panel.setIfPlayAttackAnimation(true);
					CHARACTER(active)._ifOpenUpdate = true;
				}
			}
			//碰撞检测失败则不做操作
		}

		//表示如果上面没有经历让 ifPlayAttackAnimation变成true的过程
		//即没有让AI或者player扣血
		//对monster进行相似的操作

		if (!AI_PLAYER(active)->_panel.getIfPlayAttackAnimation()) {
			for (int passive = 0; passive < allMonster.size(); passive++)
			{
				if (MONSTER(passive)->_panel.getIsSurvive()
					&& AI_PLAYER(active)->playerCollisionTest(MONSTER(passive), AI_WEAPON(active), false))
				{
					if (AI_PLAYER(active)->_panel.getPlayerState() != ATTACK && !AI_PLAYER(active)->_panel.getIfPlayAttackAnimation())
					{         // active对passive造成伤害
						AI_PLAYER(active)->stopAllActions();

						if (!AI_PLAYER(active)->magicIsFull()) {
							AI_PLAYER(active)->runAction(AI_PLAYER(active)->getAttackAction());
							AI_PLAYER(active)->launchAnAttack(AI_WEAPON(active), "attack", AI_MAGICBAR(active), MONSTER(passive), MONSTER_HEALTHBAR(passive));
						}
						else {
							AI_PLAYER(active)->runAction(AI_PLAYER(active)->getSkillAction());
							AI_PLAYER(active)->launchAnAttack(AI_WEAPON(active), "skill", AI_MAGICBAR(active), MONSTER(passive), MONSTER_HEALTHBAR(passive));
						}
						if (!MONSTER(passive)->_panel.getIsSurvive())
						{
							//monster设置为不可见，AI升级
							AI_PLAYER(active)->upgrade(AI_LEVELTEXT(active), AI_HEALTHBAR(active));
							getBuff(CHARACTER(active), passive);
							MONSTER(passive)->setVisible(false);
							MONSTER_HEALTHBAR(passive)->setVisible(false);
							MONSTER(passive)->setPosition(deathPosition);
							MONSTER_HEALTHBAR(passive)->setPosition(deathPosition);
						}
						else
						{
							MONSTER(passive)->runAction(Shake::create(0.1f, 5));
						}

						//AI相关数据重置
						AI_PLAYER(active)->_panel.setPlayerState(ATTACK);
						AI_PLAYER(active)->_panel.setIfPlayAttackAnimation(true);
						CHARACTER(active)._ifOpenUpdate = true;
					}
				}
				//碰撞检测失败则不做操作
			}
		}

		//调用schedule
		if (AI_PLAYER(active)->getID() == 1)
		{
			this->scheduleOnce(schedule_selector(MapLayer::updateSetIfPlayAttackAnimation), 0.5f);
		}
		else if (AI_PLAYER(active)->getID() == 2)
		{
			this->scheduleOnce(schedule_selector(MapLayer::updateSetIfPlayAttackAnimation), 0.5f);
		}
		else if (AI_PLAYER(active)->getID() == 3)
		{
			this->scheduleOnce(schedule_selector(MapLayer::updateSetIfPlayAttackAnimation), 0.67f);
		}
		else if (AI_PLAYER(active)->getID() == 4)
		{
			this->scheduleOnce(schedule_selector(MapLayer::updateSetIfPlayAttackAnimation), 0.167f);
		}
	}
}

/****************************
* Name ：MapLayer::updateSetIfPlayAttackAnimation
* Summary ：判断是否有攻击动画
* return ：
****************************/
void MapLayer::updateSetIfPlayAttackAnimation(float delta)
{
	for (int i = 1; i < allCharacter.size(); ++i)
	{
		if (CHARACTER(i)._player->_panel.getIsSurvive())
		{
			if (CHARACTER(i)._ifOpenUpdate)
			{
				CHARACTER(i)._ifOpenUpdate = false;
				CHARACTER(i)._player->_panel.setIfPlayAttackAnimation(false);
			}
		}
	}
}

/****************************
* Name ：MapLayer::getPlayerRank
* Summary ：获取玩家排名
* return ：玩家排名
****************************/
int MapLayer::getPlayerRank()
{
	return _numOfPlayer;
}

/****************************
* Name ：MapLayer::getHitNum
* Summary ：获取玩家击杀数
* return ：玩家击杀数
****************************/
int MapLayer::getHitNum()
{
	return PLAYER->_panel.getHitnum();
}

/****************************
* Name ：MapLayer::savePlayerKill
* Summary ：记录玩家击杀
* return ：
****************************/
void MapLayer::savePlayerKill()
{
	--_numOfPlayer;
	PLAYER->_panel.addHitnum();
	saveData();
}

/****************************
* Name ：MapLayer::saveAIKill
* Summary ：记录ai击杀
* return ：
****************************/
void MapLayer::saveAIKill()
{
	--_numOfPlayer;
	saveData();
}

/****************************
* Name ：MapLayer::saveData
* Summary ：保存数据
* return ：
****************************/
void MapLayer::saveData()
{
	Tools::setUserInt("PlayerRank", this->getPlayerRank());
	Tools::setUserInt("HitNum", this->getHitNum());
}

/****************************
* Name ：MapLayer::gameOver
* Summary ：游戏结束
* return ：
****************************/
void MapLayer::gameOver()
{
	/**/
	Tools::gameoverDataSave();
	/**/
	auto GOS = GameOverScene::createScene();
	Director::getInstance()->replaceScene(GOS);
}

/****************************
* Name ：MapLayer::getBuff
* Summary ：获取增益
* return ：
****************************/
void MapLayer::getBuff(Character& character, int numOfMonster)
{
	if (numOfMonster >= 0 && numOfMonster < MAP_GM_NUMBER)
	{
		//log("kill groundmonster");
	}
	else if (numOfMonster >= MAP_GM_NUMBER && numOfMonster < MAP_GM_NUMBER + MAP_WM_NUMBER)
	{
		//log("kill watermonster");
		getAttackBuff(character);
	}
	else if (numOfMonster >= MAP_GM_NUMBER + MAP_WM_NUMBER && numOfMonster < MAP_GM_NUMBER + MAP_WM_NUMBER + MAP_DM_NUMBER)
	{
		//log("kill desertmonster");
		getDefenceBuff(character);
	}
}

/****************************
* Name ：MapLayer::getAttackBuff
* Summary ：获取攻击增益
* return ：
****************************/
void MapLayer::getAttackBuff(Character& character)
{
	character._player->_panel.setAttack(20 + character._player->_panel.getAttack());
}

/****************************
* Name ：MapLayer::getDefenceBuff
* Summary ：获取防御增益
* return ：
****************************/
void MapLayer::getDefenceBuff(Character& character)
{
	character._player->_panel.setDefence(20 + character._player->_panel.getDefence());
}

/****************************
* Name ：MapLayer::setCharacterVisible
* Summary ：角色可见状态设置
* return ：
****************************/
void MapLayer::setCharacterVisible(bool visible, Character& character)
{
	character._player->setVisible(visible);
	character._healthBar->setVisible(visible);
	character._magicBar->setVisible(visible);
	character._levelText->setVisible(visible);
}

/****************************
* Name ：MapLayer::setCharacterPosition
* Summary ：角色移动
* return ：
****************************/
void MapLayer::setCharacterPosition(Vec2 position, Character& character)
{
	character._player->setPositionWithAll(position,
		character._weapon, character._healthBar, character._magicBar, character._levelText);
}