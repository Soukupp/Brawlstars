//���� : ��Ԫ��
//���� : 2022-5-18

//�޸� : ����
//���� : 2022-5-20
//������Playerͷ�ļ� Weaponͷ�ļ�
//�������Sprite���滻ΪPlayer�� 

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "MapLayer.h"
#include "Scene/Settings/GameSettingsScene.h"
#include "Scene/MainMenu/MainMenuScene.h"

#define GAME_SETTING_POSITION_X static_cast<float>(origin.x + visibleSize.width - 1.2 * SettingsItem->getContentSize().width / 2)
#define GAME_SETTING_POSITION_Y static_cast<float>(visibleSize.height - 1.2 * SettingsItem->getContentSize().height / 2)

#define GAME_SKILL_BUTTON_POSITION_X static_cast<float>(origin.x + 1.5 * 40)
#define GAME_SKILL_BUTTON_POSITION_Y static_cast<float>(origin.y + 1.5 * 40)


class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuCallback(cocos2d::Ref* pSender);
    void GameSettingsCallBack(cocos2d::Ref* pSender);

    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
