#pragma once
//作者 : 王鹏
//日期 : 2022-5-18
#ifndef __PANEL_H__
#define __PANEL_H__

#define PANEL_MAX_ATTACK 1000
#define PANEL_MAX_DEFENCE 1000

#include "cocos2d.h"

enum playerstates {               //人物状态的枚举
    NORMAL,                       //正常状态
    MOVING,                       //移动状态
    ATTACK,                       //攻击状态
    HURT,                         //受伤状态
    SKILL,                        //大招状态
    DEAD                          //死亡状态
};

class Panel
{
private:
    int _maxHealthPoint;           //最大血量 
    int _maxMagicPoint;            //最大蓝量
    int _attack;                   //攻击力 
    int _defence;                  //防御力 
	float _attackRate;             //普攻倍率 
	float _skillAttackRate;        //技能倍率 
    int _healthPoint;              //当前血量 
    int _magicPoint;               //当前蓝量
    float _skillRate;

    bool _survive;                 //是否存活
	bool _canBeSeen;               //是否可视(例如 躲草丛) 

    int _playerstase;              //角色的状态

    bool _ifPlayAttackAnimation = true;               //当前是否播放攻击动画
    bool _ifPlayNormalAnimationInUpdate2 = false;     //当前是否在update2中播放normal动画

    int _hitnum = 0;
  
public:
    void init(int maxHealthPoint, int attack, int defence, float skillRate, float attackRate, int maxMagicPoint = 100);

    //直接读取原始面板

    int getHealthPoint()const;
    int getMaxHealthPoint()const;
    int getMagicPoint()const;
    int getMaxMagicPoint()const;
    float getSkillRate()const;
    float getAttackRate()const;

    int getAttack()const;
    int getDefence()const;
    
    bool getIsSurvive()const;
    bool getCanBeSeen()const;

    int getPlayerState()const;
    bool getIfPlayAttackAnimation()const;
    bool getIfPlayNormalAnimationInUpdate2()const;

   //设置面板
    void setMaxHealthPoint(int maxHealthPoint);
    void setHealthPoint(int healthPoint);
    void setMagicPoint(int magicPoint);
    void setAttack(int attack);
    void setDefence(int defence);
    void setAttackRate(float attackRate);
    void setSkillRate(float skillRate);
    
    void setIsSurvive(bool survive);
    void setCanBeSeen(bool canBeSeen);

    void setPlayerState(int state);
    void setIfPlayAttackAnimation(bool ifplay);
    void setIfPlayNormalAnimationInUpdate2(bool ifplay);

    //发动攻击时结算输出的伤害
    int doAttack();
    int doSkillAttack();
    //受到攻击时结算受到的伤害
    int hit(int attack);
    //结算受到的治疗
    int treat(int healthPoint);
    //回蓝
    int restoreMagic(int magic);

    void addHitnum();
    int getHitnum();
};

#endif
