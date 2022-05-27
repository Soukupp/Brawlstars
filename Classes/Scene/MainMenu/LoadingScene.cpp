#include "LoadingScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

/****************************
* Name ��LoadingScene::createScene
* Summary ����������
* return ��������ָ��
****************************/
Scene* LoadingScene::createScene()
{
	return LoadingScene::create();
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
* Name ��LoadingScene::init
* Summary �����ؽ����ʼ��
* return ����ʼ���ɹ����
****************************/
bool LoadingScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/start_game_music.mp3");

	/*=======================����������ʼ=========================*/
	Sprite* bg = Sprite::create("background/LoadingBackground.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);
	/*=======================������������=========================*/

	/*=======================����Logo��ʼ=========================*/
	Sprite* BrawlStars = Sprite::create("BrawlStarsLogo.png");
	BrawlStars->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(BrawlStars);

    Sprite* Tongji = Sprite::create("TongjiLogo.png");
	float x = origin.x + visibleSize.width - Tongji->getContentSize().width;
	float y = visibleSize.height - Tongji->getContentSize().height / 2;
	Tongji->setPosition(Vec2(x, y));
	this->addChild(Tongji);
	/*=======================����Logo����=========================*/

	/*=======================������ʾ�￪ʼ========================*/
	auto tip = LabelTTF::create("Moderate Games, Happy Life", "fonts/Marker Felt.ttf", 25);
	tip->setColor(Color3B::WHITE);
	tip->setPosition(Vec2(origin.x + visibleSize.width / 2,
		visibleSize.height - 3 * tip->getContentSize().height));
	this->addChild(tip);






	this->scheduleOnce(schedule_selector(LoadingScene::changeScene), 3.0f); // ������ʱ����

	return true;
}

void LoadingScene::changeScene(float dt)
{
	auto MMS = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, MMS));
}