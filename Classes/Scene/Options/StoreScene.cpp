//���ߣ�����
//���ڣ�2022-5-21
//ʵ�֣���ܴ

//���ߣ���Ԫ��
//���ڣ�2022-6-6
//ʵ�֣����幦��ʵ��

#include "StoreScene.h"
#include "ui/CocosGUI.h"
using namespace ui;

/****************************
* Name ��StoreScene::createScene
* Summary ����������
* return ��������ָ��
****************************/
Scene* StoreScene::createScene()
{
    return StoreScene::create();
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

bool StoreScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/to_a_new_scene.mp3");

    /*=====================�������ذ�ť��ʼ======================*/

    //�������ذ�ť
    auto storeBackItem = MenuItemImage::create(
        "ui/backSettingsNormal.png",
        "ui/backSettingsSelected.png",
        CC_CALLBACK_1(StoreScene::storeBackCallback, this));

    if (storeBackItem == nullptr ||
        storeBackItem->getContentSize().width <= 0 ||
        storeBackItem->getContentSize().height <= 0)
    {
        problemLoading("'ui/backSettingsNormal.png' and 'ui/backSettingsSelected.png'");
    }
    else
    {
        storeBackItem->setPosition(Vec2(STORE_BACK_ITEM_POSITION_X,
            STORE_BACK_ITEM_POSITION_Y));
    }
    //�������ز˵�
    auto backMenu = Menu::create(storeBackItem, NULL);
    backMenu->setPosition(Vec2::ZERO);
    this->addChild(backMenu, 2);
    /*=====================�����رհ�ť����====================*/

    /*=====================�������⿪ʼ=======================*/

    auto storeNameLabel = Label::createWithTTF(
        "MAP",
        "fonts/PixeloidSans.ttf",
        SETTINGS_NAME_LABEL_SIZE
    );//�����ı�
    if (storeNameLabel == nullptr)
    {
        problemLoading("'fonts/PixeloidSans.ttf'");
    }
    else
    {
        const Color4B storeNameLabelColor(STORE_NAME_LABEL_COLOR, 255);//����4B��ɫ
        storeNameLabel->setTextColor(storeNameLabelColor);
        storeNameLabel->setPosition(
            Vec2(STORE_NAME_LABEL_POSITION_X,
                STORE_NAME_LABEL_POSITION_Y)
        );
        this->addChild(storeNameLabel, 1);
    }
    /*=====================�����������=======================*/

    /*=====================��������ͼ��ʼ======================*/
    auto background = Sprite::create("background/storeBackground.png");
    background->setOpacity(120);
    if (background == nullptr)
    {
        problemLoading("'background/storeBackground.png'");
    }
    else
    {
        background->setPosition(Vec2(SETTINGS_BACKGROUND_POSITION_X,
            SETTINGS_BACKGROUND_POSITION_Y));

        this->addChild(background, 0);
    }
    /*=====================��������ͼ����======================*/

    /*=====================����������������ʼ======================*/

    //�����ɻ�������
    ScrollView* storeView = ScrollView::create();
    storeView->setBounceEnabled(true);
    storeView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    storeView->setDirection(ScrollView::Direction::BOTH); //����Ϊ���򻬶�
    Size storeViewSize;
    storeViewSize.setSize(STORE_STOREVIEW_SIZE);                       //���û������ڴ�С
    storeView->setContentSize(storeViewSize);
    storeView->setInnerContainerSize(Size(STORE_STOREVIEW_INNER_CONTAINER_SIZE));      //�����ڲ��ɻ�������Ĵ�С
    storeView->setPosition(Vec2(STORE_STOREVIEW_POSITION_X, STORE_STOREVIEW_POSITION_Y));


    auto storeContainer = Sprite::create("ui/storeContainer.png");                 //�����̵걳��
    storeContainer->setPosition(Vec2(STORE_STOREVIEW_POSITION_X, STORE_STOREVIEW_POSITION_Y));
    //storeContainer->setScale(1.35);
    this->addChild(storeView, 1);
    this->addChild(storeContainer);
    /*=====================������������������======================*/

    /*=====================��ͼ��ӿ�ʼ======================*/

    auto MapUpdatedOverview_1 = MenuItemImage::create("commodity/MapUpdatedOverview_1.png",
        "commodity/MapUpdatedOverviewSelected_1.png",
        CC_CALLBACK_1(StoreScene::storeSelectMap1Callback, this));
    MapUpdatedOverview_1->setPosition(Vec2(STORE_MAP_UPDATED_OVERVIEW_POSITION_1));

    auto MapUpdatedOverviewName_1 = LabelTTF::create("CLASSIC MAP", "fonts/Lilita one.ttf", 28);
    MapUpdatedOverviewName_1->setColor(Color3B::WHITE);
    MapUpdatedOverviewName_1->setPosition(Vec2(STORE_MAP_UPDATED_OVERVIEW_NAME_POSITION_1));
    MapUpdatedOverviewName_1->enableShadow(STORE_MAP_UPDATED_OVERVIEW_NAME_SHADOW_1);
    storeView->addChild(MapUpdatedOverviewName_1);


    auto MapUpdatedOverview_3 = MenuItemImage::create("commodity/MapUpdatedOverview_3.png",
        "commodity/MapUpdatedOverview_3.png",
        CC_CALLBACK_1(StoreScene::storeSelectMap3Callback, this));
    MapUpdatedOverview_3->setPosition(Vec2(STORE_MAP_UPDATED_OVERVIEW_POSITION_3));

    auto MapUpdatedOverviewName_3 = LabelTTF::create("OBSTACLES-TERRAIN MAP", "fonts/Lilita one.ttf", 28);
    MapUpdatedOverviewName_3->setColor(Color3B::WHITE);
    MapUpdatedOverviewName_3->setPosition(Vec2(STORE_MAP_UPDATED_OVERVIEW_NAME_POSITION_3));
    MapUpdatedOverviewName_3->enableShadow(STORE_MAP_UPDATED_OVERVIEW_NAME_SHADOW_3);
    storeView->addChild(MapUpdatedOverviewName_3);
    /*=====================��ͼ��ӿ�ʼ======================*/

    /*=====================�ʵ���ӿ�ʼ======================*/

    auto PaintedEggshell_1 = MenuItemImage::create("commodity/printed_eggshell_1.png",
        "commodity/printed_eggshell_1.png",
        CC_CALLBACK_1(StoreScene::storeEggshell1Callback, this));
    PaintedEggshell_1->setPosition(Vec2(STORE_PRINTED_EGGSHELL_POSITION_1));

    auto PaintedEggshell_2 = MenuItemImage::create("commodity/printed_eggshell_2.png",
        "commodity/printed_eggshell_2.png",
        CC_CALLBACK_1(StoreScene::storeEggshell2Callback, this));
    PaintedEggshell_2->setPosition(Vec2(STORE_PRINTED_EGGSHELL_POSITION_2));

    auto PaintedEggshell_3 = MenuItemImage::create("commodity/printed_eggshell_3.png",
        "commodity/printed_eggshell_3.png",
        CC_CALLBACK_1(StoreScene::storeEggshell3Callback, this));
    PaintedEggshell_3->setPosition(Vec2(STORE_PRINTED_EGGSHELL_POSITION_3));


    auto storeViewMenu = Menu::create(MapUpdatedOverview_1, MapUpdatedOverview_3,
        PaintedEggshell_1, PaintedEggshell_2, PaintedEggshell_3, NULL);
    storeView->addChild(storeViewMenu);

    _selectedMap = UserDefault::getInstance()->getIntegerForKey("selectedMap");

    storeView->jumpToLeft();   //��һ��ʼҳ���������

    return true;

    /*=====================��Ʒ��ӽ���======================*/

}


/****************************
* Name ��storeSelectMap1Callback
* Summary  �ص���������ѡ���ͼ���������˵�
* return ��
* ***************************/
void StoreScene::storeSelectMap1Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    log("Map1 Callback��");
    UserDefault::getInstance()->setIntegerForKey("selectedMap", 0);

    auto mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, mainMenuScene));//�����������
}


/****************************
* Name ��storeSelectMap3Callback
* Summary  �ص�������ѡ���ͼ���������˵�
* return ��
* ***************************/
void StoreScene::storeSelectMap3Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    log("Map3 Callback��");
    UserDefault::getInstance()->setIntegerForKey("selectedMap", 1);

    auto mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, mainMenuScene));//�����������
}


/****************************
* Name ��storeEggshell1Callback
* Summary  �ص��������������˵�
* return ��
* ***************************/
void StoreScene::storeEggshell1Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/printed_eggshell_1.mp3");
}


/****************************
* Name ��storeEggshell2Callback
* Summary  �ص��������������˵�
* return ��
* ***************************/
void StoreScene::storeEggshell2Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/printed_eggshell_2.mp3");
}


/****************************
* Name ��storeEggshell3Callback
* Summary  �ص��������������˵�
* return ��
* ***************************/
void StoreScene::storeEggshell3Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/printed_eggshell_3.mp3");
}






/****************************
* Name ��storeBackCallback
* Summary  �ص��������������˵�
* return ��
* ***************************/
void StoreScene::storeBackCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    auto mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, mainMenuScene));//�����������
}



