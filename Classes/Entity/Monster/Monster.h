//作者 : 李元特
//日期 : 2022-5-14

#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"
#include "Entity/Entity.h"
#include "Entity/Player/Panel.h"
#include "Entity/Weapon/Weapon.h"
#include "../ui/UISlider.h"

using namespace cocos2d::ui;

#define MONSTER_HEALTHBAR_POSITION Vec2(this->getContentSize().width / 2, this->getContentSize().height * 4 / 5)

#define MONSTER_BLOOD_PERCENT 100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint())

class Monster : public Entity
{
public:
    Panel _panel;
    Slider* _healthBar;

    static Monster* create(const std::string& filename);
    void initMonster(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate);
    void initMonster(Panel& panel);
    Panel* getPanel();

};

#endif
