//作者 : 王鹏
//日期 : 2022-5-14
#include "SettingsScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

/****************************
* Name ：SettingsScene::createScene
* Summary ：创建场景
* return ：场景类指针
****************************/
Scene* SettingsScene::createScene()
{
    return SettingsScene::create();
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
/****************************
* Name ：SettingsScene::init
* Summary ：主菜单初始化
* return ：初始化成功与否
****************************/
bool SettingsScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*=====================创建返回按钮开始======================*/

    //创建返回按钮
    auto settingsBackItem = MenuItemImage::create(
        "backSettingsNormal.png",
        "backSettingsSelected.png",
        CC_CALLBACK_1(SettingsScene::settingsBackCallback, this));

    if (settingsBackItem == nullptr ||
        settingsBackItem->getContentSize().width <= 0 ||
        settingsBackItem->getContentSize().height <= 0)
    {//错误处理
        problemLoading("'backSettingsNormal.png' and 'backSettingsSelected.png'");
    }
    else
    {//设置位置
        float x = SETTINGS_BACK_ITEM_POSITION_X;
        float y = SETTINGS_BACK_ITEM_POSITION_Y;
        settingsBackItem->setPosition(Vec2(x, y));
    }
    //创建返回菜单
    auto backMenu = Menu::create(settingsBackItem, NULL);
    backMenu->setPosition(Vec2::ZERO);
    this->addChild(backMenu, 2);
    /*=====================创建关闭按钮结束====================*/

    /*=====================创建标题开始======================*/

    auto settingsNameLabel = Label::createWithTTF(
        "SETTINGS",
        "fonts/PixeloidSans.ttf",
        SETTINGS_NAME_LABEL_SIZE
    );//创建文本
    if (settingsNameLabel == nullptr)
    {
        problemLoading("'fonts/PixeloidSans.ttf'");
    }
    else
    {
        const Color4B settingsNameLabelColor(SETTINGS_TEXT_RGB_COLOR, 255);//创建4B颜色
        settingsNameLabel->setTextColor(settingsNameLabelColor);
        settingsNameLabel->setPosition(
            Vec2(SETTINGS_NAME_LABEL_POSITION_X,
                SETTINGS_NAME_LABEL_POSITION_Y)
        );

        this->addChild(settingsNameLabel, 1);
    }
    /*=====================创建标题结束======================*/

    /*===================创建设置选项开始====================*
    MenuItemFont::setFontName("fonts/PixeloidMono.ttf");
    MenuItemFont::setFontSize(64);
    const Color3B settingsItemColor(SETTINGS_TEXT_RGB_COLOR);//创建3B颜色

    //创建单个菜单项
    MenuItemFont* item = MenuItemFont::create(
        "",
        CC_CALLBACK_1(SettingsScene::, this)
    );


    //创建菜单 把菜单项放进去
    Menu* settingsMenu = Menu::create(item, NULL);
    settingsMenu->setPosition(SETTINGS_SETTINGSMENU_POSITION_X,
        SETTINGS_SETTINGSMENU_POSITION_Y);
    settingsMenu->alignItemsVertically();
    settingsMenu->setColor(settingsItemColor);

    this->addChild(settingsMenu, 1);
    /*===================创建主菜单选项结束====================*/

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
    return true;
}
/****************************
* Name ：SettingsScene::settingsBackCallback
* Summary ：设置返回按钮回调
* return ：
****************************/
void SettingsScene::settingsBackCallback(Ref* pSender)
{
    auto mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, mainMenuScene));
}
