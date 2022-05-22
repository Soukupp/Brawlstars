//���ߣ�����
//���ڣ�2022-5-21
//ʵ�֣���ܴ

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

    /*=====================�������ذ�ť��ʼ======================*/

    //�������ذ�ť
    auto storeBackItem = MenuItemImage::create(
        "backSettingsNormal.png",
        "backSettingsSelected.png",
        CC_CALLBACK_1(StoreScene::storeBackCallback, this));

    if (storeBackItem == nullptr ||
        storeBackItem->getContentSize().width <= 0 ||
        storeBackItem->getContentSize().height <= 0)
    {//������
        problemLoading("'backSettingsNormal.png' and 'backSettingsSelected.png'");
    }
    else
    {//����λ��
        float x = STORE_BACK_ITEM_POSITION_X;
        float y = STORE_BACK_ITEM_POSITION_Y;
        storeBackItem->setPosition(Vec2(x, y));
    }
    //�������ز˵�
    auto backMenu = Menu::create(storeBackItem, NULL);
    backMenu->setPosition(Vec2::ZERO);
    this->addChild(backMenu, 2);
    /*=====================�����رհ�ť����====================*/

    /*=====================�������⿪ʼ=======================*/

    auto storeNameLabel = Label::createWithTTF(
        "STORE",
        "fonts/PixeloidSans.ttf",
        SETTINGS_NAME_LABEL_SIZE
    );//�����ı�
    if (storeNameLabel == nullptr)
    {
        problemLoading("'fonts/PixeloidSans.ttf'");
    }
    else
    {
        const Color4B storeNameLabelColor(SETTINGS_TEXT_RGB_COLOR, 255);//����4B��ɫ
        storeNameLabel->setTextColor(storeNameLabelColor);
        storeNameLabel->setPosition(
            Vec2(STORE_NAME_LABEL_POSITION_X,
                STORE_NAME_LABEL_POSITION_Y)
        );
        this->addChild(storeNameLabel, 1);
    }
    /*=====================�����������=======================*/

    /*=====================��������ͼ��ʼ======================*/
    auto background = Sprite::create("storeBackground.png");
    if (background == nullptr)
    {
        problemLoading("'storeBackground.png'");
    }
    else
    {
        //������ͼ��������
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
    storeView->setDirection(ScrollView::Direction::HORIZONTAL); //����Ϊ���򻬶�
    Size storeViewSize;
    storeViewSize.setSize(720, 360);                       //���û������ڴ�С
    storeView->setContentSize(storeViewSize);
    storeView->setInnerContainerSize(Size(2000,360));      //�����ڲ��ɻ�������Ĵ�С
    storeView->setPosition(Vec2(STORE_STOREVIEW_POSITION_X, STORE_STOREVIEW_POSITION_Y));


    auto storeContainer = Sprite::create("storeContainer.png");                 //�����̵걳��
    storeContainer->setPosition(Vec2(STORE_STOREVIEW_POSITION_X,STORE_STOREVIEW_POSITION_Y));
    storeContainer->setScale(1.35);
    this->addChild(storeView,1);
    this->addChild(storeContainer);
    /*=====================������������������======================*/

    /*=====================��Ʒ��ӿ�ʼ======================*/

    //��������
    Button* object1 = Button::create("eg1Normal.png", "eg1Selected.png");
    object1->setPosition(Vec2(200,100));
    storeView->addChild(object1);

    Button* object2 = Button::create("eg2Normal.png", "eg2Selected.png");
    object2->setPosition(Vec2(800, 150));
    storeView->addChild(object2);

    Button* object3 = Button::create("eg3Normal.png", "eg3Selected.png");
    object3->setPosition(Vec2(500, 120));
    storeView->addChild(object3);

    Button* object4 = Button::create("eg4Normal.png", "eg4Selected.png");
    object4->setPosition(Vec2(900, 130));
    storeView->addChild(object4);

    Button* object5 = Button::create("eg1Normal.png", "eg1Selected.png");
    object5->setPosition(Vec2(400, 170));
    storeView->addChild(object5);

    storeView->jumpToLeft();   //��һ��ʼҳ���������

    return true;

     /*=====================��Ʒ��ӽ���======================*/

}
/****************************
* Name ��storeBackCallback
* Summary  �ص��������������˵�
* return ��
* ***************************/

void StoreScene::storeBackCallback(cocos2d::Ref* pSender)
{
    auto mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, mainMenuScene));//�����������
}



