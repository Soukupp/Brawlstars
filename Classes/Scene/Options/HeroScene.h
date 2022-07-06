#pragma once
//���ߣ�����
//ʱ�䣺2022-5-20
#ifndef __HERO_SCENE_H__
#define __HERO_SCENE_H__

#define HERO_BACK_ITEM_POSITION_X static_cast<float>(origin.x + heroBackItem->getContentSize().width / 2)
#define HERO_BACK_ITEM_POSITION_Y static_cast<float>(origin.y + heroBackItem->getContentSize().height / 2)

#define HERO_NAME_LABEL_POSITION_X static_cast<float>(origin.x + visibleSize.width / 2)
#define HERO_NAME_LABEL_POSITION_Y static_cast<float>(origin.y + visibleSize.height - heroNameLabel->getContentSize().height)

#define HERO1_SELECTED_BUTTON_POSITION_X static_cast<float>(origin.x + visibleSize.width / 4)
#define HERO1_SELECTED_BUTTON_POSITION_Y static_cast<float>(origin.y + visibleSize.height / 5*4)

#define HERO2_SELECTED_BUTTON_POSITION_X static_cast<float>(origin.x + visibleSize.width / 4)
#define HERO2_SELECTED_BUTTON_POSITION_Y static_cast<float>(origin.y + visibleSize.height / 5*3)

#define HERO3_SELECTED_BUTTON_POSITION_X static_cast<float>(origin.x + visibleSize.width / 4)
#define HERO3_SELECTED_BUTTON_POSITION_Y static_cast<float>(origin.y + visibleSize.height / 5*2)

#define HERO4_SELECTED_BUTTON_POSITION_X static_cast<float>(origin.x + visibleSize.width / 4)
#define HERO4_SELECTED_BUTTON_POSITION_Y static_cast<float>(origin.y + visibleSize.height / 5*1)

#define HERO_CONFIRM_BUTTON_POSITION_X  static_cast<float>(origin.x + visibleSize.width / 4*3)
#define HERO_CONFIRM_BUTTON_POSITION_Y  static_cast<float>(origin.y + visibleSize.height / 5)

#define HERO_INFO_ITEM_POSITION_X static_cast<float>(origin.x + visibleSize.width - heroInformation->getContentSize().width)
#define HERO_INFO_ITEM_POSITION_Y static_cast<float>(visibleSize.height - 1.2 * heroInformation->getContentSize().height / 2)

#include "cocos2d.h"
#include "Scene/MainMenu/MainMenuScene.h"
#include "Scene/Information/InformationPopLayer.h"
#include "Entity/Player/Player.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class HeroScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    void heroBackCallback(cocos2d::Ref* pSender);//�������˵��ص�����

    //����Ӣ��չʾ����Ļص�����
    void selectHero1Callback(cocos2d::Ref* pSender);
    void selectHero2Callback(cocos2d::Ref* pSender);
    void selectHero3Callback(cocos2d::Ref* pSender);
    void selectHero4Callback(cocos2d::Ref* pSender);
    void SelectHeroInformationCallback(cocos2d::Ref* pSender);

    //ȷ�ϰ�ť�ص�����
    void selectHeroConfirmCallback(cocos2d::Ref* pSender);

    void animate1();
    void animate2();
    void animate3();
    void animate4();

private:
    MenuItemSprite* _confirmButton;  //ȷ�ϰ���
    int _chooseNumber = 1;           //��ʾ��ǰѡ��ҳ��λ�ڼ���hero
    int _selectedHero = 1;
    CREATE_FUNC(HeroScene);

    Sprite* hero1;
    Sprite* hero2;
    Sprite* hero3;
    Sprite* hero4;

};
#endif  //__HERO_SCENE_H__
