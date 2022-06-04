//作者 : 李元特
//日期 : 2022-5-20

#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "Entity/Player/Hero/Hero1.h"
#include "Entity/Player/Hero/Hero2.h"
#include <vector>
#include <string>

#define MAP_SAFEAREA_SIZE 1920
#define MAP_SAFEAREA_POSITION MAP_SAFEAREA_SIZE / 2,  MAP_SAFEAREA_SIZE / 2
#define MAP_SAFEAREA_APPEAR_TIMES 15
#define MAP_SAFEAREA_DELAY_LAST 10.0f
#define MAP_SAFEAREA_INTERVAL_LAST 0.5f
#define MAP_FOG_DENSITY 16


class MapLayer : public cocos2d::Layer
{
    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::TMXLayer* _collidable;
    cocos2d::TMXLayer* _watermonster;
    cocos2d::TMXLayer* _tree;
    Sprite* _treecell;
    /**/
    Hero1* _player1;
    Weapon* _weapon1;
    Slider* _healthBar1;
    Slider* _magicBar1;
    cocos2d::Label* _levelText1;
    /**/
    Hero2* _player;
    Weapon* _weapon;
    Slider* _healthBar;
    Slider* _magicBar;
    cocos2d::Label* _levelText;

    bool FogIsPlaced[1920][1920];

    std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap; // 判断鼠标有无释放

public:

    cocos2d::Sprite* _SafeArea;

    static cocos2d::Scene* createScene();
    virtual bool init();

    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); // 必须要加作用域！！！
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); // 必须要加作用域！！！

    void update(float delta);
    void update2(float delta);
    void updateForFog(float delta);
    void updatePlayerHurtByFog(float delta);
    void updateOutsideFog(float delta);

    void setPlayerPosition(cocos2d::Vec2 position);
    void setTreeOpacity(cocos2d::Vec2 position);
    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
    void setViewpointCenter(cocos2d::Vec2 position);

    template<typename Hero>
    void createHero(Hero** hero, Weapon** weapon, Slider** healthBar, Slider** magicBar, Label** levelText,
        Vec2& position, const std::string& filenameHero, const std::string& filenameWeapon);

    Animation* getAnimationByName(std::string fileName, float interval, int fileNum, int if_repeat = -1);
    // implement the "static create()" method manually
    CREATE_FUNC(MapLayer);
};

#endif // __Map_Layer_H__
