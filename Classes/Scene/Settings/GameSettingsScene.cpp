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

    auto pDict = Tools::initDict();

    Tools::preloadBackgroundMusic("music/retro_fight_ingame_01.mp3"); //Ԥ��������
    Tools::playEffect("music/to_a_new_scene.mp3");
    Tools::setEffectsVolume("musicVolume");
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
    auto settingsBackMenu = Menu::create(settingsBackItem, NULL);
    settingsBackMenu->setPosition(Vec2::ZERO);
    this->addChild(settingsBackMenu, 2);

    /*=====================�������ذ�ť����====================*/

    /*=====================�����رհ�ť��ʼ======================*/

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
    }  // �رղ˵���Ҫ��Ϊ�̶�λ�ã��Ҵ˴��رղ˵���ʾ�����������棩

    auto backToMenuMenu = Menu::create(backToMenuItem, NULL);
    backToMenuMenu->setPosition(Vec2::ZERO);
    this->addChild(backToMenuMenu, 2);

    /*=====================�����رհ�ť����======================*/

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

    _displayedPercentage->setString(StringUtils::format("%d%%", Tools::getUserInt("musicVolume")));

    musicSlider->setPercent(Tools::getUserInt("musicVolume"));
    musicSlider->loadBarTexture("ui/progressFrame.png");
    musicSlider->loadProgressBarTexture("ui/progressBlock.png");
    musicSlider->setPosition(Vec2(GAMESETTINGS_SETTINGSMENU_POSITION_X, GAMESETTINGS_SETTINGSMENU_POSITION_Y));
    musicSlider->addEventListener(CC_CALLBACK_2(GameSettingsScene::sliderEvent, this));
    musicSlider->setScale(0.5);

    this->addChild(_displayedPercentage, 3);
    this->addChild(musicSlider, 2);

    /*===================��������������====================*/

    /*===================������ǩ��ʼ========================*/

    Label* settingsMusicLabel = Label::create(Tools::cbyid(pDict, "VOLUME SETTING"), "Maiandra GD", 35);
    settingsMusicLabel->setPosition(GAMESETTINGS_SETTINGSMUSICLABEL_POSITION_X, GAMESETTINGS_SETTINGSMUSICLABEL_POSITION_Y);
    const Color4B settingsMusicLabelColor(0, 0, 0, 255);//����4B��ɫ
    const Color4B settingsMusicLabelShadowColor(50, 50, 50, 200);
    settingsMusicLabel->enableShadow(settingsMusicLabelShadowColor);
    settingsMusicLabel->setTextColor(settingsMusicLabelColor);

    this->addChild(settingsMusicLabel, 3);

    /*===================������ǩ����=========================*/

    /*===================�����˵���ʼ========================*/

    auto musicOn = MenuItemImage::create("ui/musicOn.png", "ui/musicOn.png");
    auto musicOff = MenuItemImage::create("ui/musicOff.png", "ui/musicOff.png");
    MenuItemToggle* musicOnOrOff = MenuItemToggle::createWithTarget(this,
        menu_selector(SettingsScene::settingsPlayCallBack), musicOn, musicOff, NULL);
    //��ʾ���ֿ�ʼ����ͼ��

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
    //��ʾFPS��ʾ������ͼ��

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
    Tools::playEffect("music/if_click_buttom_on_menu.mp3");
    Tools::setEffectsVolume("musicVolume");
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

        //log(percentVolume);
        Tools::setBackgroundMusicVolume(2 * float(percentVolume) / 100);
        //CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(CocosDenshion::SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() + float(percentVolume) / 100);

        Tools::setUserInt("musicVolume", percentVolume);

        _displayedPercentage->setString(StringUtils::format("%d%%", percentVolume));   //��ʾ��ռ�ٷֱ�

    }
}

/****************************
* Name ��GameSettingsScene::settingsPlayCallBack
* Summary  �ص�����
* return ��
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
* Name ��GameSettingsScene::settingsFPSCallBack
* Summary  �ص�����
* return ��
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
* Name ��GameSettingsScene::menuCloseCallback
* Summary ������GameOverScene
* return ����
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