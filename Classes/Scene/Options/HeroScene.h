#pragma once
//作者：束赫
//时间：2022-5-20
#ifndef __HERO_SCENE_H__
#define __HERO_SCENE_H__

#define HERO_BACK_ITEM_POSITION_X origin.x + heroBackItem->getContentSize().width / 2
#define HERO_BACK_ITEM_POSITION_Y origin.y + heroBackItem->getContentSize().height / 2
#define HERO_NAME_LABEL_POSITION_X origin.x + visibleSize.width / 2
#define HERO_NAME_LABEL_POSITION_Y origin.y + visibleSize.height - heroNameLabel->getContentSize().height
#define HERO1_SELECTED_BUTTON_POSITION_X origin.x + visibleSize.width / 4
#define HERO1_SELECTED_BUTTON_POSITION_Y origin.y + visibleSize.height / 5*4
#define HERO2_SELECTED_BUTTON_POSITION_X origin.x + visibleSize.width / 4
#define HERO2_SELECTED_BUTTON_POSITION_Y origin.y + visibleSize.height / 5*3
#define HERO3_SELECTED_BUTTON_POSITION_X origin.x + visibleSize.width / 4
#define HERO3_SELECTED_BUTTON_POSITION_Y origin.y + visibleSize.height / 5*2
#define HERO4_SELECTED_BUTTON_POSITION_X origin.x + visibleSize.width / 4
#define HERO4_SELECTED_BUTTON_POSITION_Y origin.y + visibleSize.height / 5*1

#define HERO_CONFIRM_BUTTON_POSITION_X  origin.x + visibleSize.width / 4*3
#define HERO_CONFIRM_BUTTON_POSITION_Y  origin.y + visibleSize.height / 5
#include "cocos2d.h"
#include "Scene/MainMenu/MainMenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class HeroScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    //返回主菜单回调函数
    void heroBackCallback(cocos2d::Ref* pSender);

    //进入英雄展示界面的回调函数
    void selectHero1Callback(cocos2d::Ref* pSender);
    void selectHero2Callback(cocos2d::Ref* pSender);
    void selectHero3Callback(cocos2d::Ref* pSender);
    void selectHero4Callback(cocos2d::Ref* pSender);

    //确认按钮回调函数
    void selectHeroConfirmCallback(cocos2d::Ref* pSender);


private:
    MenuItemSprite* _confirmButton;  //确认按键
    int _chooseNumber = 1;           //表示当前选择页面位于几号hero
    CREATE_FUNC(HeroScene);

};
#endif  //__HERO_SCENE_H__
