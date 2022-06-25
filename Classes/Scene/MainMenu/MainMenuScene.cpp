//���� : ����
//���� : 2022-5-14

//���� : ��Ԫ��
//���� : 2022-6-3
//�޸� : �����ʾ��Ϣ��������Ч�����֣���������ϵͳ

//���� : ��Ԫ��
//���� : 2022-6-7
//�޸� ������ʵ��

#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

static bool firstSet = true;
static bool firstPlay = true;

/*
    �������ڲ�����
    ����ͼ 0��
    ��Ϸ���� 1��
    �رհ�ť����ʾ��ť 2��
    ���˵� 3��
    ����ģ�� 5��

    *hero, *weapon ������AI�� 2��
    _SafeArea 100��
*/

/****************************
* Name ��MainMenuScene::createScene
* Summary ����������
* return ��������ָ��
****************************/
Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

/****************************
* Name ��problemLoading
* Summary �������ӡ
* return ��
****************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

/****************************
* Name ��MainMenuScene::init
* Summary �����˵���ʼ��
* return ����ʼ���ɹ����
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

    /*=====================��������ͼ��ʼ======================*/

    auto background = Sprite::create("background/MainMenuBackground.jpg");
    if (background == nullptr)
    {
        problemLoading("'background/MainMenuBackground.jpg'");
    }
    else
    {
        //������ͼ��������
        background->setPosition(Vec2(MAINMENU_BACKGROUND_POSITION_X,
            MAINMENU_BACKGROUND_POSITION_Y));

        this->addChild(background, 0);
    }

    /*=====================��������ͼ����======================*/

    /*=====================������Ϸ����ʼ======================*/

    auto gameNameLabel = Label::createWithTTF(
        "BRAWLSTARS",
        "fonts/Marker Felt.ttf",
        MAINMENU_GAMENAME_LABEL_SIZE
    );//�����ı�
    if (gameNameLabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        const Color4B gameNameLabelColor(MAINMENU_TITLE_RGB_COLOR, 255);//����4B��ɫ
        gameNameLabel->setTextColor(gameNameLabelColor);
        gameNameLabel->setPosition(
            Vec2(MAINMENU_GAMENAME_LABEL_POSITION_X,
                MAINMENU_GAMENAME_LABEL_POSITION_Y)
        );

        this->addChild(gameNameLabel, 1);
    }

    /*=====================������Ϸ������======================*/

    /*===================�����رա���Ϣ��ť��ʼ=================*/
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

    //�����˵�
    auto MainMenu = Menu::create(mainMenuCloseItem, mainMenuInfoItem, NULL);
    MainMenu->setPosition(Vec2::ZERO);
    this->addChild(MainMenu, 2);

    /*===================�����رա���Ϣ��ť����=================*/

    /*===================�������˵�ѡ�ʼ====================*/

    MenuItemFont::setFontName("fonts/Segoe Print.ttf");
    MenuItemFont::setFontSize(50);
    const Color3B menuItemColor(MAINMENU_TEXT_RGB_COLOR);//����3B��ɫ

    //���������˵���
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

    //�����˵� �Ѳ˵���Ž�ȥ
    Menu* mainMenu = Menu::create(itemStart, itemMap, itemHeros, itemSettings, NULL);
    mainMenu->setPosition(MAINMENU_MAINMENU_POSITION_X,
        MAINMENU_MAINMENU_POSITION_Y);
    mainMenu->alignItemsVertically();
    mainMenu->setColor(menuItemColor);

    this->addChild(mainMenu, 3);

    /*===================�������˵�ѡ�����====================*/

    /*==================����UseDefault��ʼ====================*/

    if (firstSet) {
        UserDefault::getInstance()->setBoolForKey("ifPlayMusic", true);
        UserDefault::getInstance()->setBoolForKey("ifShowFPS", false);
        UserDefault::getInstance()->setIntegerForKey("musicVolume", 50);
        UserDefault::getInstance()->setIntegerForKey("selectedHero", 1);

        firstSet = false;
    }

    /*=================����UseDefault����====================*/

    /*=================�����������ֿ�ʼ=======================*/

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
    /*=====================�����������ֽ���=======================*/

    /*=====================���������Ϣ��ť��ʼ===================*/

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

    //�����˵�
    auto playerMassageMenu = Menu::create(playerMassageItem, NULL);
    playerMassageMenu->setPosition(Vec2::ZERO);
    this->addChild(playerMassageMenu, 2);

    /*=====================���������Ϣ��ť����===================*/

    return true;
}

/****************************
* Name ��MainMenuScene::menuCloseCallback
* Summary �����˵��رհ�ť�ص�
* return ��
****************************/
void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

/****************************
* Name ��MainMenuScene::menuInfoCallback
* Summary ������
* return ��
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
* Name ��MainMenuScene::menuStartCallback
* Summary �����˵���ʼ��ť�ص�
* return ��
****************************/
void MainMenuScene::menuStartCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
        static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
    //auto GLS1 = GameLoadingScene1::createScene();   // ת��GameLoadingScene1
    //Director::getInstance()->replaceScene(TransitionFade::create(1, GLS1));//mainmenu�ѱ��ͷ�
    auto GS = GameScene::createScene();   // ת��GameScene
    Director::getInstance()->replaceScene(TransitionFade::create(1, GS));//GSL2�ѱ��ͷ�
}

/****************************
* Name ��MainMenuScene::menuMapCallback
* Summary �����˵��̵갴ť�ص�
* return ��
****************************/
void MainMenuScene::menuMapCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
        static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
    auto storeScene = StoreScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, storeScene));//mainmenuδ���ͷ� ʹ��popScene����
}

/****************************
* Name ��MainMenuScene::menuHerosCallback
* Summary �����˵����ﰴť�ص�
* return ��
****************************/
void MainMenuScene::menuHerosCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
        static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
    auto heroScene = HeroScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, heroScene));//mainmenuδ���ͷ� ʹ��popScene����
}

/****************************
* Name ��MainMenuScene::menuSettingsCallback
* Summary �����˵����ð�ť�ص�
* return ��
****************************/
void MainMenuScene::menuSettingsCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
        static_cast<float>(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
    auto settingsScene = SettingsScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, settingsScene));//mainmenuδ���ͷ� ʹ��popScene����
}

/****************************
* Name ��MainMenuScene::playerMassageCallback
* Summary �������Ϣ��ť�ص�
* return ��
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
* Name ��MainMenuScene::onEnterTransitionDidFinish()
* Summary ������ģ��
* return ��
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