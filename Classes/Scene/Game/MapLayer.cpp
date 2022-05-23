//作者 : 李元特
//日期 : 2022-5-20

//修改 : 李元特
//日期 : 2022-5-22
//修改 : 增加键盘功能

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
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
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
	//log("1"); 
	_tileMap = TMXTiledMap::create("map/Mapupdated.tmx");
	// 用老地图MiddleMap可以，不知道为啥新地图不可以，还在研究中......
	// 	_tileMap = TMXTiledMap::create("map/MiddleMaper.tmx");
	
	  
	addChild(_tileMap, 0, 100);
	//log("2");
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("player");  // 新地图应该是player
	 
	//ValueMap spawnPoint = group->getObject("Colt");  // 从地图读取游戏人物的位置，游戏人物Colt

	float _playerX = spawnPoint["x"].asFloat();
	float _playerY = spawnPoint["y"].asFloat();
	/*=====================创建角色开始========================*/
	_player = Player::create("Colt.png");
	_player->setPosition(Vec2(_playerX, _playerY));
	_player->initPlayer(100, 2, 3, 4.0f, 5.0f);
	addChild(_player, 2, 200);

	_weapon = Weapon::create("weaponWeapon.png");
	_weapon->setAnchorPoint(
		Vec2(PLAYER_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT,
			PLAYER_WEAPON_ANCHOR_POSITION_Y));
	addChild(_weapon, 2, 200);
	_player->keepWeapon(_weapon); 
	/*=====================创建角色结束========================*/
	setViewpointCenter(_player->getPosition());

	_collidable = _tileMap->getLayer("collidable");  //障碍物collidable
	_collidable->setVisible(false);  // 对应透明度

	_watermonster = _tileMap->getLayer("watermonster");

	setTouchEnabled(true);  // 开启触摸，必须继承于layer
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);


	/*======================控制键盘开始=======================*/
	auto keyboardListener = EventListenerKeyboard::create();// 建立键盘监听器keyboardListener

	keyboardListener->onKeyPressed = CC_CALLBACK_2(MapLayer::onKeyPressed, this);  // 按键盘操作
	// 没有设置成持续按压，持续前进
    //keyboardListener->onKeyReleased = CC_CALLBACK_2(MapLayer::onKeyReleased, this); // 释放键盘操作
	
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
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

	Vec2 playerPos = _player->getPosition();  // 获取玩家位置坐标

	log("Key with keycode %d pressed", keyCode);
	switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_D:
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			playerPos.x += _tileMap->getTileSize().width;
			//_player->runAction(FlipX::create(false));
			_player->runFlipxWithWeapon(false, _weapon);
			break;
		}
		case EventKeyboard::KeyCode::KEY_A:
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		{
			playerPos.x -= _tileMap->getTileSize().width;
			//_player->runAction(FlipX::create(true));
			_player->runFlipxWithWeapon(true, _weapon);
			break;
		}
		case EventKeyboard::KeyCode::KEY_W:
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		{
			playerPos.y += _tileMap->getTileSize().height;
			break;
		}
		case EventKeyboard::KeyCode::KEY_S:
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		{
			playerPos.y -= _tileMap->getTileSize().height;
			break;
		}
		default:
			break;
	}
	this->setPlayerPosition(playerPos);
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


	/*=======================通过鼠标控制人物走动开始===========================*/
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
	int tileGid_watermonster=_watermonster->getTileGIDAt(tileCoord);
	log("success1");

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
	//_player->hitPlayer(5);//对角色造成攻击
	_player->setPositionWithAll(position, _weapon);
	//滚动地图
	this->setViewpointCenter(_player->getPosition());
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

