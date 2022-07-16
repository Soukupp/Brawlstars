//���ߣ���Ԫ��
//���ڣ�2022-6-6
//ʵ�֣�loading�����깤


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
* return ����
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
	bg->setPosition(Vec2(LOADING_BACKGROUND_POSITION));
	this->addChild(bg);

	/*=======================������������=========================*/

	/*=======================����Logo��ʼ=========================*/

	Sprite* BrawlStars = Sprite::create("BrawlStarsLogo.png");
	BrawlStars->setPosition(Vec2(LOADING_BSLOGO_POSITION));
	this->addChild(BrawlStars);

    Sprite* Tongji = Sprite::create("TongjiLogo.png");
	Tongji->setPosition(Vec2(LOADING_TJLOGO_POSITION));
	this->addChild(Tongji);

	/*=======================����Logo����=========================*/

	/*=======================������ʾ�￪ʼ========================*/

	auto tip1 = LabelTTF::create("Moderate Games, Happy Life!", "fonts/Lilita one.ttf", 36);
	tip1->enableShadow(LOADING_TIP1_SHADOW);
	tip1->setColor(Color3B::WHITE);
	tip1->setPosition(Vec2(LOADING_TIP1_POSITION));
	this->addChild(tip1);

	auto tip2 = LabelTTF::create("WELCOME TO THE WILDERNESS JOURNEY!", "fonts/Lilita one.ttf", 28);
	tip2->enableShadow(LOADING_TIP1_SHADOW);
	tip2->setColor(Color3B::WHITE);
	tip2->setPosition(Vec2(LOADING_TIP2_POSITION));
	this->addChild(tip2);
	log("WELCOME TO THE WILDERNESS JOURNEY!");

	auto tip3 = LabelTTF::create("Shoot 'em up, blow 'em up, punch 'em out and win the BRAWL!", "fonts/Lilita one.ttf", 28);
	tip3->enableShadow(LOADING_TIP1_SHADOW);
	tip3->setColor(Color3B::WHITE);
	tip3->setPosition(Vec2(LOADING_TIP3_POSITION));
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
	// ���սʤһֻ����
	SimpleAudioEngine::getInstance()->preloadEffect("music/if_hero_kill_monster.mp3");
	// ������ð�ť��Ч
	SimpleAudioEngine::getInstance()->preloadEffect("music/if_click_buttom_on_menu.mp3");
	// �������ý������Ч
	SimpleAudioEngine::getInstance()->preloadEffect("music/to_a_new_scene.mp3");
	
	// ѡ��AInumber�ɹ�
	SimpleAudioEngine::getInstance()->preloadEffect("music/select_ok.mp3");
	
	// ������printed eggshell ��Ч
	SimpleAudioEngine::getInstance()->preloadEffect("music/printed_eggshell_1.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/printed_eggshell_2.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/printed_eggshell_3.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/printed_eggshell_4.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/store_ai_number.mp3");

	// ���¶��ͼ����й�
	SimpleAudioEngine::getInstance()->preloadEffect("music/gun_skill_3times.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/gun_attack.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/laser_skill.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/laser_attack.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/knife_attack_2.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/knife_attack_1.mp3");

	// ���½���Ӣ�۳�����ѡ��ʱ�õ�
	SimpleAudioEngine::getInstance()->preloadEffect("music/hero1.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/hero2.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/hero3.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/hero4.mp3");

	// ����Ӣ��ɱ��AIʱ���õ�
	SimpleAudioEngine::getInstance()->preloadEffect("music/gun_kill.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/gun2_kill.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/knife_kill.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/sword_kill.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/hero4_kill.mp3");

	// ��ɱ��������
	SimpleAudioEngine::getInstance()->preloadEffect("music/update.mp3");

	// ��Ȧ��һ��������ʾ
	SimpleAudioEngine::getInstance()->preloadEffect("music/first_takedown.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/double_takedown.mp3");

	/*=======================Ԥ����Audio����=======================*/

	this->scheduleOnce(schedule_selector(LoadingScene::changeScene), 4.0f); // ������ʱ����

	return true;
}

/****************************
* Name ��LoadingScene::changeScene
* Summary ������˵�����
* return ����
****************************/
void LoadingScene::changeScene(float dt)
{
	auto MMS = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, MMS));
}