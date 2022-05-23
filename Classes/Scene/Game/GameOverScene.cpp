//作者 : 李元特
//日期 : 2022-5-18

#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

/****************************
* Name ：GameOverScene::createScene
* Summary ：创建场景，实质layer
* return ：场景类指针
****************************/
Scene* GameOverScene::createScene()
{
    auto GameOverScene = Scene::create();
    auto GameOverLayer = GameOverScene::create();
    GameOverScene->addChild(GameOverLayer);
    return GameOverScene;
}

/****************************
* Name ：problemLoading
* Summary ：错误打印
* return ：
****************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

/****************************
* Name ：GameOverScene::init
* Summary ：游戏结束场景初始化
* return ：初始化成功与否
****************************/
bool GameOverScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto GameOverBackground = Sprite::create("background/GameOverBackground.png");
    GameOverBackground->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(GameOverBackground, 0);


    auto closeItem = MenuItemImage::create(
        "ui/CloseNormal.png",
        "ui/CloseSelected.png",
        CC_CALLBACK_1(GameOverScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'ui/CloseNormal.png' and 'ui/CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("Victory!", "fonts/Marker Felt.ttf", 60);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    return true;
}

/****************************
* Name ：GameOverScene::menuCloseCallback
* Summary ：返回目录界面
* return ：无
****************************/
void GameOverScene::menuCloseCallback(Ref* pSender)
{
    auto MMS = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(MMS);
}
