//���� : ��Ԫ��
//���� : 2022-5-18

#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

/****************************
* Name ��GameOverScene::createScene
* Summary ������������ʵ��layer
* return ��������ָ��
****************************/
Scene* GameOverScene::createScene()
{
    auto gameOverScene = Scene::create();
    auto gameOverLayer = GameOverScene::create();
    gameOverScene->addChild(gameOverLayer);
    return gameOverScene;
}

/****************************
* Name ��problemLoading
* Summary �������ӡ
* return ��
****************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

/****************************
* Name ��GameOverScene::init
* Summary ����Ϸ����������ʼ��
* return ����ʼ���ɹ����
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

    const Color4B labelTextColor(255, 255, 255, 255);//����4B��ɫ
    const Color4B labelOutlineColor(0, 0, 0, 255);//����4B��ɫ

    auto rankString = "YOUR POSITION : NO." + std::to_string(UserDefault::getInstance()->getIntegerForKey("PlayerRank"));
    auto rankLabel = Label::createWithTTF(rankString, "fonts/Marker Felt.ttf", 72);
    if (rankLabel == nullptr)
    {
        log("rankLabel false");
    }
    else
    {
        log("rankLabel true");
        
        rankLabel->setTextColor(labelTextColor);
        rankLabel->enableOutline(labelOutlineColor,2);
        rankLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 3 * 2));
        this->addChild(rankLabel, 1);
    }


    auto hitString = "YOU KILLED : " + std::to_string(UserDefault::getInstance()->getIntegerForKey("HitNum")) + " ENEMY";
    auto hitLabel = Label::createWithTTF(hitString, "fonts/Marker Felt.ttf", 60);
    if (hitLabel == nullptr)
    {
        log("hitLabel false");
    }
    else
    {
        log("hitLabel true");
 
        hitLabel->setTextColor(labelTextColor);
        hitLabel->enableOutline(labelOutlineColor, 2);
        hitLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));
        this->addChild(hitLabel, 1);
    }
    
    return true;
}

/****************************
* Name ��GameOverScene::menuCloseCallback
* Summary ������Ŀ¼����
* return ����
****************************/
void GameOverScene::menuCloseCallback(Ref* pSender)
{
    auto MMS = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(MMS);
}
