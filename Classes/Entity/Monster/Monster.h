//作者 : 李元特
//日期 : 2022-5-14

#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"
#include "Entity/Entity.h"
#include "Entity/Player/Panel.h"
#include "Entity/Weapon/Weapon.h"
#include "../ui/UISlider.h"

using namespace cocos2d;
using namespace cocos2d::ui;


//血条、蓝条相对人物的纵向位置
#define MONSTER_YOU_BAR_POSITION (this->getContentSize().height / 2)

/*==============================以上是你需要修改的宏定义=================================*/

/*==============================!!!!!以下宏请勿修改!!!!!=================================*/

//血条 蓝条位置 this->getContentSize().width / 2
#define MONSTER_HEALTHBAR_POSITION Vec2(this->getPosition().x, this->getPosition().y + MONSTER_YOU_BAR_POSITION + healthBar->getContentSize().height / 2)

//血、蓝百分比计算
#define MONSTER_BLOOD_PERCENT int(100 * float(_panel.getHealthPoint()) / float(_panel.getMaxHealthPoint()))

/*==============================!!!!!以上宏请勿修改!!!!!=================================*/

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
    // 后续如果想让怪兽也可以发动攻击，可以加（类似野怪了）


    //virtual void keepWeapon(Weapon* weapon);
    //virtual void runFlipxWithWeapon(bool flipx, Weapon* weapon);
    void setPositionWithAll(cocos2d::Vec2& position, Slider* healthBar);
    virtual void keepHealthBar(Slider* healthBar);


    void refreshHealthBar(Slider* healthBar);
    void refreshPlayer();
};

#endif
