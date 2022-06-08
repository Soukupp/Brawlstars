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


/*
	对象所在层数：
	_tileMap 0层
	_tree, _collidable 在_tileMap 上 （一部分）
	_portal, _portalDetermination 系列 1层
	*hero, *weapon （包括AI） 2层
	_SafeArea 100层


*/




#include "MapLayer.h"


//USING_NS_CC;
using namespace CocosDenshion;


/****************************
* Name ：MapLayer::createScene
* Summary ：创建MapLayer
* return ：MapLayer
****************************/
Scene* MapLayer::createScene()
{
	auto MapLayer = Scene::create();
	auto layer = MapLayer::create();
	MapLayer->addChild(layer);
	return MapLayer;
}


/****************************
* Name ：problemLoading
* Summary ：错误打印
* return ：
****************************/
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MapLayer.cpp\n");
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

	srand((unsigned)time(0));


	/*===================Tilemap相关设置开始==================*/
	log("Map begin");

	int selectedMap = UserDefault::getInstance()->getIntegerForKey("selectedMap");

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

	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	log("Get Player finished");
	ValueMap spawnPoint = group->getObject("player");

	/*=====================创建角色开始========================*/


	int _playerX = spawnPoint["x"].asInt();
	int _playerY = spawnPoint["y"].asInt();

	int selectedHero = UserDefault::getInstance()->getIntegerForKey("selectedHero");   //selectedHero表示玩家选择的英雄

	switch (selectedHero)     //由于测试的需要，不同英雄的createHero的参数统一为一套
	{
		case 1:
			createHero(&_player1, &_weapon, &_healthBar, &_magicBar, &_levelText,
				Vec2(_playerX, _playerY), "Character/Hero1/hero.png", "Character/Hero1/emptyWeapon.png");
			tempCharacter = { _player1,_weapon,_healthBar,_magicBar,_levelText };
			allCharacter.push_back(tempCharacter);
			break;
		case 2:
			createHero(&_player2, &_weapon, &_healthBar, &_magicBar, &_levelText,
				Vec2(_playerX, _playerY), "Character/Hero2/hero.png", "Character/Hero2/emptyWeapon.png");
			tempCharacter = { _player2,_weapon,_healthBar,_magicBar,_levelText };
			allCharacter.push_back(tempCharacter);
			break;
		case 3:
			createHero(&_player3, &_weapon, &_healthBar, &_magicBar, &_levelText,
				Vec2(_playerX, _playerY), "Character/Hero3/hero.png", "Character/Hero3/emptyWeapon.png");
			tempCharacter = { _player3,_weapon,_healthBar,_magicBar,_levelText };
			allCharacter.push_back(tempCharacter);
			break;
		case 4:
			createHero(&_player4, &_weapon, &_healthBar, &_magicBar, &_levelText,
				Vec2(_playerX, _playerY), "Character/Hero4/hero.png", "Character/Hero4/emptyWeapon.png");
			tempCharacter = { _player4,_weapon,_healthBar,_magicBar,_levelText };
			allCharacter.push_back(tempCharacter);
			break;
	}

	/*=====================创建角色结束========================*/

	/*====================创建安全区开始=======================*/
	log("Safe Area added");
	_SafeArea = Sprite::create("ui/SafeAreaLarge.png");
	_SafeArea->setAnchorPoint(Vec2(0.5, 0.5));
	_SafeArea->setPosition(MAP_SAFEAREA_POSITION);
	//_SafeArea->setVisible(false);
	this->addChild(_SafeArea, 100);
	/*====================创建安全区结束=======================*/

	/*=====================测试对象创建开始=====================*/

	int _aiX[MAP_AI_NUMBER + 1];
	int _aiY[MAP_AI_NUMBER + 1];

	memset(_aiX, 0, sizeof(_aiX));
	memset(_aiY, 0, sizeof(_aiY));

	for (int i = 1; i <= MAP_AI_NUMBER; ++i)
	{
		std::string aiNumber = "ai" + std::to_string(i);
		_aiX[i] = _tileMap->getObjectGroup("AI")->getObject(aiNumber).at("x").asInt();
		_aiY[i] = _tileMap->getObjectGroup("AI")->getObject(aiNumber).at("y").asInt();
	}

	for (int i = 1; i <= MAP_AI_NUMBER; ++i)
	{
		if (i % 4 == 1) {
			createHero(&_player1, &_weapon, &_healthBar, &_magicBar, &_levelText,
				Vec2(_aiX[i], _aiY[i]), "Character/Hero1/hero.png", "Character/Hero1/empty.png");
			tempCharacter = { _player1,_weapon,_healthBar,_magicBar,_levelText };
			allCharacter.push_back(tempCharacter);
		}
		if (i % 4 == 2) {
			createHero(&_player2, &_weapon, &_healthBar, &_magicBar, &_levelText,
				Vec2(_aiX[i], _aiY[i]), "Character/Hero2/hero.png", "Character/Hero2/empty.png");
			tempCharacter = { _player1,_weapon,_healthBar,_magicBar,_levelText };
			allCharacter.push_back(tempCharacter);
		}
		if (i % 4 == 3) {
			createHero(&_player3, &_weapon, &_healthBar, &_magicBar, &_levelText,
				Vec2(_aiX[i], _aiY[i]), "Character/Hero3/hero.png", "Character/Hero3/empty.png");
			tempCharacter = { _player3,_weapon,_healthBar,_magicBar,_levelText };
			allCharacter.push_back(tempCharacter);
		}
		if (i % 4 == 0) {
			createHero(&_player4, &_weapon, &_healthBar, &_magicBar, &_levelText,
				Vec2(_aiX[i], _aiY[i]), "Character/Hero4/hero.png", "Character/Hero4/empty.png");
			tempCharacter = { _player4,_weapon,_healthBar,_magicBar,_levelText };
			allCharacter.push_back(tempCharacter);
		}

	}


	for (int i = 1; i < allCharacter.size(); ++i)
	{
		CHARACTER(i)._player->_panel.setPlayerState(ATTACK);
		CHARACTER(i)._player->_panel.setIfPlayAttackAnimation(false);
		CHARACTER(i)._player->initWalkAction();
		CHARACTER(i)._player->initAttackAction();
		CHARACTER(i)._player->initSkillAction();
		CHARACTER(i)._player->initNormalAction();
		CHARACTER(i)._player->setScale(1.3f);
	}


	this->schedule(schedule_selector(MapLayer::updateAIMove), 0.05f);
	this->schedule(schedule_selector(MapLayer::updateAIAttack), 1.0f);
	createMonster(&_monster, &_monsterHealthBar,
		Vec2(_playerX, _playerY), "Character/Hero3/hero.png");

	/*=====================测试对象创建结束=====================*/

	auto SkillButton = SkillButton::create("ui/buttonForSkill.png", "ui/buttonShadow.png", 30);

	SkillButton->setPosition(Vec2(GAME_SKILL_BUTTON_POSITION_X, GAME_SKILL_BUTTON_POSITION_X));
	this->addChild(SkillButton, 100); // 放在最前面

	PLAYER->initWalkAction();
	PLAYER->initNormalAction();
	PLAYER->initAttackAction();
	PLAYER->initSkillAction();
	PLAYER->setScale(1.3);
	log("%d ID", PLAYER->getID());
	setViewpointCenter(PLAYER->getPosition());

	_collidable = _tileMap->getLayer("collidable");  //障碍物collidable
	_collidable->setVisible(false);                  // 对应collidable图层是否可见
	_tree = _tileMap->getLayer("tree");
	//addChild(_tree, 3);



	/*===================传送阵起点创建开始===================*/
	TMXObjectGroup* portalGroup = _tileMap->getObjectGroup("portal");
	log("Get Portal Finished");
	ValueMap portal_1_Position = portalGroup->getObject("portal1");
	ValueMap portal_2_Position = portalGroup->getObject("portal2");
	ValueMap portal_3_Position = portalGroup->getObject("portal3");
	ValueMap portal_4_Position = portalGroup->getObject("portal4");

	_portal_1 = Sprite::create("ui/scrap.png");
	_portal_1->setPosition(portal_1_Position["x"].asInt(), portal_1_Position["y"].asInt());
	this->addChild(_portal_1, 1);
	/*double x=_portal_1->getPositionX();
	log("p-1-position-x %lf", x);
	double y = _portal_1->getPositionY();
	log("p-1-position-y %lf", y);*/

	_portal_2 = Sprite::create("ui/scrap.png");
	_portal_2->setPosition(portal_2_Position["x"].asInt(), portal_2_Position["y"].asInt());
	this->addChild(_portal_2, 1);

	_portal_3 = Sprite::create("ui/scrap.png");
	_portal_3->setPosition(portal_3_Position["x"].asInt(), portal_3_Position["y"].asInt());
	this->addChild(_portal_3, 1);

	_portal_4 = Sprite::create("ui/scrap.png");
	_portal_4->setPosition(portal_4_Position["x"].asInt(), portal_4_Position["y"].asInt());
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
	_portal_Determination_1->setPosition(portal_Determination_1_Position["x"].asInt(),
		portal_Determination_1_Position["y"].asInt());
	this->addChild(_portal_Determination_1, 1);

	_portal_Determination_2 = Sprite::create("ui/scrapDetermination.png");
	_portal_Determination_2->setPosition(portal_Determination_2_Position["x"].asInt(),
		portal_Determination_2_Position["y"].asInt());
	this->addChild(_portal_Determination_2, 1);

	_portal_Determination_3 = Sprite::create("ui/scrapDetermination.png");
	_portal_Determination_3->setPosition(portal_Determination_3_Position["x"].asInt(),
		portal_Determination_3_Position["y"].asInt());
	this->addChild(_portal_Determination_3, 1);

	_portal_Determination_4 = Sprite::create("ui/scrapDetermination.png");
	_portal_Determination_4->setPosition(portal_Determination_4_Position["x"].asInt(),
		portal_Determination_4_Position["y"].asInt());
	this->addChild(_portal_Determination_4, 1);

	/*===================传送阵终点创建结束===================*/


	//死亡点
	TMXObjectGroup* deathPositionGroup = _tileMap->getObjectGroup("DiePoint");
	ValueMap deathMapPosition = deathPositionGroup->getObject("diePoint");
	deathPosition = Vec2(deathMapPosition["x"].asInt(), deathMapPosition["y"].asInt());

	//log("dddddddddddddddddd %d %d", deathMapPosition["x"].asInt(), deathMapPosition["y"].asInt());


	setTouchEnabled(true);  // 开启触摸，必须继承于layer
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);






    /*===================Tilemap相关设置结束===================*/


	/*====================控制键盘开始==========================*/


	PLAYER->runAction(PLAYER->getNormalAction());

	auto keyboardListener = EventListenerKeyboard::create();// 建立键盘监听器keyboardListener

	keyboardListener->onKeyPressed = CC_CALLBACK_2(MapLayer::onKeyPressed, this);  // 按键盘操作
	// 没有设置成持续按压，持续前进
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MapLayer::onKeyReleased, this); // 释放键盘操作
	
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->schedule(schedule_selector(MapLayer::update), 0.05); 
	//每一帧都进入 update 函数，判断键盘有没有被按压住 参数（也可以控制行走速度）
	/*=====================控制键盘结束===========================*/

	/*=====================控制毒圈开始===========================*/
	memset(FogIsPlaced, 0, sizeof(FogIsPlaced));
	//this->scheduleOnce(schedule_selector(MapLayer::updateForFog), 5.0); // 第一次缩圈
	//this->scheduleOnce(schedule_selector(MapLayer::updateForFog), 5.0); // 第二次缩圈
	//this->scheduleOnce(schedule_selector(MapLayer::updateForFog), 5.0); // 第三次缩圈
	this->schedule(schedule_selector(MapLayer::updateForFog), MAP_SAFEAREA_INTERVAL_LAST, MAP_SAFEAREA_APPEAR_TIMES, MAP_SAFEAREA_DELAY_LAST); // 持续到结束
	this->schedule(schedule_selector(MapLayer::updateOutsideFog));
	this->schedule(schedule_selector(MapLayer::updatePlayerHurtByFog), 0.01);
	this->schedule(schedule_selector(MapLayer::updateForPortal));
	/*=====================控制毒圈结束===========================*/


	return true;
}

/****************************
* Name ：MapLayer::onKeyPressed
* Summary ：按下键盘后分别带来的操作
* return ：无
****************************/
void MapLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//log("Key with keycode %d pressed", keyCode);
	if (
		keyCode== EventKeyboard::KeyCode:: KEY_RIGHT_ARROW||                 //忽略其他非功能按键
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

		PLAYER->_panel.setIfPlayNormalAnimationInUpdate2(false);        //调用normal动画有两个函数，为此函数和update2函数
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

		) {

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

			) {

			PLAYER->stopAllActions();
			PLAYER->_panel.setPlayerState(NORMAL);
			PLAYER->_panel.setIfPlayAttackAnimation(true);
			PLAYER->runAction(PLAYER->getNormalAction());

		}
	}

}


/****************************
* Name ：MapLayer::update
* Summary ：更新函数，改变player实施动态
* return ：无
****************************/
void MapLayer::update(float delta)
{

	Vec2 playerPos = PLAYER->getPosition();  // 获取玩家位置坐标

	if (keyMap[EventKeyboard::KeyCode::KEY_D] || keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
	{
		playerPos.x +=4;
		PLAYER->_panel.setPlayerState(MOVING);          //只要精灵发生位移就在MOVING状态
		PLAYER->runFlipxWithWeapon(false, WEAPON);
	}
	else if (keyMap[EventKeyboard::KeyCode::KEY_A] || keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
	{
		playerPos.x -=4;
		PLAYER->_panel.setPlayerState(MOVING);          //只要精灵发生位移就在MOVING状态
		PLAYER->runFlipxWithWeapon(true, WEAPON);
	}
	else if (keyMap[EventKeyboard::KeyCode::KEY_W] || keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW])
	{
		playerPos.y += 4;
		PLAYER->_panel.setPlayerState(MOVING);           //只要精灵发生位移就在MOVING状态
	}
	else if (keyMap[EventKeyboard::KeyCode::KEY_S] || keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW])
	{
		playerPos.y -= 4;
		PLAYER->_panel.setPlayerState(MOVING);           //只要精灵发生位移就在MOVING状态
	}
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
	log("onTouchBegan"); //日志

	//下面是针对近距离攻击英雄的示范，远距离英雄未实现
	if (PLAYER->_panel.getIfPlayAttackAnimation()&&PLAYER->_panel.getPlayerState()!=MOVING) {        //保证不会实现连续攻击，不会实现一边位移一边攻击
		
		if (PLAYER->_panel.getPlayerState() != ATTACK) {
			PLAYER->_panel.setPlayerState(ATTACK);
			PLAYER->stopAllActions();
			//PLAYER->runAction(PLAYER->getAttackAction());
			//pz 为了测试暂时写死成AIplayer1
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
			if (!PLAYER->magicIsFull())
			{
				PLAYER->runAction(PLAYER->getAttackAction());
				//_player->launchAnAttack(_weapon, "attack", _magicBar, _AIplayer1, _AIhealthBar1);
			}
			else
			{
				PLAYER->runAction(PLAYER->getSkillAction());
				//_player->launchAnAttack(_AIweapon1, "skill", _AImagicBar1, _AIplayer1, _AIhealthBar1);
			}
			PLAYER->_panel.setIfPlayAttackAnimation(false);                                          //保证不会实现连续攻击
																									  //检测攻击时是否碰到PLAYER1
		    //此处仅为测试，_player1是哪个对象需要后期遍历算法得到（目前_player1为ai7）

			PLAYER->_panel.setIfPlayNormalAnimationInUpdate2(true);                                  //使得可以调用update2
			bool ifAttackEnemy = false;
			for (int i = 1; i < allCharacter.size(); i++)
			{
				if (PLAYER->playerCollisionTest1(CHARACTER(i)._player, WEAPON))
				{
					CHARACTER(i).isCollidedByPlayer = true;
					ifAttackEnemy = true;
					break;
				}
			}
			if (PLAYER->magicIsFull())
			if (PLAYER->magicIsFull() && !ifAttackEnemy)
			{
				PLAYER->useMagic();
				PLAYER->launchAnAttack(WEAPON, "skill", MAGICBAR, nullptr, nullptr);
				
			}

			if(PLAYER->getID()==1)
				this->scheduleOnce(schedule_selector(MapLayer::update2), 0.5f);  //1.0f是动画时间，1.0f后进入update2执行一次normal动画
			else if(PLAYER->getID() == 2)
				this->scheduleOnce(schedule_selector(MapLayer::update2), 0.8f);
			else if(PLAYER->getID() == 3)
				this->scheduleOnce(schedule_selector(MapLayer::update2), 0.67f);
			else if (PLAYER->getID() == 4)
				this->scheduleOnce(schedule_selector(MapLayer::update2), 0.33f);

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
	log("onTouchMoved"); //日志
}
 

/****************************
* Name ：MapLayer::onTouchEnded
* Summary ：触摸结束
* return ：是否执行
****************************/
void MapLayer::onTouchEnded(Touch* touch, Event* event)
{
	log("onTouchEnded");  //日志 



	/*================获取触摸点的坐标，并转化为当前层模型坐标系==================*/
	Vec2 touchLocation = touch->getLocation();  //获得在OpenGL坐标
	touchLocation = this->convertToNodeSpace(touchLocation);  //转换为当前层的模型坐标系

	Vec2 playerPos = PLAYER->getPosition();  // 获取玩家位置坐标

	Vec2 diff = touchLocation - playerPos;    // 获取上述两者坐标差 

	/*=============================坐标获取结束================================*/

	/*=============================角度获取开始================================*/
	float playerWeaponAngle;
	if (fabs(touchLocation.x - playerPos.x) < 1e-6 && touchLocation.y > playerPos.y)      //横坐标相等，纵坐标不等，向上90°
		playerWeaponAngle = 0.5 * M_PI;
	else if (fabs(touchLocation.x - playerPos.x) < 1e-6 && touchLocation.y <= playerPos.y)  //横坐标相等，纵坐标不等，向下90°
		playerWeaponAngle = -0.5 * M_PI;
	else
		playerWeaponAngle = atan((touchLocation.y - playerPos.y) / (touchLocation.x - playerPos.x));
	log("playerWeaponAngle is %lf", playerWeaponAngle);
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
	//int tileGid_watermonster=_watermonster->getTileGIDAt(tileCoord);
  /*
	log("get TileGIDAt");*/

	// 碰撞检测
	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();
		// 元素+true
		if (collision == "true") { //碰撞检测成功
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/empty.wav");
			return;
		}
	}

	PLAYER->setPositionWithAll(position, WEAPON, HEALTHBAR, MAGICBAR, LEVELTEXT);

	//滚动地图
	this->setViewpointCenter(PLAYER->getPosition());
}

/****************************
* Name ：MapLayer::setTreeOpacity
* Summary ：树的透明度
* return ：无
****************************/
void MapLayer::setTreeOpacity(Vec2 pos)
{
	static std::vector<Vec2> playerVisionArea = {};
	
	for (int i = 0; i < playerVisionArea.size(); ++i)
	{
		Vec2 treetileCoord = this->tileCoordFromPosition(playerVisionArea[i]);
		if (_tree->getTileAt(treetileCoord))
		{
			_treecell = _tree->getTileAt(treetileCoord); //通过tile坐标访问指定草丛单元格
			_treecell->setOpacity(255);  //不透明
		}
	}
	Vec2 cellsize = _tileMap->getTileSize();

	playerVisionArea = {
		pos,
		Vec2(pos.x + cellsize.x,pos.y),
		Vec2(pos.x - cellsize.x,pos.y),
		Vec2(pos.x,pos.y + cellsize.y),
		Vec2(pos.x,pos.y - cellsize.y),
	};
	
	for (int i = 0; i < playerVisionArea.size(); ++i)
	{
		Vec2 treetileCoord = this->tileCoordFromPosition(playerVisionArea[i]);
		if (_tree->getTileAt(treetileCoord))
		{
			_treecell = _tree->getTileAt(treetileCoord); //通过tile坐标访问指定草丛单元格
			_treecell->setOpacity(100);  //透明
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
	//log("setViewpointCenter"); //日志

	//log("position (%f ,%f) ", position.x, position.y);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//可以防止，视图左边超出屏幕之外。
	int visible_x = MAX(position.x, visibleSize.width / 2);
	int visible_y = MAX(position.y, visibleSize.height / 2);
	//可以防止，视图右边超出屏幕之外。
	visible_x = MIN(visible_x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
		- visibleSize.width / 2);
	visible_y = MIN(visible_y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
		- visibleSize.height / 2);

	//屏幕中心点
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);

	//使精灵处于屏幕中心，移动地图目标位置
	Vec2 pointB = Vec2(visible_x, visible_y);
	//log("目标位置 (%f ,%f) ", pointB.x, pointB.y);

	//地图移动偏移量
	Vec2 offset = pointA - pointB;
	//log("offset (%f ,%f) ", offset.x, offset.y);
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
	addChild(*hero, 3, 200);

	*weapon = Weapon::create(filenameWeapon);
	(**weapon).setAnchorPoint(
		Vec2((**hero)._weaponAnchorPositionX,
			(**hero)._weaponAnchorPositionY));
	addChild(*weapon, 2, 200);

	*healthBar = Slider::create();
	(**healthBar).setPercent((**hero).getHealthPercent());
	(**healthBar).loadBarTexture("/ui/playerHealthbarFrame.png");
	(**healthBar).loadProgressBarTexture("/ui/playerHealthbarBlock.png");
	(**healthBar).setScale(0.5);
	(**healthBar).setAnchorPoint(Vec2(0.5f, 0.0f));
	addChild(*healthBar);

	*magicBar = Slider::create();
	(**magicBar).setPercent((**hero).getMagicPercent());
	(**magicBar).loadBarTexture("/ui/playerMagicbarFrame.png");
	(**magicBar).loadProgressBarTexture("/ui/playerMagicbarBlock.png");
	(**magicBar).setScale(0.5);
	(**magicBar).setAnchorPoint(Vec2(0.5f, 0.0f));
	addChild(*magicBar);
  	*levelText = Label::createWithTTF("Lv.0","fonts/Marker Felt.ttf", 24);
	(**levelText).setString((std::string("Lv.") + std::to_string((**hero)._level)));
	(**levelText).setScale(0.5);
	(**levelText).setAnchorPoint(Vec2(0.5f, 0.0f));
	addChild(*levelText);

	(**hero).setPositionWithAll(position, *weapon, *healthBar, *magicBar, *levelText);
}

void MapLayer::createMonster(Monster** monster, Slider** healthBar,
	Vec2& position, const std::string& filenameMonster)
{
	*monster = Monster::create(filenameMonster);
	(**monster).initMonster(1000,0,100,0,0);//无用数据直接空置
	addChild(*monster, 3, 200);

	*healthBar = Slider::create();
	(**healthBar).setPercent((**monster).getHealthPercent());
	(**healthBar).loadBarTexture("/ui/playerHealthbarFrame.png");
	(**healthBar).loadProgressBarTexture("/ui/playerHealthbarBlock.png");
	(**healthBar).setScale(0.5);
	(**healthBar).setAnchorPoint(Vec2(0.5f, 0.0f));
	addChild(*healthBar);

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
void MapLayer::update2(float delta)
{
	bool ifattack = false;
	int j = 0;
	for (int i = 1; i < allCharacter.size(); i++) {
		if (CHARACTER(i).isCollidedByPlayer) { j++; }
	}
	log("j = %d",j);
	int times = 0;
	if (PLAYER->_panel.getIfPlayNormalAnimationInUpdate2()) {
		for (int i = 1; i < allCharacter.size(); i++) {
			if (CHARACTER(i).isCollidedByPlayer) {
				ifattack = true;
				times++;
				if (PLAYER->_panel.getIfPlayNormalAnimationInUpdate2())
				{
					if (!PLAYER->magicIsFull()||times>1)
					{
						log("attack!");
						PLAYER->launchAnAttack(WEAPON, "attack", MAGICBAR, CHARACTER(i)._player, CHARACTER(i)._healthBar);
					}
					else
					{
						log("skill!");
						PLAYER->launchAnAttack(WEAPON, "skill", MAGICBAR, CHARACTER(i)._player, CHARACTER(i)._healthBar);
					}

				}
				CHARACTER(i).isCollidedByPlayer = false;
			}
		}
		int i = ifattack;
		log("ifattack:  %d", i);

		PLAYER->_panel.setPlayerState(NORMAL);
		PLAYER->_panel.setIfPlayAttackAnimation(true);
		if (PLAYER->_panel.getPlayerState() == NORMAL) {
			PLAYER->stopAllActions();
			PLAYER->runAction(PLAYER->getNormalAction());
		}
	}
	else
	{
		for (int i = 1; i < allCharacter.size(); i++)
		{
			CHARACTER(i).isCollidedByPlayer = false;
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
		log("PLAYER Teleport One!");
		PLAYER->setPosition(_portal_Determination_1->getPosition());
	}

	if (PLAYER->getPositionX() <= (_portal_2->getPositionX() + MAP_PORTAL_SIZE) &&
		PLAYER->getPositionX() >= (_portal_2->getPositionX() - MAP_PORTAL_SIZE) &&
		PLAYER->getPositionY() <= (_portal_2->getPositionY() + MAP_PORTAL_SIZE) &&
		PLAYER->getPositionY() >= (_portal_2->getPositionY() - MAP_PORTAL_SIZE))
	{
		log("PLAYER Teleport Two!");
		PLAYER->setPosition(_portal_Determination_2->getPosition());
	}
	if (PLAYER->getPositionX() <= (_portal_3->getPositionX() + MAP_PORTAL_SIZE) &&
		PLAYER->getPositionX() >= (_portal_3->getPositionX() - MAP_PORTAL_SIZE) &&
		PLAYER->getPositionY() <= (_portal_3->getPositionY() + MAP_PORTAL_SIZE) &&
		PLAYER->getPositionY() >= (_portal_3->getPositionY() - MAP_PORTAL_SIZE))
	{
		log("PLAYER Teleport Three!");
		PLAYER->setPosition(_portal_Determination_3->getPosition());
	}

	if (PLAYER->getPositionX() <= (_portal_4->getPositionX() + MAP_PORTAL_SIZE) &&
		PLAYER->getPositionX() >= (_portal_4->getPositionX() - MAP_PORTAL_SIZE) &&
		PLAYER->getPositionY() <= (_portal_4->getPositionY() + MAP_PORTAL_SIZE) &&
		PLAYER->getPositionY() >= (_portal_4->getPositionY() - MAP_PORTAL_SIZE))
	{
		log("PLAYER Teleport Four!");
		PLAYER->setPosition(_portal_Determination_4->getPosition());
	}

	for (int i = 1; i < allCharacter.size(); ++i)
	{
		if (CHARACTER(i)._player->getPositionX() <= (_portal_1->getPositionX() + MAP_PORTAL_SIZE) &&
			CHARACTER(i)._player->getPositionX() >= (_portal_1->getPositionX() - MAP_PORTAL_SIZE) &&
			CHARACTER(i)._player->getPositionY() <= (_portal_1->getPositionY() + MAP_PORTAL_SIZE) &&
			CHARACTER(i)._player->getPositionY() >= (_portal_1->getPositionY() - MAP_PORTAL_SIZE))
			CHARACTER(i)._player->setPosition(_portal_Determination_1->getPosition());
		if (CHARACTER(i)._player->getPositionX() <= (_portal_2->getPositionX() + MAP_PORTAL_SIZE) &&
			CHARACTER(i)._player->getPositionX() >= (_portal_2->getPositionX() - MAP_PORTAL_SIZE) &&
			CHARACTER(i)._player->getPositionY() <= (_portal_2->getPositionY() + MAP_PORTAL_SIZE) &&
			CHARACTER(i)._player->getPositionY() >= (_portal_2->getPositionY() - MAP_PORTAL_SIZE))
			CHARACTER(i)._player->setPosition(_portal_Determination_2->getPosition());
		if (CHARACTER(i)._player->getPositionX() <= (_portal_3->getPositionX() + MAP_PORTAL_SIZE) &&
			CHARACTER(i)._player->getPositionX() >= (_portal_3->getPositionX() - MAP_PORTAL_SIZE) &&
			CHARACTER(i)._player->getPositionY() <= (_portal_3->getPositionY() + MAP_PORTAL_SIZE) &&
			CHARACTER(i)._player->getPositionY() >= (_portal_3->getPositionY() - MAP_PORTAL_SIZE))
			CHARACTER(i)._player->setPosition(_portal_Determination_3->getPosition());
		if (CHARACTER(i)._player->getPositionX() <= (_portal_4->getPositionX() + MAP_PORTAL_SIZE) &&
			CHARACTER(i)._player->getPositionX() >= (_portal_4->getPositionX() - MAP_PORTAL_SIZE) &&
			CHARACTER(i)._player->getPositionY() <= (_portal_4->getPositionY() + MAP_PORTAL_SIZE) &&
			CHARACTER(i)._player->getPositionY() >= (_portal_4->getPositionY() - MAP_PORTAL_SIZE))
			CHARACTER(i)._player->setPosition(_portal_Determination_4->getPosition());
	}

}


/****************************
* Name ：MapLayer::updateForFog
* Summary ：安全区不断缩小
* return ：
****************************/
void MapLayer::updateForFog(float delta)
{
	//_SafeArea;

	/*ScaleBy* SafeAreaScaleBy = ScaleBy::create(2.0f, 0.8f);*/
	_SafeArea->runAction(ScaleBy::create(2.0f, 0.8f));

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
			if ((!_SafeArea->boundingBox().containsPoint(Vec2(position_x, position_y))) && (FogIsPlaced[position_x][position_y] == false))
			{
				auto FogFullfill = Sprite::create("ui/purple_fog3.png");
				FogFullfill->setAnchorPoint(Vec2(0.5, 0.5));
				FogFullfill->setPosition(position_x, position_y);
				this->addChild(FogFullfill, 100);
				FogIsPlaced[position_x][position_y] = true;
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
	if (!_SafeArea->boundingBox().containsPoint(Vec2(PLAYER->getPosition())))
	{
		//扣血
		//log("hurt!");
		PLAYER->_panel.hit(MAP_FOG_DAMAGE_TO_PLAYER);
		PLAYER->refreshHealthBar(HEALTHBAR);
		if (!PLAYER->_panel.getIsSurvive())  // player死亡==》GameOverScene
		{
			PLAYER->setVisible(false);
			PLAYER->setPosition(deathPosition);
		}
	}
	for (int i = 1; i < allCharacter.size(); ++i)
	{
		if (!_SafeArea->boundingBox().containsPoint(Vec2(CHARACTER(i)._player->getPosition())))
		{
			CHARACTER(i)._player->_panel.hit(MAP_FOG_DAMAGE_TO_PLAYER);
			CHARACTER(i)._player->refreshHealthBar(AI_HEALTHBAR(i));
			if (!CHARACTER(i)._player->_panel.getIsSurvive())  // AI死亡
			{
				CHARACTER(i)._player->setVisible(false);
				CHARACTER(i)._player->setPosition(deathPosition);
			}
		}
	}
}

void MapLayer::updateAIMove(float delta)
{
	for (int i = 1; i < allCharacter.size(); ++i) {
		updateAIMoveOne(CHARACTER(i));

	}
}

void MapLayer::updateAIMoveOne(Character& character)
{
	int i = character._player->_panel.getIfPlayAttackAnimation();

	if (character._player->_panel.getIfPlayAttackAnimation() == false) {
		if (character._player->_panel.getPlayerState() != MOVING)
		{
			character._player->stopAllActions();
			character._player->runAction(character._player->getWalkAction());
		}
		if (!_SafeArea->boundingBox().containsPoint(Vec2(character._player->getPosition())))//不在安全区
		{
			//log("not safe area");
			++character.searchTimes;
			if (character.searchTimes <= 100)//寻路少于一定数量则进行逃离方向选择逻辑
			{
				//log("searchTimes <= 200");
				if (!character.backDirectChanged)//且没有掉头
				{//那么掉头
					//log("!backDirectChanged");
					if (character.direct <= 1)//左右
					{
						character.direct = 1 - character.direct;
					}
					else//上下
					{
						character.direct = 5 - character.direct;
					}
					character.backDirectChanged = true;
				}
				//否则维持原方向
			}
			else//达到寻路上限还没逃离则开始随机选方向逃出
			{
				//log("searchTimes > 200");
				character.backDirectChanged = false;//参数重置
				int tempDirect = rand() % 60;
				if (tempDirect <= 3)//除去原本的方向，每一帧有3/60的几率转向
				{//这样是为了保证ai基本可以走一段路 而不是原地不停转向
					character.direct = tempDirect;//每一帧小概率获取新方向或者大概率维持原方向
				}
			}
		}
		else//在安全区
		{//正常选方向
			character.searchTimes = 0;//参数重置
			character.backDirectChanged = false;//参数重置
			int tempDirect = rand() % 60;
			if (tempDirect <= 3)//除去原本的方向，每一帧有3/60的几率转向
			{//这样是为了保证ai基本可以走一段路 而不是原地不停转向
				character.direct = tempDirect;//每一帧小概率获取新方向或者大概率维持原方向
			}
		}

		/*
		* 这里应当判断ai的角色的当前状态 比如如果在攻击则不移动 现在暂时写成一直移动
		*/
		if (/*character._player->_panel.getIfPlayAttackAnimation() == false*/1) {
			/*=====================以下由键盘操作改写=====================*/
			Vec2 playerPos = character._player->getPosition();  // 获取位置坐标
			if (character.direct == 0)
			{
				playerPos.x += 2;
				character._player->_panel.setPlayerState(MOVING);          //只要精灵发生位移就在MOVING状态
				//PLAYER->runAction(FlipX::create(false));
				character._player->runFlipxWithWeapon(false, character._weapon);
			}
			else if (character.direct == 1)
			{
				playerPos.x -= 2;
				character._player->_panel.setPlayerState(MOVING);          //只要精灵发生位移就在MOVING状态
				//PLAYER->runAction(FlipX::create(true));
				character._player->runFlipxWithWeapon(true, character._weapon);
			}
			else if (character.direct == 2)
			{
				playerPos.y += 2;
				character._player->_panel.setPlayerState(MOVING);           //只要精灵发生位移就在MOVING状态
			}
			else if (character.direct == 3)
			{
				playerPos.y -= 2;
				character._player->_panel.setPlayerState(MOVING);           //只要精灵发生位移就在MOVING状态
			}
			/*=====================以上由键盘操作改写=====================*/

				/*=====================以下由位置移动改写=====================*/
				// 读取坐标
			Vec2 tileCoord = this->tileCoordFromPosition(playerPos);  //从像素点坐标转化为瓦片坐标

			int tileGid = _collidable->getTileGIDAt(tileCoord);   //获得瓦片的GID

			// 碰撞检测
			if (tileGid > 0) {
				Value prop = _tileMap->getPropertiesForGID(tileGid);
				ValueMap propValueMap = prop.asValueMap();

				std::string collision = propValueMap["Collidable"].asString();
				// 元素+true
				if (collision == "true") { //碰撞检测成功
					character.direct = rand() % 4;//当ai撞墙 每一帧有3/4概率转向 一秒有几十帧 则基本可以做到撞墙即转向
					return;
				}
			}

			character._player->setPositionWithAll(playerPos, character._weapon, character._healthBar, character._magicBar, character._levelText);
			/*=====================以上由位置移动改写=====================*/

				//this->setTreeOpacity(playerPos);//

		}
	}
}

void MapLayer::updateAIAttack(float delta)
{
	for (int i = 1; i < allCharacter.size(); ++i) {
		for (int j = 0; j < allCharacter.size(); ++j)
		{
			if (i != j && CHARACTER(i)._player->playerCollisionTest2(CHARACTER(j)._player, CHARACTER(i)._weapon))//修改这里 改成碰撞检测成功 现在暂时是一直发动攻击
			{
				//这里暂时写成始终攻击玩家
				//后续改成所碰撞到的角色

				if (CHARACTER(i)._player->_panel.getPlayerState() != ATTACK && !CHARACTER(i)._player->_panel.getIfPlayAttackAnimation())
				{         // i对j造成伤害
					CHARACTER(i)._player->stopAllActions();
					if (!CHARACTER(i)._player->magicIsFull()) {
						CHARACTER(i)._player->runAction(CHARACTER(i)._player->getAttackAction());
						CHARACTER(i)._player->launchAnAttack(CHARACTER(i)._weapon, "attack", CHARACTER(i)._magicBar, CHARACTER(j)._player, CHARACTER(j)._healthBar);
						if (!CHARACTER(j)._player->_panel.getIsSurvive() && j != 0)   // AI 死亡
						{
							CHARACTER(j)._player->setVisible(false);
							CHARACTER(j)._player->setPosition(deathPosition);
						}
						else if (!CHARACTER(j)._player->_panel.getIsSurvive())   // 玩家 死亡
						{
							CHARACTER(j)._player->setVisible(false);
							CHARACTER(j)._player->setPosition(deathPosition);
						}
					}
					else {
						CHARACTER(i)._player->runAction(CHARACTER(i)._player->getSkillAction());
						CHARACTER(i)._player->launchAnAttack(CHARACTER(i)._weapon, "skill", CHARACTER(i)._magicBar, CHARACTER(j)._player, CHARACTER(j)._healthBar);
						if (!CHARACTER(j)._player->_panel.getIsSurvive() && j != 0)   // AI 死亡
						{
							CHARACTER(j)._player->setVisible(false);
							CHARACTER(j)._player->setPosition(deathPosition);
						}
						else if (!CHARACTER(j)._player->_panel.getIsSurvive())   // 玩家 死亡
						{
							CHARACTER(j)._player->setVisible(false);
							CHARACTER(j)._player->setPosition(deathPosition);
						}
					}
					CHARACTER(i)._player->_panel.setPlayerState(ATTACK);
					CHARACTER(i)._player->_panel.setIfPlayAttackAnimation(true);
					CHARACTER(i).ifOpenUpdate = true;

					if (CHARACTER(i)._player->getID() == 1)
						this->scheduleOnce(schedule_selector(MapLayer::updateSetIfPlayAttackAnimation), 0.5f);
					else if (CHARACTER(i)._player->getID() == 2)
						this->scheduleOnce(schedule_selector(MapLayer::updateSetIfPlayAttackAnimation), 0.75f);
					else if (CHARACTER(i)._player->getID() == 3)
						this->scheduleOnce(schedule_selector(MapLayer::updateSetIfPlayAttackAnimation), 0.67f);
					else if (CHARACTER(i)._player->getID() == 4)
						this->scheduleOnce(schedule_selector(MapLayer::updateSetIfPlayAttackAnimation), 0.33f);
				}

			}
			//碰撞检测失败则不做操作
		}
	}
}

void MapLayer::updateSetIfPlayAttackAnimation(float delta)
{
	
	for (int i = 1; i < allCharacter.size() ; ++i) 
	{
		if (CHARACTER(i).ifOpenUpdate)
		{
			CHARACTER(i).ifOpenUpdate = false;
			CHARACTER(i)._player->_panel.setIfPlayAttackAnimation(false);
		}
	}

}

//
