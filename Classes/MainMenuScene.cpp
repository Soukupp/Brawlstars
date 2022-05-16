//���� : ����
//���� : 2022-5-14
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

/****************************
* Name ��MainMenu::createScene
* Summary ����������
* return ��������ָ��
****************************/
Scene* MainMenu::createScene()
{
    return MainMenu::create();
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
* Name ��MainMenu::init
* Summary �����˵���ʼ��
* return ����ʼ���ɹ����
****************************/
bool MainMenu::init()
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
    //�����رղ˵�
    auto closeMenu = Menu::create(mainMenuCloseItem, NULL);
    closeMenu->setPosition(Vec2::ZERO);
    this->addChild(closeMenu, 1);
    /*=====================�����رհ�ť����====================*/

    /*=====================������Ϸ����ʼ======================*/

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
    /*=====================������Ϸ������======================*/

    /*===================�������˵�ѡ�ʼ====================*/
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
    /*===================�������˵�ѡ�����====================*/

    /*=====================��������ͼ��ʼ======================*/
    auto sprite = Sprite::create("mainmenuBackground.png");
    if (sprite == nullptr)
    {
        problemLoading("'mainmenuBackground.png'");
    }
    else
    {
        //������ͼ��������
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, 
            visibleSize.height / 2 + origin.y));

        this->addChild(sprite, 0);
    }
    /*=====================��������ͼ����======================*/
    return true;
}
/****************************
* Name ��MainMenu::menuCloseCallback
* Summary �����˵��رհ�ť�ص�
* return ��
****************************/
void MainMenu::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

/****************************
* Name ��menuStartCallback
* Summary �����˵���ʼ��ť�ص�
* return ��
****************************/
void menuStartCallback(cocos2d::Ref* pSender)
{
	auto gameScene = GameScene::createScene();
	Director::getInstance()->
}
/****************************
* Name ��menuStoreCallback
* Summary �����˵��̵갴ť�ص�
* return ��
****************************/
void menuStoreCallback(cocos2d::Ref* pSender)
{
	auto storeScene = StoreScene::createScene();
	Director::getInstance()->pushScene(storeScene);
}
/****************************
* Name ��menuHerosCallback
* Summary �����˵����ﰴť�ص�
* return ��
****************************/
void menuHerosCallback(cocos2d::Ref* pSender)
{
	auto playerScene = PlayerScene::createScene();
	Director::getInstance()->pushScene(playerScene);
}
/****************************
* Name ��menuSettingsCallback
* Summary �����˵����ð�ť�ص�
* return ��
****************************/
void menuSettingsCallback(cocos2d::Ref* pSender)
{
}
