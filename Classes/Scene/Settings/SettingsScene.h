//作者 : 王鹏
//日期 : 2022-5-17
//实现 ：框架搭建
 
//作者 ：束赫
//日期 : 2022-5-19
//实现 ：具体功能实现

#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#define SETTINGS_BACK_ITEM_POSITION_X static_cast<float>(origin.x + settingsBackItem->getContentSize().width / 2)
#define SETTINGS_BACK_ITEM_POSITION_Y static_cast<float>(origin.y + settingsBackItem->getContentSize().height / 2)

#define SETTINGS_CLEAR_USERDATA_ITEM_POSITION_X static_cast<float>(origin.x + visibleSize.width - clearUserDataItem->getContentSize().width / 2)
#define SETTINGS_CLEAR_USERDATA_ITEM_POSITION_Y static_cast<float>(origin.y + 1.5 * clearUserDataItem->getContentSize().height / 2)

#define SETTINGS_CLEARUSERDATA_LABEL_POSITION_X static_cast<float>(origin.x + visibleSize.width - clearUserDataItem->getContentSize().width - clearUserDataLabel->getContentSize().width / 2)
#define SETTINGS_CLEARUSERDATA_LABEL_POSITION_Y static_cast<float>(origin.y + 1.5 * clearUserDataItem->getContentSize().height / 2)

#define SETTINGS_NAME_LABEL_POSITION_X static_cast<float>(origin.x + visibleSize.width / 2)
#define SETTINGS_NAME_LABEL_POSITION_Y static_cast<float>(origin.y + visibleSize.height - settingsNameLabel->getContentSize().height)

#define SETTINGS_BACKGROUND_POSITION_X static_cast<float>(visibleSize.width / 2 + origin.x)
#define SETTINGS_BACKGROUND_POSITION_Y static_cast<float>(visibleSize.height / 2 + origin.y)

#define SETTINGS_SETTINGSMENU_POSITION_X static_cast<float>(visibleSize.width / 2 + origin.x)
#define SETTINGS_SETTINGSMENU_POSITION_Y static_cast<float>(visibleSize.height / 2 * 1.25 + origin.y)

#define SETTINGS_SETTINGSMUSICLABEL_POSITION_X static_cast<float>(visibleSize.width / 2 * 0.5 + origin.x)
#define SETTINGS_SETTINGSMUSICLABEL_POSITION_Y static_cast<float>(visibleSize.height / 2 * 1.4 + origin.y)

#define SETTINGS_SETTINGMUSICSTATES_POSITION_X static_cast<float>(visibleSize.width / 4 + origin.x)
#define SETTINGS_SETTINGMUSICSTATES_POSITION_Y static_cast<float>(visibleSize.height / 2  + origin.y)

#define SETTINGS_SETTINGFPSSTATES_POSITION_X static_cast<float>(visibleSize.width / 7 -130)
#define SETTINGS_SETTINGFPSSTATES_POSITION_Y static_cast<float>(visibleSize.height /15-150)

#define SETTINGS_SETTINGSFPSLABEL_POSITION_X static_cast<float>(visibleSize.width / 4 + origin.x)
#define SETTINGS_SETTINGSFPSLABEL_POSITION_Y static_cast<float>(visibleSize.height / 3 + origin.y + 20)

#define SETTINGS_CHINESE_POSITION_X static_cast<float>(origin.x + visibleSize.width / 2 - itemChinese->getContentSize().width / 1.5)
#define SETTINGS_CHINESE_POSITION_Y static_cast<float>(origin.y + visibleSize.height / 4)
#define SETTINGS_ENGLISH_POSITION_X static_cast<float>(origin.x + visibleSize.width / 2 + itemEnglish->getContentSize().width / 1.5)
#define SETTINGS_ENGLISH_POSITION_Y static_cast<float>(origin.y + visibleSize.height / 4)

#define SETTINGS_LANGUAGE_RGB_COLOR 55, 55, 55

#define SETTINGS_TEXT_RGB_COLOR 0, 0, 0

#define SETTINGS_NAME_LABEL_SIZE 64


#include "cocos2d.h"
#include "Scene/MainMenu/MainMenuScene.h"
#include "Tools.h"
#include "../ui/UISlider.h"
#include <cocos/ui/UIText.h>

using namespace cocos2d::ui;


class SettingsScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();    //返回主菜单回调函数

    void settingsBackCallback(cocos2d::Ref* pSender);    //按钮回调函数
    void settingsPlayCallBack(cocos2d::Ref* pSender);

    void choseChineseCallback(cocos2d::Ref* pSender);
    void choseEnglishCallback(cocos2d::Ref* pSender);

    void clearUserDataCallback(cocos2d::Ref* pSender);

    void sliderEvent(Ref* pSender, Slider::EventType type);   //滑动事件监听

    void settingsFPSCallBack(cocos2d::Ref* pSender);

    CREATE_FUNC(SettingsScene);

private:
    Text* _displayedPercentage;          //显示音量百分比
    //Text* _displayedMusicStates = Text::create("MUSIC ON", "fonts/PixeloidSans.ttf", 27);    //显示音乐开关
    //Text* _displayedFPSStates = Text::create("FPS DISPLAY", "fonts/PixeloidSans.ttf", 27);   //显示FPS显示或隐藏
    Label* _displayedMusicStates = Label::create("MUSIC ON", "Maiandra GD", 35);
    Label* _displayedFPSStates = Label::create("FPS DISPLAY", "Maiandra GD", 35);
};

#endif  //__SETTINGS_SCENE_H__
