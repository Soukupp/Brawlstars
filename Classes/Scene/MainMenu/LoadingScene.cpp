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
* Name ：problemLoading
* Summary ：错误打印
* return ：无
****************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
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


	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/start_game_music.mp3");

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

	/*=======================创建提示语结束========================*/

	/*=======================预加载Audio开始=======================*/
	 //初始化 音乐
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/retro_fight_ingame_01.mp3");
	// 游戏中的音乐
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/first_music.mp3");
	// 进入游戏menu的音乐


	//初始化 音效
	SimpleAudioEngine::getInstance()->preloadEffect("sound/empty.wav");
	// 障碍物碰撞
	SimpleAudioEngine::getInstance()->preloadEffect("music/start_game_music.mp3");
	// 玩家战胜一只怪兽
	SimpleAudioEngine::getInstance()->preloadEffect("music/if_hero_kill_monster.mp3");
	// 点击设置按钮音效
	SimpleAudioEngine::getInstance()->preloadEffect("music/if_click_buttom_on_menu.mp3");
	// 进入设置界面的音效
	SimpleAudioEngine::getInstance()->preloadEffect("music/to_a_new_scene.mp3");
	
	// 选择AInumber成功
	SimpleAudioEngine::getInstance()->preloadEffect("music/select_ok.mp3");
	
	// 以下是printed eggshell 音效
	SimpleAudioEngine::getInstance()->preloadEffect("music/printed_eggshell_1.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/printed_eggshell_2.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/printed_eggshell_3.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/printed_eggshell_4.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/store_ai_number.mp3");

	// 以下都和技能有关
	SimpleAudioEngine::getInstance()->preloadEffect("music/gun_skill_3times.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/gun_attack.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/laser_skill.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/laser_attack.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/knife_attack_2.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/knife_attack_1.mp3");

	// 以下介绍英雄出场（选择）时用到
	SimpleAudioEngine::getInstance()->preloadEffect("music/hero1.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/hero2.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/hero3.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/hero4.mp3");

	// 以下英雄杀死AI时候用到
	SimpleAudioEngine::getInstance()->preloadEffect("music/gun_kill.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/gun2_kill.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/knife_kill.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/sword_kill.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/hero4_kill.mp3");

	// 击杀怪兽升级
	SimpleAudioEngine::getInstance()->preloadEffect("music/update.mp3");

	// 缩圈第一、二次提示
	SimpleAudioEngine::getInstance()->preloadEffect("music/first_takedown.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/double_takedown.mp3");

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