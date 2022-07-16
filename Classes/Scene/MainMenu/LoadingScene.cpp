//作者：李元特
//日期：2022-6-6
//实现：loading界面完工


#include "LoadingScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

/****************************
* Name ：LoadingScene::createScene
* Summary ：创建场景
* return ：场景类指针
****************************/
Scene* LoadingScene::createScene()
{
	return LoadingScene::create();
}

/****************************
* Name ：LoadingScene::init
* Summary ：加载界面初始化
* return ：初始化成功与否
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

	/*=======================创建背景开始=========================*/

	Sprite* bg = Sprite::create("background/LoadingBackground.png");
	bg->setPosition(Vec2(LOADING_BACKGROUND_POSITION));
	this->addChild(bg);

	/*=======================创建背景结束=========================*/

	/*=======================创建Logo开始=========================*/

	Sprite* BrawlStars = Sprite::create("BrawlStarsLogo.png");
	BrawlStars->setPosition(Vec2(LOADING_BSLOGO_POSITION));
	this->addChild(BrawlStars);

    Sprite* Tongji = Sprite::create("TongjiLogo.png");
	Tongji->setPosition(Vec2(LOADING_TJLOGO_POSITION));
	this->addChild(Tongji);

	/*=======================创建Logo结束=========================*/

	/*=======================创建提示语开始========================*/
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

	/*=======================创建提示语结束========================*/

	/*=======================预加载Audio开始=======================*/
	 //初始化 音乐
	Tools::preloadBackgroundMusic("sound/retro_fight_ingame_01.mp3");
	// 游戏中的音乐
	Tools::preloadBackgroundMusic("music/first_music.mp3");
	// 进入游戏menu的音乐


	//初始化 音效
	Tools::preloadEffect("sound/empty.wav");
	// 障碍物碰撞
	Tools::preloadEffect("music/start_game_music.mp3");
	// 玩家战胜一只怪兽
	Tools::preloadEffect("music/if_hero_kill_monster.mp3");
	// 点击设置按钮音效
	Tools::preloadEffect("music/if_click_buttom_on_menu.mp3");
	// 进入设置界面的音效
	Tools::preloadEffect("music/to_a_new_scene.mp3");
	
	// 选择AInumber成功
	Tools::preloadEffect("music/select_ok.mp3");
	
	// 以下是printed eggshell 音效
	Tools::preloadEffect("music/printed_eggshell_1.mp3");
	Tools::preloadEffect("music/printed_eggshell_2.mp3");
	Tools::preloadEffect("music/printed_eggshell_3.mp3");
	Tools::preloadEffect("music/printed_eggshell_4.mp3");
	Tools::preloadEffect("music/store_ai_number.mp3");

	// 以下都和技能有关
	Tools::preloadEffect("music/gun_skill_3times.mp3");
	Tools::preloadEffect("music/gun_attack.mp3");
	Tools::preloadEffect("music/laser_skill.mp3");
	Tools::preloadEffect("music/laser_attack.mp3");
	Tools::preloadEffect("music/knife_attack_2.mp3");
	Tools::preloadEffect("music/knife_attack_1.mp3");

	// 以下介绍英雄出场（选择）时用到
	Tools::preloadEffect("music/hero1.mp3");
	Tools::preloadEffect("music/hero2.mp3");
	Tools::preloadEffect("music/hero3.mp3");
	Tools::preloadEffect("music/hero4.mp3");

	// 以下英雄杀死AI时候用到
	Tools::preloadEffect("music/gun_kill.mp3");
	Tools::preloadEffect("music/gun2_kill.mp3");
	Tools::preloadEffect("music/knife_kill.mp3");
	Tools::preloadEffect("music/sword_kill.mp3");
	Tools::preloadEffect("music/hero4_kill.mp3");

	// 击杀怪兽升级
	Tools::preloadEffect("music/update.mp3");

	// 缩圈第一、二次提示
	Tools::preloadEffect("music/first_takedown.mp3");
	Tools::preloadEffect("music/double_takedown.mp3");

	/*=======================预加载Audio结束=======================*/

	this->scheduleOnce(schedule_selector(LoadingScene::changeScene), 4.0f); // 开启计时器！

	return true;
}

/****************************
* Name ：LoadingScene::changeScene
* Summary ：进入菜单界面
* return ：无
****************************/
void LoadingScene::changeScene(float dt)
{
	auto MMS = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, MMS));
}