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

	auto pDict = Tools::initDict();

	Tools::playBackgroundMusic("music/start_game_music.mp3");
	Tools::setEffectsVolume("musicVolume");

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
	Color3B tipColor(220, 220, 220);

	auto tip1 = LabelTTF::create(Tools::cbyid(pDict, "Moderate Games, Happy Life!"), "fonts/Lilita one.ttf", 36);
	tip1->enableShadow(LOADING_TIP1_SHADOW);
	tip1->setColor(tipColor);
	tip1->setPosition(Vec2(LOADING_TIP1_POSITION));
	this->addChild(tip1);

	auto tip2 = LabelTTF::create(Tools::cbyid(pDict, "WELCOME TO THE WILDERNESS JOURNEY!"), "fonts/Lilita one.ttf", 28);
	tip2->enableShadow(LOADING_TIP1_SHADOW);
	tip2->setColor(tipColor);
	tip2->setPosition(Vec2(LOADING_TIP2_POSITION));
	this->addChild(tip2);
	log("WELCOME TO THE WILDERNESS JOURNEY!");

	auto tip3 = LabelTTF::create(Tools::cbyid(pDict, "Shoot 'em up, blow 'em up, punch 'em out and win the BRAWL!"), "fonts/Lilita one.ttf", 28);
	tip3->enableShadow(LOADING_TIP1_SHADOW);
	tip3->setColor(tipColor);
	tip3->setPosition(Vec2(LOADING_TIP3_POSITION));
	this->addChild(tip3);
	log("Shoot 'em up, blow 'em up, punch 'em out and win the BRAWL!");

	/*=======================������ʾ�����========================*/

	/*=======================Ԥ����Audio��ʼ=======================*/
	 //��ʼ�� ����
	Tools::preloadBackgroundMusic("sound/retro_fight_ingame_01.mp3");
	// ��Ϸ�е�����
	Tools::preloadBackgroundMusic("music/first_music.mp3");
	// ������Ϸmenu������


	//��ʼ�� ��Ч
	Tools::preloadEffect("sound/empty.wav");
	// �ϰ�����ײ
	Tools::preloadEffect("music/start_game_music.mp3");
	// ���սʤһֻ����
	Tools::preloadEffect("music/if_hero_kill_monster.mp3");
	// ������ð�ť��Ч
	Tools::preloadEffect("music/if_click_buttom_on_menu.mp3");
	// �������ý������Ч
	Tools::preloadEffect("music/to_a_new_scene.mp3");
	
	// ѡ��AInumber�ɹ�
	Tools::preloadEffect("music/select_ok.mp3");
	
	// ������printed eggshell ��Ч
	Tools::preloadEffect("music/printed_eggshell_1.mp3");
	Tools::preloadEffect("music/printed_eggshell_2.mp3");
	Tools::preloadEffect("music/printed_eggshell_3.mp3");
	Tools::preloadEffect("music/printed_eggshell_4.mp3");
	Tools::preloadEffect("music/store_ai_number.mp3");

	// ���¶��ͼ����й�
	Tools::preloadEffect("music/gun_skill_3times.mp3");
	Tools::preloadEffect("music/gun_attack.mp3");
	Tools::preloadEffect("music/laser_skill.mp3");
	Tools::preloadEffect("music/laser_attack.mp3");
	Tools::preloadEffect("music/knife_attack_2.mp3");
	Tools::preloadEffect("music/knife_attack_1.mp3");

	// ���½���Ӣ�۳�����ѡ��ʱ�õ�
	Tools::preloadEffect("music/hero1.mp3");
	Tools::preloadEffect("music/hero2.mp3");
	Tools::preloadEffect("music/hero3.mp3");
	Tools::preloadEffect("music/hero4.mp3");

	// ����Ӣ��ɱ��AIʱ���õ�
	Tools::preloadEffect("music/gun_kill.mp3");
	Tools::preloadEffect("music/gun2_kill.mp3");
	Tools::preloadEffect("music/knife_kill.mp3");
	Tools::preloadEffect("music/sword_kill.mp3");
	Tools::preloadEffect("music/hero4_kill.mp3");

	// ��ɱ��������
	Tools::preloadEffect("music/update.mp3");

	// ��Ȧ��һ��������ʾ
	Tools::preloadEffect("music/first_takedown.mp3");
	Tools::preloadEffect("music/double_takedown.mp3");

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