//作者 : 王鹏
//日期 : 2022-5-17
//实现 ：框架搭建

//作者 ：束赫
//日期 : 2022-5-19
//实现 ：具体功能实现

//作者 ：李元特
//日期 : 2022-6-6
//实现 ：音乐音效update


#include "SettingsScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

static bool ifShowPlay = true;          //是否播放音乐
static bool ifShowStates = false;       //是否显示FPS

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
* Name ：SettingsScene::init
* Summary ：设置初始化
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

    auto pDict = Tools::initDict();

    Tools::playEffect("music/to_a_new_scene.mp3");
    Tools::setEffectsVolume("musicVolume");

    /*=====================创建返回按钮开始======================*/

    //创建返回按钮
    auto settingsBackItem = MenuItemImage::create(
        "ui/backSettingsNormal.png",
        "ui/backSettingsSelected.png",
        CC_CALLBACK_1(SettingsScene::settingsBackCallback, this));

    if (settingsBackItem == nullptr ||
        settingsBackItem->getContentSize().width <= 0 ||
        settingsBackItem->getContentSize().height <= 0)
    {//错误处理
        problemLoading("'ui/backSettingsNormal.png' and 'ui/backSettingsSelected.png'");
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

    /*=====================创建语言选择开始======================*/
    MenuItemFont::setFontName("fonts/Lilita one.ttf");
    MenuItemFont::setFontSize(40);
    const Color3B languageColor(SETTINGS_LANGUAGE_RGB_COLOR);//创建3B颜色

    MenuItemFont* itemChinese = MenuItemFont::create(
        "中文",
        CC_CALLBACK_1(SettingsScene::choseChineseCallback, this)
    );
    Menu* menuChinese = Menu::create(itemChinese, NULL);
    menuChinese->setPosition(SETTINGS_CHINESE_POSITION_X, SETTINGS_CHINESE_POSITION_Y);
    menuChinese->alignItemsVertically();
    menuChinese->setColor(languageColor);
    this->addChild(menuChinese, 2);

    MenuItemFont* itemEnglish = MenuItemFont::create(
        "English",
        CC_CALLBACK_1(SettingsScene::choseEnglishCallback, this)
    );
    Menu* menuEnglish = Menu::create(itemEnglish, NULL);
    menuEnglish->setPosition(SETTINGS_ENGLISH_POSITION_X, SETTINGS_ENGLISH_POSITION_Y);
    menuEnglish->alignItemsVertically();
    menuEnglish->setColor(languageColor);
    this->addChild(menuEnglish, 2);

    /*=====================创建语言选择结束====================*/

    /*=================创建清除用户数据按钮开始================*/

    //创建返回按钮
    auto clearUserDataItem = MenuItemImage::create(
        "ui/clearUserDataNormal.png",
        "ui/clearUserDataSelected.png",
        CC_CALLBACK_1(SettingsScene::clearUserDataCallback, this));

    if (clearUserDataItem == nullptr ||
        clearUserDataItem->getContentSize().width <= 0 ||
        clearUserDataItem->getContentSize().height <= 0)
    {//错误处理
        problemLoading("'ui/clearUserDataNormal.png' and 'ui/clearUserDataSelected.png'");
    }
    else
    {//设置位置
        float x = SETTINGS_CLEAR_USERDATA_ITEM_POSITION_X;
        float y = SETTINGS_CLEAR_USERDATA_ITEM_POSITION_Y;
        clearUserDataItem->setPosition(Vec2(x, y));
    }
    //创建返回菜单
    auto clearUserDataMenu = Menu::create(clearUserDataItem, NULL);
    clearUserDataMenu->setPosition(Vec2::ZERO);
    this->addChild(clearUserDataMenu, 2);

    //创建文本
    std::string strClearData = Tools::cbyid(pDict, "Clear");
    strClearData += "\n";
    strClearData += Tools::cbyid(pDict, "Data");
    auto clearUserDataLabel = Label::create(strClearData, "Maiandra GD", 25);
    if (clearUserDataLabel == nullptr || clearUserDataItem == nullptr)
    {
        problemLoading("'fonts/Segoe Print.ttf'");
    }
    else
    {
        const Color4B gameNameLabelColor(220, 0, 0, 255);//创建4B颜色
        clearUserDataLabel->setTextColor(gameNameLabelColor);
        clearUserDataLabel->setBMFontSize(25);
        clearUserDataLabel->setPosition(
            Vec2(SETTINGS_CLEARUSERDATA_LABEL_POSITION_X,
                SETTINGS_CLEARUSERDATA_LABEL_POSITION_Y)
        );

        this->addChild(clearUserDataLabel, 2);
    }

    /*=================创建清除用户数据按钮结束==============*/

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

    /*======================创建标题结束=======================*/

    /*=====================创建滑动条开始======================*/

    _displayedPercentage = Text::create("0", "fonts/Lilita one.ttf", 32);          //_displayedPercentage 用于显示滑块拖动后所占比例
    _displayedPercentage->setPosition(Vec2(SETTINGS_SETTINGSMENU_POSITION_X, SETTINGS_SETTINGSMENU_POSITION_Y));

    auto musicSlider = Slider::create();

    _displayedPercentage->setString(StringUtils::format("%d%%", Tools::getUserInt("musicVolume")));

    musicSlider->setPercent(Tools::getUserInt("musicVolume"));
    musicSlider->loadBarTexture("ui/progressFrame.png");
    musicSlider->loadProgressBarTexture("ui/progressBlock.png");
    musicSlider->setPosition(Vec2(SETTINGS_SETTINGSMENU_POSITION_X, SETTINGS_SETTINGSMENU_POSITION_Y));
    musicSlider->addEventListener(CC_CALLBACK_2(SettingsScene::sliderEvent, this));
    musicSlider->setScale(0.5);

    this->addChild(_displayedPercentage,3);
    this->addChild(musicSlider,2);

    /*=====================创建滑动条结束======================*/

    /*======================创建标签开始=======================*/

    Label* settingsMusicLabel = Label::create(Tools::cbyid(pDict, "VOLUME SETTING"), "Maiandra GD", 35);
    settingsMusicLabel->setPosition(SETTINGS_SETTINGSMUSICLABEL_POSITION_X, SETTINGS_SETTINGSMUSICLABEL_POSITION_Y);
    const Color4B settingsMusicLabelColor(0, 0, 0, 255);//创建4B颜色
    const Color4B settingsMusicLabelShadowColor(50, 50, 50, 200);
    settingsMusicLabel->enableShadow(settingsMusicLabelShadowColor);
    settingsMusicLabel->setTextColor(settingsMusicLabelColor);

    this->addChild(settingsMusicLabel, 3);

    /*====================创建标签结束=========================*/

    /*=====================创建菜单开始========================*/

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
    _displayedMusicStates->setPosition(Vec2(SETTINGS_SETTINGMUSICSTATES_POSITION_X, SETTINGS_SETTINGMUSICSTATES_POSITION_Y));

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
    _displayedFPSStates->setPosition(Vec2(SETTINGS_SETTINGSFPSLABEL_POSITION_X, SETTINGS_SETTINGSFPSLABEL_POSITION_Y));

    /*===============*/

    Menu* settingsMenu = Menu::create(musicOnOrOff, FPSOnOrOff, NULL);
    this->addChild(settingsMenu, 3);
    addChild(_displayedMusicStates, 3);
    addChild(_displayedFPSStates, 3);

    /*=====================创建菜单结束========================*/

    /*=====================创建背景图开始======================*/

    auto background = Sprite::create("background/GameSettingsBackground.png");
    if (background == nullptr)
    {
        problemLoading("'background/GameSettingsBackground.png'");
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
    Tools::playEffect("music/if_click_buttom_on_menu.mp3");
    Tools::setEffectsVolume("musicVolume");
    auto mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, mainMenuScene));//过场动画设计
}

/****************************
* Name ：SettingsScene::sliderEvent
* Summary ：滑动事件监听
* return ：
* ***************************/
void SettingsScene::sliderEvent(Ref* pSender, Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider* slider = dynamic_cast<Slider*>(pSender);
        int percentVolume = slider->getPercent();

        Tools::setBackgroundMusicVolume(float(percentVolume) / 100);

        Tools::setUserInt("musicVolume", percentVolume);

        _displayedPercentage->setString(StringUtils::format("%d%%", percentVolume));   //显示所占百分比

    }
}

/****************************
* Name ：SettingsScene::settingsPlayCallBack
* Summary  回调函数
* return ：
* ***************************/
void SettingsScene::settingsPlayCallBack(Ref* pSender)
{
    auto pDict = Tools::initDict();
    Tools::playEffect("music/if_click_buttom_on_menu.mp3");
    Tools::preloadBackgroundMusic("music/first_music.mp3");//预加载音乐
    Tools::setEffectsVolume("musicVolume");
    if (Tools::isBackgroundMusicPlaying())
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
* Name ：SettingsScene::settingsFPSCallBack
* Summary  回调函数
* return ：
* ***************************/
void SettingsScene::settingsFPSCallBack(Ref* pSender)
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
* Name ：SettingsScene::clearUserDataCallback
* Summary  回调函数
* return ：
* ***************************/
void SettingsScene::clearUserDataCallback(cocos2d::Ref* pSender)
{
    Tools::playEffect("music/if_click_buttom_on_menu.mp3");
    Tools::setEffectsVolume("musicVolume");
    if (Tools::getUserInt("_winTimes"))
    {
        Tools::setUserInt("_winTimes", 0);
    }
    if (Tools::getUserInt("_gameTimes"))
    {
        Tools::setUserInt("_gameTimes", 0);
    }
    if (Tools::getUserInt("_killNums"))
    {
        Tools::setUserInt("_killNums", 0);
    }
    if (Tools::getUserInt("_cupNums"))
    {
        Tools::setUserInt("_cupNums", 0);
    }
    if (Tools::getUserInt("selectedHero"))
    {
        Tools::setUserInt("selectedHero", 1);
    }
}

void SettingsScene::choseChineseCallback(cocos2d::Ref* pSender)
{
    Tools::setUserInt("language", enumChinese);
    auto settingsScene = SettingsScene::createScene();
    Director::getInstance()->replaceScene(settingsScene);
}
void SettingsScene::choseEnglishCallback(cocos2d::Ref* pSender)
{
    Tools::setUserInt("language", enumEnglish);
    auto settingsScene = SettingsScene::createScene();
    Director::getInstance()->replaceScene(settingsScene);
}