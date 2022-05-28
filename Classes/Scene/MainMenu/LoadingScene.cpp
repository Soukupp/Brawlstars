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
	auto tip1 = LabelTTF::create("Moderate Games, Happy Life", "fonts/Lilita one.ttf", 25);
	tip1->setColor(Color3B::WHITE);
	tip1->setPosition(Vec2(origin.x + visibleSize.width / 2,
		visibleSize.height - 3 * tip1->getContentSize().height));
	this->addChild(tip1);

	auto tip2 = LabelTTF::create("WELCOME TO THE WILDERNESS JOURNEY!", "fonts/Lilita one.ttf", 25);
	tip2->setColor(Color3B::WHITE);
	tip2->setPosition(Vec2(origin.x + visibleSize.width / 2,
		3 * tip2->getContentSize().height));
	this->addChild(tip2);
	log("WELCOME TO THE WILDERNESS JOURNEY!");

	auto tip3 = LabelTTF::create("Shoot 'em up, blow 'em up, punch 'em out and win the BRAWL!", "fonts/Lilita one.ttf", 25);
	tip3->setColor(Color3B::WHITE);
	tip3->setPosition(Vec2(origin.x + visibleSize.width / 2,
		5 * tip3->getContentSize().height));
	this->addChild(tip3);
	log("Shoot 'em up, blow 'em up, punch 'em out and win the BRAWL!");

	/*=======================������ʾ�����========================*/

	/*=======================Ԥ����Audio��ʼ=======================*/
	 //��ʼ�� ����
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/retro_fight_ingame_01.mp3");
	// ��Ϸ�е�����
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/first_music.mp3");
	// ������Ϸmenu������


	//��ʼ�� ��Ч
	SimpleAudioEngine::getInstance()->preloadEffect("sound/empty.wav");
	// �ϰ�����ײ
	SimpleAudioEngine::getInstance()->preloadEffect("music/start_game_music.mp3");
	// ��������һ����ʶ������Ϸ�Ľ���

	SimpleAudioEngine::getInstance()->preloadEffect("music/if_hero_kill_monster.mp3");
	// ���սʤһֻ����
	SimpleAudioEngine::getInstance()->preloadEffect("music/if_click_buttom_on_menu.mp3");
	// ������ð�ť��Ч

	// һ�¶��ͼ����й�
	SimpleAudioEngine::getInstance()->preloadEffect("music/gun_skill_3times.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/gun_attack.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/laser_skill.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/laser_attack.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/knife_attack_2.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/knife_attack_1.mp3");

	/*=======================Ԥ����Audio����=======================*/

	this->scheduleOnce(schedule_selector(LoadingScene::changeScene), 3.0f); // ������ʱ����

	return true;
}

void LoadingScene::changeScene(float dt)
{
	auto MMS = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, MMS));
}