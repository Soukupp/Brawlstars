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
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MapLayer.cpp\n");
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
	_tileMap = TMXTiledMap::create("map/Mapupdated.tmx");
	
	  
	addChild(_tileMap, 0, 100);
	//log("2");
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("player");  // �µ�ͼӦ����player
	 

	float _playerX = spawnPoint["x"].asFloat();
	float _playerY = spawnPoint["y"].asFloat();
	/*=====================������ɫ��ʼ========================*/
	createHero(&_player, &_weapon, &_healthBar, &_magicBar, Vec2(_playerX, _playerY), "Character/Hero2/hero.png", "Character/Hero2/empty.png");
	createHero(&_player1, &_weapon1, &_healthBar1, &_magicBar1, Vec2(_playerX, _playerY), "Character/Hero1/hero.png", "Character/Hero1/empty.png");

	/*=====================������ɫ����========================*/
	setViewpointCenter(_player->getPosition());

	_collidable = _tileMap->getLayer("collidable");  //�ϰ���collidable
	_collidable->setVisible(false);  // ��Ӧ͸����

	_watermonster = _tileMap->getLayer("watermonster");

	setTouchEnabled(true);  // ��������������̳���layer
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);


	/*======================���Ƽ��̿�ʼ=======================*/
	auto keyboardListener = EventListenerKeyboard::create();// �������̼�����keyboardListener

	keyboardListener->onKeyPressed = CC_CALLBACK_2(MapLayer::onKeyPressed, this);  // �����̲���
	// û�����óɳ�����ѹ������ǰ��
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MapLayer::onKeyReleased, this); // �ͷż��̲���
	
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	/*======================���Ƽ��̽���=======================*/

	/*======================������ͼ����=======================*/

	this->schedule(schedule_selector(MapLayer::update), 0.15); //ÿһ֡������ update �������жϼ�����û�б���ѹס

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
	keyMap[keyCode] = true;

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
* Name ��MapLayer::onKeyReleased
* Summary �����¼��̺�ֱ�����Ĳ���
* return ����
****************************/
void MapLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

	log("Key with keycode %d released", keyCode);
	keyMap[keyCode] = false;
}


/****************************
* Name ��MapLayer::update
* Summary ������
* return ����
****************************/
void MapLayer::update(float delta)
{
	delta = 2.0;
	Vec2 playerPos = _player->getPosition();  // ��ȡ���λ������
	if (keyMap[EventKeyboard::KeyCode::KEY_D] || keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
	{
		playerPos.x += _tileMap->getTileSize().width;
		//_player->runAction(FlipX::create(false));
		_player->runFlipxWithWeapon(false, _weapon);
	}
	else if (keyMap[EventKeyboard::KeyCode::KEY_A] || keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
	{
		playerPos.x -= _tileMap->getTileSize().width;
		//_player->runAction(FlipX::create(true));
		_player->runFlipxWithWeapon(true, _weapon);
	}
	else if (keyMap[EventKeyboard::KeyCode::KEY_W] || keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW])
	{
		playerPos.y += _tileMap->getTileSize().height;
	}
	else if (keyMap[EventKeyboard::KeyCode::KEY_S] || keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW])
	{
		playerPos.y -= _tileMap->getTileSize().height;
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
	//int tileGid_watermonster=_watermonster->getTileGIDAt(tileCoord);
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
	_player->setPositionWithAll(position, _weapon, _healthBar, _magicBar);
	/**/
	_player->launchAnAttack(_weapon, "skill", _magicBar);
	/**
	_player->launchAnAttack(_weapon, "attack");
	/**/

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


/****************************
* Name ��MapLayer::createHero
* Summary ��������ɫ
* return ��
****************************/
template<typename Hero>
void MapLayer::createHero(Hero** hero, Weapon** weapon, Slider** healthBar, Slider** magicBar,
	                      Vec2& position, const std::string& filenameHero, const std::string& filenameWeapon)
{
	*hero = Hero::create(filenameHero);
	(**hero).initPlayer(100, 2, 3, 4.0f, 5.0f);
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

	(**hero).setPositionWithAll(position, *weapon, *healthBar, *magicBar);
}