//作者 : 李元特
//日期 : 2022-5-18

#include "GameScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/****************************
* Name ：GameScene::createScene
* Summary ：创建场景，实质layer
* return ：场景类指针
****************************/
Scene* GameScene::createScene()
{
	auto GameScene = Scene::create();
	auto MapLayer = GameScene::create();
	GameScene->addChild(MapLayer);
	return GameScene;
}

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
* Name ：GameScene::init
* Summary ：游戏场景初始化
* return ：初始化成功与否
****************************/
bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	

	/*=====================创建关闭按钮开始======================*/
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}  // 关闭菜单需要改为固定位置（且此处关闭菜单表示跳到结束界面）

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);
	/*=====================创建关闭按钮结束====================*/

	/*======================创建地图开始=======================*/

	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	addChild(_tileMap, 0, 100);

	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("Colt");  // 从地图读取游戏人物的位置，游戏人物Colt

	float _playerX = spawnPoint["x"].asFloat();
	float _playerY = spawnPoint["y"].asFloat();

	_player = Sprite::create("Colt.png");
	_player->setPosition(Vec2(_playerX, _playerY));
	addChild(_player, 2, 200);

	setViewpointCenter(_player->getPosition());

	_collidable = _tileMap->getLayer("collidable");  //障碍物collidable
	_collidable->setVisible(false);  // 对应透明度

	setTouchEnabled(true);  // 开启触摸，必须继承于layer
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	/*======================创建地图结束=======================*/

	return true;
}

/****************************
* Name ：GameScene::onTouchBegan
* Summary ：触摸开始
* return ：是否执行
****************************/
bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	log("onTouchBegan"); //日志
	return true;
}

/****************************
* Name ：GameScene::onTouchMoved
* Summary ：触摸移动
* return ：是否执行
****************************/
void GameScene::onTouchMoved(Touch* touch, Event* event)
{
	log("onTouchMoved"); //日志
}

/****************************
* Name ：GameScene::onTouchEnded
* Summary ：触摸结束
* return ：是否执行
****************************/
void GameScene::onTouchEnded(Touch* touch, Event* event)
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
			_player->runAction(FlipX::create(false));
		}
		else {
			playerPos.x -= _tileMap->getTileSize().width;
			_player->runAction(FlipX::create(true));
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
* Name ：GameScene::setPlayerPosition
* Summary ：是否走动
* return ：无
****************************/
void GameScene::setPlayerPosition(Vec2 position)
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
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");
			return;
		}
	}
	//移动精灵
	_player->setPosition(position);
	//滚动地图
	this->setViewpointCenter(_player->getPosition());
}

/****************************
* Name ：GameScene::tileCoordFromPosition
* Summary ：从像素点坐标转化为瓦片坐标
* return ：Vec2(x,y)
****************************/
Vec2 GameScene::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x, y);
}

/****************************
* Name ：GameScene::setViewpointCenter
* Summary ：滚动地图
* return ：无
****************************/
void GameScene::setViewpointCenter(Vec2 position)
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
* Name ：GameScene::menuCloseCallback
* Summary ：跳到GameOverScene
* return ：无
****************************/
void GameScene::menuCloseCallback(Ref* pSender)
{
	auto GOS = GameOverScene::createScene();
	Director::getInstance()->replaceScene(GOS);
}

void GameScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("GameScene onEnterTransitionDidFinish");
	//播放
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/retro_fight_ingame_01.mp3", true);
	log("run the music");

}

void GameScene::cleanup()
{
	Layer::cleanup();
	log("GameScene cleanup");
	//停止
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/retro_fight_ingame_01.mp3");
}
