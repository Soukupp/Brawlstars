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


#include "MapLayer.h"
#include "GameOverScene.h"


USING_NS_CC;
using namespace CocosDenshion;


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
	 

	/*======================创建地图开始=======================*/
	log("Map begin"); 
	_tileMap = TMXTiledMap::create("map/Mapupdated1.tmx");
	//	_tileMap = TMXTiledMap::create("map/Mapupdated3.tmx");  // 也可以用了，Mapupdated2是Mapupdated3的材料，不可删去
	
	  
	addChild(_tileMap, 0, 100);
	log("Map finished");

	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	log("Get Player finished");
	ValueMap spawnPoint = group->getObject("player");  // 新地图应该是player
	

	/*=====================创建角色开始========================*/
	int _playerX = spawnPoint["x"].asInt();
	int _playerY = spawnPoint["y"].asInt();

	int selectedHero = UserDefault::getInstance()->getIntegerForKey("selectedHero");   //selectedHero表示玩家选择的英雄

	switch (selectedHero)     //由于测试的需要，不同英雄的createHero的参数统一为一套
	{       
	case 1:
		createHero(&_player, &_weapon, &_healthBar, &_magicBar, &_levelText,
			Vec2(_playerX, _playerY), "Character/Hero1/hero.png", "Character/Hero1/emptyWeapon.png");
		break;
	case 2:
		createHero(&_player, &_weapon, &_healthBar, &_magicBar, &_levelText,
			Vec2(_playerX, _playerY), "Character/Hero2/hero.png", "Character/Hero2/emptyWeapon.png");
		break;
	case 3:
		createHero(&_player, &_weapon, &_healthBar, &_magicBar, &_levelText,
			Vec2(_playerX, _playerY), "Character/Hero3/hero.png", "Character/Hero3/emptyWeapon.png");
		break;
	case 4:
		break;
	}
	/*=====================创建角色结束========================*/
	setViewpointCenter(_player->getPosition());

	_collidable = _tileMap->getLayer("collidable");  //障碍物collidable
	_collidable->setVisible(false);                  // 对应collidable图层是否可见
	_tree = _tileMap->getLayer("tree");
	//addChild(_tree, 3);



	//_watermonster = _tileMap->getLayer("watermonster");

	setTouchEnabled(true);  // 开启触摸，必须继承于layer
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);


	/*======================控制键盘开始=======================*/
	auto keyboardListener = EventListenerKeyboard::create();// 建立键盘监听器keyboardListener

	keyboardListener->onKeyPressed = CC_CALLBACK_2(MapLayer::onKeyPressed, this);  // 按键盘操作
	// 没有设置成持续按压，持续前进
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MapLayer::onKeyReleased, this); // 释放键盘操作
	
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->schedule(schedule_selector(MapLayer::update), 0.05); 
	//每一帧都进入 update 函数，判断键盘有没有被按压住 参数（也可以控制行走速度）
	/*======================控制键盘结束=======================*/

	/*======================创建地图结束=======================*/


	return true;
}


/****************************
* Name ：MapLayer::onKeyPressed
* Summary ：按下键盘后分别带来的操作
* return ：无
****************************/
void MapLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("Key with keycode %d pressed", keyCode);
	keyMap[keyCode] = true;

}


/****************************
* Name ：MapLayer::onKeyReleased
* Summary ：按下键盘后分别带来的操作
* return ：无
****************************/
void MapLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

	log("Key with keycode %d released", keyCode);
	keyMap[keyCode] = false;
}


/****************************
* Name ：MapLayer::update
* Summary ：更新函数，改变player实施动态
* return ：无
****************************/
void MapLayer::update(float delta)
{

	Vec2 playerPos = _player->getPosition();  // 获取玩家位置坐标
	if (keyMap[EventKeyboard::KeyCode::KEY_D] || keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
	{
		playerPos.x +=4;

		//_player->runAction(FlipX::create(false));
		_player->runFlipxWithWeapon(false, _weapon);
	}
	else if (keyMap[EventKeyboard::KeyCode::KEY_A] || keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
	{
		playerPos.x -=4;

		//_player->runAction(FlipX::create(true));
		_player->runFlipxWithWeapon(true, _weapon);
	}
	else if (keyMap[EventKeyboard::KeyCode::KEY_W] || keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW])
	{
		playerPos.y += 4;
	}
	else if (keyMap[EventKeyboard::KeyCode::KEY_S] || keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW])
	{
		playerPos.y -= 4;
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

	Vec2 playerPos = _player->getPosition();  // 获取玩家位置坐标

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




	/*=======================通过鼠标控制人物走动开始===========================*
	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += _tileMap->getTileSize().width;
			//_player->runAction(FlipX::create(false));
			_player->runFlipxWithWeapon(false, _weapon);
		}
		else {
			playerPos.x -= _tileMap->getTileSize().width;
			//_player->runAction(FlipX::create(true));
			_player->runFlipxWithWeapon(true, _weapon);
		}
	}
	else {
		if (diff.y > 0) {
			playerPos.y += _tileMap->getTileSize().height;
		}
		else {
			playerPos.y -= _tileMap->getTileSize().height;
		}
	}
	this->setPlayerPosition(playerPos);   // 判断可不可以走动
	/*=======================通过鼠标控制人物走动结束===========================*/
}


/****************************
* Name ：MapLayer::setPlayerPosition
* Summary ：是否走动
* return ：无
****************************/
void MapLayer::setPlayerPosition(Vec2 position)
{
	log("setPlayerPosition");
	// 读取坐标
	Vec2 tileCoord = this->tileCoordFromPosition(position);  //从像素点坐标转化为瓦片坐标

	int tileGid = _collidable->getTileGIDAt(tileCoord);   //获得瓦片的GID
	//int tileGid_watermonster=_watermonster->getTileGIDAt(tileCoord);
	log("get TileGIDAt");

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
	//if (tileGid_watermonster > 0) {
	//	Value prop = _tileMap->getPropertiesForGID(tileGid_watermonster);
	//	log("success2");
	//	ValueMap propValueMap = prop.asValueMap();  // 报错
	//	log("success3");
	//	std::string collision = propValueMap["crash"].asString();
	//	// 元素+true
	//	if (collision == "true") { //碰撞检测成功
	//		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");
	//		return;
	//	}
	//}
	//移动精灵
	_player->setPositionWithAll(position, _weapon, _healthBar, _magicBar, _levelText);
	/**/
	//_player->launchAnAttack(_weapon, "attack", _magicBar);
	/**
	_player->launchAnAttack(_weapon, "attack");
	/**/

	//滚动地图
	this->setViewpointCenter(_player->getPosition());
}

/****************************
* Name ：MapLayer::setTreeOpacity
* Summary ：树的透明度
* return ：无
****************************/
void MapLayer::setTreeOpacity(Vec2 pos)
{
	log("setTreeOpacity");
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
	log("tileCoordFromPosition");
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
	log("setViewpointCenter"); //日志

	log("position (%f ,%f) ", position.x, position.y);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//可以防止，视图左边超出屏幕之外。
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	//可以防止，视图右边超出屏幕之外。
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
		- visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
		- visibleSize.height / 2);

	//屏幕中心点
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);

	//使精灵处于屏幕中心，移动地图目标位置
	Vec2 pointB = Vec2(x, y);
	log("目标位置 (%f ,%f) ", pointB.x, pointB.y);

	//地图移动偏移量
	Vec2 offset = pointA - pointB;
	log("offset (%f ,%f) ", offset.x, offset.y);
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
	addChild(*hero, 2, 200);

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