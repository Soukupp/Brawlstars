//作者 : 李元特
//日期 : 2022-5-18

//修改 : 王鹏
//日期 : 2022-5-20
//将人物从Sprite类替换为Player类 

#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

static bool ifShowPlay = true;          //是否播放音乐
static bool ifShowStates = false;       //是否显示FPS


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
* Name ：GameScene::init
* Summary ：游戏场景初始化
* return ：初始化成功与否
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

	

	/*=====================创建设置按钮开始======================*/

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

    /*=====================创建设置按钮结束====================*/

	/*=====================创建背景音乐开始=======================*/

	Tools::preloadBackgroundMusic("music/retro_fight_ingame_01.mp3");
	if (Tools::isBackgroundMusicPlaying())
	{
		Tools::playBackgroundMusic("music/retro_fight_ingame_01.mp3", true);
	}
	Tools::setBackgroundMusicVolume("musicVolume");
	/*=====================创建背景音乐结束=======================*/

	return true;
}

/****************************
* Name ：GameScene::menuCloseCallback
* Summary ：跳到GameOverScene
* return ：无
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
* Name ：GameScene::GameSettingsCallBack
* Summary ：跳到GameSettingsScene
* return ：无
****************************/
void GameScene::GameSettingsCallBack(cocos2d::Ref* pSender)
{
	Tools::playEffect("music/if_click_buttom_on_menu.mp3");
	Tools::setEffectsVolume("musicVolume");
	auto GSS = GameSettingsScene::createScene();
	Director::getInstance()->pushScene(GSS);  // 此处用push的方式，保留游戏进度
}