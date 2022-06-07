#pragma once
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
#define STORE_STOREVIEW_INNER_CONTAINER_SIZE 1600, 1000

#define STORE_MAP_UPDATED_OVERVIEW_POSITION_1 10, 150
#define STORE_MAP_UPDATED_OVERVIEW_NAME_POSITION_1  480, 500 - 0.5 * MapUpdatedOverview_1->getContentSize().height - 1.5 * MapUpdatedOverviewName_1->getContentSize().height
#define STORE_MAP_UPDATED_OVERVIEW_NAME_SHADOW_1 Size(5.0f, -5.0f), 150, 10, true

#define STORE_MAP_UPDATED_OVERVIEW_POSITION_3 710, 150
#define STORE_MAP_UPDATED_OVERVIEW_NAME_POSITION_3  1200, 500 - 0.5 * MapUpdatedOverview_3->getContentSize().height - 1.5 * MapUpdatedOverviewName_3->getContentSize().height
#define STORE_MAP_UPDATED_OVERVIEW_NAME_SHADOW_3 Size(5.0f, -5.0f), 150, 10, true

#define STORE_PRINTED_EGGSHELL_POSITION_1 -350, 150
#define STORE_PRINTED_EGGSHELL_POSITION_2 375, 400
#define STORE_PRINTED_EGGSHELL_POSITION_3 375, -60


#include "cocos2d.h"
#include "Scene/MainMenu/MainMenuScene.h"

class StoreScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    //关闭主界面回调函数
    void storeBackCallback(cocos2d::Ref* pSender);

    void storeSelectMap1Callback(cocos2d::Ref* pSender);
    void storeSelectMap3Callback(cocos2d::Ref* pSender);

    void storeEggshell1Callback(cocos2d::Ref* pSender);
    void storeEggshell2Callback(cocos2d::Ref* pSender);
    void storeEggshell3Callback(cocos2d::Ref* pSender);

    int _selectedMap = 0;

    //创建
    CREATE_FUNC(StoreScene);
};

#endif  //__STORE_SCENE_H__

