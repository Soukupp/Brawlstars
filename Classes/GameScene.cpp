//作者 : 李元特
//日期 : 2022-5-18

//修改 : 王鹏
//日期 : 2022-5-20
//将人物从Sprite类替换为Player类 

#include "GameScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "MapLayer.h"
#include "GameSettingsScene.h"

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
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto GameSettingLayer = LayerColor::create();
	GameSettingLayer->changeWidthAndHeight(960, 720);
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

		/*=====================创建设置按钮开始======================*/
	auto SettingsItem = MenuItemImage::create(
		"GameSettingsButton.png", "GameSettingsButton.png",
		CC_CALLBACK_1(GameScene::GameSettingsCallBack, this));

	if (SettingsItem == nullptr ||
		SettingsItem->getContentSize().width <= 0 ||
		SettingsItem->getContentSize().height <= 0)
	{
		problemLoading("'GameSettingsButton.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - 3 * SettingsItem->getContentSize().width / 2;
		float y = visibleSize.height - SettingsItem->getContentSize().height / 2;
		SettingsItem->setPosition(Vec2(x, y));
	}


	auto menu = Menu::create(closeItem, SettingsItem, NULL);
	menu->setPosition(Vec2::ZERO);
	GameSettingLayer->addChild(menu);
	/*=====================创建关闭按钮结束====================*/
	this->addChild(GameSettingLayer, 1);
	auto MapLayer1 = MapLayer::create();
	this->addChild(MapLayer1, 0);

	return true;
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


/****************************
* Name ：GameScene::GameSettingsCallBack
* Summary ：跳到GameSettingsScene
* return ：无
****************************/
void GameScene::GameSettingsCallBack(cocos2d::Ref* pSender)
{
	auto GSS = GameSettingsScene::createScene();
	Director::getInstance()->pushScene(GSS);  // 此处用push的方式，保留游戏进度
}
