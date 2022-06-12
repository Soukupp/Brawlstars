#pragma once
//���� : ��Ԫ��
//���� : 2022-5-14

//���� : ����
//���� : 2022-6-6
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"
#include "Entity/Player/Player.h"
#include "Entity/Player/Panel.h"

using namespace cocos2d::ui;

/*==============================����������Ҫ�޸ĵĺ궨��=================================*/

//Ѫ����Թ��޵�����λ��
#define MONSTER_YOU_BAR_POSITION (this->getContentSize().height / 2)

/*==============================����������Ҫ�޸ĵĺ궨��=================================*/

/*==============================!!!!!���º������޸�!!!!!=================================*/
//Ѫ�� λ�� this->getContentSize().width / 2
#define MONSTER_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + MONSTER_YOU_BAR_POSITION + healthBar->getContentSize().height / 2)
//Ѫ�ٷֱȼ���
#define MONSTER_BLOOD_PERCENT static_cast<int>(100 * static_cast<float>(_panel.getHealthPoint()) / static_cast<float>(_panel.getMaxHealthPoint()))
/*==============================!!!!!���Ϻ������޸�!!!!!=================================*/
class Hero1;
class Hero2;
class Hero3;
class Hero4;
class Monster : public Player
{
public:

    float _direct = 1.0f;//��ʾ����

    static Monster* create(const std::string& filename);
    virtual void initMonster(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate);
    virtual void initMonster(Panel& panel);
    virtual void initMonster();
    Panel* getPanel();

    virtual void launchAnAttack(Player* enemy, Slider* enemyHealthBar);
    int hitMonster(int attack);
    int getHealthPercent();

    virtual void keepHealthBar(Slider* healthBar);

    virtual void setPositionWithAll(cocos2d::Vec2& position, Slider* healthBar);

    void refreshHealthBar(Slider* healthBar);
    void refreshMonster();

    virtual bool playerCollisionTest1(Monster* target);

    const int _width = 26;
    const int _height = 44;
};

#endif
