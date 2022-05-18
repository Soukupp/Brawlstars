//���� : ��Ԫ��
//���� : 2022-5-18

#include "GameScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/****************************
* Name ��GameScene::createScene
* Summary ������������ʵ��layer
* return ��������ָ��
****************************/
Scene* GameScene::createScene()
{
	auto GameScene = Scene::create();
	auto MapLayer = GameScene::create();
	GameScene->addChild(MapLayer);
	return GameScene;
}

/****************************
* Name ��problemLoading
* Summary �������ӡ
* return ��
****************************/
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


/****************************
* Name ��GameScene::init
* Summary ����Ϸ������ʼ��
* return ����ʼ���ɹ����
****************************/
bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	

	/*=====================�����رհ�ť��ʼ======================*/
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
	}  // �رղ˵���Ҫ��Ϊ�̶�λ�ã��Ҵ˴��رղ˵���ʾ�����������棩

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);
	/*=====================�����رհ�ť����====================*/

	/*======================������ͼ��ʼ=======================*/

	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	addChild(_tileMap, 0, 100);

	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("Colt");  // �ӵ�ͼ��ȡ��Ϸ�����λ�ã���Ϸ����Colt

	float _playerX = spawnPoint["x"].asFloat();
	float _playerY = spawnPoint["y"].asFloat();

	_player = Sprite::create("Colt.png");
	_player->setPosition(Vec2(_playerX, _playerY));
	addChild(_player, 2, 200);

	setViewpointCenter(_player->getPosition());

	_collidable = _tileMap->getLayer("collidable");  //�ϰ���collidable
	_collidable->setVisible(false);  // ��Ӧ͸����

	setTouchEnabled(true);  // ��������������̳���layer
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	/*======================������ͼ����=======================*/

	return true;
}

/****************************
* Name ��GameScene::onTouchBegan
* Summary ��������ʼ
* return ���Ƿ�ִ��
****************************/
bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	log("onTouchBegan"); //��־
	return true;
}

/****************************
* Name ��GameScene::onTouchMoved
* Summary �������ƶ�
* return ���Ƿ�ִ��
****************************/
void GameScene::onTouchMoved(Touch* touch, Event* event)
{
	log("onTouchMoved"); //��־
}

/****************************
* Name ��GameScene::onTouchEnded
* Summary ����������
* return ���Ƿ�ִ��
****************************/
void GameScene::onTouchEnded(Touch* touch, Event* event)
{
	log("onTouchEnded");  //��־ 

	/*================��ȡ����������꣬��ת��Ϊ��ǰ��ģ������ϵ==================*/
	Vec2 touchLocation = touch->getLocation();  //�����OpenGL����
	touchLocation = this->convertToNodeSpace(touchLocation);  //ת��Ϊ��ǰ���ģ������ϵ

	Vec2 playerPos = _player->getPosition();  // ��ȡ���λ������

	Vec2 diff = touchLocation - playerPos;    // ��ȡ������������� 

	/*=============================�����ȡ����================================*/


	/*=======================ͨ�������������߶���ʼ===========================*/
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
	this->setPlayerPosition(playerPos);   // �жϿɲ������߶�
	/*=======================ͨ�������������߶�����===========================*/
}

/****************************
* Name ��GameScene::setPlayerPosition
* Summary ���Ƿ��߶�
* return ����
****************************/
void GameScene::setPlayerPosition(Vec2 position)
{
	// ��ȡ����
	Vec2 tileCoord = this->tileCoordFromPosition(position);  //�����ص�����ת��Ϊ��Ƭ����
	
	int tileGid = _collidable->getTileGIDAt(tileCoord);   //�����Ƭ��GID

	// ��ײ���
	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();
		// Ԫ��+true
		if (collision == "true") { //��ײ���ɹ�
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");
			return;
		}
	}
	//�ƶ�����
	_player->setPosition(position);
	//������ͼ
	this->setViewpointCenter(_player->getPosition());
}

/****************************
* Name ��GameScene::tileCoordFromPosition
* Summary �������ص�����ת��Ϊ��Ƭ����
* return ��Vec2(x,y)
****************************/
Vec2 GameScene::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x, y);
}

/****************************
* Name ��GameScene::setViewpointCenter
* Summary ��������ͼ
* return ����
****************************/
void GameScene::setViewpointCenter(Vec2 position)
{
	log("setViewpointCenter"); //��־

	log("position (%f ,%f) ", position.x, position.y);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//���Է�ֹ����ͼ��߳�����Ļ֮�⡣
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	//���Է�ֹ����ͼ�ұ߳�����Ļ֮�⡣
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
		- visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
		- visibleSize.height / 2);

	//��Ļ���ĵ�
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);

	//ʹ���鴦����Ļ���ģ��ƶ���ͼĿ��λ��
	Vec2 pointB = Vec2(x, y);
	log("Ŀ��λ�� (%f ,%f) ", pointB.x, pointB.y);

	//��ͼ�ƶ�ƫ����
	Vec2 offset = pointA - pointB;
	log("offset (%f ,%f) ", offset.x, offset.y);
	this->setPosition(offset);

}

/****************************
* Name ��GameScene::menuCloseCallback
* Summary ������GameOverScene
* return ����
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
	//����
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/retro_fight_ingame_01.mp3", true);
	log("run the music");

}

void GameScene::cleanup()
{
	Layer::cleanup();
	log("GameScene cleanup");
	//ֹͣ
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/retro_fight_ingame_01.mp3");
}
