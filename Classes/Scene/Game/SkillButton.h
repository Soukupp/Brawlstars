//���� : ��Ԫ��
//���� : 2022-5-29
//˵�� : �ο�����


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


    virtual const bool& isSkillCD() const { return _isSkillCD; }   //  �����Ƿ�����ȴ��
    virtual void setupNormalImage(const std::string normalImage);  //  ��������״̬�µ�Image
    virtual void setupCoolImage(const std::string coolImage);      //  ������ȴ״̬�µ�Image



    /**
     ���ܵĵ���ص�
     ע�⣺�����������ѹ���µĻ�  ��ѹʱ��һֱΪ0
     */
    virtual void addClickCallback(const alSkillClickCallback& callback);

    /**
     ���ܰ�ѹ��ʼ�Ļص� ��ѹʱ��Ϊ 0
     */
    virtual void addTouchBeginCallback(const alSkillTouchCallback& callback);


    /**
     ���ܰ�ѹ�����Ļص�
     ע�⣺�����������ѹ���µĻ�  ��ѹʱ��һֱΪ0
     */
    virtual void addTouchEndCallback(const alSkillTouchCallback& callback);

    /**
     ���ܰ�ѹ���»ص� ��ÿ��һ��ʱ�� ���и��£�
     ע�⣺�����������ѹ���µĻ����˻ص������������
     @param callback �ص�����
     @param interval ʱ����Ӧ�ô��ڵ���0.1����0.1�ı���  ���ʱ����Ϊ0 ���ʾ�������ø��º���
     */
    virtual void addTouchUpdateCallback(const alSkillTouchCallback& callback, float interval);

    /**
     ��Ӽ���CD������Ļص�
     */
    virtual void addSkillCDEndCallback(const alSkillCDEndCallback& callback);


protected:
    virtual bool init() override;
    virtual bool init(const std::string normalImage, const std::string coolImage, float skillTime);

    virtual void addTouchListener();                           // ��Ӵ����¼�
    virtual bool doSkillTouchBegin(const Point& touchPoint);   // ִ�м��ܰ�ť������ʼ����
    virtual void doSkillTouchEnd(const Point& touchPoint);     // ִ�м��ܰ�ť������������


    virtual void startSkillCDAction();    // ��ʼ������ȴ
    virtual void resetSkillCDAction();    // ���ü�����ȴ
    virtual void reduceSkillCDTimeAction(float time);    // ������ȴʱ��

protected:
    Sprite* _pSkill;
    ProgressTimer* _pProgressCD;


    
    CC_PROPERTY_PASS_BY_REF(bool, _skillEnable, SkillEnable);          //** �����Ƿ���� *//
   
    bool _isSkillCD = false;   //** �����Ƿ�����ȴʱ�� *//
    
    CC_SYNTHESIZE_PASS_BY_REF(float, _skillCoolTime, SkillCoolTime);   //** ������ȴʱ�� *//
    
    CC_SYNTHESIZE_PASS_BY_REF(bool, _updateEnable, UpdateEnable);      //** ���ܰ�ѹ��ʱ�����Ƿ���� *//
  
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(float, _pressTime, PressTime);  //** ��ѹʱ�� *//
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
    //** �Ƿ��ܴ������� *//
    bool _isSkillTouchEnd = true;
    //** ����ʱ������������Ҫ���� *//
    float _deltaSum = 0;
};

#endif /* SkillButton_h */
