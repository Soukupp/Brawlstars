#pragma once
//作者 : 王鹏
//日期 : 2022-5-18
#ifndef __PANEL_H__
#define __PANEL_H__

#define PANEL_MAX_ATTACK 1000
#define PANEL_MAX_DEFENCE 1000

#include "cocos2d.h"

class Panel
{
private:
    int _maxHealthPoint;//最大血量 
    int _maxMagicPoint;//最大蓝量
    int _attack;//攻击力 
    int _defence;//防御力 
	float _attackRate;//普攻倍率 
	float _skillAttackRate;//技能倍率 
    int _healthPoint;//当前血量 
    int _magicPoint;//当前蓝量 

    bool _survive;//是否存活
	bool _canBeSeen;//是否可视(例如 躲草丛) 
public:
    void init(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate, int maxMagicPoint = 100);
    //直接读取原始面板
    int getHealthPoint()const;
    int getMaxHealthPoint()const;
    int getMagicPoint()const;
    int getMaxMagicPoint()const;
    float getSkillAttackRate()const;
    float getAttackRate()const;

    int getAttack()const;
    int getDefence()const;
    
    bool getIsSurvive()const;
    bool getCanBeSeen()const;

   //设置面板
    void setHealthPoint(int healthPoint);
    void setMagicPoint(int magicPoint);
    void setAttack(int attack);
    void setDefence(int defence);
    
    void setIsSurvive(bool survive);
    void setCanBeSeen(bool canBeSeen);
    //发动攻击时结算输出的伤害
    int doAttack();
    int doSkillAttack();
    //受到攻击时结算受到的伤害
    int hit(int attack);
    //结算受到的治疗
    int treat(int healthPoint);
    //回蓝
    int restoreMagic(int magic);
};

#endif
