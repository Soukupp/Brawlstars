//���� : ����
//���� : 2022-5-14
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

static bool firstSet = true;
static bool firstPlay = true;

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

    /*=====================�����رհ�ť��ʼ======================*/

    //�����رհ�ť
    auto mainMenuCloseItem = MenuItemImage::create(
        "ui/exitMainMenuNormal.png",
        "ui/exitMainMenuSelected.png",
        CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));

    if (mainMenuCloseItem == nullptr ||
        mainMenuCloseItem->getContentSize().width <= 0 ||
        mainMenuCloseItem->getContentSize().height <= 0)
    {//������
        problemLoading("'ui/exitMainMenuNormal.png' and 'ui/exitMainMenuSelected.png'");
    }
    else
    {//����λ��
        float x = MAINMENU_CLOSE_ITEM_POSITION_X;
        float y = MAINMENU_CLOSE_ITEM_POSITION_Y;
        mainMenuCloseItem->setPosition(Vec2(x, y));
    }

    auto mainMenuInfoItem = MenuItemImage::create(
        "ui/button_info.png", 
        "ui/button_info.png",
        CC_CALLBACK_1(MainMenuScene::menuInfoCallback, this));
    if (mainMenuInfoItem == nullptr ||
        mainMenuInfoItem->getContentSize().width <= 0 ||
        mainMenuInfoItem->getContentSize().height <= 0)
    {//������
        problemLoading("'ui/button_info.png' and 'ui/button_info.png'");
    }
    else
    {//����λ��
        float x = MAINMENU_INFO_ITEM_POSITION_X;
        float y = MAINMENU_INFO_ITEM_POSITION_Y;
        mainMenuInfoItem->setPosition(Vec2(x, y));
    }

    //�����رղ˵�
    auto closeMenu = Menu::create(mainMenuCloseItem, mainMenuInfoItem, NULL);
    closeMenu->setPosition(Vec2::ZERO);
    this->addChild(closeMenu, 2);
    /*=====================�����رհ�ť����====================*/



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
        const Color4B gameNameLabelColor(MAINMENU_TITLE_RGB_COLOR,255);//����4B��ɫ
        gameNameLabel->setTextColor(gameNameLabelColor);
        gameNameLabel->setPosition(
            Vec2(MAINMENU_GAMENAME_LABEL_POSITION_X,
            MAINMENU_GAMENAME_LABEL_POSITION_Y)
        );

        this->addChild(gameNameLabel, 1);
    }
    /*=====================������Ϸ������======================*/

    /*===================�������˵�ѡ�ʼ====================*/
    MenuItemFont::setFontName("fonts/Segoe Print.ttf");
    MenuItemFont::setFontSize(50);
    const Color3B menuItemColor(MAINMENU_TEXT_RGB_COLOR);//����3B��ɫ

    //���������˵���
    MenuItemFont* itemStart = MenuItemFont::create(
        "START",
        CC_CALLBACK_1(MainMenuScene::menuStartCallback, this)
    );
    MenuItemFont* itemStore = MenuItemFont::create(
        "MAP",
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

    //�����˵� �Ѳ˵���Ž�ȥ
    Menu* mainMenu = Menu::create(itemStart, itemStore, itemHeros, itemSettings, NULL);
    mainMenu->setPosition(MAINMENU_MAINMENU_POSITION_X,
        MAINMENU_MAINMENU_POSITION_Y);
    mainMenu->alignItemsVertically();
    mainMenu->setColor(menuItemColor);

    this->addChild(mainMenu,1);
    /*===================�������˵�ѡ�����====================*/


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
    
    /*=====================����UseDefault��ʼ======================*/
    if (firstSet) {
        UserDefault::getInstance()->setBoolForKey("ifPlayMusic", true);
        UserDefault::getInstance()->setBoolForKey("ifShowFPS", false);
        UserDefault::getInstance()->setIntegerForKey("musicVolume", 50);
        UserDefault::getInstance()->setIntegerForKey("selectedHero", 1);

        firstSet = false;
    }

    /*=====================����UseDefault����======================*/

    /*=====================�����������ֿ�ʼ=======================*/

    if (firstPlay)
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/first_music.mp3", true);
    firstPlay = false;
    if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/first_music.mp3", true);
    }
    /*else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/first_music.mp3", true);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }*/
    /*=====================�����������ֽ���=======================*/

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
* Summary �����˵��رհ�ť�ص�
* return ��
****************************/
void MainMenuScene::menuInfoCallback(Ref* pSender)
{
    Director::getInstance()->end();
}


/****************************
* Name ��menuStartCallback
* Summary �����˵���ʼ��ť�ص�
* return ��
****************************/
void MainMenuScene::menuStartCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
	auto gameScene = GameScene::createScene();   // ת��GameScene
    Director::getInstance()->replaceScene(gameScene);//mainmenu�ѱ��ͷ�
}


/****************************
* Name ��menuStoreCallback
* Summary �����˵��̵갴ť�ص�
* return ��
****************************/
void MainMenuScene::menuStoreCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
	auto storeScene = StoreScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, storeScene));//mainmenuδ���ͷ� ʹ��popScene����
}


/****************************
* Name ��menuHerosCallback
* Summary �����˵����ﰴť�ص�
* return ��
****************************/
void MainMenuScene::menuHerosCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
	auto heroScene = HeroScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, heroScene));//mainmenuδ���ͷ� ʹ��popScene����
}


/****************************
* Name ��menuSettingsCallback
* Summary �����˵����ð�ť�ص�
* return ��
****************************/
void MainMenuScene::menuSettingsCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    auto settingsScene = SettingsScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, settingsScene));//mainmenuδ���ͷ� ʹ��popScene����
}


void MainMenuScene::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();
    ParticleSystem* system;
    system = ParticleFireworks::create();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    system->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
    this->addChild(system,5);
}