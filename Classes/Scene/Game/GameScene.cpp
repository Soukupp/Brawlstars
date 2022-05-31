//���� : ��Ԫ��
//���� : 2022-5-18

//�޸� : ����
//���� : 2022-5-20
//�������Sprite���滻ΪPlayer�� 

#include "GameScene.h"
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
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto GameSettingLayer = LayerColor::create();
	GameSettingLayer->changeWidthAndHeight(960, 720);

	/*=====================�����رհ�ť��ʼ======================*/
	auto closeItem = MenuItemImage::create(
		"ui/CloseNormal.png",
		"ui/CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'ui/CloseNormal.png' and 'ui/CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}  // �رղ˵���Ҫ��Ϊ�̶�λ�ã��Ҵ˴��رղ˵���ʾ�����������棩

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
		float x = origin.x + visibleSize.width - 3 * SettingsItem->getContentSize().width / 2;
		float y = visibleSize.height - SettingsItem->getContentSize().height / 2;
		SettingsItem->setPosition(Vec2(x, y));
	}
	auto menu = Menu::create(closeItem, SettingsItem, NULL);
	menu->setPosition(Vec2::ZERO);
    /*=====================�������ð�ť����====================*/

	auto SkillButton = SkillButton::create("ui/buttonForSkill.png", "ui/buttonShadow.png", 30);
	float x = origin.x + 1.5 * 40;
	float y = origin.y + 1.5 * 40;
	SkillButton->setPosition(Vec2(x, y));
	this->addChild(SkillButton, 100);

	





	GameSettingLayer->addChild(menu);
	
	this->addChild(GameSettingLayer, 1);


	auto MapLayer1 = MapLayer::create();
	this->addChild(MapLayer1, 0);

	return true;
}


/****************************
* Name ��GameScene::menuCloseCallback
* Summary ������GameOverScene
* return ����
****************************/
void GameScene::menuCloseCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
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
	auto GSS = GameSettingsScene::createScene();
	Director::getInstance()->pushScene(GSS);  // �˴���push�ķ�ʽ��������Ϸ����
}
