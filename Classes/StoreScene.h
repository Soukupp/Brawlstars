#pragma once
//���ߣ�����
//���ڣ�2022-5-21
//ʵ�֣���ܴ

#ifndef __STORE_SCENE_H__
#define __STORE_SCENE_H__

#define STORE_BACK_ITEM_POSITION_X origin.x + storeBackItem->getContentSize().width / 2
#define STORE_BACK_ITEM_POSITION_Y origin.y + storeBackItem->getContentSize().height / 2

#define STORE_NAME_LABEL_POSITION_X origin.x + visibleSize.width / 2
#define STORE_NAME_LABEL_POSITION_Y origin.y + visibleSize.height - storeNameLabel->getContentSize().height

#define STORE_STOREVIEW_POSITION_X origin.x + visibleSize.width/2
#define STORE_STOREVIEW_POSITION_Y origin.x + visibleSize.height/2

#include "cocos2d.h"
#include "MainMenuScene.h"

class StoreScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    //�ر�������ص�����
    void storeBackCallback(cocos2d::Ref* pSender);

    //����
    CREATE_FUNC(StoreScene);
};

#endif  //__STORE_SCENE_H__

