//作者 : 王鹏
//日期 : 2022-5-14
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

    /*===================创建滑动条开始======================*/

    _displayedPercentage = Text::create("0", "fonts/PixeloidSans.ttf", 27);          //_displayedPercentage 用于显示滑块拖动后所占比例
    _displayedPercentage->setPosition(Vec2(SETTINGS_SETTINGSMENU_POSITION_X, SETTINGS_SETTINGSMENU_POSITION_Y * 0.5));

    auto musicSlider = Slider::create();

    musicVolume = UserDefault::getInstance()->getFloatForKey("musicVolume");   //musicVolume 用于记录音量大小（百分制）
    musicVolume = 50.0f;                                                        //定义初始值为50
    _displayedPercentage->setString(StringUtils::format("Percent %d", 50));

    musicSlider->setPercent(musicVolume);
    musicSlider->loadBarTexture("progressFrame.png");
    musicSlider->loadProgressBarTexture("progressBlock.png");
    musicSlider->setPosition(Vec2(SETTINGS_SETTINGSMENU_POSITION_X, SETTINGS_SETTINGSMENU_POSITION_Y));
    musicSlider->addEventListener(CC_CALLBACK_2(SettingsScene::sliderEvent, this));
    musicSlider->setScale(0.5);

    this->addChild(_displayedPercentage,3);
    this->addChild(musicSlider,2);

    /*===================创建滑动条结束====================*/

    /*===================创建标签开始========================*/

    Label* settingsMusicLabel = Label::create("MUSIC SETTING", "fonts/PixeloidSans.ttf", 27);
    settingsMusicLabel->setPosition(SETTINGS_SETTINGSMUSICLABEL_POSITION_X, SETTINGS_SETTINGSMUSICLABEL_POSITION_Y);
    const Color4B settingsMusicLabelColor(SETTINGS_TEXT_RGB_COLOR, 255);//创建4B颜色
    settingsMusicLabel->setTextColor(settingsMusicLabelColor);
    
    this->addChild(settingsMusicLabel, 3);

    /*===================创建标签结束=========================*/

    /*===================创建菜单开始========================*/

    auto musicOn = MenuItemImage::create("musicOn.png", "musicOn.png");
    auto musicOff = MenuItemImage::create("musicOff.png", "musicOff.png");

    MenuItemToggle* musicOnOrOff = MenuItemToggle::createWithTarget(this,
        menu_selector(SettingsScene::settingsPlayCallBack), musicOn, musicOff, NULL);
                                                                                        //显示音乐开始或静音图标
    
    if (ifShowPlay)
    {
        musicOnOrOff->setSelectedIndex(0);
        _displayedMusicStates->setString(StringUtils::format("MUSIC ON"));
    }
    else
    {
        musicOnOrOff->setSelectedIndex(1);
        _displayedMusicStates->setString(StringUtils::format("MUSIC OFF"));
    }

    _displayedMusicStates->setTextColor(settingsMusicLabelColor);
    _displayedMusicStates->setPosition(Vec2(SETTINGS_SETTINGMUSICSTATES_POSITION_X, SETTINGS_SETTINGMUSICSTATES_POSITION_Y));

 

    auto FPSOn = MenuItemImage::create("FPSOn.png", "FPSOn.png");
    auto FPSOff = MenuItemImage::create("FPSOff.png", "FPSOff.png");

    MenuItemToggle* FPSOnOrOff = MenuItemToggle::createWithTarget(this,
        menu_selector(SettingsScene::settingsFPSCallBack),FPSOn , FPSOff, NULL);
    //显示FPS显示或隐藏图标


    FPSOnOrOff->setPosition(Vec2(SETTINGS_SETTINGFPSSTATES_POSITION_X, SETTINGS_SETTINGFPSSTATES_POSITION_Y));

    if (ifShowStates)
    {
        FPSOnOrOff->setSelectedIndex(0);
        _displayedFPSStates->setString(StringUtils::format("DISPLAY FPS"));
    }
    else
    {
        FPSOnOrOff->setSelectedIndex(1);
        _displayedFPSStates->setString(StringUtils::format("CONCEAL FPS"));
    }

    _displayedFPSStates->setTextColor(settingsMusicLabelColor);
    _displayedFPSStates->setPosition(Vec2(SETTINGS_SETTINGSFPSLABEL_POSITION_X, SETTINGS_SETTINGSFPSLABEL_POSITION_Y));


    Menu* settingsMenu = Menu::create(musicOnOrOff,FPSOnOrOff, NULL);
    
    this->addChild(settingsMenu, 3);
    addChild(_displayedMusicStates,3);
    addChild(_displayedFPSStates, 3);

    /*===================创建菜单结束========================*/




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


        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(float(percentVolume) / 100);
        //实在调不了音量，烂尾了，~~~~~~~~~~~~~~~~~~~~~~~~这个函数要自己实现，先烂尾了
        //需要用是sliderEvent中进行修改

        UserDefault::getInstance()->setFloatForKey("musicVolume", percentVolume);

        _displayedPercentage->setString(StringUtils::format("Percent %d", percentVolume));   //显示所占百分比

    }
}
/****************************
* Name ：SettingsScene::settingsPlayCallBack
* Summary  回调函数
* return ：
* ***************************/

void SettingsScene::settingsPlayCallBack(Ref* pSender)
{
   

    if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        ifShowPlay = false;
        _displayedMusicStates->setString(StringUtils::format("MUSIC OFF"));
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        ifShowPlay = true;
        _displayedMusicStates->setString(StringUtils::format("MUSIC ON"));
    }
}
/****************************
* Name ：SettingsScene::settingsFPSCallBack
* Summary  回调函数
* return ：
* ***************************/

void SettingsScene::settingsFPSCallBack(Ref* pSender)
{
    auto director = Director::getInstance();
    if (director->isDisplayStats())
    {
        director->setDisplayStats(false);
        ifShowStates = false;
        _displayedFPSStates->setString(StringUtils::format("CONCEAL FPS"));
    }
    else
    {
        director->setDisplayStats(true);
        ifShowStates = true;
        _displayedFPSStates->setString(StringUtils::format("DISPLAY FPS"));
    }
}
