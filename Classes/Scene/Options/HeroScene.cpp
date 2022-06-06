//���ߣ�����
//ʱ�䣺2022-5-20

//���ߣ���Ԫ��
//ʱ��: 2022-6-6
//�޸ģ����֣���Ч������update

#include "HeroScene.h"
#include "SimpleAudioEngine.h"
#include "Entity/Player/Player.h"

USING_NS_CC;

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

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/to_a_new_scene.mp3");

    /*=====================��������ͼ��ʼ======================*/
    auto heroBackground = Sprite::create("background/heroBackground.jpg");
    heroBackground->setOpacity(200);
    if (heroBackground == nullptr)
    {
        problemLoading("'background/heroBackground.jpg'");
    }
    else
    {
        heroBackground->setPosition(Vec2(SETTINGS_BACKGROUND_POSITION_X,
            SETTINGS_BACKGROUND_POSITION_Y));

        this->addChild(heroBackground, 0);
    }
    /*=====================��������ͼ����======================*/


    /*=====================�������ذ�ť��ʼ====================*/

    //�������ذ�ť
    auto heroBackItem = MenuItemImage::create(
        "ui/backSettingsNormal.png",
        "ui/backSettingsSelected.png",
        CC_CALLBACK_1(HeroScene::heroBackCallback, this));

    if (heroBackItem == nullptr ||
        heroBackItem->getContentSize().width <= 0 ||
        heroBackItem->getContentSize().height <= 0)
    {
        problemLoading("'ui/backSettingsNormal.png' and 'ui/backSettingsSelected.png'");
    }
    else
    {
        heroBackItem->setPosition(Vec2(HERO_BACK_ITEM_POSITION_X, HERO_BACK_ITEM_POSITION_Y));
    }
    //�������ز˵�
    auto backMenu = Menu::create(heroBackItem, NULL);
    backMenu->setPosition(Vec2::ZERO);
    this->addChild(backMenu, 2);
    /*=====================�������ذ�ť����==================*/

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
    auto* hero1LabelImage = MenuItemImage::create("ui/heroLabelNormal.png",
        "ui/heroLabelSelected.png", this, menu_selector(HeroScene::selectHero1Callback));

    auto* hero1LabelText = LabelTTF::create("HERO1", "Maiandra GD", 35);
    auto* hero1Label = MenuItemLabel::create(hero1LabelText,
        this, menu_selector(HeroScene::selectHero1Callback));

    auto* hero1Button = Menu::create(hero1LabelImage, hero1Label, NULL);
    hero1Button->setPosition(HERO1_SELECTED_BUTTON_POSITION_X, HERO1_SELECTED_BUTTON_POSITION_Y);

    this->addChild(hero1Button);

    //HERO2
    auto* hero2LabelImage = MenuItemImage::create("ui/heroLabelNormal.png",
        "ui/heroLabelSelected.png", this, menu_selector(HeroScene::selectHero2Callback));

    auto* hero2LabelText = LabelTTF::create("HERO2", "Maiandra GD", 35);
    auto* hero2Label = MenuItemLabel::create(hero2LabelText,
        this, menu_selector(HeroScene::selectHero2Callback));

    auto* hero2Button = Menu::create(hero2LabelImage, hero2Label, NULL);
    hero2Button->setPosition(HERO2_SELECTED_BUTTON_POSITION_X, HERO2_SELECTED_BUTTON_POSITION_Y);

    this->addChild(hero2Button);

    //HERO3
    auto* hero3LabelImage = MenuItemImage::create("ui/heroLabelNormal.png",
        "ui/heroLabelSelected.png", this, menu_selector(HeroScene::selectHero3Callback));

    auto* hero3LabelText = LabelTTF::create("HERO3", "Maiandra GD", 35);
    auto* hero3Label = MenuItemLabel::create(hero3LabelText,
        this, menu_selector(HeroScene::selectHero3Callback));

    auto* hero3Button = Menu::create(hero3LabelImage, hero3Label, NULL);
    hero3Button->setPosition(HERO3_SELECTED_BUTTON_POSITION_X, HERO3_SELECTED_BUTTON_POSITION_Y);

    this->addChild(hero3Button);

    //HERO4
    auto* hero4LabelImage = MenuItemImage::create("ui/heroLabelNormal.png",
        "ui/heroLabelSelected.png", this, menu_selector(HeroScene::selectHero4Callback));

    auto* hero4LabelText = LabelTTF::create("HERO4", "Maiandra GD", 35);
    auto* hero4Label = MenuItemLabel::create(hero4LabelText,
        this, menu_selector(HeroScene::selectHero3Callback));

    auto* hero4Button = Menu::create(hero4LabelImage, hero4Label, NULL);
    hero4Button->setPosition(HERO4_SELECTED_BUTTON_POSITION_X, HERO4_SELECTED_BUTTON_POSITION_Y);

    this->addChild(hero4Button);

    //δȷ��״̬����
    auto* normal = Sprite::create("ui/rightSignNormal.png");
    //���״̬����
    auto* moving = Sprite::create("ui/rightSignMoving.png");
    //����״̬����
    auto* selected = Sprite::create("ui/rightSignSelected.png");
    _confirmButton = MenuItemSprite::create(normal, moving, selected);
    auto* menu = CCMenu::create(_confirmButton, NULL);
    menu->setPosition(HERO_CONFIRM_BUTTON_POSITION_X, HERO_CONFIRM_BUTTON_POSITION_Y);
    this->addChild(menu);
    _confirmButton->setTarget(this, menu_selector(HeroScene::selectHeroConfirmCallback));
    _confirmButton->setScale(0.5);

   /*=====================����Ӣ��ѡ���ǩ����======================*/

   //�������Ѿ�ѡ����Ӣ�ۣ���ô����չʾ��Ӣ�۵Ķ���
       _selectedHero = UserDefault::getInstance()->getIntegerForKey("selectedHero");
    if (_selectedHero) {
        switch (_selectedHero) {
        case 1:
            animate1();
            break;
        case 2:
            animate2();
            break;
        case 3:
            animate3();
            break;
        case 4:
            break;
        }
        _confirmButton->setEnabled(false);
    }


    return true;
 
    
}


/****************************
* Name ��heroBackCallback
* Summary ���������˵�
* return ��
****************************/
void HeroScene::heroBackCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    AnimationCache::destroyInstance();
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    TextureCache::getInstance()->removeUnusedTextures();
    auto mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, mainMenuScene));//�����������
}


/****************************
* Name ��selectHero1Callback
* Summary ������hero1����ص�����
* return ��
****************************/
void HeroScene::selectHero1Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    if (_selectedHero == 1)                    //���ȷ��ѡ��hero1
        _confirmButton->setEnabled(false);   //��ť����Ϊ����
    else
        _confirmButton->setEnabled(true);

    if (_chooseNumber != 1) {

        if (hero2 != nullptr)
            hero2->setVisible(false);
        if (hero3 != nullptr)
            hero3->setVisible(false);
        if (hero4 != nullptr)
            hero4->setVisible(false);

        animate1();
        _chooseNumber = 1;
    }

}
//ͬ��

void HeroScene::selectHero2Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    if (_selectedHero == 2)
        _confirmButton->setEnabled(false);
    else
        _confirmButton->setEnabled(true);

    if (_chooseNumber != 2) {

        if (hero1 != nullptr)
            hero1->setVisible(false);
        if (hero3 != nullptr)
            hero3->setVisible(false);
        if (hero4 != nullptr)
            hero4->setVisible(false);

        animate2();
        _chooseNumber = 2;

    }
}
//ͬ��
void HeroScene::selectHero3Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    if (_selectedHero == 3)
        _confirmButton->setEnabled(false);
    else
        _confirmButton->setEnabled(true);
    if (_chooseNumber != 3) {

        if (hero1 != nullptr)
            hero1->setVisible(false);
        if (hero2 != nullptr)
            hero2->setVisible(false);
        if (hero4 != nullptr)
            hero4->setVisible(false);

        animate3();
        _chooseNumber = 3;
    }

}
//ͬ��
void HeroScene::selectHero4Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    if (_selectedHero == 4)
        _confirmButton->setEnabled(false);
    else
        _confirmButton->setEnabled(true);
    if (_chooseNumber != 4) {
        if (hero1 != nullptr)
            hero1->setVisible(false);
        if (hero2 != nullptr)
            hero2->setVisible(false);
        if (hero3 != nullptr)
            hero3->setVisible(false);

        animate4();
        _chooseNumber = 4;
    }

}


/****************************
* Name ��selectHeroConfirmCallback
* Summary �����ȷ�ϰ�ť�Ļص�����
* return ��
****************************/
void HeroScene::selectHeroConfirmCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    switch (_chooseNumber) {
    case 1:
        UserDefault::getInstance()->setIntegerForKey("selectedHero", 1);
        break;
    case 2:
        UserDefault::getInstance()->setIntegerForKey("selectedHero", 2);
        break;
    case 3:
        UserDefault::getInstance()->setIntegerForKey("selectedHero", 3);
        break;
    case 4:
        UserDefault::getInstance()->setIntegerForKey("selectedHero", 4);
        break;
    }
    _selectedHero= UserDefault::getInstance()->getIntegerForKey("selectedHero");
    _confirmButton->setEnabled(false);
}


/****************************
* Name ��animate1
* Summary ��hero1����ʵ��
* return ��
****************************/
void HeroScene::animate1()
{
    hero1 = Sprite::create("Character/Hero1/hero.png");
    hero1->setPosition(700, 350);
    addChild(hero1);
    auto* m_frameCache = CCSpriteFrameCache::getInstance();
    m_frameCache->addSpriteFramesWithFile("Character/Hero1/hero1_Start.plist", "Character/Hero1/hero1_Start.png");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/hero1.mp3");
    Vector<CCSpriteFrame*> hero1FrameArray;
    for (int i = 4; i < 8; i++)
    {
        auto frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("adventurer-idle (%d).png", i)->getCString());
        hero1FrameArray.pushBack(frame);
    }
    auto* animation1 = Animation::createWithSpriteFrames(hero1FrameArray);
    animation1->setDelayPerUnit(0.15f);
    animation1->setRestoreOriginalFrame(true);
    animation1->setLoops(-1);
    hero1->setScale(5.0f);
    auto* action1 = Animate::create(animation1);

    hero1->runAction(action1);
}


/****************************
* Name ��animate2
* Summary ��hero2����ʵ��
* return ��
****************************/
void HeroScene::animate2()
{
    hero2 = Sprite::create("Character/Hero2/hero.png");
    hero2->setPosition(700, 350);
    addChild(hero2);
    auto* m_frameCache = CCSpriteFrameCache::getInstance();
    m_frameCache->addSpriteFramesWithFile("Character/Hero2/hero2_Start.plist", "Character/Hero2/hero2_Start.png");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/hero2.mp3");
    Vector<CCSpriteFrame*> hero2FrameArray;
    for (int i = 1; i < 8; i++)
    {
        auto frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("skill0%d.png", i)->getCString());
        hero2FrameArray.pushBack(frame);
    }
    auto* animation1 = Animation::createWithSpriteFrames(hero2FrameArray);
    animation1->setDelayPerUnit(0.1f);
    animation1->setRestoreOriginalFrame(true);
    hero2->setScale(5.0f);
    auto* action1 = Animate::create(animation1);

    hero2->runAction(action1);
}


/****************************
* Name ��animate3
* Summary ��hero3����ʵ��
* return ��
****************************/
void HeroScene::animate3()
{
    hero3 = Sprite::create("Character/Hero3/hero.png");
    hero3->setPosition(700, 350);
    addChild(hero3);
    auto* m_frameCache = CCSpriteFrameCache::getInstance();
    m_frameCache->addSpriteFramesWithFile("Character/Hero3/hero3_Start.plist", "Character/Hero3/hero3_Start.png");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/hero3.mp3");
    Vector<CCSpriteFrame*> hero3FrameArray;
    for (int i = 1; i < 7; i++)
    {
        auto frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("Idle_0%d.png", i)->getCString());
        hero3FrameArray.pushBack(frame);
    }
    auto* animation = Animation::createWithSpriteFrames(hero3FrameArray);
    animation->setDelayPerUnit(0.1f);
    animation->setLoops(-1);
    hero3->setScale(3.0f);
    auto* action = Animate::create(animation);
    hero3->runAction(action);
}


/****************************
* Name ��animate4
* Summary ��hero4����ʵ��
* return ��
****************************/
void HeroScene::animate4()
{

}