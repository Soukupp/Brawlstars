//作者：束赫
//日期：2022-5-21
//实现：框架搭建

#include "StoreScene.h"
#include "ui/CocosGUI.h"
using namespace ui;

/****************************
* Name ：StoreScene::createScene
* Summary ：创建场景
* return ：场景类指针
****************************/
Scene* StoreScene::createScene()
{
    return StoreScene::create();
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

bool StoreScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*=====================创建返回按钮开始======================*/

    //创建返回按钮
    auto storeBackItem = MenuItemImage::create(
        "backSettingsNormal.png",
        "backSettingsSelected.png",
        CC_CALLBACK_1(StoreScene::storeBackCallback, this));

    if (storeBackItem == nullptr ||
        storeBackItem->getContentSize().width <= 0 ||
        storeBackItem->getContentSize().height <= 0)
    {//错误处理
        problemLoading("'backSettingsNormal.png' and 'backSettingsSelected.png'");
    }
    else
    {//设置位置
        float x = STORE_BACK_ITEM_POSITION_X;
        float y = STORE_BACK_ITEM_POSITION_Y;
        storeBackItem->setPosition(Vec2(x, y));
    }
    //创建返回菜单
    auto backMenu = Menu::create(storeBackItem, NULL);
    backMenu->setPosition(Vec2::ZERO);
    this->addChild(backMenu, 2);
    /*=====================创建关闭按钮结束====================*/

    /*=====================创建标题开始=======================*/

    auto storeNameLabel = Label::createWithTTF(
        "STORE",
        "fonts/PixeloidSans.ttf",
        SETTINGS_NAME_LABEL_SIZE
    );//创建文本
    if (storeNameLabel == nullptr)
    {
        problemLoading("'fonts/PixeloidSans.ttf'");
    }
    else
    {
        const Color4B storeNameLabelColor(SETTINGS_TEXT_RGB_COLOR, 255);//创建4B颜色
        storeNameLabel->setTextColor(storeNameLabelColor);
        storeNameLabel->setPosition(
            Vec2(STORE_NAME_LABEL_POSITION_X,
                STORE_NAME_LABEL_POSITION_Y)
        );
        this->addChild(storeNameLabel, 1);
    }
    /*=====================创建标题结束=======================*/

    /*=====================创建背景图开始======================*/
    auto background = Sprite::create("storeBackground.png");
    if (background == nullptr)
    {
        problemLoading("'storeBackground.png'");
    }
    else
    {
        //将背景图放在中央
        background->setPosition(Vec2(SETTINGS_BACKGROUND_POSITION_X,
            SETTINGS_BACKGROUND_POSITION_Y));

        this->addChild(background, 0);
    }
    /*=====================创建背景图结束======================*/

    /*=====================创建滚动层容器开始======================*/
    
    //创建可滑动区域
    ScrollView* storeView = ScrollView::create();          
    storeView->setBounceEnabled(true);
    storeView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    storeView->setDirection(ScrollView::Direction::HORIZONTAL); //设置为横向滑动
    Size storeViewSize;
    storeViewSize.setSize(720, 360);                       //设置滑动窗口大小
    storeView->setContentSize(storeViewSize);
    storeView->setInnerContainerSize(Size(2000,360));      //设置内部可滑动区域的大小
    storeView->setPosition(Vec2(STORE_STOREVIEW_POSITION_X, STORE_STOREVIEW_POSITION_Y));


    auto storeContainer = Sprite::create("storeContainer.png");                 //设置商店背景
    storeContainer->setPosition(Vec2(STORE_STOREVIEW_POSITION_X,STORE_STOREVIEW_POSITION_Y));
    storeContainer->setScale(1.35);
    this->addChild(storeView,1);
    this->addChild(storeContainer);
    /*=====================创建滚动层容器结束======================*/

    /*=====================商品添加开始======================*/

    //测试用例
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

    storeView->jumpToLeft();   //让一开始页面在最左边

    return true;

     /*=====================商品添加结束======================*/

}
/****************************
* Name ：storeBackCallback
* Summary  回调函数，返回主菜单
* return ：
* ***************************/

void StoreScene::storeBackCallback(cocos2d::Ref* pSender)
{
    auto mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, mainMenuScene));//过场动画设计
}



