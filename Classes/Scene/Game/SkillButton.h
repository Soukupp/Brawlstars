//作者 : 李元特
//日期 : 2022-5-29
//说明 : 参考网络


#ifndef SkillButton_h
#define SkillButton_h

#include <stdio.h>
#include "cocos2d.h"


USING_NS_CC;

#define SCHEDULE_SKILL_UPDATE_TIME "SCHEDULE_SKILL_UPDATE_TIME"
#define SKILL_UPDATE_INTERVAL 0.1


class SkillButton :public Node
{
public:
    typedef std::function<void(float pressTime)> alSkillClickCallback;
    typedef std::function<void(float pressTime)> alSkillTouchCallback;
    typedef std::function<void(void)> alSkillCDEndCallback;



public:
    static SkillButton* create(const std::string normalImage, const std::string coolImage = "", float skillTime = 0);

    SkillButton();
    virtual ~SkillButton();


    virtual const bool& isSkillCD() const { return _isSkillCD; }   //  技能是否处于冷却中
    virtual void setupNormalImage(const std::string normalImage);  //  设置正常状态下的Image
    virtual void setupCoolImage(const std::string coolImage);      //  设置冷却状态下的Image



    /**
     技能的点击回调
     注意：如果不开启按压更新的话  按压时间一直为0
     */
    virtual void addClickCallback(const alSkillClickCallback& callback);

    /**
     技能按压开始的回调 按压时间为 0
     */
    virtual void addTouchBeginCallback(const alSkillTouchCallback& callback);


    /**
     技能按压结束的回调
     注意：如果不开启按压更新的话  按压时间一直为0
     */
    virtual void addTouchEndCallback(const alSkillTouchCallback& callback);

    /**
     技能按压更新回调 （每隔一段时间 进行更新）
     注意：如果不开启按压更新的话，此回调函数不会调用
     @param callback 回调函数
     @param interval 时间间隔应该大于等于0.1且是0.1的倍数  如果时间间隔为0 则表示不会启用更新函数
     */
    virtual void addTouchUpdateCallback(const alSkillTouchCallback& callback, float interval);

    /**
     添加技能CD结束后的回调
     */
    virtual void addSkillCDEndCallback(const alSkillCDEndCallback& callback);


protected:
    virtual bool init() override;
    virtual bool init(const std::string normalImage, const std::string coolImage, float skillTime);

    virtual void addTouchListener();                           // 添加触摸事件
    virtual bool doSkillTouchBegin(const Point& touchPoint);   // 执行技能按钮触摸开始操作
    virtual void doSkillTouchEnd(const Point& touchPoint);     // 执行技能按钮触摸结束操作


    virtual void startSkillCDAction();    // 开始技能冷却
    virtual void resetSkillCDAction();    // 重置技能冷却
    virtual void reduceSkillCDTimeAction(float time);    // 减少冷却时间

protected:
    Sprite* _pSkill;
    ProgressTimer* _pProgressCD;


    
    CC_PROPERTY_PASS_BY_REF(bool, _skillEnable, SkillEnable);          //** 技能是否可用 *//
   
    bool _isSkillCD = false;   //** 技能是否处于冷却时间 *//
    
    CC_SYNTHESIZE_PASS_BY_REF(float, _skillCoolTime, SkillCoolTime);   //** 技能冷却时间 *//
    
    CC_SYNTHESIZE_PASS_BY_REF(bool, _updateEnable, UpdateEnable);      //** 技能按压计时更新是否可用 *//
  
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(float, _pressTime, PressTime);  //** 按压时间 *//
    //**  *//
    float _tUpdateInerval = 0;


    std::string _normalImageName;
    std::string _coolImageName;
    alSkillClickCallback _clickCallback;
    alSkillTouchCallback _touchBeginCallback;
    alSkillTouchCallback _touchEndCallback;
    alSkillClickCallback _touchUpdateCallback;
    alSkillCDEndCallback _skillCDEndCallback;


private:
    //** 是否技能触摸结束 *//
    bool _isSkillTouchEnd = true;
    //** 更新时间增量数，主要用于 *//
    float _deltaSum = 0;
};

#endif /* SkillButton_h */
