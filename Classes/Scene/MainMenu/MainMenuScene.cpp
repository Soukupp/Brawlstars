//作者 : 王鹏
//日期 : 2022-5-14
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

static bool ifMusicBegin = true;
/****************************
* Name ：MainMenuScene::createScene
* Summary ：创建场景
* return ：场景类指针
****************************/
Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}
/****************************
* Name ：problemLoading
* Summary ：错误打印
* return ：
****************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}
/****************************
* Name ：MainMenuScene::init
* Summary ：主菜单初始化
* return ：初始化成功与否
****************************/
bool MainMenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*=====================创建关闭按钮开始======================*/

    //创建关闭按钮
    auto mainMenuCloseItem = MenuItemImage::create(
        "ui/exitMainMenuNormal.png",
        "ui/exitMainMenuSelected.png",
        CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));

    if (mainMenuCloseItem == nullptr ||
        mainMenuCloseItem->getContentSize().width <= 0 ||
        mainMenuCloseItem->getContentSize().height <= 0)
    {//错误处理
        problemLoading("'ui/exitMainMenuNormal.png' and 'ui/exitMainMenuSelected.png'");
    }
    else
    {//设置位置
        float x = MAINMENU_CLOSE_ITEM_POSITION_X;
        float y = MAINMENU_CLOSE_ITEM_POSITION_Y;
        mainMenuCloseItem->setPosition(Vec2(x, y));
    }
    //创建关闭菜单
    auto closeMenu = Menu::create(mainMenuCloseItem, NULL);
    closeMenu->setPosition(Vec2::ZERO);
    this->addChild(closeMenu, 2);
    /*=====================创建关闭按钮结束====================*/
    /*=====================创建背景音乐开始=======================*/

    if(ifMusicBegin)
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/retro_fight_ingame_01.mp3",true);
    ifMusicBegin = false;
    /*=====================创建背景音乐结束=======================*/

    /*=====================创建游戏名开始======================*/

    auto gameNameLabel = Label::createWithTTF(
        "BRAWLSTARS", 
        "fonts/PixeloidSans.ttf", 
        MAINMENU_GAMENAME_LABEL_SIZE
    );//创建文本
    if (gameNameLabel == nullptr)
    {
        problemLoading("'fonts/PixeloidSans.ttf'");
    }
    else
    {
        const Color4B gameNameLabelColor(MAINMENU_TEXT_RGB_COLOR,255);//创建4B颜色
        gameNameLabel->setTextColor(gameNameLabelColor);
        gameNameLabel->setPosition(
            Vec2(MAINMENU_GAMENAME_LABEL_POSITION_X,
            MAINMENU_GAMENAME_LABEL_POSITION_Y)
        );

        this->addChild(gameNameLabel, 1);
    }
    /*=====================创建游戏名结束======================*/

    /*===================创建主菜单选项开始====================*/
    MenuItemFont::setFontName("fonts/PixeloidMono.ttf");
    MenuItemFont::setFontSize(64);
    const Color3B menuItemColor(MAINMENU_TEXT_RGB_COLOR);//创建3B颜色

    //创建单个菜单项
    MenuItemFont* itemStart = MenuItemFont::create(
        "START",
        CC_CALLBACK_1(MainMenuScene::menuStartCallback, this)
    );
    MenuItemFont* itemStore = MenuItemFont::create(
        "STORE",
        CC_CALLBACK_1(MainMenuScene::menuStoreCallback, this)
    );
    MenuItemFont* itemHeros = MenuItemFont::create(
        "HEROS",
        CC_CALLBACK_1(MainMenuScene::menuHerosCallback, this)
    );
    MenuItemFont* itemSettings = MenuItemFont::create(
        "SETTINGS",
        CC_CALLBACK_1(MainMenuScene::menuSettingsCallback, this)
    );

    //创建菜单 把菜单项放进去
    Menu* mainMenu = Menu::create(itemStart, itemStore, itemHeros, itemSettings, NULL);
    mainMenu->setPosition(MAINMENU_MAINMENU_POSITION_X,
        MAINMENU_MAINMENU_POSITION_Y);
    mainMenu->alignItemsVertically();
    mainMenu->setColor(menuItemColor);

    this->addChild(mainMenu,1);
    /*===================创建主菜单选项结束====================*/

    /*=====================创建背景图开始======================*/
    auto background = Sprite::create("background/mainmenuBackground.png");
    if (background == nullptr)
    {
        problemLoading("'background/mainmenuBackground.png'");
    }
    else
    {
        //将背景图放在中央
        background->setPosition(Vec2(MAINMENU_BACKGROUND_POSITION_X,
            MAINMENU_BACKGROUND_POSITION_Y));

        this->addChild(background, 0);
    }
    /*=====================创建背景图结束======================*/
    return true;
}
/****************************
* Name ：MainMenuScene::menuCloseCallback
* Summary ：主菜单关闭按钮回调
* return ：
****************************/
void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

/****************************
* Name ：menuStartCallback
* Summary ：主菜单开始按钮回调
* return ：
****************************/
void MainMenuScene::menuStartCallback(cocos2d::Ref* pSender)
{
	auto gameScene = GameScene::createScene();   // 转入GameScene
    Director::getInstance()->replaceScene(gameScene);//mainmenu已被释放
}
/****************************
* Name ：menuStoreCallback
* Summary ：主菜单商店按钮回调
* return ：
****************************/
void MainMenuScene::menuStoreCallback(cocos2d::Ref* pSender)
{
	auto storeScene = StoreScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, storeScene));//mainmenu未被释放 使用popScene返回
}
/****************************
* Name ：menuHerosCallback
* Summary ：主菜单人物按钮回调
* return ：
****************************/
void MainMenuScene::menuHerosCallback(cocos2d::Ref* pSender)
{
	auto heroScene = HeroScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, heroScene));//mainmenu未被释放 使用popScene返回
}
/****************************
* Name ：menuSettingsCallback
* Summary ：主菜单设置按钮回调
* return ：
****************************/
void MainMenuScene::menuSettingsCallback(cocos2d::Ref* pSender)
{
    auto settingsScene = SettingsScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, settingsScene));//mainmenu未被释放 使用popScene返回
}

