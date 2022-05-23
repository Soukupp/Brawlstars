//���� : ����
//���� : 2022-5-14
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

static bool ifMusicBegin = true;
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
    //�����رղ˵�
    auto closeMenu = Menu::create(mainMenuCloseItem, NULL);
    closeMenu->setPosition(Vec2::ZERO);
    this->addChild(closeMenu, 2);
    /*=====================�����رհ�ť����====================*/
    /*=====================�����������ֿ�ʼ=======================*/

    if(ifMusicBegin)
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/retro_fight_ingame_01.mp3",true);
    ifMusicBegin = false;
    /*=====================�����������ֽ���=======================*/

    /*=====================������Ϸ����ʼ======================*/

    auto gameNameLabel = Label::createWithTTF(
        "BRAWLSTARS", 
        "fonts/PixeloidSans.ttf", 
        MAINMENU_GAMENAME_LABEL_SIZE
    );//�����ı�
    if (gameNameLabel == nullptr)
    {
        problemLoading("'fonts/PixeloidSans.ttf'");
    }
    else
    {
        const Color4B gameNameLabelColor(MAINMENU_TEXT_RGB_COLOR,255);//����4B��ɫ
        gameNameLabel->setTextColor(gameNameLabelColor);
        gameNameLabel->setPosition(
            Vec2(MAINMENU_GAMENAME_LABEL_POSITION_X,
            MAINMENU_GAMENAME_LABEL_POSITION_Y)
        );

        this->addChild(gameNameLabel, 1);
    }
    /*=====================������Ϸ������======================*/

    /*===================�������˵�ѡ�ʼ====================*/
    MenuItemFont::setFontName("fonts/PixeloidMono.ttf");
    MenuItemFont::setFontSize(64);
    const Color3B menuItemColor(MAINMENU_TEXT_RGB_COLOR);//����3B��ɫ

    //���������˵���
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

    //�����˵� �Ѳ˵���Ž�ȥ
    Menu* mainMenu = Menu::create(itemStart, itemStore, itemHeros, itemSettings, NULL);
    mainMenu->setPosition(MAINMENU_MAINMENU_POSITION_X,
        MAINMENU_MAINMENU_POSITION_Y);
    mainMenu->alignItemsVertically();
    mainMenu->setColor(menuItemColor);

    this->addChild(mainMenu,1);
    /*===================�������˵�ѡ�����====================*/

    /*=====================��������ͼ��ʼ======================*/
    auto background = Sprite::create("background/mainmenuBackground.png");
    if (background == nullptr)
    {
        problemLoading("'background/mainmenuBackground.png'");
    }
    else
    {
        //������ͼ��������
        background->setPosition(Vec2(MAINMENU_BACKGROUND_POSITION_X,
            MAINMENU_BACKGROUND_POSITION_Y));

        this->addChild(background, 0);
    }
    /*=====================��������ͼ����======================*/
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
* Name ��menuStartCallback
* Summary �����˵���ʼ��ť�ص�
* return ��
****************************/
void MainMenuScene::menuStartCallback(cocos2d::Ref* pSender)
{
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
    auto settingsScene = SettingsScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, settingsScene));//mainmenuδ���ͷ� ʹ��popScene����
}

