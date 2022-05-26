//���� : ��Ԫ��
//���� : 2022-5-14

#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"
#include "Entity/Entity.h"
#include "Entity/Player/Panel.h"
#include "Entity/Weapon/Weapon.h"
#include "../ui/UISlider.h"

using namespace cocos2d;
using namespace cocos2d::ui;


//Ѫ��������������������λ��
#define MONSTER_YOU_BAR_POSITION (this->getContentSize().height / 2)

/*==============================����������Ҫ�޸ĵĺ궨��=================================*/

/*==============================!!!!!���º������޸�!!!!!=================================*/

//Ѫ�� ����λ�� this->getContentSize().width / 2
#define MONSTER_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + MONSTER_YOU_BAR_POSITION + healthBar->getContentSize().height / 2)

//Ѫ�����ٷֱȼ���
#define MONSTER_BLOOD_PERCENT int(100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint()))

/*==============================!!!!!���Ϻ������޸�!!!!!=================================*/

class Monster : public Entity
{
private:

public:
    Panel _panel;
    //Slider* _healthBar;
    //Slider* _magicBar;

    static Monster* create(const std::string& filename);
    virtual void initMonster(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate);
    virtual void initMonster(Panel& panel);
    Panel* getPanel();

    //virtual void launchAnAttack(Weapon* weapon, const std::string& attackType);
    //int hitPlayer(int attack);
    // ����������ù���Ҳ���Է������������Լӣ�����Ұ���ˣ�


    //virtual void keepWeapon(Weapon* weapon);
    //virtual void runFlipxWithWeapon(bool flipx, Weapon* weapon);
    void setPositionWithAll(cocos2d::Vec2& position, Slider* healthBar);
    virtual void keepHealthBar(Slider* healthBar);


    void refreshHealthBar(Slider* healthBar);
    void refreshPlayer();
};

#endif
