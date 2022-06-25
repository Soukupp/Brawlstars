//作者 : 王鹏
//日期 : 2022-5-14

//作者 : 李元特
//日期 : 2022-6-3
//修改 : 添加提示信息，增加音效、音乐，增加粒子系统

//作者 : 李元特
//日期 : 2022-6-7
//修改 ：弹窗实现

#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

static bool firstSet = true;
static bool firstPlay = true;

/*
    对象所在层数：
    背景图 0层
    游戏名字 1层
    关闭按钮、提示按钮 2层
    主菜单 3层
    粒子模型 5层

    *hero, *weapon （包括AI） 2层
    _SafeArea 100层
*/

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

    auto pDict = Tools::initDict();

    /*=====================创建背景图开始======================*/

    auto background = Sprite::create("background/MainMenuBackground.jpg");
    if (background == nullptr)
    {
        problemLoading("'background/MainMenuBackground.jpg'");
    }
    else
    {
        //将背景图放在中央
        background->setPosition(Vec2(MAINMENU_BACKGROUND_POSITION_X,
            MAINMENU_BACKGROUND_POSITION_Y));

        this->addChild(background, 0);
    }

    /*=====================创建背景图结束======================*/

    /*=====================创建游戏名开始======================*/

    auto gameNameLabel = Label::createWithTTF(
        "BRAWLSTARS",
        "fonts/Marker Felt.ttf",
        MAINMENU_GAMENAME_LABEL_SIZE
    );//创建文本
    if (gameNameLabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        const Color4B gameNameLabelColor(MAINMENU_TITLE_RGB_COLOR, 255);//创建4B颜色
        gameNameLabel->setTextColor(gameNameLabelColor);
        gameNameLabel->setPosition(
            Vec2(MAINMENU_GAMENAME_LABEL_POSITION_X,
                MAINMENU_GAMENAME_LABEL_POSITION_Y)
        );

        this->addChild(gameNameLabel, 1);
    }

    /*=====================创建游戏名结束======================*/

    /*===================创建关闭、信息按钮开始=================*/
    auto mainMenuCloseItem = MenuItemImage::create(
        "ui/exitMainMenuNormal.png",
        "ui/exitMainMenuSelected.png",
        CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));

    if (mainMenuCloseItem == nullptr ||
        mainMenuCloseItem->getContentSize().width <= 0 ||
        mainMenuCloseItem->getContentSize().height <= 0)
    {
        problemLoading("'ui/exitMainMenuNormal.png' and 'ui/exitMainMenuSelected.png'");
    }
    else
    {
        mainMenuCloseItem->setPosition(Vec2(MAINMENU_CLOSE_ITEM_POSITION_X, MAINMENU_CLOSE_ITEM_POSITION_Y));
    }

    auto mainMenuInfoItem = MenuItemImage::create(
        "ui/button_info.png",
        "ui/button_info.png",
        CC_CALLBACK_1(MainMenuScene::menuInfoCallback, this));
    if (mainMenuInfoItem == nullptr ||
        mainMenuInfoItem->getContentSize().width <= 0 ||
        mainMenuInfoItem->getContentSize().height <= 0)
    {
        problemLoading("'ui/button_info.png' and 'ui/button_info.png'");
    }
    else
    {
        mainMenuInfoItem->setPosition(Vec2(MAINMENU_INFO_ITEM_POSITION_X, MAINMENU_INFO_ITEM_POSITION_Y));
    }

    //创建菜单
    auto MainMenu = Menu::create(mainMenuCloseItem, mainMenuInfoItem, NULL);
    MainMenu->setPosition(Vec2::ZERO);
    this->addChild(MainMenu, 2);

    /*===================创建关闭、信息按钮结束=================*/

    /*===================创建主菜单选项开始====================*/

    MenuItemFont::setFontName("fonts/Segoe Print.ttf");
    MenuItemFont::setFontSize(50);
    const Color3B menuItemColor(MAINMENU_TEXT_RGB_COLOR);//创建3B颜色

    //创建单个菜单项
    MenuItemFont* itemStart = MenuItemFont::create(
        Tools::strid(pDict, "start"),
        CC_CALLBACK_1(MainMenuScene::menuStartCallback, this)
    );
    MenuItemFont* itemMap = MenuItemFont::create(
        Tools::strid(pDict, "maps"),
        CC_CALLBACK_1(MainMenuScene::menuMapCallback, this)
    );
    MenuItemFont* itemHeros = MenuItemFont::create(
        Tools::strid(pDict, "heros"),
        CC_CALLBACK_1(MainMenuScene::menuHerosCallback, this)
    );
    MenuItemFont* itemSettings = MenuItemFont::create(
        Tools::strid(pDict, "settings"),
        CC_CALLBACK_1(MainMenuScene::menuSettingsCallback, this)
    );

    //创建菜单 把菜单项放进去
    Menu* mainMenu = Menu::create(itemStart, itemMap, itemHeros, itemSettings, NULL);
    mainMenu->setPosition(MAINMENU_MAINMENU_POSITION_X,
        MAINMENU_MAINMENU_POSITION_Y);
    mainMenu->alignItemsVertically();
    mainMenu->setColor(menuItemColor);

    this->addChild(mainMenu, 3);

    /*===================创建主菜单选项结束====================*/

    /*==================设置UseDefault开始====================*/

    if (firstSet) {
        UserDefault::getInstance()->setBoolForKey("ifPlayMusic", true);
        UserDefault::getInstance()->setBoolForKey("ifShowFPS", false);
        UserDefault::getInstance()->setIntegerForKey("musicVolume", 50);
        UserDefault::getInstance()->setIntegerForKey("selectedHero", 1);

        firstSet = false;
    }

    /*=================设置UseDefault结束====================*/

    /*=================创建背景音乐开始=======================*/

    if (firstPlay)
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/first_music.mp3", true);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(
        static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
    firstPlay = false;
    if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/first_music.mp3", true);
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(
            static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
    }
    /*=====================创建背景音乐结束=======================*/

    /*=====================创建玩家信息按钮开始===================*/

    auto playerMassageItem = MenuItemImage::create(
        "ui/playerMassage.png",
        "ui/playerMassage.png",
        CC_CALLBACK_1(MainMenuScene::playerMassageCallback, this));

    if (playerMassageItem == nullptr ||
        playerMassageItem->getContentSize().width <= 0 ||
        playerMassageItem->getContentSize().height <= 0)
    {
        problemLoading("'ui/playerMassage.png' and 'ui/playerMassage.png'");
    }
    else
    {
        playerMassageItem->setPosition(Vec2(MAINMENU_PLAYERMASSAGE_POSITION_X, MAINMENU_PLAYERMASSAGE_POSITION_Y));
    }

    //创建菜单
    auto playerMassageMenu = Menu::create(playerMassageItem, NULL);
    playerMassageMenu->setPosition(Vec2::ZERO);
    this->addChild(playerMassageMenu, 2);

    /*=====================创建玩家信息按钮结束===================*/

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
* Name ：MainMenuScene::menuInfoCallback
* Summary ：弹窗
* return ：
****************************/
void MainMenuScene::menuInfoCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
        static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto MainMenuInformation = InformationPopLayer::create
    ("background/MainMenuINformationBackground.png", Size(700, 490), 150);
    MainMenuInformation->setPosition(0, -50);
    MainMenuInformation->setTitle("BRAWLSTARS INTRODUCTION", "fonts/Lilita one.ttf", 40);
    MainMenuInformation->setContentText(" \n Welcome to the BRAWLSTARS world, my handsome(pretty) brawlstar! \n Click \"MAP\" to select the map \n (Classic mode or Terrain warfare mode) \n and select the number of game NPC(5 to 9) \n Click \"HERO\" to select a hero (4 types). \n  After your choices, you can start your\n marvelous and fantasy adventure! \n If you need to adjust the volume during your adventure, you can also personalize the settings on the menu page or in the game. \n Finally, enjoy your wonderful adventure!"
        , "fonts/Lilita one.ttf", 30, MAINMENU_INFORMATION_CONTENT_TEXT_PADDING,
        MAINMENU_INFORMATION_CONTENT_TEXT_PADDINGTOP);
    MainMenuInformation->createButton("ui/button_close.png", "ui/button_close.png");
    this->addChild(MainMenuInformation, 4);
}

/****************************
* Name ：MainMenuScene::menuStartCallback
* Summary ：主菜单开始按钮回调
* return ：
****************************/
void MainMenuScene::menuStartCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
        static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
    //auto GLS1 = GameLoadingScene1::createScene();   // 转入GameLoadingScene1
    //Director::getInstance()->replaceScene(TransitionFade::create(1, GLS1));//mainmenu已被释放
    auto GS = GameScene::createScene();   // 转入GameScene
    Director::getInstance()->replaceScene(TransitionFade::create(1, GS));//GSL2已被释放
}

/****************************
* Name ：MainMenuScene::menuMapCallback
* Summary ：主菜单商店按钮回调
* return ：
****************************/
void MainMenuScene::menuMapCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
        static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
    auto storeScene = StoreScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, storeScene));//mainmenu未被释放 使用popScene返回
}

/****************************
* Name ：MainMenuScene::menuHerosCallback
* Summary ：主菜单人物按钮回调
* return ：
****************************/
void MainMenuScene::menuHerosCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
        static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
    auto heroScene = HeroScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, heroScene));//mainmenu未被释放 使用popScene返回
}

/****************************
* Name ：MainMenuScene::menuSettingsCallback
* Summary ：主菜单设置按钮回调
* return ：
****************************/
void MainMenuScene::menuSettingsCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
        static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
    auto settingsScene = SettingsScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, settingsScene));//mainmenu未被释放 使用popScene返回
}

/****************************
* Name ：MainMenuScene::playerMassageCallback
* Summary ：玩家信息按钮回调
* return ：
****************************/
void MainMenuScene::playerMassageCallback(cocos2d::Ref* pSender)
{
    log("_winTimes %d", Tools::getUserInt("_winTimes"));
    log("_gameTimes %d", Tools::getUserInt("_gameTimes"));
    log("_killNums %d", Tools::getUserInt("_killNums"));
    log("_cupNums %d", Tools::getUserInt("_cupNums"));

    std::string playerInfo =
        "\n                                    GAME WINNING :      " + std::to_string(Tools::getUserInt("_winTimes"))
        + "\n" +
        "                                           GAME COUNT :      " + std::to_string(Tools::getUserInt("_gameTimes"))
        + "\n" +
        "                                         KILL NUMBERS :     " + std::to_string(Tools::getUserInt("_killNums"))
        + "\n" +
        "                                 CROWN NUMBERS :     " + std::to_string(Tools::getUserInt("_cupNums"))
        + "\n\n" +
        "               COME ON, MY BRAVE BRAWLSTAR!"
        + "\n" +
        "                GO AND FIGHT FOR YOUR HONOR!"
        ;

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
        static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto MainMenuPlayerInformation = InformationPopLayer::create
    ("background/HeroPlayerInformationBackground.jpg", Size(980, 490), 150);
    MainMenuPlayerInformation->setPosition(0, -50);
    MainMenuPlayerInformation->setTitle("PLAYER INFORMATION", "fonts/Lilita one.ttf", 50);
    MainMenuPlayerInformation->setContentText(playerInfo.c_str(),
        "fonts/Lilita one.ttf", 40, MAINMENU_INFORMATION_CONTENT_TEXT_PADDING,
        MAINMENU_INFORMATION_CONTENT_TEXT_PADDINGTOP);
    MainMenuPlayerInformation->createButton("ui/button_close.png", "ui/button_close.png");
    this->addChild(MainMenuPlayerInformation, 6);

}

/****************************
* Name ：MainMenuScene::onEnterTransitionDidFinish()
* Summary ：粒子模型
* return ：
****************************/
void MainMenuScene::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();
    ParticleSystem* system;
    system = ParticleFireworks::create();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    system->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
    this->addChild(system, 5);
}