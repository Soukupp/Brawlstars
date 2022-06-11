//作者：束赫
//日期：2022-5-21
//实现：框架搭建

//作者：李元特
//日期：2022-6-6
//实现：具体功能实现

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

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/to_a_new_scene.mp3");

    /*=====================创建返回按钮开始======================*/

    //创建返回按钮
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
    //创建返回菜单
    auto backMenu = Menu::create(storeBackItem, NULL);
    backMenu->setPosition(Vec2::ZERO);
    this->addChild(backMenu, 2);

    /*=====================创建关闭按钮结束====================*/

    /*=====================创建标题开始=======================*/

    auto storeNameLabel = Label::createWithTTF(
        "MAP",
        "fonts/PixeloidSans.ttf",
        SETTINGS_NAME_LABEL_SIZE
    );//创建文本
    if (storeNameLabel == nullptr)
    {
        problemLoading("'fonts/PixeloidSans.ttf'");
    }
    else
    {
        const Color4B storeNameLabelColor(STORE_NAME_LABEL_COLOR, 255);//创建4B颜色
        storeNameLabel->setTextColor(storeNameLabelColor);
        storeNameLabel->setPosition(
            Vec2(STORE_NAME_LABEL_POSITION_X,
                STORE_NAME_LABEL_POSITION_Y)
        );
        this->addChild(storeNameLabel, 1);
    }

    /*=====================创建标题结束=======================*/

    /*=====================创建背景图开始======================*/

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

    /*=====================创建背景图结束======================*/

    /*创建游戏人数开始*/
    auto aiNumber5 = MenuItemImage::create("ui/gameNumber_5.png", "ui/gameNumber_5.png",
        CC_CALLBACK_1(StoreScene::Select_AI_5_Callback, this));
    aiNumber5->setPosition(Vec2(STORE_AI_NUMBER_5_POSITION));

    auto aiNumber6 = MenuItemImage::create("ui/gameNumber_6.png", "ui/gameNumber_6.png",
        CC_CALLBACK_1(StoreScene::Select_AI_6_Callback, this));
    aiNumber6->setPosition(Vec2(STORE_AI_NUMBER_6_POSITION));

    auto aiNumber7 = MenuItemImage::create("ui/gameNumber_7.png", "ui/gameNumber_7.png",
        CC_CALLBACK_1(StoreScene::Select_AI_7_Callback, this));
    aiNumber7->setPosition(Vec2(STORE_AI_NUMBER_7_POSITION));

    auto aiNumber8 = MenuItemImage::create("ui/gameNumber_8.png", "ui/gameNumber_8.png",
        CC_CALLBACK_1(StoreScene::Select_AI_8_Callback, this));
    aiNumber8->setPosition(Vec2(STORE_AI_NUMBER_8_POSITION));

    auto aiNumber9 = MenuItemImage::create("ui/gameNumber_9.png", "ui/gameNumber_9.png",
        CC_CALLBACK_1(StoreScene::Select_AI_9_Callback, this));
    aiNumber9->setPosition(Vec2(STORE_AI_NUMBER_9_POSITION));

    MenuItemFont::setFontName("fonts/Lilita one.ttf");
    MenuItemFont::setFontSize(25);
    MenuItemFont* aiNUmberTip = MenuItemFont::create(
        "Choose the number of NPC (DEFAULT NUMBER is 9)",
        CC_CALLBACK_1(StoreScene::AINumberTipCallback, this)
    );
    aiNUmberTip->setPosition(STORE_AI_TIP);
    
    MenuItemFont::setFontName("fonts/Lilita one.ttf");
    MenuItemFont::setFontSize(25);
    MenuItemFont* vincibleModeTip = MenuItemFont::create(
        "NORMAL MODE",
        CC_CALLBACK_1(StoreScene::Select_Vincible_Mode_Callback, this)
    );
    vincibleModeTip->setPosition(STORE_VINCIBLE_POSITION);

    MenuItemFont::setFontName("fonts/Lilita one.ttf");
    MenuItemFont::setFontSize(25);
    MenuItemFont* invincibleModeTip = MenuItemFont::create(
        "INVINCIBLE MODE",
        CC_CALLBACK_1(StoreScene::Select_Invincible_Mode_Callback, this)
    );
    invincibleModeTip->setPosition(STORE_INVINCIBLE_POSITION);


    auto aiNumberSelectMenu = Menu::create(aiNumber5, aiNumber6, aiNumber7,
        aiNumber8, aiNumber9, aiNUmberTip, vincibleModeTip, invincibleModeTip, NULL);
    aiNumberSelectMenu->setPosition(Vec2::ZERO);
    this->addChild(aiNumberSelectMenu, 2);  // 增加AI个数选择

    _selectedAINumber = UserDefault::getInstance()->getIntegerForKey("selectedAINumber");
    _selectedInvincible = UserDefault::getInstance()->getIntegerForKey("invincibleMode");

    /*=====================创建滚动层容器开始======================*/

    //创建可滑动区域
    ScrollView* storeView = ScrollView::create();
    storeView->setBounceEnabled(true);
    storeView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    storeView->setDirection(ScrollView::Direction::BOTH); //设置为横向滑动
    Size storeViewSize;
    storeViewSize.setSize(STORE_STOREVIEW_SIZE);                       //设置滑动窗口大小
    storeView->setContentSize(storeViewSize);
    storeView->setInnerContainerSize(Size(STORE_STOREVIEW_INNER_CONTAINER_SIZE));      //设置内部可滑动区域的大小
    storeView->setPosition(Vec2(STORE_STOREVIEW_POSITION_X, STORE_STOREVIEW_POSITION_Y));


    auto storeContainer = Sprite::create("ui/storeContainer.png");                 //设置商店背景
    storeContainer->setPosition(Vec2(STORE_STOREVIEW_POSITION_X, STORE_STOREVIEW_POSITION_Y));
    //storeContainer->setScale(1.35);
    this->addChild(storeView, 1);
    this->addChild(storeContainer);

    /*=====================创建滚动层容器结束======================*/

    /*=====================地图添加开始======================*/

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

    /*=====================地图添加开始======================*/

    /*=====================彩蛋添加开始======================*/

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

    storeView->jumpToLeft();   //让一开始页面在最左边

    return true;

    /*=====================商品添加结束======================*/

}

/****************************
* Name ：StoreScene::storeSelectMap1Callback
* Summary  回调函数，，选择地图，返回主菜单
* return ：
* ***************************/
void StoreScene::storeSelectMap1Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    log("Map1 Callback！");
    UserDefault::getInstance()->setIntegerForKey("selectedMap", 0);

    auto mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, mainMenuScene));//过场动画设计
}

/****************************
* Name ：StoreScene::Select_AI_5_Callback
* Summary ：AI人数为5
* return ：
* ***************************/
void StoreScene::Select_AI_5_Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/select_ok.mp3");
    UserDefault::getInstance()->setIntegerForKey("selectedAINUmber", 5);
}

/****************************
* Name ：StoreScene::Select_AI_6_Callback
* Summary ：AI人数为6
* return ：
* ***************************/
void StoreScene::Select_AI_6_Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/select_ok.mp3");
    UserDefault::getInstance()->setIntegerForKey("selectedAINUmber", 6);
}

/****************************
* Name ：StoreScene::Select_AI_7_Callback
* Summary ：AI人数为7
* return ：
* ***************************/
void StoreScene::Select_AI_7_Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/select_ok.mp3");
    UserDefault::getInstance()->setIntegerForKey("selectedAINUmber", 7);
}

/****************************
* Name ：StoreScene::Select_AI_8_Callback
* Summary ：AI人数为8
* return ：
* ***************************/
void StoreScene::Select_AI_8_Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/select_ok.mp3");
    UserDefault::getInstance()->setIntegerForKey("selectedAINUmber", 8);
}

/****************************
* Name ：StoreScene::Select_AI_9_Callback
* Summary ：AI人数为9
* return ：
* ***************************/
void StoreScene::Select_AI_9_Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/select_ok.mp3");
    UserDefault::getInstance()->setIntegerForKey("selectedAINUmber", 9);
}

/****************************
* Name ：StoreScene::AINumberTipCallback
* Summary ：小彩蛋
* return ：
* ***************************/
void StoreScene::AINumberTipCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/store_ai_number.mp3");
}

/****************************
* Name ：StoreScene::Select_Vincible_Mode_Callback
* Summary ：选择正常模式
* return ：
* ***************************/
void StoreScene::Select_Vincible_Mode_Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/select_ok.mp3");
    UserDefault::getInstance()->setIntegerForKey("invincibleMode", 0); // 常规模式
    //_selectedInvincible = 0;
    log("mode 0 selected");
    log("now mode %d", UserDefault::getInstance()->getIntegerForKey("invincibleMode"));
}

/****************************
* Name ：StoreScene::Select_Invincible_Mode_Callback
* Summary ：选择无敌模式
* return ：
* ***************************/
void StoreScene::Select_Invincible_Mode_Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/select_ok.mp3");
    UserDefault::getInstance()->setIntegerForKey("invincibleMode", 1); // 无敌模式
    //_selectedInvincible = 1;
    log("mode 1 selected");
    log("now mode %d", UserDefault::getInstance()->getIntegerForKey("invincibleMode"));
}

/****************************
* Name ：StoreScene::storeSelectMap3Callback
* Summary  回调函数，选择地图，返回主菜单
* return ：
* ***************************/
void StoreScene::storeSelectMap3Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    log("Map3 Callback！");
    UserDefault::getInstance()->setIntegerForKey("selectedMap", 1);

    auto mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, mainMenuScene));//过场动画设计
}

/****************************
* Name ：StoreScene::storeEggshell1Callback
* Summary  回调函数，返回主菜单
* return ：
* ***************************/
void StoreScene::storeEggshell1Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/printed_eggshell_1.mp3");
}

/****************************
* Name ：StoreScene::storeEggshell2Callback
* Summary  回调函数，返回主菜单
* return ：
* ***************************/
void StoreScene::storeEggshell2Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/printed_eggshell_2.mp3");
}

/****************************
* Name ：StoreScene::storeEggshell3Callback
* Summary  回调函数，返回主菜单
* return ：
* ***************************/
void StoreScene::storeEggshell3Callback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/printed_eggshell_3.mp3");
}


/****************************
* Name ：StoreScene::storeBackCallback
* Summary  回调函数，返回主菜单
* return ：
* ***************************/
void StoreScene::storeBackCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
    auto mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, mainMenuScene));//过场动画设计
}



