#pragma once
//作者 : 李元特
//日期 : 2022-5-20


#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "Entity/Character.h"
#include "Entity/TheMonster.h"
#include "Scene/SpecialEffects/Shake.h"
#include "Tools.h"
#include <vector>
#include "string"
#include <ctime>

//MAP相关宏定义
#define MAP_SAFEAREA_SIZE 1920
#define MAP_SAFEAREA_POSITION MAP_SAFEAREA_SIZE / 2,  MAP_SAFEAREA_SIZE / 2
#define MAP_SAFEAREA_APPEAR_TIMES 5
#define MAP_SAFEAREA_DELAY_LAST 30.0f
#define MAP_SAFEAREA_INTERVAL_LAST 15.0f

#define MAP_FOG_DENSITY 24
#define MAP_FOG_DAMAGE_TO_PLAYER 2
#define MAP_PORTAL_SIZE 6
#define MAP_PLAYER_TO_AI_VISIBLE_SIZE 30
#define MAP_GM_NUMBER 16
#define MAP_WM_NUMBER 8
#define MAP_DM_NUMBER 14
#define MAP_PLAYER_NOT_IN_TREE 0
#define MAP_PLAYER_IN_TREE_AND_NOT_AROUND_AI 1
#define MAP_PLAYER_IN_TREE_AND_AROUND_AI 2
#define MAP_AI_NUMBER 9

//AI和player结构体数组宏定义
#define  CHARACTER(a) (allCharacter[a])

//player相关宏定义
#define  PLAYER (allCharacter[0]._player)
#define  WEAPON (allCharacter[0]._weapon)
#define  HEALTHBAR (allCharacter[0]._healthBar)
#define  MAGICBAR (allCharacter[0]._magicBar)
#define  LEVELTEXT (allCharacter[0]._levelText)

//AI相关宏定义
#define  AI_PLAYER(a) (allCharacter[a]._player)
#define  AI_WEAPON(a) (allCharacter[a]._weapon)
#define  AI_HEALTHBAR(a) (allCharacter[a]._healthBar)
#define  AI_MAGICBAR(a) (allCharacter[a]._magicBar)
#define  AI_LEVELTEXT(a) (allCharacter[a]._levelText)

//monster相关宏定义
#define THEMONSTER(a) (allMonster[a])
#define MONSTER(a) (allMonster[a]._monster)
#define MONSTER_HEALTHBAR(a) (allMonster[a]._healthBar)

#define MAPLAYER_SHAKERATE 50

class MapLayer : public cocos2d::Layer
{
private:

    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::TMXLayer* _collidable;
    cocos2d::TMXLayer* _watermonster;
    cocos2d::TMXLayer* _tree;
    Sprite* _treecell;

    std::vector<Character> allCharacter;
    Character tempCharacter;

    std::vector<TheMonster> allMonster;
    TheMonster tempMonster;

    Hero1* _player1;
    Hero2* _player2;
    Hero3* _player3;
    Hero4* _player4;

    DesertMonster* _monsterD;
    GroundMonster* _monsterG;
    WaterMonster* _monsterW;

    Weapon* _weapon;
    Slider* _healthBar;
    Slider* _magicBar;
    cocos2d::Label* _levelText;

    Sprite* _portal_1;
    Sprite* _portal_2;
    Sprite* _portal_3;
    Sprite* _portal_4;

    Sprite* _portal_Determination_1;
    Sprite* _portal_Determination_2;
    Sprite* _portal_Determination_3;
    Sprite* _portal_Determination_4;

    Vec2 deathPosition;

    int _fogTurn = 0;
    int _numOfPlayer;
    int _invincibleMode;


    bool aroundPlayer[10] = { false,false,false,false,false,false,false,false,false,false };

    int playerOpacity = 0;  // MAP_PLAYER_NOT_IN_TREE 表示人可见，且不在树丛里
                                                 //   1   // 表示人在树丛里，树丛半透明，且AI不在人的周围
                                                 //   2   // 表示人在树丛里，树丛半透明，且AI在人的周围

    std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap; // 判断鼠标有无释放

    bool _fogIsPlaced[1920][1920];


public:

    cocos2d::Sprite* _SafeArea;

    static cocos2d::Scene* createScene();
    virtual bool init();
    bool initTilemap();
    bool initCharacter();
    bool initSafeArea();
    bool initAICharacter();
    bool initAllMonster();
    bool initPortal();
    bool initDeathPosition();

    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); 
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); 

    void update(float delta);
    void updatePlayerDoAttack(float delta);
    void updateForPortal(float delta);
    void updateForFog(float delta);
    void updatePlayerHurtByFog(float delta);
    void updateOutsideFog(float delta);

    void updateAIMove(float delta);                      //AI遍历
    void updateAIMoveOne(Character& character);          //单个AI的移动实现
    void updateAIAttack(float delta);                    //AI碰撞检测

    void updateSetIfPlayAttackAnimation(float delta);

    void setPlayerPosition(cocos2d::Vec2 position);
    void setTreeOpacity(cocos2d::Vec2 position);
    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
    void setViewpointCenter(cocos2d::Vec2 position);

    int getPlayerRank();
    int getHitNum();

    template<typename Hero>
    void createHero(Hero** hero, Weapon** weapon, Slider** healthBar, Slider** magicBar, Label** levelText,
        Vec2& position, const std::string& filenameHero, const std::string& filenameWeapon);

    template<typename Monsters>
    void createMonster(Monsters** monster, Slider** healthBar,
        Vec2& position, const std::string& filenameMonster);

    void savePlayerKill();
    void saveAIKill();
    void saveData();
    void gameOver();

    void getBuff(Character& character, int numOfMonster);
    void getAttackBuff(Character& character);
    void getDefenceBuff(Character& character);

    void setCharacterVisible(bool visible, Character& character);
    void setCharacterPosition(Vec2 position, Character& character);

    Animation* getAnimationByName(std::string fileName, float interval, int fileNum, int if_repeat = -1);

    CREATE_FUNC(MapLayer);

};

#endif // __Map_Layer_H__
