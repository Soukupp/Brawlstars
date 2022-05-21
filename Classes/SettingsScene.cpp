//���� : ����
//���� : 2022-5-14
#include "SettingsScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

static bool ifShowPlay = true;          //�Ƿ񲥷�����
static bool ifShowStates = false;       //�Ƿ���ʾFPS

/****************************
* Name ��SettingsScene::createScene
* Summary ����������
* return ��������ָ��
****************************/
Scene* SettingsScene::createScene()
{
    return SettingsScene::create();
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
* Name ��SettingsScene::init
* Summary �����˵���ʼ��
* return ����ʼ���ɹ����
****************************/
bool SettingsScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*=====================�������ذ�ť��ʼ======================*/

    //�������ذ�ť
    auto settingsBackItem = MenuItemImage::create(
        "backSettingsNormal.png",
        "backSettingsSelected.png",
        CC_CALLBACK_1(SettingsScene::settingsBackCallback, this));

    if (settingsBackItem == nullptr ||
        settingsBackItem->getContentSize().width <= 0 ||
        settingsBackItem->getContentSize().height <= 0)
    {//������
        problemLoading("'backSettingsNormal.png' and 'backSettingsSelected.png'");
    }
    else
    {//����λ��
        float x = SETTINGS_BACK_ITEM_POSITION_X;
        float y = SETTINGS_BACK_ITEM_POSITION_Y;
        settingsBackItem->setPosition(Vec2(x, y));
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
        SETTINGS_NAME_LABEL_SIZE
    );//�����ı�
    if (settingsNameLabel == nullptr)
    {
        problemLoading("'fonts/PixeloidSans.ttf'");
    }
    else
    {
        const Color4B settingsNameLabelColor(SETTINGS_TEXT_RGB_COLOR, 255);//����4B��ɫ
        settingsNameLabel->setTextColor(settingsNameLabelColor);
        settingsNameLabel->setPosition(
            Vec2(SETTINGS_NAME_LABEL_POSITION_X,
                SETTINGS_NAME_LABEL_POSITION_Y)
        );

        this->addChild(settingsNameLabel, 1);
    }
    /*=====================�����������======================*/

    /*===================������������ʼ======================*/

    _displayedPercentage = Text::create("0", "fonts/PixeloidSans.ttf", 27);          //_displayedPercentage ������ʾ�����϶�����ռ����
    _displayedPercentage->setPosition(Vec2(SETTINGS_SETTINGSMENU_POSITION_X, SETTINGS_SETTINGSMENU_POSITION_Y * 0.5));

    auto musicSlider = Slider::create();

    musicVolume = UserDefault::getInstance()->getFloatForKey("musicVolume");   //musicVolume ���ڼ�¼������С���ٷ��ƣ�
    musicVolume = 50.0f;                                                        //�����ʼֵΪ50
    _displayedPercentage->setString(StringUtils::format("Percent %d", 50));

    musicSlider->setPercent(musicVolume);
    musicSlider->loadBarTexture("progressFrame.png");
    musicSlider->loadProgressBarTexture("progressBlock.png");
    musicSlider->setPosition(Vec2(SETTINGS_SETTINGSMENU_POSITION_X, SETTINGS_SETTINGSMENU_POSITION_Y));
    musicSlider->addEventListener(CC_CALLBACK_2(SettingsScene::sliderEvent, this));
    musicSlider->setScale(0.5);

    this->addChild(_displayedPercentage,3);
    this->addChild(musicSlider,2);

    /*===================��������������====================*/

    /*===================������ǩ��ʼ========================*/

    Label* settingsMusicLabel = Label::create("MUSIC SETTING", "fonts/PixeloidSans.ttf", 27);
    settingsMusicLabel->setPosition(SETTINGS_SETTINGSMUSICLABEL_POSITION_X, SETTINGS_SETTINGSMUSICLABEL_POSITION_Y);
    const Color4B settingsMusicLabelColor(SETTINGS_TEXT_RGB_COLOR, 255);//����4B��ɫ
    settingsMusicLabel->setTextColor(settingsMusicLabelColor);
    
    this->addChild(settingsMusicLabel, 3);

    /*===================������ǩ����=========================*/

    /*===================�����˵���ʼ========================*/

    auto musicOn = MenuItemImage::create("musicOn.png", "musicOn.png");
    auto musicOff = MenuItemImage::create("musicOff.png", "musicOff.png");

    MenuItemToggle* musicOnOrOff = MenuItemToggle::createWithTarget(this,
        menu_selector(SettingsScene::settingsPlayCallBack), musicOn, musicOff, NULL);
                                                                                        //��ʾ���ֿ�ʼ����ͼ��
    
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
    //��ʾFPS��ʾ������ͼ��


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

    /*===================�����˵�����========================*/




    /*=====================��������ͼ��ʼ======================*/
    auto background = Sprite::create("settingsBackground.png");
    if (background == nullptr)
    {
        problemLoading("'settingsBackground.png'");
    }
    else
    {
        //������ͼ��������
        background->setPosition(Vec2(SETTINGS_BACKGROUND_POSITION_X,
            SETTINGS_BACKGROUND_POSITION_Y));

        this->addChild(background, 0);
    }
    /*=====================��������ͼ����======================*/
    return true;
}

/****************************
* Name ��SettingsScene::settingsBackCallback
* Summary �����÷��ذ�ť�ص�
* return ��
****************************/
void SettingsScene::settingsBackCallback(Ref* pSender)
{
    auto mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, mainMenuScene));//�����������
}

/****************************
* Name ��SettingsScene::sliderEvent
* Summary �������¼�����
* return ��
* ***************************/
void SettingsScene::sliderEvent(Ref* pSender, Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider* slider = dynamic_cast<Slider*>(pSender);
        int percentVolume = slider->getPercent();


        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(float(percentVolume) / 100);
        //ʵ�ڵ�������������β�ˣ�~~~~~~~~~~~~~~~~~~~~~~~~�������Ҫ�Լ�ʵ�֣�����β��
        //��Ҫ����sliderEvent�н����޸�

        UserDefault::getInstance()->setFloatForKey("musicVolume", percentVolume);

        _displayedPercentage->setString(StringUtils::format("Percent %d", percentVolume));   //��ʾ��ռ�ٷֱ�

    }
}
/****************************
* Name ��SettingsScene::settingsPlayCallBack
* Summary  �ص�����
* return ��
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
* Name ��SettingsScene::settingsFPSCallBack
* Summary  �ص�����
* return ��
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
