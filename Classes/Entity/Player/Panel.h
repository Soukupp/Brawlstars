#pragma once
//���� : ����
//���� : 2022-5-18
#ifndef __PANEL_H__
#define __PANEL_H__

#define PANEL_MAX_ATTACK 1000
#define PANEL_MAX_DEFENCE 1000

#include "cocos2d.h"

class Panel
{
private:
    int _maxHealthPoint;//���Ѫ�� 
    int _maxMagicPoint;//�������
    int _attack;//������ 
    int _defence;//������ 
	float _attackRate;//�չ����� 
	float _skillAttackRate;//���ܱ��� 
    int _healthPoint;//��ǰѪ�� 
    int _magicPoint;//��ǰ���� 

    bool _survive;//�Ƿ���
	bool _canBeSeen;//�Ƿ����(���� ��ݴ�) 
public:
    void init(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate, int maxMagicPoint = 100);
    //ֱ�Ӷ�ȡԭʼ���
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

   //�������
    void setHealthPoint(int healthPoint);
    void setMagicPoint(int magicPoint);
    void setAttack(int attack);
    void setDefence(int defence);
    
    void setIsSurvive(bool survive);
    void setCanBeSeen(bool canBeSeen);
    //��������ʱ����������˺�
    int doAttack();
    int doSkillAttack();
    //�ܵ�����ʱ�����ܵ����˺�
    int hit(int attack);
    //�����ܵ�������
    int treat(int healthPoint);
    //����
    int restoreMagic(int magic);
};

#endif
