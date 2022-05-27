//作者 : 李元特
//日期 : 2022-5-20

#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Entity/Player/Hero/Hero1.h"
#include "Entity/Player/Hero/Hero2.h"

class MapLayer : public cocos2d::Layer
{
    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::TMXLayer* _collidable;
    cocos2d::TMXLayer* _watermonster;
    /**/
    Hero1* _player1;
    Weapon* _weapon1;
    Slider* _healthBar1;
    Slider* _magicBar1;
    /**/
    Hero2* _player;
    Weapon* _weapon;
    Slider* _healthBar;
    Slider* _magicBar;

    std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap; // 判断鼠标有误释放

public:

    virtual bool init();

    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); // 必须要加作用域！！！
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); // 必须要加作用域！！！
    void update(float delta);


    void setPlayerPosition(cocos2d::Vec2 position);
    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
    void setViewpointCenter(cocos2d::Vec2 position);

    template<typename Hero>
    void createHero(Hero** hero, Weapon** weapon, Slider** healthBar, Slider** magicBar, Vec2& position, const std::string& filenameHero, const std::string& filenameWeapon);

    // implement the "static create()" method manually
    CREATE_FUNC(MapLayer);
};

#endif // __GAME_SCENE_H__
