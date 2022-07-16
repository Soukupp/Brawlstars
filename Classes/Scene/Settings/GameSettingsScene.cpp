//作者 : 王鹏
//日期 : 2022-5-14

//作者 ：李元特
//日期 : 2022-5-21
//实现 ：对接游戏界面，音量调节


#include "GameSettingsScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

static bool ifShowPlay = true;          //是否播放音乐
static bool ifShowStates = false;       //是否显示FPS

/****************************
* Name ：GameSettingsScene::createScene
* Summary ：创建场景
* return ：场景类指针
****************************/
Scene* GameSettingsScene::createScene()
{
    return GameSettingsScene::create();
}

/****************************
* Name ：GameSettingsScene::init
* Summary ：主菜单初始化
* return ：初始化成功与否
****************************/
bool GameSettingsScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto pDict = Tools::initDict();

    Tools::preloadBackgroundMusic("music/retro_fight_ingame_01.mp3"); //预加载音乐
    Tools::playEffect("music/to_a_new_scene.mp3");
    Tools::setEffectsVolume("musicVolume");
    /*=====================创建返回按钮开始======================*/

    //创建返回按钮
    auto settingsBackItem = MenuItemImage::create(
        "ui/backSettingsNormal.png",
        "ui/backSettingsSelected.png",
        CC_CALLBACK_1(GameSettingsScene::settingsBackToGameCallback, this));

    if (settingsBackItem == nullptr ||
        settingsBackItem->getContentSize().width <= 0 ||
        settingsBackItem->getContentSize().height <= 0)
    {
        problemLoading("'ui/backSettingsNormal.png' and 'ui/backSettingsSelected.png'");
    }
    else
    {
        settingsBackItem->setPosition(Vec2(GAMESETTINGS_BACK_ITEM_POSITION_X, GAMESETTINGS_BACK_ITEM_POSITION_Y));
    }
    //创建返回菜单
    auto settingsBackMenu = Menu::create(settingsBackItem, NULL);
    settingsBackMenu->setPosition(Vec2::ZERO);
    this->addChild(settingsBackMenu, 2);

    /*=====================创建返回按钮结束====================*/

    /*=====================创建关闭按钮开始======================*/

    auto backToMenuItem = MenuItemImage::create(
        "ui/button_close.png",
        "ui/button_close.png",
        CC_CALLBACK_1(GameSettingsScene::menuCallback, this));

    if (backToMenuItem == nullptr ||
        backToMenuItem->getContentSize().width <= 0 ||
        backToMenuItem->getContentSize().height <= 0)
    {
        problemLoading("'ui/button_close.png' and 'ui/button_close.png'");
    }
    else
    {
        backToMenuItem->setPosition(Vec2(GAMESETTINGS_BACK_TO_MENU_POSITION_X, GAMESETTINGS_BACK_TO_MENU_POSITION_Y));
    }  // 关闭菜单需要改为固定位置（且此处关闭菜单表示跳到结束界面）

    auto backToMenuMenu = Menu::create(backToMenuItem, NULL);
    backToMenuMenu->setPosition(Vec2::ZERO);
    this->addChild(backToMenuMenu, 2);

    /*=====================创建关闭按钮结束======================*/

    /*=====================创建标题开始======================*/

    auto settingsNameLabel = Label::createWithTTF(
        "SETTINGS",
        "fonts/PixeloidSans.ttf",
        GAMESETTINGS_NAME_LABEL_SIZE
    );//创建文本
    if (settingsNameLabel == nullptr)
    {
        problemLoading("'fonts/PixeloidSans.ttf'");
    }
    else
    {
        const Color4B settingsNameLabelColor(GAMESETTINGS_TEXT_RGB_COLOR, 255);//创建4B颜色
        settingsNameLabel->setTextColor(settingsNameLabelColor);
        settingsNameLabel->setPosition(
            Vec2(GAMESETTINGS_NAME_LABEL_POSITION_X,
                GAMESETTINGS_NAME_LABEL_POSITION_Y)
        );

        this->addChild(settingsNameLabel, 1);
    }

    /*=====================创建标题结束======================*/

    /*===================创建滑动条开始======================*/

    _displayedPercentage = Text::create("0", "fonts/Lilita one.ttf", 27);          //_displayedPercentage 用于显示滑块拖动后所占比例
    _displayedPercentage->setPosition(Vec2(GAMESETTINGS_SETTINGSMENU_POSITION_X, GAMESETTINGS_SETTINGSMENU_POSITION_Y));

    auto musicSlider = Slider::create();

    _displayedPercentage->setString(StringUtils::format("%d%%", Tools::getUserInt("musicVolume")));

    musicSlider->setPercent(Tools::getUserInt("musicVolume"));
    musicSlider->loadBarTexture("ui/progressFrame.png");
    musicSlider->loadProgressBarTexture("ui/progressBlock.png");
    musicSlider->setPosition(Vec2(GAMESETTINGS_SETTINGSMENU_POSITION_X, GAMESETTINGS_SETTINGSMENU_POSITION_Y));
    musicSlider->addEventListener(CC_CALLBACK_2(GameSettingsScene::sliderEvent, this));
    musicSlider->setScale(0.5);

    this->addChild(_displayedPercentage, 3);
    this->addChild(musicSlider, 2);

    /*===================创建滑动条结束====================*/

    /*===================创建标签开始========================*/

    Label* settingsMusicLabel = Label::create(Tools::cbyid(pDict, "VOLUME SETTING"), "Maiandra GD", 35);
    settingsMusicLabel->setPosition(GAMESETTINGS_SETTINGSMUSICLABEL_POSITION_X, GAMESETTINGS_SETTINGSMUSICLABEL_POSITION_Y);
    const Color4B settingsMusicLabelColor(0, 0, 0, 255);//创建4B颜色
    const Color4B settingsMusicLabelShadowColor(50, 50, 50, 200);
    settingsMusicLabel->enableShadow(settingsMusicLabelShadowColor);
    settingsMusicLabel->setTextColor(settingsMusicLabelColor);

    this->addChild(settingsMusicLabel, 3);

    /*===================创建标签结束=========================*/

    /*===================创建菜单开始========================*/

    auto musicOn = MenuItemImage::create("ui/musicOn.png", "ui/musicOn.png");
    auto musicOff = MenuItemImage::create("ui/musicOff.png", "ui/musicOff.png");
    MenuItemToggle* musicOnOrOff = MenuItemToggle::createWithTarget(this,
        menu_selector(SettingsScene::settingsPlayCallBack), musicOn, musicOff, NULL);
    //显示音乐开始或静音图标

    if (UserDefault::getInstance()->getBoolForKey("ifPlayMusic", true))
    {
        musicOnOrOff->setSelectedIndex(0);
        _displayedMusicStates->setString(StringUtils::format(Tools::cbyid(pDict, "MUSIC ON")));
    }
    else
    {
        musicOnOrOff->setSelectedIndex(1);
        _displayedMusicStates->setString(StringUtils::format(Tools::cbyid(pDict, "MUSIC OFF")));
    }

    _displayedMusicStates->setTextColor(settingsMusicLabelColor);
    const Color4B displayedMusicStatesShadowColor(50, 50, 50, 200);
    _displayedMusicStates->enableShadow(displayedMusicStatesShadowColor);
    _displayedMusicStates->setPosition(Vec2(GAMESETTINGS_SETTINGMUSICSTATES_POSITION_X, GAMESETTINGS_SETTINGMUSICSTATES_POSITION_Y));

    /*===============*/

    auto FPSOn = MenuItemImage::create("ui/FPSOn.png", "ui/FPSOn.png");
    auto FPSOff = MenuItemImage::create("ui/FPSOff.png", "ui/FPSOff.png");
    MenuItemToggle* FPSOnOrOff = MenuItemToggle::createWithTarget(this,
        menu_selector(SettingsScene::settingsFPSCallBack), FPSOn, FPSOff, NULL);
    //显示FPS显示或隐藏图标

    FPSOnOrOff->setPosition(Vec2(SETTINGS_SETTINGFPSSTATES_POSITION_X, SETTINGS_SETTINGFPSSTATES_POSITION_Y));

    if (UserDefault::getInstance()->getBoolForKey("ifShowFPS", true))
    {

        FPSOnOrOff->setSelectedIndex(0);
        _displayedFPSStates->setString(StringUtils::format(Tools::cbyid(pDict, "DISPLAY FPS")));
    }
    else
    {
        FPSOnOrOff->setSelectedIndex(1);
        _displayedFPSStates->setString(StringUtils::format(Tools::cbyid(pDict, "CONCEAL FPS")));
    }

    _displayedFPSStates->setTextColor(settingsMusicLabelColor);
    const Color4B displayedFPSStatesShadowColor(50, 50, 50, 200);
    _displayedFPSStates->enableShadow(displayedFPSStatesShadowColor);
    _displayedFPSStates->setPosition(Vec2(GAMESETTINGS_SETTINGSFPSLABEL_POSITION_X, GAMESETTINGS_SETTINGSFPSLABEL_POSITION_Y));

    /*===============*/

    Menu* GameSettingsMenu = Menu::create(musicOnOrOff, FPSOnOrOff, NULL);
    this->addChild(GameSettingsMenu, 3);
    addChild(_displayedMusicStates, 3);
    addChild(_displayedFPSStates, 3);

    /*===================创建菜单结束========================*/

    /*====================创建背景图开始======================*/
    auto background = Sprite::create("background/GameSettingsBackground.png");
    if (background == nullptr)
    {
        problemLoading("'background/GameSettingsBackground.png'");
    }
    else
    {
        //将背景图放在中央
        background->setPosition(Vec2(GAMESETTINGS_BACKGROUND_POSITION_X,
            GAMESETTINGS_BACKGROUND_POSITION_Y));

        this->addChild(background, 0);
    }

    /*=====================创建背景图结束======================*/

    return true;
}

/****************************
* Name ：GameSettingsScene::settingsBackCallback
* Summary ：设置返回按钮回调
* return ：
****************************/
void GameSettingsScene::settingsBackToGameCallback(Ref* pSender)
{
    Tools::playEffect("music/if_click_buttom_on_menu.mp3");
    Tools::setEffectsVolume("musicVolume");
    auto GS = GameScene::createScene();
    Director::getInstance()->popScene();//过场动画设计
}

/****************************
* Name ：GameSettingsScene::sliderEvent
* Summary ：滑动事件监听
* return ：
* ***************************/
void GameSettingsScene::sliderEvent(Ref* pSender, Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider* slider = dynamic_cast<Slider*>(pSender);
        int percentVolume = slider->getPercent();

        //log(percentVolume);
        Tools::setBackgroundMusicVolume(2 * float(percentVolume) / 100);
        //CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(CocosDenshion::SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() + float(percentVolume) / 100);

        Tools::setUserInt("musicVolume", percentVolume);

        _displayedPercentage->setString(StringUtils::format("%d%%", percentVolume));   //显示所占百分比

    }
}

/****************************
* Name ：GameSettingsScene::settingsPlayCallBack
* Summary  回调函数
* return ：
* ***************************/
void GameSettingsScene::settingsPlayCallBack(Ref* pSender)
{
    auto pDict = Tools::initDict();
    Tools::playEffect("music/if_click_buttom_on_menu.mp3");
    Tools::setEffectsVolume("musicVolume");
    if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
    {
        Tools::pauseBackgroundMusic();
        Tools::setUserBool("ifPlayMusic", false);
        _displayedMusicStates->setString(StringUtils::format(Tools::cbyid(pDict, "MUSIC OFF")));
    }
    else
    {
        Tools::resumeBackgroundMusic();
        Tools::setUserBool("ifPlayMusic", true);
        _displayedMusicStates->setString(StringUtils::format(Tools::cbyid(pDict, "MUSIC ON")));
    }
}

/****************************
* Name ：GameSettingsScene::settingsFPSCallBack
* Summary  回调函数
* return ：
* ***************************/
void GameSettingsScene::settingsFPSCallBack(Ref* pSender)
{
    auto pDict = Tools::initDict();
    Tools::playEffect("music/if_click_buttom_on_menu.mp3");
    Tools::setEffectsVolume("musicVolume");
    auto director = Director::getInstance();
    if (director->isDisplayStats())
    {
        director->setDisplayStats(false);
        Tools::setUserBool("ifShowFPS", false);
        _displayedFPSStates->setString(StringUtils::format(Tools::cbyid(pDict, "CONCEAL FPS")));
    }
    else
    {
        director->setDisplayStats(true);
        Tools::setUserBool("ifShowFPS", true);
        _displayedFPSStates->setString(StringUtils::format(Tools::cbyid(pDict, "DISPLAY FPS")));
    }
}

/****************************
* Name ：GameSettingsScene::menuCloseCallback
* Summary ：跳到GameOverScene
* return ：无
****************************/
void GameSettingsScene::menuCallback(Ref* pSender)
{
    Tools::playEffect("music/if_click_buttom_on_menu.mp3");
    Tools::setEffectsVolume("musicVolume");
    /**/
    Tools::gameoverDataSave();
    /**/
    auto GOS = GameOverScene::createScene();
    Director::getInstance()->replaceScene(GOS);
}