//作者 : 王鹏
//创建日期 : 2022-5-14
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
    {//错误处理
        problemLoading("'exitMainMenu.png' and 'exitMainMenu.png'");
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


    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music2.mp3", true);
        log("have played music");

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
        CC_CALLBACK_1(MainMenu::menuStartCallback, this)
    );
    MenuItemFont* itemStore = MenuItemFont::create(
        "STORE",
        CC_CALLBACK_1(MainMenu::menuStartCallback, this)
    );
    MenuItemFont* itemHeros = MenuItemFont::create(
        "HEROS",
        CC_CALLBACK_1(MainMenu::menuSettingsCallback, this)
    );
    MenuItemFont* itemSettings = MenuItemFont::create(
        "SETTINGS",
        CC_CALLBACK_1(MainMenu::menuSettingsCallback, this)
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
    auto sprite = Sprite::create("mainmenuBackground.png");
    if (sprite == nullptr)
    {
        problemLoading("'mainmenuBackground.png'");
    }
    else
    {
        //将背景图放在中央
        sprite->setPosition(Vec2(MAINMENU_BACKGROUND_POSITION_X,
            MAINMENU_BACKGROUND_POSITION_Y));

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
void MainMenu::menuStartCallback(cocos2d::Ref* pSender)
{
	//auto gameScene = GameScene::createScene();
 //   Director::getInstance()->replaceScene(gameScene);//mainmenu已被释放
}
/****************************
* Name ：menuStoreCallback
* Summary ：主菜单商店按钮回调
* return ：
****************************/
void MainMenu::menuStoreCallback(cocos2d::Ref* pSender)
{
	//auto storeScene = StoreScene::createScene();
	//Director::getInstance()->pushScene(storeScene);//mainmenu未被释放 使用popScene返回
}
/****************************
* Name ：menuHerosCallback
* Summary ：主菜单人物按钮回调
* return ：
****************************/
void MainMenu::menuHerosCallback(cocos2d::Ref* pSender)
{
	//auto playerScene = PlayerScene::createScene();
	//Director::getInstance()->pushScene(playerScene);//mainmenu未被释放 使用popScene返回
}
/****************************
* Name ：menuSettingsCallback
* Summary ：主菜单设置按钮回调
* return ：
****************************/
void MainMenu::menuSettingsCallback(cocos2d::Ref* pSender)
{
    auto settingScene = SettingScene::createScene();
    Director::getInstance()->pushScene(settingScene);//mainmenu未被释放 使用popScene返回
}

