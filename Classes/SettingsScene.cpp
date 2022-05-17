//���� : ����
//���� : 2022-5-14
#include "SettingsScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

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

    /*===================��������ѡ�ʼ====================*
    MenuItemFont::setFontName("fonts/PixeloidMono.ttf");
    MenuItemFont::setFontSize(64);
    const Color3B settingsItemColor(SETTINGS_TEXT_RGB_COLOR);//����3B��ɫ

    //���������˵���
    MenuItemFont* item = MenuItemFont::create(
        "",
        CC_CALLBACK_1(SettingsScene::, this)
    );


    //�����˵� �Ѳ˵���Ž�ȥ
    Menu* settingsMenu = Menu::create(item, NULL);
    settingsMenu->setPosition(SETTINGS_SETTINGSMENU_POSITION_X,
        SETTINGS_SETTINGSMENU_POSITION_Y);
    settingsMenu->alignItemsVertically();
    settingsMenu->setColor(settingsItemColor);

    this->addChild(settingsMenu, 1);
    /*===================�������˵�ѡ�����====================*/

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
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, mainMenuScene));
}
