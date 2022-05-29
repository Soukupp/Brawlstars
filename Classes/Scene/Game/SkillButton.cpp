//作者 : 李元特
//日期 : 2022-5-29
//说明 : 参考网络



#include "SkillButton.h"





/****************************
* Name ：SkillButton::SkillButton
* Summary ：初始化
* return ：构造函数
****************************/
SkillButton::SkillButton()
{
    _pSkill = nullptr;
    _pProgressCD = nullptr;


    _skillEnable = true;
    _skillCoolTime = 0;
    _isSkillCD = false;
    _updateEnable = false;
    _pressTime = 0;
    _tUpdateInerval = 0;

    _normalImageName = "";
    _coolImageName = "";

    _clickCallback = nullptr;
    _touchBeginCallback = nullptr;
    _touchEndCallback = nullptr;
    _touchUpdateCallback = nullptr;
    _skillCDEndCallback = nullptr;


    _deltaSum = 0;
}


/****************************
* Name ：SkillButton::SkillButton
* Summary ：析构
* return ：析构函数
****************************/
SkillButton::~SkillButton()
{

}


/****************************
* Name ：SkillButton::create
* Summary ：创建一个SkillButton对象
* return ：SkillButton
****************************/
SkillButton* SkillButton::create(const std::string normalImage, const std::string coolImage, float skillTime)
{
    SkillButton* skillBtn = new (std::nothrow) SkillButton();
    if (skillBtn && skillBtn->init(normalImage, coolImage, skillTime)) 
    {
        return skillBtn;
    }
    else 
    {
        CC_SAFE_DELETE(skillBtn);
        return nullptr;
    }
}


/****************************
* Name ：SkillButton::init
* Summary ：SkillButton初始化
* return ：初始化是否成功
****************************/
bool SkillButton::init()
{
    if (Node::init()) 
    {
        return true;
    }
    return false;
}


/****************************
* Name ：SkillButton::init
* Summary ：SkillButton初始化
* return ：初始化是否成功
****************************/
bool SkillButton::init(const std::string normalImage, const std::string coolImage, float skillTime)
{
    if (init()) 
    {
        _skillCoolTime = skillTime;
        setupNormalImage(normalImage);
        setupCoolImage(coolImage);

        addTouchListener(); // 开启可触摸模式
        return true;
    }
    return false;
}


/****************************
* Name ：SkillButton::addTouchListener
* Summary ：添加鼠标读取功能
* return ：无
****************************/
void SkillButton::addTouchListener()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(false);
    listener->onTouchBegan = [this](Touch* touch, Event* evnt)->bool
    {
        return this->doSkillTouchBegin(touch->getLocation());
    };

    auto touchEndedCallback = [this](Touch* touch, Event* evnt)
    {
        this->doSkillTouchEnd(touch->getLocation());
    };

    listener->onTouchCancelled = touchEndedCallback;

    listener->onTouchEnded = touchEndedCallback;

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}


/****************************
* Name ：SkillButton::doSkillTouchBegin
* Summary ：是否点击该按钮，若是开始计时
* return ：无
****************************/
bool SkillButton::doSkillTouchBegin(const Point& touchPoint)
{
    Size contentSize = _pSkill->getContentSize();    // 判断点击区域
    Rect btnRect = Rect(this->getPositionX() - contentSize.width / 2, this->getPositionY() - contentSize.height / 2, contentSize.width, contentSize.height);
    if (btnRect.containsPoint(touchPoint))
    {
        if (_skillEnable && !_isSkillCD)
        {
            // 开启计时器
            if (_updateEnable)
            {
                unschedule(SCHEDULE_SKILL_UPDATE_TIME);
                _pressTime = 0;
                _deltaSum = 0;
                schedule([this](float delta)
                    {
                        _pressTime += delta;
                        _pressTime = (float)((int)(_pressTime * 1000 + 0.5f)) / 1000;    //保留小数点后三位
                        if (_tUpdateInerval >= delta && _touchUpdateCallback)
                        {
                            _deltaSum += delta;
                            _deltaSum = (float)((int)(_deltaSum * 1000 + 0.5f)) / 1000;  // 保留小数点后三位
                            if (_deltaSum >= _tUpdateInerval) {
                                _touchUpdateCallback(_pressTime);
                                _deltaSum = 0;
                            }
                        }
                    }, SKILL_UPDATE_INTERVAL, SCHEDULE_SKILL_UPDATE_TIME);
            }
            // 调用开始回调
            if (_touchBeginCallback)
            {
                _touchBeginCallback(0);
            }
            _isSkillTouchEnd = false;
            return true;
        }
    }
    _isSkillTouchEnd = true;
    return false;
}


/****************************
* Name ：SkillButton::doSkillTouchEnd
* Summary ：是否结束点击该按钮，若是开始冷却
* return ：无
****************************/
void SkillButton::doSkillTouchEnd(const Point& touchPoint)
{
    if (!_isSkillTouchEnd)
    {
        
        unschedule(SCHEDULE_SKILL_UPDATE_TIME);  // 停止计时器

        float pressTime = _pressTime;
        _pressTime = 0;
        _deltaSum = 0;

        if (_touchEndCallback)
            _touchEndCallback(pressTime);

        if (_clickCallback)
            _clickCallback(pressTime);
       
        this->startSkillCDAction();   // 开始读冷却
        _isSkillTouchEnd = true;
    }
}


/****************************
* Name ：SkillButton::startSkillCDAction
* Summary ：开始技能冷却
* return ：无
****************************/
void SkillButton::startSkillCDAction()
{
    if (_skillCoolTime > 0) 
    {
        _isSkillCD = true;
        _pProgressCD->setPercentage(100);
        _pProgressCD->stopAllActions();
        _pProgressCD->runAction(Sequence::create(ProgressTo::create(_skillCoolTime, 0), CallFunc::create([this] 
            {
            _isSkillCD = false;     // 技能冷却结束
            // 技能冷却完成后的回调
            if (_skillCDEndCallback) 
            {
                _skillCDEndCallback();
            }
            }), NULL));
    }
    else 
    {
        _pProgressCD->stopAllActions();
        _pProgressCD->setPercentage(0);
        _isSkillCD = false;
      
        if (_skillCDEndCallback)      // 技能冷却完成后的回调
            _skillCDEndCallback();
        
    }
}


/****************************
* Name ：SkillButton::resetSkillCDAction
* Summary ：重新技能冷却
* return ：无
****************************/
void SkillButton::resetSkillCDAction()
{
    if (_isSkillCD) 
    {
        _pProgressCD->stopAllActions();
        _pProgressCD->setPercentage(0);
        _isSkillCD = false;
        
        if (_skillCDEndCallback)  // 技能冷却完成后的回调
            _skillCDEndCallback();
    }
}


/****************************
* Name ：SkillButton::reduceSkillCDTimeAction
* Summary ：减少冷却时间
* return ：无
****************************/
void SkillButton::reduceSkillCDTimeAction(float time)
{
    if (_isSkillCD)
    {
        _pProgressCD->stopAllActions();
        float percent = _pProgressCD->getPercentage();
        float remainingTime = MIN(0, percent * _skillCoolTime - time);
        if (remainingTime > 0)
        {
            float nowPercent = 100.f / _skillCoolTime * remainingTime;
            _pProgressCD->setPercentage(nowPercent);
            _pProgressCD->runAction(Sequence::create(ProgressTo::create(remainingTime, 0), CallFunc::create([this] {
                // 技能冷却结束
                _isSkillCD = false;
                // 技能冷却完成后的回调
                if (_skillCDEndCallback)
                    _skillCDEndCallback();
                }), NULL));
        }
        else
            resetSkillCDAction();
    }
}


/****************************
* Name ：SkillButton::setSkillEnable
* Summary ：减少冷却时间
* return ：无
****************************/
void SkillButton::setSkillEnable(const bool& enable)
{
    if (_skillEnable != enable) 
    {
        _skillEnable = enable;
        if (!_skillEnable) 
        {
            _pProgressCD->stopAllActions();
            _pProgressCD->setPercentage(100);
            _isSkillCD = true;
        }
    }
}


const bool& SkillButton::getSkillEnable() const
{
    return _skillEnable;
}

/****************************
* Name ：SkillButton::setupNormalImage
* Summary ：创建技能按钮照片
* return ：无
****************************/
void SkillButton::setupNormalImage(const std::string normalImage)
{
    _normalImageName = normalImage;
    CCASSERT(!normalImage.empty(), "SkillButton : normalImage is empty");
    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(normalImage);
    if (_pSkill) 
    {
        (frame ? _pSkill->setSpriteFrame(frame) : _pSkill->setSpriteFrame(normalImage));
    }
    else 
    {
        _pSkill = frame ? Sprite::createWithSpriteFrame(frame) : Sprite::create(normalImage);
        this->addChild(_pSkill, 0);
    }
    setContentSize(_pSkill->getContentSize());

    if (_coolImageName.empty()) 
        setupCoolImage("");
}


/****************************
* Name ：SkillButton::setupCoolImage
* Summary ：创建技能冷却按钮照片
* return ：无
****************************/
void SkillButton::setupCoolImage(const std::string coolImage)
{
    _coolImageName = coolImage;
    Sprite* coolSprite = nullptr;
    if (coolImage.empty()) 
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(_normalImageName);
        coolSprite = frame ? Sprite::createWithSpriteFrame(frame) : Sprite::create(_normalImageName);
        coolSprite->setColor(Color3B(64, 64, 64));
    }
    else 
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(coolImage);
        coolSprite = frame ? Sprite::createWithSpriteFrame(frame) : Sprite::create(coolImage);
    }
    if (_pProgressCD) 
        _pProgressCD->setSprite(coolSprite);
    
    else 
    {
        _pProgressCD = ProgressTimer::create(coolSprite);
        _pProgressCD->setType(ProgressTimer::Type::RADIAL);
        _pProgressCD->setReverseProgress(true);
        _pProgressCD->setPercentage(0);
        this->addChild(_pProgressCD, 1);
    }
}

void SkillButton::addClickCallback(const SkillButton::alSkillClickCallback& callback)
{
    _clickCallback = callback;
}

void SkillButton::addTouchBeginCallback(const SkillButton::alSkillTouchCallback& callback)
{
    _touchBeginCallback = callback;
}

void SkillButton::addTouchEndCallback(const SkillButton::alSkillTouchCallback& callback)
{
    _touchEndCallback = callback;
}

void SkillButton::addTouchUpdateCallback(const SkillButton::alSkillTouchCallback& callback, float interval)
{
    if (interval >= SKILL_UPDATE_INTERVAL) 
    {
        _touchUpdateCallback = callback;
        _tUpdateInerval = interval;
    }
}

void SkillButton::addSkillCDEndCallback(const alSkillCDEndCallback& callback)
{
    _skillCDEndCallback = callback;
}
