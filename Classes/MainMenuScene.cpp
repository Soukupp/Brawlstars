//浣滆�� : 鐜嬮箯
//鍒涘缓鏃ユ湡 : 2022-5-14
#include "MainMenuScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

static bool ifMusicBegin = true;
/****************************
* Name 锛歁ainMenuScene::createScene
* Summary 锛氬垱寤哄満鏅�
* return 锛氬満鏅被鎸囬拡
****************************/
Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}
/****************************
* Name 锛歱roblemLoading
* Summary 锛氶敊璇墦鍗�
* return 锛�
****************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}
/****************************
* Name 锛歁ainMenuScene::init
* Summary 锛氫富鑿滃崟鍒濆鍖�
* return 锛氬垵濮嬪寲鎴愬姛涓庡惁
****************************/
bool MainMenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*=====================鍒涘缓鍏抽棴鎸夐挳寮�濮�======================*/

    //鍒涘缓鍏抽棴鎸夐挳
    auto mainMenuCloseItem = MenuItemImage::create(
        "exitMainMenuNormal.png",
        "exitMainMenuSelected.png",
        CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));

    if (mainMenuCloseItem == nullptr ||
        mainMenuCloseItem->getContentSize().width <= 0 ||
        mainMenuCloseItem->getContentSize().height <= 0)
    {//閿欒澶勭悊
        problemLoading("'exitMainMenuNormal.png' and 'exitMainMenuSelected.png'");
    }
    else
    {//璁剧疆浣嶇疆
        float x = MAINMENU_CLOSE_ITEM_POSITION_X;
        float y = MAINMENU_CLOSE_ITEM_POSITION_Y;
        mainMenuCloseItem->setPosition(Vec2(x, y));
    }
    //鍒涘缓鍏抽棴鑿滃崟
    auto closeMenu = Menu::create(mainMenuCloseItem, NULL);
    closeMenu->setPosition(Vec2::ZERO);
    this->addChild(closeMenu, 2);
    /*=====================鍒涘缓鍏抽棴鎸夐挳缁撴潫====================*/

    /*=====================创建关闭按钮结束====================*/
  
    /*=====================创建背景音乐开始=======================*/

    if(ifMusicBegin)
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/retro_fight_ingame_01.mp3",true);
    ifMusicBegin = false;
    /*=====================创建背景音乐结束=======================*/
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music2.mp3", true);
        log("have played music");

    /*=====================鍒涘缓娓告垙鍚嶅紑濮�======================*/

    auto gameNameLabel = Label::createWithTTF(
        "BRAWLSTARS", 
        "fonts/PixeloidSans.ttf", 
        MAINMENU_GAMENAME_LABEL_SIZE
    );//鍒涘缓鏂囨湰
    if (gameNameLabel == nullptr)
    {
        problemLoading("'fonts/PixeloidSans.ttf'");
    }
    else
    {
        const Color4B gameNameLabelColor(MAINMENU_TEXT_RGB_COLOR,255);//鍒涘缓4B棰滆壊
        gameNameLabel->setTextColor(gameNameLabelColor);
        gameNameLabel->setPosition(
            Vec2(MAINMENU_GAMENAME_LABEL_POSITION_X,
            MAINMENU_GAMENAME_LABEL_POSITION_Y)
        );

        this->addChild(gameNameLabel, 1);
    }
    /*=====================鍒涘缓娓告垙鍚嶇粨鏉�======================*/

    /*===================鍒涘缓涓昏彍鍗曢�夐」寮�濮�====================*/
    MenuItemFont::setFontName("fonts/PixeloidMono.ttf");
    MenuItemFont::setFontSize(64);
    const Color3B menuItemColor(MAINMENU_TEXT_RGB_COLOR);//鍒涘缓3B棰滆壊

    //鍒涘缓鍗曚釜鑿滃崟椤�
    MenuItemFont* itemStart = MenuItemFont::create(
        "START",
        CC_CALLBACK_1(MainMenuScene::menuStartCallback, this)
    );
    MenuItemFont* itemStore = MenuItemFont::create(
        "STORE",
        CC_CALLBACK_1(MainMenuScene::menuStartCallback, this)
    );
    MenuItemFont* itemHeros = MenuItemFont::create(
        "HEROS",
        CC_CALLBACK_1(MainMenuScene::menuSettingsCallback, this)
    );
    MenuItemFont* itemSettings = MenuItemFont::create(
        "SETTINGS",
        CC_CALLBACK_1(MainMenuScene::menuSettingsCallback, this)
    );

    //鍒涘缓鑿滃崟 鎶婅彍鍗曢」鏀捐繘鍘�
    Menu* mainMenu = Menu::create(itemStart, itemStore, itemHeros, itemSettings, NULL);
    mainMenu->setPosition(MAINMENU_MAINMENU_POSITION_X,
        MAINMENU_MAINMENU_POSITION_Y);
    mainMenu->alignItemsVertically();
    mainMenu->setColor(menuItemColor);

    this->addChild(mainMenu,1);
    /*===================鍒涘缓涓昏彍鍗曢�夐」缁撴潫====================*/

    /*=====================鍒涘缓鑳屾櫙鍥惧紑濮�======================*/
    auto background = Sprite::create("mainmenuBackground.png");
    if (background == nullptr)
    {
        problemLoading("'mainmenuBackground.png'");
    }
    else
    {
        //灏嗚儗鏅浘鏀惧湪涓ぎ
        background->setPosition(Vec2(MAINMENU_BACKGROUND_POSITION_X,
            MAINMENU_BACKGROUND_POSITION_Y));

        this->addChild(background, 0);
    }
    /*=====================鍒涘缓鑳屾櫙鍥剧粨鏉�======================*/
    return true;
}
/****************************
* Name 锛歁ainMenuScene::menuCloseCallback
* Summary 锛氫富鑿滃崟鍏抽棴鎸夐挳鍥炶皟
* return 锛�
****************************/
void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

/****************************
* Name 锛歮enuStartCallback
* Summary 锛氫富鑿滃崟寮�濮嬫寜閽洖璋�
* return 锛�
****************************/
void MainMenuScene::menuStartCallback(cocos2d::Ref* pSender)
{
	auto gameScene = GameScene::createScene();   // 杞叆GameScene
    Director::getInstance()->replaceScene(gameScene);//mainmenu宸茶閲婃斁
}
/****************************
* Name 锛歮enuStoreCallback
* Summary 锛氫富鑿滃崟鍟嗗簵鎸夐挳鍥炶皟
* return 锛�
****************************/
void MainMenuScene::menuStoreCallback(cocos2d::Ref* pSender)
{
	//auto storeScene = StoreScene::createScene();
	//Director::getInstance()->pushScene(storeScene);//mainmenu鏈閲婃斁 浣跨敤popScene杩斿洖
}
/****************************
* Name 锛歮enuHerosCallback
* Summary 锛氫富鑿滃崟浜虹墿鎸夐挳鍥炶皟
* return 锛�
****************************/
void MainMenuScene::menuHerosCallback(cocos2d::Ref* pSender)
{
	//auto playerScene = PlayerScene::createScene();
	//Director::getInstance()->pushScene(playerScene);//mainmenu鏈閲婃斁 浣跨敤popScene杩斿洖
}
/****************************
* Name 锛歮enuSettingsCallback
* Summary 锛氫富鑿滃崟璁剧疆鎸夐挳鍥炶皟
* return 锛�
****************************/
void MainMenuScene::menuSettingsCallback(cocos2d::Ref* pSender)
{
    auto settingsScene = SettingsScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, settingsScene));//mainmenu鏈閲婃斁 浣跨敤popScene杩斿洖

}

