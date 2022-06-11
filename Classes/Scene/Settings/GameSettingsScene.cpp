//���� : ����
//���� : 2022-5-14

//���� ����Ԫ��
//���� : 2022-5-21
//ʵ�� ���Խ���Ϸ���棬��������


#include "GameSettingsScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

static bool ifShowPlay = true;          //�Ƿ񲥷�����
static bool ifShowStates = false;       //�Ƿ���ʾFPS

/****************************
* Name ��GameSettingsScene::createScene
* Summary ����������
* return ��������ָ��
****************************/
Scene* GameSettingsScene::createScene()
{
    return GameSettingsScene::create();
}

/****************************
* Name ��problemLoading
* Summary �������ӡ
* return ��
****************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SettingsScene.cpp\n");
}

/****************************
* Name ��GameSettingsScene::init
* Summary �����˵���ʼ��
* return ����ʼ���ɹ����
****************************/
bool GameSettingsScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/retro_fight_ingame_01.mp3"); //Ԥ��������
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/to_a_new_scene.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
        float(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
    /*=====================�������ذ�ť��ʼ======================*/

    //�������ذ�ť
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
    //�������ز˵�
    auto backMenu = Menu::create(settingsBackItem, NULL);
    backMenu->setPosition(Vec2::ZERO);
    this->addChild(backMenu, 2);

    /*=====================�����رհ�ť����====================*/

    /*=====================�������⿪ʼ======================*/

    auto settingsNameLabel = Label::createWithTTF(
        "SETTINGS",
        "fonts/PixeloidSans.ttf",
        GAMESETTINGS_NAME_LABEL_SIZE
    );//�����ı�
    if (settingsNameLabel == nullptr)
    {
        problemLoading("'fonts/PixeloidSans.ttf'");
    }
    else
    {
        const Color4B settingsNameLabelColor(GAMESETTINGS_TEXT_RGB_COLOR, 255);//����4B��ɫ
        settingsNameLabel->setTextColor(settingsNameLabelColor);
        settingsNameLabel->setPosition(
            Vec2(GAMESETTINGS_NAME_LABEL_POSITION_X,
                GAMESETTINGS_NAME_LABEL_POSITION_Y)
        );

        this->addChild(settingsNameLabel, 1);
    }

    /*=====================�����������======================*/

    /*===================������������ʼ======================*/

    _displayedPercentage = Text::create("0", "fonts/Lilita one.ttf", 27);          //_displayedPercentage ������ʾ�����϶�����ռ����
    _displayedPercentage->setPosition(Vec2(GAMESETTINGS_SETTINGSMENU_POSITION_X, GAMESETTINGS_SETTINGSMENU_POSITION_Y));

    auto musicSlider = Slider::create();

    _displayedPercentage->setString(StringUtils::format("Percent %d", UserDefault::getInstance()->getIntegerForKey("musicVolume")));

    musicSlider->setPercent(UserDefault::getInstance()->getIntegerForKey("musicVolume"));
    musicSlider->loadBarTexture("ui/progressFrame.png");
    musicSlider->loadProgressBarTexture("ui/progressBlock.png");
    musicSlider->setPosition(Vec2(GAMESETTINGS_SETTINGSMENU_POSITION_X, GAMESETTINGS_SETTINGSMENU_POSITION_Y));
    musicSlider->addEventListener(CC_CALLBACK_2(GameSettingsScene::sliderEvent, this));
    musicSlider->setScale(0.5);

    this->addChild(_displayedPercentage, 3);
    this->addChild(musicSlider, 2);

    /*===================��������������====================*/

    /*===================������ǩ��ʼ========================*/

    Label* settingsMusicLabel = Label::create("MUSIC SETTING", "fonts/Lilita one.ttf", 35);
    settingsMusicLabel->setPosition(GAMESETTINGS_SETTINGSMUSICLABEL_POSITION_X, GAMESETTINGS_SETTINGSMUSICLABEL_POSITION_Y);
    const Color4B settingsMusicLabelColor(0, 0, 0, 255);//����4B��ɫ
    settingsMusicLabel->enableShadow();
    settingsMusicLabel->setTextColor(settingsMusicLabelColor);

    this->addChild(settingsMusicLabel, 3);

    /*===================������ǩ����=========================*/

    /*===================�����˵���ʼ========================*/

    auto musicOn = MenuItemImage::create("ui/musicOn.png", "ui/musicOn.png");
    auto musicOff = MenuItemImage::create("ui/musicOff.png", "ui/musicOff.png");

    MenuItemToggle* musicOnOrOff = MenuItemToggle::createWithTarget(this,
        menu_selector(GameSettingsScene::settingsPlayCallBack), musicOn, musicOff, NULL);
    //��ʾ���ֿ�ʼ����ͼ��

    if (UserDefault::getInstance()->getBoolForKey("ifPlayMusic",true))
    {
        musicOnOrOff->setSelectedIndex(0);
        _displayedMusicStates->setString(StringUtils::format("MUSIC ON"));
        _displayedMusicStates->setFontName("fonts/Lilita one.ttf");
        _displayedMusicStates->setFontSize(35);
        _displayedMusicStates->enableShadow();
    }
    else
    {
        musicOnOrOff->setSelectedIndex(1);
        _displayedMusicStates->setString(StringUtils::format("MUSIC OFF"));
        _displayedMusicStates->setFontName("fonts/Lilita one.ttf");
        _displayedMusicStates->setFontSize(35);
        _displayedMusicStates->enableShadow();
    }

    _displayedMusicStates->setTextColor(settingsMusicLabelColor);
    _displayedMusicStates->setPosition(Vec2(GAMESETTINGS_SETTINGMUSICSTATES_POSITION_X, GAMESETTINGS_SETTINGMUSICSTATES_POSITION_Y));

    auto FPSOn = MenuItemImage::create("ui/FPSOn.png", "ui/FPSOn.png");
    auto FPSOff = MenuItemImage::create("ui/FPSOff.png", "ui/FPSOff.png");

    MenuItemToggle* FPSOnOrOff = MenuItemToggle::createWithTarget(this,
        menu_selector(SettingsScene::settingsFPSCallBack), FPSOn, FPSOff, NULL);
    //��ʾFPS��ʾ������ͼ��

    FPSOnOrOff->setPosition(Vec2(GAMESETTINGS_SETTINGFPSSTATES_POSITION_X, GAMESETTINGS_SETTINGFPSSTATES_POSITION_Y));

    if (UserDefault::getInstance()->getBoolForKey("ifShowFPS", false))
    {
        FPSOnOrOff->setSelectedIndex(0);
        _displayedFPSStates->setString(StringUtils::format("DISPLAY FPS"));
        _displayedFPSStates->setFontName("fonts/Lilita one.ttf");
        _displayedFPSStates->setFontSize(35);
        _displayedFPSStates->enableShadow();
    }
    else
    {
        FPSOnOrOff->setSelectedIndex(1);
        _displayedFPSStates->setString(StringUtils::format("CONCEAL FPS"));
        _displayedFPSStates->setFontName("fonts/Lilita one.ttf");
        _displayedFPSStates->setFontSize(35);
        _displayedFPSStates->enableShadow();
    }

    _displayedFPSStates->setTextColor(settingsMusicLabelColor);
    _displayedFPSStates->setPosition(Vec2(GAMESETTINGS_SETTINGSFPSLABEL_POSITION_X, GAMESETTINGS_SETTINGSFPSLABEL_POSITION_Y));

    Menu* GameSettingsMenu = Menu::create(musicOnOrOff, FPSOnOrOff, NULL);
    this->addChild(GameSettingsMenu, 3);
    addChild(_displayedMusicStates, 3);
    addChild(_displayedFPSStates, 3);

    /*===================�����˵�����========================*/

    /*====================��������ͼ��ʼ======================*/
    auto background = Sprite::create("background/GameSettingsBackground.png");
    if (background == nullptr)
    {
        problemLoading("'background/GameSettingsBackground.png'");
    }
    else
    {
        //������ͼ��������
        background->setPosition(Vec2(GAMESETTINGS_BACKGROUND_POSITION_X,
            GAMESETTINGS_BACKGROUND_POSITION_Y));

        this->addChild(background, 0);
    }

    /*=====================��������ͼ����======================*/

    return true;
}

/****************************
* Name ��GameSettingsScene::settingsBackCallback
* Summary �����÷��ذ�ť�ص�
* return ��
****************************/
void GameSettingsScene::settingsBackToGameCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
        float(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
    auto GS = GameScene::createScene();
    Director::getInstance()->popScene();//�����������
}

/****************************
* Name ��GameSettingsScene::sliderEvent
* Summary �������¼�����
* return ��
* ***************************/
void GameSettingsScene::sliderEvent(Ref* pSender, Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider* slider = dynamic_cast<Slider*>(pSender);
        int percentVolume = slider->getPercent();

        log(percentVolume);
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(2 * float(percentVolume) / 100);
        //CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(CocosDenshion::SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() + float(percentVolume) / 100);

        UserDefault::getInstance()->setIntegerForKey("musicVolume", percentVolume);

        _displayedPercentage->setString(StringUtils::format("Percent %d", percentVolume));   //��ʾ��ռ�ٷֱ�

    }
}

/****************************
* Name ��GameSettingsScene::settingsPlayCallBack
* Summary  �ص�����
* return ��
* ***************************/
void GameSettingsScene::settingsPlayCallBack(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
        float(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
    if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        UserDefault::getInstance()->setBoolForKey("ifPlayMusic", false);
        _displayedMusicStates->setString(StringUtils::format("MUSIC OFF"));
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        UserDefault::getInstance()->setBoolForKey("ifPlayMusic", true);
        _displayedMusicStates->setString(StringUtils::format("MUSIC ON"));
    }
}

/****************************
* Name ��GameSettingsScene::settingsFPSCallBack
* Summary  �ص�����
* return ��
* ***************************/
void GameSettingsScene::settingsFPSCallBack(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
        float(UserDefault::getInstance()->getIntegerForKey("musicVolume")) / 100);
    auto director = Director::getInstance();
    if (director->isDisplayStats())
    {
        director->setDisplayStats(false);
        UserDefault::getInstance()->setBoolForKey("ifShowFPS", false);
        _displayedFPSStates->setString(StringUtils::format("CONCEAL FPS"));
    }
    else
    {
        director->setDisplayStats(true);
        UserDefault::getInstance()->setBoolForKey("ifShowFPS", true);
        _displayedFPSStates->setString(StringUtils::format("DISPLAY FPS"));
    }
}
