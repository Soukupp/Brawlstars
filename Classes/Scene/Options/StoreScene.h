//作者：束赫
//日期：2022-5-21
//实现：框架搭建

#ifndef __STORE_SCENE_H__
#define __STORE_SCENE_H__

#define STORE_BACK_ITEM_POSITION_X origin.x + storeBackItem->getContentSize().width / 2
#define STORE_BACK_ITEM_POSITION_Y origin.y + storeBackItem->getContentSize().height / 2

#define STORE_NAME_LABEL_POSITION_X origin.x + visibleSize.width / 2
#define STORE_NAME_LABEL_POSITION_Y origin.y + visibleSize.height - 0.8 * storeNameLabel->getContentSize().height
#define STORE_NAME_LABEL_COLOR 255, 140, 0

#define STORE_STOREVIEW_POSITION_X origin.x + visibleSize.width/2
#define STORE_STOREVIEW_POSITION_Y origin.x + visibleSize.height/2

#define STORE_STOREVIEW_SIZE 700, 400
#define STORE_STOREVIEW_INNER_CONTAINER_SIZE 1000, 550

#define STORE_MAP_UPDATED_OVERVIEW_POSITION_1 -200, -5
#define STORE_MAP_UPDATED_OVERVIEW_NAME_POSITION_1  250, 250 + 0.5 * MapUpdatedOverview_1->getContentSize().height - 6.5 * MapUpdatedOverviewName_1->getContentSize().height
#define STORE_MAP_UPDATED_OVERVIEW_NAME_SHADOW_1 Size(5.0f, -5.0f), 150, 10, true

#define STORE_MAP_UPDATED_OVERVIEW_POSITION_3 220, -5
#define STORE_MAP_UPDATED_OVERVIEW_NAME_POSITION_3  700, 250 + 0.5 * MapUpdatedOverview_3->getContentSize().height - 6.5 * MapUpdatedOverviewName_3->getContentSize().height
#define STORE_MAP_UPDATED_OVERVIEW_NAME_SHADOW_3 Size(5.0f, -5.0f), 150, 10, true

#define STORE_PRINTED_EGGSHELL_POSITION_1 -420, -60
#define STORE_PRINTED_EGGSHELL_POSITION_2 420, -55
#define STORE_PRINTED_EGGSHELL_POSITION_3 10, -55

#define STORE_AI_NUMBER_HEIGHT 75
#define STORE_AI_NUMBER_WIDTH 99

#define STORE_AI_NUMBER_5_POSITION  200, STORE_AI_NUMBER_HEIGHT
#define STORE_AI_NUMBER_6_POSITION  200 + STORE_AI_NUMBER_WIDTH, STORE_AI_NUMBER_HEIGHT
#define STORE_AI_NUMBER_7_POSITION  200 + 2 * STORE_AI_NUMBER_WIDTH, STORE_AI_NUMBER_HEIGHT
#define STORE_AI_NUMBER_8_POSITION  200 + 3 * STORE_AI_NUMBER_WIDTH, STORE_AI_NUMBER_HEIGHT
#define STORE_AI_NUMBER_9_POSITION  200 + 4 * STORE_AI_NUMBER_WIDTH, STORE_AI_NUMBER_HEIGHT
#define STORE_AI_TIP 460, 138

#define STORE_INVINCIBLE_POSITION 720, 650
#define STORE_VINCIBLE_POSITION 260, 650


#include "cocos2d.h"
#include "Scene/MainMenu/MainMenuScene.h"

class StoreScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void storeBackCallback(cocos2d::Ref* pSender);   //关闭主界面回调函数

    void Select_AI_5_Callback(cocos2d::Ref* pSender);
    void Select_AI_6_Callback(cocos2d::Ref* pSender);
    void Select_AI_7_Callback(cocos2d::Ref* pSender);
    void Select_AI_8_Callback(cocos2d::Ref* pSender);
    void Select_AI_9_Callback(cocos2d::Ref* pSender);

    void Select_Invincible_Mode_Callback(cocos2d::Ref* pSender);
    void Select_Vincible_Mode_Callback(cocos2d::Ref* pSender);

    void AINumberTipCallback(cocos2d::Ref* pSender);

    void storeSelectMap1Callback(cocos2d::Ref* pSender);
    void storeSelectMap3Callback(cocos2d::Ref* pSender);

    void storeEggshell1Callback(cocos2d::Ref* pSender);
    void storeEggshell2Callback(cocos2d::Ref* pSender);
    void storeEggshell3Callback(cocos2d::Ref* pSender);

    int _selectedMap = 0;

    int _selectedInvincible = 0;

    int _selectedAINumber = 9;

    CREATE_FUNC(StoreScene);     //创建
};

#endif  //__STORE_SCENE_H__

