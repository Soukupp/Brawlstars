//作者：束赫
//时间：2022-5-20

#include "HeroScene.h"
#include "SimpleAudioEngine.h"
#include "Entity/Player/Player.h"

USING_NS_CC;

/****************************
* Name ：HeroScene::createScene
* Summary ：创建场景
* return ：场景类指针
****************************/
Scene* HeroScene::createScene()
{
    return HeroScene::create();
}

/****************************
* Name ：problemLoading
* Summary ：错误打印
* return ：
****************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SettingsScene.cpp\n");
}

bool HeroScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*=====================创建背景图开始======================*/
    auto background = Sprite::create("background/settingsBackground.png");
    if (background == nullptr)
    {
        problemLoading("'background/settingsBackground.png'");
    }
    else
    {
        //将背景图放在中央
        background->setPosition(Vec2(SETTINGS_BACKGROUND_POSITION_X,
            SETTINGS_BACKGROUND_POSITION_Y));

        this->addChild(background, 0);
    }
    /*=====================创建背景图结束======================*/
     /*=====================创建返回按钮开始======================*/

    //创建返回按钮
    auto heroBackItem = MenuItemImage::create(
        "ui/backSettingsNormal.png",
        "ui/backSettingsSelected.png",
        CC_CALLBACK_1(HeroScene::heroBackCallback, this));

    if (heroBackItem == nullptr ||
        heroBackItem->getContentSize().width <= 0 ||
        heroBackItem->getContentSize().height <= 0)
    {//错误处理
        problemLoading("'ui/backSettingsNormal.png' and 'ui/backSettingsSelected.png'");
    }
    else
    {//设置位置
        float x = HERO_BACK_ITEM_POSITION_X;
        float y = HERO_BACK_ITEM_POSITION_Y;
        heroBackItem->setPosition(Vec2(x, y));
    }
    //创建返回菜单
    auto backMenu = Menu::create(heroBackItem, NULL);
    backMenu->setPosition(Vec2::ZERO);
    this->addChild(backMenu, 2);
    /*=====================创建返回按钮结束======================*/

    /*=====================创建标题开始======================*/

    auto heroNameLabel = Label::createWithTTF(
        "HEROS",
        "fonts/PixeloidSans.ttf",
        SETTINGS_NAME_LABEL_SIZE
    );//创建文本
    if (heroNameLabel == nullptr)
    {
        problemLoading("'fonts/PixeloidSans.ttf'");
    }
    else
    {
        const Color4B heroNameLabelColor(SETTINGS_TEXT_RGB_COLOR, 255);//创建4B颜色
        heroNameLabel->setTextColor(heroNameLabelColor);
        heroNameLabel->setPosition(
            Vec2(HERO_NAME_LABEL_POSITION_X,
                HERO_NAME_LABEL_POSITION_Y));

        this->addChild(heroNameLabel, 1);
    }
    /*=====================创建标题结束======================*/

    /*=====================创建英雄选项标签开始======================*/
    //HERO1
    auto* hero1LabelImage = MenuItemImage::create("ui/heroLabelNormal.png",
        "ui/heroLabelSelected.png", this, menu_selector(HeroScene::selectHero1Callback));

    auto* hero1LabelText = LabelTTF::create("HERO1", "Maiandra GD", 35);
    auto* hero1Label = MenuItemLabel::create(hero1LabelText,
        this, menu_selector(HeroScene::selectHero1Callback));

    auto* hero1Button = Menu::create(hero1LabelImage, hero1Label, NULL);
    hero1Button->setPosition(HERO1_SELECTED_BUTTON_POSITION_X, HERO1_SELECTED_BUTTON_POSITION_Y);

    this->addChild(hero1Button);

    //HERO2
    auto* hero2LabelImage = MenuItemImage::create("ui/heroLabelNormal.png",
        "ui/heroLabelSelected.png", this, menu_selector(HeroScene::selectHero2Callback));

    auto* hero2LabelText = LabelTTF::create("HERO2", "Maiandra GD", 35);
    auto* hero2Label = MenuItemLabel::create(hero2LabelText,
        this, menu_selector(HeroScene::selectHero2Callback));

    auto* hero2Button = Menu::create(hero2LabelImage, hero2Label, NULL);
    hero2Button->setPosition(HERO2_SELECTED_BUTTON_POSITION_X, HERO2_SELECTED_BUTTON_POSITION_Y);

    this->addChild(hero2Button);

    //HERO3
    auto* hero3LabelImage = MenuItemImage::create("ui/heroLabelNormal.png",
        "ui/heroLabelSelected.png", this, menu_selector(HeroScene::selectHero3Callback));

    auto* hero3LabelText = LabelTTF::create("HERO3", "Maiandra GD", 35);
    auto* hero3Label = MenuItemLabel::create(hero3LabelText,
        this, menu_selector(HeroScene::selectHero3Callback));

    auto* hero3Button = Menu::create(hero3LabelImage, hero3Label, NULL);
    hero3Button->setPosition(HERO3_SELECTED_BUTTON_POSITION_X, HERO3_SELECTED_BUTTON_POSITION_Y);

    this->addChild(hero3Button);

    //HERO4
    auto* hero4LabelImage = MenuItemImage::create("ui/heroLabelNormal.png",
        "ui/heroLabelSelected.png", this, menu_selector(HeroScene::selectHero4Callback));

    auto* hero4LabelText = LabelTTF::create("HERO4", "Maiandra GD", 35);
    auto* hero4Label = MenuItemLabel::create(hero4LabelText,
        this, menu_selector(HeroScene::selectHero3Callback));

    auto* hero4Button = Menu::create(hero4LabelImage, hero4Label, NULL);
    hero4Button->setPosition(HERO4_SELECTED_BUTTON_POSITION_X, HERO4_SELECTED_BUTTON_POSITION_Y);

    this->addChild(hero4Button);

    //未确认状态设置
    auto* normal = Sprite::create("ui/rightSignNormal.png");
    //点击状态设置
    auto* moving = Sprite::create("ui/rightSignMoving.png");
    //禁用状态设置
    auto* selected = Sprite::create("ui/rightSignSelected.png");
    _confirmButton = MenuItemSprite::create(normal, moving, selected);
    auto* menu = CCMenu::create(_confirmButton, NULL);
    menu->setPosition(HERO_CONFIRM_BUTTON_POSITION_X, HERO_CONFIRM_BUTTON_POSITION_Y);
    this->addChild(menu);
    _confirmButton->setTarget(this, menu_selector(HeroScene::selectHeroConfirmCallback));
    _confirmButton->setScale(0.5);

   /*=====================创建英雄选项标签结束======================*/

   //如果玩家已经选择了英雄，那么优先展示该英雄的动画
       _selectedHero = UserDefault::getInstance()->getIntegerForKey("selectedHero");
    if (_selectedHero) {
        switch (_selectedHero) {
        case 1:
            animate1();
            break;
        case 2:
            animate2();
            break;
        case 3:
            animate3();
            break;
        case 4:
            break;
        }
        _confirmButton->setEnabled(false);
    }


    return true;
 
    
}
/****************************
* Name ：heroBackCallback
* Summary ：返回主菜单
* return ：
****************************/
void HeroScene::heroBackCallback(cocos2d::Ref* pSender)
{
    AnimationCache::destroyInstance();
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    TextureCache::getInstance()->removeUnusedTextures();
    auto mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, mainMenuScene));//过场动画设计
}
/****************************
* Name ：selectHero1Callback
* Summary ：进入hero1界面回调函数
* return ：
****************************/
void HeroScene::selectHero1Callback(cocos2d::Ref* pSender)
{
    if (_selectedHero == 1)                    //如果确认选择hero1
        _confirmButton->setEnabled(false);   //按钮设置为禁用
    else
        _confirmButton->setEnabled(true);

    if (_chooseNumber != 1) {

        if (hero2 != nullptr)
            hero2->setVisible(false);
        if (hero3 != nullptr)
            hero3->setVisible(false);
        if (hero4 != nullptr)
            hero4->setVisible(false);

        animate1();
        _chooseNumber = 1;
    }

}
//同上

void HeroScene::selectHero2Callback(cocos2d::Ref* pSender)
{
    
    if (_selectedHero == 2)
        _confirmButton->setEnabled(false);
    else
        _confirmButton->setEnabled(true);

    if (_chooseNumber != 2) {

        if (hero1 != nullptr)
            hero1->setVisible(false);
        if (hero3 != nullptr)
            hero3->setVisible(false);
        if (hero4 != nullptr)
            hero4->setVisible(false);

        animate2();
        _chooseNumber = 2;

    }
}
//同上
void HeroScene::selectHero3Callback(cocos2d::Ref* pSender)
{
    if (_selectedHero == 3)
        _confirmButton->setEnabled(false);
    else
        _confirmButton->setEnabled(true);
    if (_chooseNumber != 3) {

        if (hero1 != nullptr)
            hero1->setVisible(false);
        if (hero2 != nullptr)
            hero2->setVisible(false);
        if (hero4 != nullptr)
            hero4->setVisible(false);

        animate3();
        _chooseNumber = 3;
    }

}
//同上
void HeroScene::selectHero4Callback(cocos2d::Ref* pSender)
{
    _chooseNumber = 4;
    if (_selectedHero == 4)
        _confirmButton->setEnabled(false);
    else
        _confirmButton->setEnabled(true);
    if (_chooseNumber != 4) {
        if (hero1 != nullptr)
            hero1->setVisible(false);
        if (hero2 != nullptr)
            hero2->setVisible(false);
        if (hero3 != nullptr)
            hero3->setVisible(false);

        animate4();
        _chooseNumber = 4;
    }

}
/****************************
* Name ：selectHeroConfirmCallback
* Summary ：点击确认按钮的回调函数
* return ：
****************************/
void HeroScene::selectHeroConfirmCallback(cocos2d::Ref* pSender)
{
    switch (_chooseNumber) {
    case 1:
        UserDefault::getInstance()->setIntegerForKey("selectedHero", 1);
        break;
    case 2:
        UserDefault::getInstance()->setIntegerForKey("selectedHero", 2);
        break;
    case 3:
        UserDefault::getInstance()->setIntegerForKey("selectedHero", 3);
        break;
    case 4:
        UserDefault::getInstance()->setIntegerForKey("selectedHero", 4);
        break;
    }
    _selectedHero= UserDefault::getInstance()->getIntegerForKey("selectedHero");
    _confirmButton->setEnabled(false);
}
/****************************
* Name ：animate1
* Summary ：hero1动画实现
* return ：
****************************/
void HeroScene::animate1()
{
    hero1 = Sprite::create("Character/Hero1/hero.png");
    hero1->setPosition(700, 350);
    addChild(hero1);
    auto* m_frameCache = CCSpriteFrameCache::getInstance();
    m_frameCache->addSpriteFramesWithFile("Character/Hero1/hero1_Start.plist", "Character/Hero1/hero1_Start.png");

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
* Name ：animate2
* Summary ：hero2动画实现
* return ：
****************************/
void HeroScene::animate2()
{
    hero2 = Sprite::create("Character/Hero2/hero.png");
    hero2->setPosition(700, 350);
    addChild(hero2);
    auto* m_frameCache = CCSpriteFrameCache::getInstance();
    m_frameCache->addSpriteFramesWithFile("Character/Hero2/hero2_Start.plist", "Character/Hero2/hero2_Start.png");

    Vector<CCSpriteFrame*> hero2FrameArray;
    for (int i = 1; i < 8; i++)
    {
        auto frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("skill0%d.png", i)->getCString());
        hero2FrameArray.pushBack(frame);
    }
    auto* animation1 = Animation::createWithSpriteFrames(hero2FrameArray);
    animation1->setDelayPerUnit(0.1f);
    animation1->setRestoreOriginalFrame(true);
    hero2->setScale(5.0f);
    auto* action1 = Animate::create(animation1);

    hero2->runAction(action1);
}
/****************************
* Name ：animate3
* Summary ：hero3动画实现
* return ：
****************************/
void HeroScene::animate3()
{
    hero3 = Sprite::create("Character/Hero3/hero.png");
    hero3->setPosition(700, 350);
    addChild(hero3);
    auto* m_frameCache = CCSpriteFrameCache::getInstance();
    m_frameCache->addSpriteFramesWithFile("Character/Hero3/hero3_Start.plist", "Character/Hero3/hero3_Start.png");

    Vector<CCSpriteFrame*> hero3FrameArray;
    for (int i = 1; i < 7; i++)
    {
        auto frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("Idle_0%d.png", i)->getCString());
        hero3FrameArray.pushBack(frame);
    }
    auto* animation = Animation::createWithSpriteFrames(hero3FrameArray);
    animation->setDelayPerUnit(0.1f);
    animation->setLoops(-1);
    hero3->setScale(3.0f);
    auto* action = Animate::create(animation);
    hero3->runAction(action);
}
/****************************
* Name ：animate4
* Summary ：hero4动画实现
* return ：
****************************/
void HeroScene::animate4()
{

}