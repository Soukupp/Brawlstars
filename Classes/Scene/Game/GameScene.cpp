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
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto GameSettingLayer = LayerColor::create();
	GameSettingLayer->changeWidthAndHeight(960, 720);

	/*=====================�����رհ�ť��ʼ======================*/

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
	}  // �رղ˵���Ҫ��Ϊ�̶�λ�ã��Ҵ˴��رղ˵���ʾ�����������棩

	/*=====================�����رհ�ť����======================*/

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

	auto menu = Menu::create(BackToMenuItem, SettingsItem, NULL);
	menu->setPosition(Vec2::ZERO);
	GameSettingLayer->addChild(menu);
	this->addChild(GameSettingLayer, 1);

	auto MapLayer1 = MapLayer::create();
	this->addChild(MapLayer1, 0);

    /*=====================�������ð�ť����====================*/

	/*=====================�����������ֿ�ʼ=======================*/

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/retro_fight_ingame_01.mp3");
	if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/retro_fight_ingame_01.mp3", true);
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(
		static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
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
* Name ��GameScene::GameSettingsCallBack
* Summary ������GameSettingsScene
* return ����
****************************/
void GameScene::GameSettingsCallBack(cocos2d::Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
		static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
	auto GSS = GameSettingsScene::createScene();
	Director::getInstance()->pushScene(GSS);  // �˴���push�ķ�ʽ��������Ϸ����
}

/****************************
* Name ��GameScene::getUserInt
* Summary ����ȡӢ������
* return ��Ӣ�����ֶ�Ӧ��ID
****************************/
int GameScene::getUserInt(const char* name)
{
	return UserDefault::getInstance()->getIntegerForKey(name);
}

/****************************
* Name ��GameScene::setUserInt
* Summary ������Ӣ�����ֶ�Ӧ��ID
* return ����
****************************/
void GameScene::setUserInt(const char* name, int num)
{
	UserDefault::getInstance()->setIntegerForKey(name, num);
}

