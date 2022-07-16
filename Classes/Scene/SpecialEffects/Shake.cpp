//作者：王鹏
//日期：2022-6-25
//实现：精灵晃动

#include "Shake.h"

/****************************
* Name ：Shake()
* Summary ：构造
* return ：
****************************/
Shake::Shake() : _strengthX(0.0f), _strengthY(0.0f), _initialX(0.0f), _initialY(0.0f)
{
}

/****************************
* Name ：create
* Summary ：创建抖动动作
* return ：抖动动作指针
****************************/
Shake* Shake::create(float duration, float strength)
{
    return create(duration, strength, strength);
}

/****************************
* Name ：create
* Summary ：创建抖动动作
* return ：抖动动作指针
****************************/
Shake* Shake::create(float duration, float strengthX, float strengthY)
{
    Shake* pAction = new (std::nothrow) Shake();
    if (pAction && pAction->initWithDuration(duration, strengthX, strengthY))
    {
        pAction->autorelease();
        return pAction;
    }
    CC_SAFE_DELETE(pAction);
    return nullptr;
}

/****************************
* Name ：initWithDuration
* Summary ：根据抖动时长初始化
* return ：初始化成功与否
****************************/
bool Shake::initWithDuration(float duration, float strengthX, float strengthY)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _strengthX = strengthX;
        _strengthY = strengthY;
        return true;
    }
    return false;
}

/****************************
* Name ：fgRangeRand
* Summary ：在抖动范围内获取抖动值
* return ：抖动值
****************************/
float fgRangeRand(float min,float max)
{
    float rnd = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
    return rnd * (max - min) + min;
}

/****************************
* Name ：update
* Summary ：每帧执行
* return ：
****************************/
void Shake::update(float time)
{
    float randX = fgRangeRand(-_strengthX, _strengthX);
    float randY = fgRangeRand(-_strengthY, _strengthY);
    _target->setPosition(Vec2(_initialX + randX, _initialY + randY));
}

/****************************
* Name ：clone
* Summary ：复制一个抖动动作
* return ：抖动动作指针
****************************/
Shake* Shake::clone() const
{
    auto a = new Shake();
    a->initWithDuration(_duration, _strengthX, _strengthY);
    a->autorelease();
    return a;
}

/****************************
* Name ：reverse
* Summary ：抖动动作翻转
* return ：抖动动作指针
****************************/
Shake* Shake::reverse(void) const
{
    return Shake::create(_duration, -_strengthX, -_strengthY);
}

/****************************
* Name ：startWithTarget
* Summary ：开始抖动
* return ：
****************************/
void Shake::startWithTarget(Node *target)
{
    CCActionInterval::startWithTarget(target);
    _initialX = target->getPosition().x;
    _initialY = target->getPosition().y;
}

/****************************
* Name ：stop
* Summary ：停止抖动
* return ：
****************************/
void Shake::stop(void)
{
    _target->setPosition(Vec2(_initialX, _initialY));
    CCActionInterval::stop();
}

//http://www.kokojia.com/article/18170.html