//作者 : 李元特
//日期 : 2022-5-18

#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

/****************************
* Name ：createScene
* Summary ：创建场景，实质layer
* return ：场景类指针
****************************/
Scene* GameOverScene::createScene()
{
    auto gameOverScene = Scene::create();
    auto gameOverLayer = GameOverScene::create();
    gameOverScene->addChild(gameOverLayer);
    return gameOverScene;
}

/****************************
* Name ：init
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

    auto pDict = Tools::initDict();

    auto GameOverBackground = Sprite::create("background/GameOverBackground.png");
    GameOverBackground->setPosition(Vec2(GAMEOVER_BACKGROUND_POSITION));
    this->addChild(GameOverBackground, 0);


    auto settingsBackItem = MenuItemImage::create(
        "ui/backSettingsNormal.png",
        "ui/backSettingsSelected.png",
        CC_CALLBACK_1(GameOverScene::menuCloseCallback, this));

    if (settingsBackItem == nullptr ||
        settingsBackItem->getContentSize().width <= 0 ||
        settingsBackItem->getContentSize().height <= 0)
    {
        problemLoading("'ui/backSettingsNormal.png' and 'ui/backSettingsSelected.png'");
    }
    else
    {
        settingsBackItem->setPosition(Vec2(GAMEOVER_BACK_ITEM_POSITION_X, GAMEOVER_BACK_ITEM_POSITION_Y));
    }

    //创建返回菜单
    auto backMenu = Menu::create(settingsBackItem, NULL);
    backMenu->setPosition(Vec2::ZERO);
    this->addChild(backMenu, 6);

    auto label = Label::createWithTTF(Tools::cbyid(pDict, "GAME OVER"), Tools::cbyid(pDict, "gameoverLabelFont"), 60);
    if (label == nullptr)
    {
        problemLoading(Tools::cbyid(pDict, "gameoverLabelFont"));
    }
    else
    {
        label->setPosition(Vec2(GAMEOVER_TITLE_LABLE_POSITION_X, GAMEOVER_TITLE_LABLE_POSITION_Y));
        this->addChild(label, 1);
    }

    //确定选择的英雄，进行相关英雄展示
    int selectedHero = Tools::getUserInt("selectedHero");

    std::string playerName;
    switch (selectedHero)
    {
        case 1:
            hero1();
            playerName = Tools::cbyid(pDict, "Winston");
            break;
        case 2:
            hero2();
            playerName = Tools::cbyid(pDict, "Wrderly");
            break;
        case 3:
            hero3();
            playerName = Tools::cbyid(pDict, "Pearl");
            break;
        case 4:
            hero4();
            playerName = Tools::cbyid(pDict, "Soren");
            break;
    }

    auto crown = Sprite::create("ui/crown.png");
    crown->setPosition(GAMEOVER_CROWN_POSITION);
    addChild(crown, 5);

    std::string tip;
    if (Tools::getUserInt("PlayerRank") <= 4)
        tip = Tools::cbyid(pDict, "CONGRATULATION!");
    else

        tip = Tools::cbyid(pDict, "WHAT A PITY!");

    auto GameOverInformation = InformationPopLayer::create
    ("background/HeroInformationBackground.png", Size(570, 350), 150);
    GameOverInformation->setPosition(Vec2(150, 0)); // �������

    /*=======================文本处理开始=======================*/
    std::string gameoverInfo = tip + "\n";
    gameoverInfo += (Tools::cbyid(pDict, "HERO"));
    gameoverInfo += (" :     " + playerName + "\n");
    gameoverInfo += (Tools::cbyid(pDict, "YOUR RANK"));
    gameoverInfo += (" :     NO." + std::to_string(Tools::getUserInt("PlayerRank")) + "\n");
    gameoverInfo += (Tools::cbyid(pDict, "KILL COUNT"));
    gameoverInfo += (" :     " + std::to_string(Tools::getUserInt("HitNum")) + "\n");
    gameoverInfo += (Tools::cbyid(pDict, "CROWN NUMBER"));
    gameoverInfo += (" :    " + (std::to_string(Tools::getUserInt("PlayerRank") <= 5 ? 6 - Tools::getUserInt("PlayerRank") : 0)) + " x ");
    /*=======================文本处理结束=======================*/

    GameOverInformation->setContentText(gameoverInfo.c_str(), "fonts/Lilita one.ttf", 45, MAINMENU_INFORMATION_CONTENT_TEXT_PADDING,

        MAINMENU_INFORMATION_CONTENT_TEXT_PADDINGTOP);
    this->addChild(GameOverInformation, 4);

    return true;
}

/****************************
* Name ：menuCloseCallback
* Summary ：返回主菜单界面
* return ：无
****************************/
void GameOverScene::menuCloseCallback(Ref* pSender)
{
    auto MMS = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(MMS);
}

/****************************
* Name GameOverScene::hero1
* Summary hero1结束展示
* return : 
****************************/
void GameOverScene::hero1()
{
    auto hero1 = Sprite::create("character/Hero1/hero.png");
    hero1->setPosition(GAMEOVER_HERO_ANIMATON_POSITION);
    addChild(hero1);
    auto* m_frameCache = CCSpriteFrameCache::getInstance();
    m_frameCache->addSpriteFramesWithFile("character/Hero1/hero1_Start.plist", "character/Hero1/hero1_Start.png");
    Tools::playEffect("music/hero1.mp3");
    Tools::setEffectsVolume("musicVolume");
    Vector<CCSpriteFrame*> hero1FrameArray;
    for (int i = 4; i < 8; i++)
    {
        auto frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("adventurer-idle (%d).png", i)->getCString());
        hero1FrameArray.pushBack(frame);
    }
    auto* animation1 = Animation::createWithSpriteFrames(hero1FrameArray);
    animation1->setDelayPerUnit(0.15f);
    animation1->setRestoreOriginalFrame(true);
    animation1->setLoops(-1);
    hero1->setScale(5.0f);
    auto* action1 = Animate::create(animation1);

    hero1->runAction(action1);
}

/****************************
* Name ：hero2
* Summary ：hero2结束展示
* return ：无
****************************/
void GameOverScene::hero2()
{
    auto hero2 = Sprite::create("character/Hero2/hero.png");
    hero2->setPosition(GAMEOVER_HERO_ANIMATON_POSITION);
    addChild(hero2);
    auto* m_frameCache = CCSpriteFrameCache::getInstance();
    m_frameCache->addSpriteFramesWithFile("character/Hero2/hero2_Normal.plist", "character/Hero2/hero2_Normal.png");
    Tools::playEffect("music/hero2.mp3");
    Tools::setEffectsVolume("musicVolume");
    Vector<CCSpriteFrame*> hero2FrameArray;
    for (int i = 0; i < 8; i++)
    {
        auto frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("Idle-%d.png", i)->getCString());
        hero2FrameArray.pushBack(frame);
    }
    auto* animation1 = Animation::createWithSpriteFrames(hero2FrameArray);
    animation1->setDelayPerUnit(0.1f);
    animation1->setRestoreOriginalFrame(true);
    animation1->setLoops(-1);
    hero2->setScale(5.0f);
    auto* action1 = Animate::create(animation1);

    hero2->runAction(action1);
}

/****************************
* Name ：hero3
* Summary ：hero3结束展示
* return ：无
****************************/
void GameOverScene::hero3()
{
    auto hero3 = Sprite::create("character/Hero3/hero.png");
    hero3->setPosition(GAMEOVER_HERO_ANIMATON_POSITION);
    addChild(hero3);
    auto* m_frameCache = CCSpriteFrameCache::getInstance();
    m_frameCache->addSpriteFramesWithFile("character/Hero3/hero3_Start2.plist", "character/Hero3/hero3_Start2.png");
    Tools::playEffect("music/hero3.mp3");
    Tools::setEffectsVolume("musicVolume");
    Vector<CCSpriteFrame*> hero3FrameArray;
    for (int i = 1; i < 7; i++)
    {
        auto frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("Start3 (%d).png", i)->getCString());
        hero3FrameArray.pushBack(frame);
    }
    auto* animation = Animation::createWithSpriteFrames(hero3FrameArray);
    animation->setDelayPerUnit(0.1f);
    animation->setLoops(-1);
    hero3->setScale(2.5f);
    auto* action = Animate::create(animation);
    hero3->runAction(action);
}

/****************************
* Name ��GameOverScene::hero4
* Summary hero4结束展示
* return : 
****************************/
void GameOverScene::hero4()
{
    auto hero4 = Sprite::create("character/Hero4/hero.png");
    hero4->setPosition(200,400);
    addChild(hero4);
    auto* m_frameCache = CCSpriteFrameCache::getInstance();
    m_frameCache->addSpriteFramesWithFile("character/Hero4/hero4_Start.plist", "character/Hero4/hero4_Start.png");
    Tools::playEffect("music/hero4.mp3");
    Tools::setEffectsVolume("musicVolume");
    Vector<CCSpriteFrame*> hero4FrameArray;
    for (int i = 1; i < 9; i++)
    {
        auto frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("Start4 (%d).png", i)->getCString());
        hero4FrameArray.pushBack(frame);
    }
    auto* animation = Animation::createWithSpriteFrames(hero4FrameArray);
    animation->setDelayPerUnit(0.1f);
    animation->setLoops(-1);
    hero4->setScale(5.0f);
    auto* action = Animate::create(animation);
    hero4->runAction(action);
}
