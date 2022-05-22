//作者：束赫
//时间：2022-5-20

#include "HeroScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

static int slectedHero = 0;   //用户选择的hero，分别用1，2，3，4表示
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
    auto background = Sprite::create("settingsBackground.png");
    if (background == nullptr)
    {
        problemLoading("'settingsBackground.png'");
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
        "backSettingsNormal.png",
        "backSettingsSelected.png",
        CC_CALLBACK_1(HeroScene::heroBackCallback, this));

    if (heroBackItem == nullptr ||
        heroBackItem->getContentSize().width <= 0 ||
        heroBackItem->getContentSize().height <= 0)
    {//错误处理
        problemLoading("'backSettingsNormal.png' and 'backSettingsSelected.png'");
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
    auto* hero1LabelImage = MenuItemImage::create("heroLabelNormal.png",
        "heroLabelSelected.png", this, menu_selector(HeroScene::selectHero1Callback));

    auto* hero1LabelText = LabelTTF::create("HERO1", "Maiandra GD", 35);
    auto* hero1Label = MenuItemLabel::create(hero1LabelText,
        this, menu_selector(HeroScene::selectHero1Callback));

    auto* hero1Button = Menu::create(hero1LabelImage, hero1Label, NULL);
    hero1Button->setPosition(HERO1_SELECTED_BUTTON_POSITION_X, HERO1_SELECTED_BUTTON_POSITION_Y);

    this->addChild(hero1Button);

    //HERO2
    auto* hero2LabelImage = MenuItemImage::create("heroLabelNormal.png",
        "heroLabelSelected.png", this, menu_selector(HeroScene::selectHero2Callback));

    auto* hero2LabelText = LabelTTF::create("HERO2", "Maiandra GD", 35);
    auto* hero2Label = MenuItemLabel::create(hero2LabelText,
        this, menu_selector(HeroScene::selectHero2Callback));

    auto* hero2Button = Menu::create(hero2LabelImage, hero2Label, NULL);
    hero2Button->setPosition(HERO2_SELECTED_BUTTON_POSITION_X, HERO2_SELECTED_BUTTON_POSITION_Y);

    this->addChild(hero2Button);

    //HERO3
    auto* hero3LabelImage = MenuItemImage::create("heroLabelNormal.png",
        "heroLabelSelected.png", this, menu_selector(HeroScene::selectHero3Callback));

    auto* hero3LabelText = LabelTTF::create("HERO3", "Maiandra GD", 35);
    auto* hero3Label = MenuItemLabel::create(hero3LabelText,
        this, menu_selector(HeroScene::selectHero3Callback));

    auto* hero3Button = Menu::create(hero3LabelImage, hero3Label, NULL);
    hero3Button->setPosition(HERO3_SELECTED_BUTTON_POSITION_X, HERO3_SELECTED_BUTTON_POSITION_Y);

    this->addChild(hero3Button);

    //HERO4
    auto* hero4LabelImage = MenuItemImage::create("heroLabelNormal.png",
        "heroLabelSelected.png", this, menu_selector(HeroScene::selectHero4Callback));

    auto* hero4LabelText = LabelTTF::create("HERO4", "Maiandra GD", 35);
    auto* hero4Label = MenuItemLabel::create(hero4LabelText,
        this, menu_selector(HeroScene::selectHero3Callback));

    auto* hero4Button = Menu::create(hero4LabelImage, hero4Label, NULL);
    hero4Button->setPosition(HERO4_SELECTED_BUTTON_POSITION_X, HERO4_SELECTED_BUTTON_POSITION_Y);

    this->addChild(hero4Button);

    //未确认状态设置
    auto* normal = Sprite::create("rightSignNormal.png");
    //点击状态设置
    auto* moving = Sprite::create("rightSignMoving.png");
    //禁用状态设置
    auto* selected = Sprite::create("rightSignSelected.png");
    _confirmButton = MenuItemSprite::create(normal, moving, selected);
    auto* menu = CCMenu::create(_confirmButton, NULL);
    menu->setPosition(HERO_CONFIRM_BUTTON_POSITION_X, HERO_CONFIRM_BUTTON_POSITION_Y);
    this->addChild(menu);
    _confirmButton->setTarget(this, menu_selector(HeroScene::selectHeroConfirmCallback));
    _confirmButton->setScale(0.5);

    return true;
    /*=====================创建英雄选项标签开始======================*/
    
}
/****************************
* Name ：heroBackCallback
* Summary ：返回主菜单
* return ：
****************************/
void HeroScene::heroBackCallback(cocos2d::Ref* pSender)
{
    auto* mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, mainMenuScene));//过场动画设计
}
/****************************
* Name ：selectHero1Callback
* Summary ：进入hero1界面回调函数
* return ：
****************************/
void HeroScene::selectHero1Callback(cocos2d::Ref* pSender)
{
    _chooseNumber = 1;                       //表示此时在hero1界面
    if (slectedHero == 1)                    //如果确认选择hero1
        _confirmButton->setEnabled(false);   //按钮设置为禁用
    else
        _confirmButton->setEnabled(true);

}
//同上
void HeroScene::selectHero2Callback(cocos2d::Ref* pSender)
{
    _chooseNumber = 2;
    if (slectedHero == 2)
        _confirmButton->setEnabled(false);
    else
        _confirmButton->setEnabled(true);
}
//同上
void HeroScene::selectHero3Callback(cocos2d::Ref* pSender)
{
    _chooseNumber = 3;
    if (slectedHero == 3)
        _confirmButton->setEnabled(false);
    else
        _confirmButton->setEnabled(true);
}
//同上
void HeroScene::selectHero4Callback(cocos2d::Ref* pSender)
{
    _chooseNumber = 4;
    if (slectedHero == 4)
        _confirmButton->setEnabled(false);
    else
        _confirmButton->setEnabled(true);
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
        slectedHero = 1;
        break;
    case 2:
        slectedHero = 2;
        break;
    case 3:
        slectedHero = 3;
        break;
    case 4:
        slectedHero = 4;
        break;
    }
    _confirmButton->setEnabled(false);
}