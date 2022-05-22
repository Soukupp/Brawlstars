//���ߣ�����
//ʱ�䣺2022-5-20

#include "HeroScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

static int slectedHero = 0;   //�û�ѡ���hero���ֱ���1��2��3��4��ʾ
/****************************
* Name ��HeroScene::createScene
* Summary ����������
* return ��������ָ��
****************************/
Scene* HeroScene::createScene()
{
    return HeroScene::create();
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

bool HeroScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

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
     /*=====================�������ذ�ť��ʼ======================*/

    //�������ذ�ť
    auto heroBackItem = MenuItemImage::create(
        "backSettingsNormal.png",
        "backSettingsSelected.png",
        CC_CALLBACK_1(HeroScene::heroBackCallback, this));

    if (heroBackItem == nullptr ||
        heroBackItem->getContentSize().width <= 0 ||
        heroBackItem->getContentSize().height <= 0)
    {//������
        problemLoading("'backSettingsNormal.png' and 'backSettingsSelected.png'");
    }
    else
    {//����λ��
        float x = HERO_BACK_ITEM_POSITION_X;
        float y = HERO_BACK_ITEM_POSITION_Y;
        heroBackItem->setPosition(Vec2(x, y));
    }
    //�������ز˵�
    auto backMenu = Menu::create(heroBackItem, NULL);
    backMenu->setPosition(Vec2::ZERO);
    this->addChild(backMenu, 2);
    /*=====================�������ذ�ť����======================*/

    /*=====================�������⿪ʼ======================*/

    auto heroNameLabel = Label::createWithTTF(
        "HEROS",
        "fonts/PixeloidSans.ttf",
        SETTINGS_NAME_LABEL_SIZE
    );//�����ı�
    if (heroNameLabel == nullptr)
    {
        problemLoading("'fonts/PixeloidSans.ttf'");
    }
    else
    {
        const Color4B heroNameLabelColor(SETTINGS_TEXT_RGB_COLOR, 255);//����4B��ɫ
        heroNameLabel->setTextColor(heroNameLabelColor);
        heroNameLabel->setPosition(
            Vec2(HERO_NAME_LABEL_POSITION_X,
                HERO_NAME_LABEL_POSITION_Y));

        this->addChild(heroNameLabel, 1);
    }
    /*=====================�����������======================*/

    /*=====================����Ӣ��ѡ���ǩ��ʼ======================*/

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

    //δȷ��״̬����
    auto* normal = Sprite::create("rightSignNormal.png");
    //���״̬����
    auto* moving = Sprite::create("rightSignMoving.png");
    //����״̬����
    auto* selected = Sprite::create("rightSignSelected.png");
    _confirmButton = MenuItemSprite::create(normal, moving, selected);
    auto* menu = CCMenu::create(_confirmButton, NULL);
    menu->setPosition(HERO_CONFIRM_BUTTON_POSITION_X, HERO_CONFIRM_BUTTON_POSITION_Y);
    this->addChild(menu);
    _confirmButton->setTarget(this, menu_selector(HeroScene::selectHeroConfirmCallback));
    _confirmButton->setScale(0.5);

    return true;
    /*=====================����Ӣ��ѡ���ǩ��ʼ======================*/
    
}
/****************************
* Name ��heroBackCallback
* Summary ���������˵�
* return ��
****************************/
void HeroScene::heroBackCallback(cocos2d::Ref* pSender)
{
    auto* mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, mainMenuScene));//�����������
}
/****************************
* Name ��selectHero1Callback
* Summary ������hero1����ص�����
* return ��
****************************/
void HeroScene::selectHero1Callback(cocos2d::Ref* pSender)
{
    _chooseNumber = 1;                       //��ʾ��ʱ��hero1����
    if (slectedHero == 1)                    //���ȷ��ѡ��hero1
        _confirmButton->setEnabled(false);   //��ť����Ϊ����
    else
        _confirmButton->setEnabled(true);

}
//ͬ��
void HeroScene::selectHero2Callback(cocos2d::Ref* pSender)
{
    _chooseNumber = 2;
    if (slectedHero == 2)
        _confirmButton->setEnabled(false);
    else
        _confirmButton->setEnabled(true);
}
//ͬ��
void HeroScene::selectHero3Callback(cocos2d::Ref* pSender)
{
    _chooseNumber = 3;
    if (slectedHero == 3)
        _confirmButton->setEnabled(false);
    else
        _confirmButton->setEnabled(true);
}
//ͬ��
void HeroScene::selectHero4Callback(cocos2d::Ref* pSender)
{
    _chooseNumber = 4;
    if (slectedHero == 4)
        _confirmButton->setEnabled(false);
    else
        _confirmButton->setEnabled(true);
}
/****************************
* Name ��selectHeroConfirmCallback
* Summary �����ȷ�ϰ�ť�Ļص�����
* return ��
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