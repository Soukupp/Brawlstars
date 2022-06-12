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
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto GameSettingLayer = LayerColor::create();
	GameSettingLayer->changeWidthAndHeight(960, 720);

	/*=====================创建关闭按钮开始======================*/

	auto BackToMenuItem = MenuItemImage::create(
		"ui/button_close.png",
		"ui/button_close.png",
		CC_CALLBACK_1(GameScene::menuCallback, this));

	if (BackToMenuItem == nullptr ||
		BackToMenuItem->getContentSize().width <= 0 ||
		BackToMenuItem->getContentSize().height <= 0)
	{
		problemLoading("'ui/button_close.png' and 'ui/button_close.png'");
	}
	else
	{
		BackToMenuItem->setPosition(Vec2(GAME_BACK_TO_MENU_POSITION_X, GAME_BACK_TO_MENU_POSITION_Y));
	}  // 关闭菜单需要改为固定位置（且此处关闭菜单表示跳到结束界面）

	/*=====================创建关闭按钮结束======================*/

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

	auto menu = Menu::create(BackToMenuItem, SettingsItem, NULL);
	menu->setPosition(Vec2::ZERO);
	GameSettingLayer->addChild(menu);
	this->addChild(GameSettingLayer, 1);

	auto MapLayer1 = MapLayer::create();
	this->addChild(MapLayer1, 0);

    /*=====================创建设置按钮结束====================*/

	/*=====================创建背景音乐开始=======================*/

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/retro_fight_ingame_01.mp3");
	if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/retro_fight_ingame_01.mp3", true);
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(
		static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
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
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
		static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
	/**/
	if (getUserInt("_numOfPlayer") == 1)
	{
		setUserInt("_winTimes", 1 + getUserInt("_winTimes"));
	}
	setUserInt("_gameTimes", 1 + getUserInt("_gameTimes"));
	setUserInt("_killNums", getUserInt("_hitNum") + getUserInt("_killNums"));
	if (getUserInt("_numOfPlayer") <= 5)
	{
		setUserInt("_cupNums", 6 + getUserInt("_numOfPlayer") + getUserInt("_cupNums"));
	}
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
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
		static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
	auto GSS = GameSettingsScene::createScene();
	Director::getInstance()->pushScene(GSS);  // 此处用push的方式，保留游戏进度
}

/****************************
* Name ：GameScene::getUserInt
* Summary ：获取英雄名字
* return ：英雄名字对应的ID
****************************/
int GameScene::getUserInt(const char* name)
{
	return UserDefault::getInstance()->getIntegerForKey(name);
}

/****************************
* Name ：GameScene::setUserInt
* Summary ：设置英雄名字对应的ID
* return ：无
****************************/
void GameScene::setUserInt(const char* name, int num)
{
	UserDefault::getInstance()->setIntegerForKey(name, num);
}

