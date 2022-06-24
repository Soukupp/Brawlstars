//作者：王鹏
//日期：2022-6-25
//实现：精灵晃动

#ifndef __SHAKE__
#define __SHAKE__

#include "cocos2d.h"

using namespace cocos2d;

class Shake : public ActionInterval
{
public:
    Shake();
    static Shake* create(float duration, float strength);
    static Shake* create(float duration, float strengthX, float strengthY);
    bool initWithDuration(float duration, float strengthX, float strengthY);

    virtual Shake* clone() const override;
    virtual Shake* reverse(void) const override;
    virtual void startWithTarget(Node* target) override;

    virtual void update(float time) override;
    virtual void stop(void);

protected:
    float _initialX, _initialY;
    float _strengthX, _strengthY;
};
#endif //http://www.kokojia.com/article/18170.html