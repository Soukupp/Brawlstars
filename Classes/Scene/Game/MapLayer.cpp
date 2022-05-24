//���� : ��Ԫ��
//���� : 2022-5-20

//�޸� : ��Ԫ��
//���� : 2022-5-22
//�޸� : ���Ӽ��̹���

#include "MapLayer.h"
#include "GameOverScene.h"


USING_NS_CC;
using namespace CocosDenshion;


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
* Name ��MapLayer::init
* Summary ����ͼ���ʼ��
* return ����ʼ���ɹ����
****************************/
bool MapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	 

	/*======================������ͼ��ʼ=======================*/
	//log("1"); 
	_tileMap = TMXTiledMap::create("map/Mapupdated2.tmx");
	// ���ϵ�ͼMiddleMap���ԣ���֪��Ϊɶ�µ�ͼ�����ԣ������о���......
	// 	_tileMap = TMXTiledMap::create("map/MiddleMaper.tmx");
	addChild(_tileMap, 0, 100);
	//log("2");

	/*=====================������ɫ��ʼ========================*/
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("player");  // �µ�ͼӦ����player

	float _playerX = spawnPoint["x"].asFloat();
	float _playerY = spawnPoint["y"].asFloat();
	
	_player = Hero1::create("Character/Hero1/hero.png");
	//_player->retain(); // ����û��
	_player->initPlayer(100, 2, 3, 4.0f, 5.0f);
	addChild(_player, 2, 200);

	_weapon = Weapon::create("Character/Hero1/empty.png");
	_weapon->setAnchorPoint(
		Vec2(_player->_weaponAnchorPositionX,
			_player->_weaponAnchorPositionY));
	addChild(_weapon, 2, 200);

	_healthBar = Slider::create();
	_healthBar->setPercent(_player->getHealthPercent());
	_healthBar->loadBarTexture("/ui/playerHealthbarFrame.png");
	_healthBar->loadProgressBarTexture("/ui/playerHealthbarBlock.png");
	_healthBar->setScale(0.5);
	_healthBar->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->addChild(_healthBar);

	_magicBar = Slider::create();
	_magicBar->setPercent(_player->getMagicPercent());
	_magicBar->loadBarTexture("/ui/playerMagicbarFrame.png");
	_magicBar->loadProgressBarTexture("/ui/playerMagicbarBlock.png");
	_magicBar->setScale(0.5);
	_magicBar->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->addChild(_magicBar);

	_player->setPositionWithAll(Vec2(_playerX, _playerY), _weapon, _healthBar, _magicBar);
	/*=====================������ɫ����========================*/

	/*=================����groundmonster��ʼ===================*/

	// �����޸� Look at me��
	//TMXObjectGroup* groupgm = _tileMap->getObjectGroup("try");
	//ValueMap spawnPointgm = groupgm->getObject("try1"); // ��ȡʾ������try1��Ӧ����һ���ص㣩����Ҫ����������Ƭ

	//float _tryX = spawnPointgm["x"].asFloat();
	//float _tryY = spawnPointgm["y"].asFloat();
	//log("point1");  // ����Ͷ����ܹ���ȡ�ɹ�

	//_groundmonster = Monster::create("map/groundmonster.png");

	//_groundmonster->setPosition(Vec2(_tryX, _tryY));
	//_groundmonster->initMonster(100, 2, 3, 4.0f, 5.0f);
	//addChild(_groundmonster, 3, 100);




	//_player->retain(); // ����û��
	////FileUtils::getInstance()->setSearchPaths({ "map" });
	////Player _try1;
	////_player = &_try1;
	////_try1 = Player::create("map/groundmonster.png");  // ��Ƭʼ�մ򲻿�������Ϊ_try1ʼ����һ����ָ��
	////_try1->setPosition(Vec2(_tryX, _tryY));
	//////_try->initPlayer(100, 2, 3, 4.0f, 5.0f);
	////addChild(_try1, 3, 100);

	/*auto layer = _tileMap->getObjectGroup("groundmonster");
	auto Group = layer->getObjects();
	for (auto obj : Group)
	{
		auto valueMap = obj.asValueMap();
		auto monster = Player::create("map/groundmonster.png");
		addChild(monster);
	}*/







	//float _groundmonsterX = spawnPointgm["x"].asFloat();
	//float _groundmonsterY = spawnPointgm["y"].asFloat();

	//_groundmonster = Sprite::create("map/groundmonster.png");
	//_groundmonster->setPosition(Vec2(_groundmonsterX, _groundmonsterY));
	////_groundmonster[1]->initPlayer(100, 2, 3, 4.0f, 5.0f);
	//addChild(_groundmonster, 2, 200);






	/*=================����groundmonster����===================*/

	/*===================�����ϰ���㿪ʼ======================*/
	setViewpointCenter(_player->getPosition());

	_collidable = _tileMap->getLayer("collidable");  //�ϰ���collidable
	_collidable->setVisible(false);  // ��Ӧ͸����

	//_watermonster = _tileMap->getLayer("watermonster");

	setTouchEnabled(true);  // ��������������̳���layer
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	/*===================�����ϰ�������======================*/

	/*======================���Ƽ��̿�ʼ=======================*/
	auto keyboardListener = EventListenerKeyboard::create();// �������̼�����keyboardListener

	keyboardListener->onKeyPressed = CC_CALLBACK_2(MapLayer::onKeyPressed, this);  // �����̲���
	// û�����óɳ�����ѹ������ǰ��
    //keyboardListener->onKeyReleased = CC_CALLBACK_2(MapLayer::onKeyReleased, this); // �ͷż��̲���
	
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	/*======================���Ƽ��̽���=======================*/

	/*======================������ͼ����=======================*/

	return true;
}


/****************************
* Name ��MapLayer::onKeyPressed
* Summary �����¼��̺�ֱ�����Ĳ���
* return ����
****************************/
void MapLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

	Vec2 playerPos = _player->getPosition();  // ��ȡ���λ������

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
* Name ��MapLayer::onTouchBegan
* Summary ��������ʼ
* return ���Ƿ�ִ��
****************************/
bool MapLayer::onTouchBegan(Touch* touch, Event* event)
{
	log("onTouchBegan"); //��־
	return true;
}

/****************************
* Name ��MapLayer::onTouchMoved
* Summary �������ƶ�
* return ���Ƿ�ִ��
****************************/
void MapLayer::onTouchMoved(Touch* touch, Event* event)
{
	log("onTouchMoved"); //��־
}
 
/****************************
* Name ��MapLayer::onTouchEnded
* Summary ����������
* return ���Ƿ�ִ��
****************************/
void MapLayer::onTouchEnded(Touch* touch, Event* event)
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
	this->setPlayerPosition(playerPos);   // �жϿɲ������߶�
	/*=======================ͨ�������������߶�����===========================*/
}

/****************************
* Name ��MapLayer::setPlayerPosition
* Summary ���Ƿ��߶�
* return ����
****************************/
void MapLayer::setPlayerPosition(Vec2 position)
{
	log("setPlayerPosition");
	// ��ȡ����
	Vec2 tileCoord = this->tileCoordFromPosition(position);  //�����ص�����ת��Ϊ��Ƭ����

	int tileGid = _collidable->getTileGIDAt(tileCoord);   //�����Ƭ��GID
	//int tileGid_watermonster=_watermonster->getTileGIDAt(tileCoord);  Look at me������
	// �������ͬ����ʹthis��ɿ�ָ�룡��������
	log("success1");

	// ��ײ���
	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();
		// Ԫ��+true
		if (collision == "true") { //��ײ���ɹ�
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/empty.wav");
			return;
		}
	}
	//if (tileGid_watermonster > 0) {
	//	Value prop = _tileMap->getPropertiesForGID(tileGid_watermonster);
	//	log("success2");
	//	ValueMap propValueMap = prop.asValueMap();  // ����
	//	log("success3");
	//	std::string collision = propValueMap["crash"].asString();
	//	// Ԫ��+true
	//	if (collision == "true") { //��ײ���ɹ�
	//		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");
	//		return;
	//	}
	//}
	//�ƶ�����
	//_player->hitPlayer(5);//�Խ�ɫ��ɹ���
	_player->setPositionWithAll(position, _weapon);
	//������ͼ
	this->setViewpointCenter(_player->getPosition());
}

/****************************
* Name ��MapLayer::tileCoordFromPosition
* Summary �������ص�����ת��Ϊ��Ƭ����
* return ��Vec2(x,y)
****************************/
Vec2 MapLayer::tileCoordFromPosition(Vec2 pos)
{
	log("tileCoordFromPosition");
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x, y);
}

/****************************
* Name ��MapLayer::setViewpointCenter
* Summary ��������ͼ
* return ����
****************************/
void MapLayer::setViewpointCenter(Vec2 position)
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

