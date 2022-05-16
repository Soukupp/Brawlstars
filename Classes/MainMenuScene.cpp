//作者 : 王鹏
//日期 : 2022-5-14
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

/****************************
* Name ：MainMenu::createScene
* Summary ：创建场景
* return ：场景类指针
****************************/
Scene* MainMenu::createScene()
{
    return MainMenu::create();
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
* Name ：MainMenu::init
* Summary ：主菜单初始化
* return ：初始化成功与否
****************************/
bool MainMenu::init()
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
        "exitMainMenu.png",
        "exitMainMenu.png",
        CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

    if (mainMenuCloseItem == nullptr ||
        mainMenuCloseItem->getContentSize().width <= 0 ||
        mainMenuCloseItem->getContentSize().height <= 0)
    {
        problemLoading("'exitMainMenu.png' and 'exitMainMenu.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - mainMenuCloseItem->getContentSize().width / 2;
        float y = origin.y + mainMenuCloseItem->getContentSize().height / 2;
        mainMenuCloseItem->setPosition(Vec2(x, y));
    }
    //创建关闭菜单
    auto closeMenu = Menu::create(mainMenuCloseItem, NULL);
    closeMenu->setPosition(Vec2::ZERO);
    this->addChild(closeMenu, 1);
    /*=====================创建关闭按钮结束====================*/

    /*=====================创建游戏名开始======================*/

    auto gameNameLabel = Label::createWithTTF("BRAWLSTARS", "fonts/PixeloidMono.ttf", 96);
    if (gameNameLabel == nullptr)
    {
        problemLoading("'fonts/PixeloidMono.ttf'");
    }
    else
    {
        gameNameLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height/8*7 - gameNameLabel->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(gameNameLabel, 1);
    }
    /*=====================创建游戏名结束======================*/

    /*===================创建主菜单选项开始====================*/
    MenuItemFont::setFontName("fonts/PixeloidMono.ttf");
    MenuItemFont::setFontSize(40);

    MenuItemFont* itemStart = MenuItemFont::create("Start",
        CC_CALLBACK_1(MainMenu::menuStartCallback, this));
    MenuItemFont* itemStore = MenuItemFont::create("Store",
        CC_CALLBACK_1(MainMenu::menuStoreCallback, this));
    MenuItemFont* itemHeros = MenuItemFont::create("Heros",
        CC_CALLBACK_1(MainMenu::menuHerosCallback, this));
    MenuItemFont* itemSettings = MenuItemFont::create("Settings",
        CC_CALLBACK_1(MainMenu::menuSettingsCallback, this));

    Menu* mainMenu = Menu::create(itemStart, itemStore, itemHeros, itemSettings, NULL);
    mainMenu->setPosition(visibleSize.width / 2 + origin.x,
        origin.y + mainMenu->getContentSize().height / 2);
    mainMenu->alignItemsVertically();

    this->addChild(mainMenu);
    /*===================创建主菜单选项结束====================*/

    /*=====================创建背景图开始======================*/
    auto sprite = Sprite::create("mainmenuBackground.png");
    if (sprite == nullptr)
    {
        problemLoading("'mainmenuBackground.png'");
    }
    else
    {
        //将背景图放在中央
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, 
            visibleSize.height / 2 + origin.y));

        this->addChild(sprite, 0);
    }
    /*=====================创建背景图结束======================*/
    return true;
}
/****************************
* Name ：MainMenu::menuCloseCallback
* Summary ：主菜单关闭按钮回调
* return ：
****************************/
void MainMenu::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

/****************************
* Name ：menuStartCallback
* Summary ：主菜单开始按钮回调
* return ：
****************************/
void menuStartCallback(cocos2d::Ref* pSender)
{
	auto gameScene = GameScene::createScene();
	Director::getInstance()->
}
/****************************
* Name ：menuStoreCallback
* Summary ：主菜单商店按钮回调
* return ：
****************************/
void menuStoreCallback(cocos2d::Ref* pSender)
{
	auto storeScene = StoreScene::createScene();
	Director::getInstance()->pushScene(storeScene);
}
/****************************
* Name ：menuHerosCallback
* Summary ：主菜单人物按钮回调
* return ：
****************************/
void menuHerosCallback(cocos2d::Ref* pSender)
{
	auto playerScene = PlayerScene::createScene();
	Director::getInstance()->pushScene(playerScene);
}
/****************************
* Name ：menuSettingsCallback
* Summary ：主菜单设置按钮回调
* return ：
****************************/
void menuSettingsCallback(cocos2d::Ref* pSender)
{
}
