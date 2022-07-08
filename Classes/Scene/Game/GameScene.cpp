//���� : ��Ԫ��
//���� : 2022-5-18

//�޸� : ����
//���� : 2022-5-20
//�������Sprite���滻ΪPlayer�� 

#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

static bool ifShowPlay = true;          //�Ƿ񲥷�����
static bool ifShowStates = false;       //�Ƿ���ʾFPS


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
* Name ��GameScene::init
* Summary ����Ϸ������ʼ��
* return ����ʼ���ɹ����
****************************/
bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto GameSettingLayer = LayerColor::create();
	GameSettingLayer->changeWidthAndHeight(960, 720);

	

	/*=====================�������ð�ť��ʼ======================*/

	auto SettingsItem = MenuItemImage::create(
		"ui/GameSettingsButton.png", "ui/GameSettingsButton.png",
		CC_CALLBACK_1(GameScene::GameSettingsCallBack, this));

	if (SettingsItem == nullptr ||
		SettingsItem->getContentSize().width <= 0 ||
		SettingsItem->getContentSize().height <= 0)
	{
		problemLoading("'ui/GameSettingsButton.png'");
	}
	else
	{
		SettingsItem->setPosition(Vec2(GAME_SETTING_POSITION_X, GAME_SETTING_POSITION_Y));
	}

	auto menu = Menu::create(SettingsItem, NULL);
	menu->setPosition(Vec2::ZERO);
	GameSettingLayer->addChild(menu);
	this->addChild(GameSettingLayer, 1);

	auto MapLayer1 = MapLayer::create();
	this->addChild(MapLayer1, 0);

    /*=====================�������ð�ť����====================*/

	/*=====================�����������ֿ�ʼ=======================*/

	Tools::preloadBackgroundMusic("music/retro_fight_ingame_01.mp3");
	if (Tools::isBackgroundMusicPlaying())
	{
		Tools::playBackgroundMusic("music/retro_fight_ingame_01.mp3", true);
	}
	Tools::setBackgroundMusicVolume("musicVolume");
	/*=====================�����������ֽ���=======================*/

	return true;
}

/****************************
* Name ��GameScene::menuCloseCallback
* Summary ������GameOverScene
* return ����
****************************/
void GameScene::menuCallback(Ref* pSender)
{
	Tools::playEffect("music/if_click_buttom_on_menu.mp3");
	Tools::setEffectsVolume("musicVolume");
	/**/
	Tools::gameoverDataSave();
	/**/
	auto GOS = GameOverScene::createScene();
	Director::getInstance()->replaceScene(GOS);
}

/****************************
* Name ��GameScene::GameSettingsCallBack
* Summary ������GameSettingsScene
* return ����
****************************/
void GameScene::GameSettingsCallBack(cocos2d::Ref* pSender)
{
	Tools::playEffect("music/if_click_buttom_on_menu.mp3");
	Tools::setEffectsVolume("musicVolume");
	auto GSS = GameSettingsScene::createScene();
	Director::getInstance()->pushScene(GSS);  // �˴���push�ķ�ʽ��������Ϸ����
}