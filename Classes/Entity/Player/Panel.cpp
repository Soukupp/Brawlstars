//���� : ����
//���� : 2022-5-18

//�޸� : ����
//���� : 2022-6-3
//ʵ�� : �����жϱ�������Ӧ����

#include "Panel.h"

USING_NS_CC;

/****************************
* Name ��Panel::init
* Summary ����ʼ�����
* return ��
****************************/
void Panel::init(int maxHealthPoint, int attack, int defence, float skillRate, float attackRate, int maxMagicPoint)
{
	_maxHealthPoint = maxHealthPoint;
	_healthPoint = maxHealthPoint;
	_maxMagicPoint = maxMagicPoint;
	_magicPoint = maxMagicPoint;
	_attack = attack % (PANEL_MAX_ATTACK + 1);
	_defence = defence % (PANEL_MAX_DEFENCE + 1);
	_skillRate = skillRate;
	_attackRate = attackRate;

	_survive = true;
	_canBeSeen = true;
}

/*===============================================================================*/
/*============================����������ֱ�Ӷ�ȡ===============================*/
/*===============================================================================*/

/****************************
* Name ��Panel::getHealthPoint()const
* Summary ����ȡ��ǰѪ��
* return ��Ѫ��
****************************/
int Panel::getHealthPoint()const
{
	return _healthPoint;
}

/****************************
* Name ��Panel::getMaxHealthPoint()const
* Summary ����ȡ���Ѫ��
* return �����Ѫ��
****************************/
int Panel::getMaxHealthPoint()const
{
	return _maxHealthPoint;
}

/****************************
* Name ��Panel::getMagicPoint()const
* Summary ����ȡ��ǰ����
* return ������
****************************/
int Panel::getMagicPoint()const
{
	return _magicPoint;
}

/****************************
* Name ��Panel::getMaxMagicPoint()const
* Summary ����ȡ�������
* return ���������
****************************/
int Panel::getMaxMagicPoint()const
{
	return _maxMagicPoint;
}

/****************************
* Name ��Panel::getSkillAttackRate()const
* Summary ����ȡ���ܱ���
* return �����ܱ���
****************************/
float Panel::getSkillRate()const
{
	return _skillRate;
}

/****************************
* Name ��Panel::getAttackRate()const
* Summary ����ȡ�չ�����
* return ���չ�����
****************************/
float Panel::getAttackRate()const
{
	return _attackRate;
}

/****************************
* Name ��Panel::getAttack()const
* Summary ����ȡ������
* return ��������
****************************/
int Panel::getAttack()const
{
	return _attack;
}

/****************************
* Name ��Panel::getDefence()const
* Summary ����ȡ������
* return ��������
****************************/
int Panel::getDefence()const
{
	return _defence;
}

/****************************
* Name ��getIsSurvive()const
* Summary ����ȡ�Ƿ��� 
* return ��true ���, false δ��� 
****************************/
bool Panel::getIsSurvive()const
{
	return _survive;
}

/****************************
* Name ��getCanBeSeen()const
* Summary ����ȡ�Ƿ���� 
* return ��true ����, false ������ 
****************************/
bool Panel::getCanBeSeen()const
{
	return _canBeSeen;
}

/*===============================================================================*/
/*============================����������ֱ������===============================*/
/*===============================================================================*/

/****************************
* Name ��Panel::setMaxHealthPoint
* Summary ���������Ѫ��
* return ��
****************************/
void Panel::setMaxHealthPoint(int maxHealthPoint)
{
	_maxHealthPoint = maxHealthPoint;
}

/****************************
* Name ��Panel::setHealthPoint
* Summary �����õ�ǰѪ��
* return ��
****************************/
void Panel::setHealthPoint(int healthPoint)
{
	_healthPoint = healthPoint;
}

/****************************
* Name ��Panel::setMagicPoint
* Summary �����õ�ǰ����
* return ��
****************************/
void Panel::setMagicPoint(int magicPoint)
{
	_magicPoint = magicPoint;
}

/****************************
* Name ��Panel::setAttack
* Summary �����ù�����
* return ��
****************************/
void Panel::setAttack(int attack)
{
	_attack = attack;
	if (_attack > PANEL_MAX_ATTACK)
	{
		_attack = PANEL_MAX_ATTACK;
	}
}

/****************************
* Name ��Panel::setDefence
* Summary �����÷�����
* return ��
****************************/
void Panel::setDefence(int defence)
{
	_defence = defence;
	if (_defence > PANEL_MAX_DEFENCE)
	{
		_defence = PANEL_MAX_DEFENCE;
	}
}

/****************************
* Name ��Panel::setAttackRate
* Summary �������չ�����
* return ��
****************************/
void Panel::setAttackRate(float attackRate)
{
	_attackRate = attackRate;
}

/****************************
* Name ��Panel::setSkillRate
* Summary �������չ�����
* return ��
****************************/
void Panel::setSkillRate(float skillRate)
{
	_skillRate = skillRate;
}

/****************************
* Name ��setIsSurvive
* Summary �������Ƿ��� 
* return ��
****************************/
void Panel::setIsSurvive(bool survive)
{
	_survive = survive;
}

/****************************
* Name ��setCanBeSeen
* Summary �������Ƿ�ɼ� 
* return ��
****************************/
void Panel::setCanBeSeen(bool canBeSeen)
{
	_canBeSeen = canBeSeen;
}

/*===============================================================================*/
/*=========================�����Ƿ��𹥻����˺��Ľ���============================*/
/*===============================================================================*/

/****************************
* Name ��Panel::doAttack()
* Summary �������չ��˺�
* return ���չ��˺�
****************************/
int Panel::doAttack()
{
	return static_cast<int>(_attack * _attackRate);
}

/****************************
* Name ��Panel::doSkillAttack()
* Summary �����㼼���˺�
* return �������˺�
****************************/
int Panel::doSkillAttack()
{
	return static_cast<int>(_attack * _skillRate);
}

/*===============================================================================*/
/*=========================�������ܹ����������ƵĽ���============================*/
/*===============================================================================*/

/****************************
* Name ��Panel::hit
* Summary ���ܹ���
* return �����ս�����˺�ֵ
****************************/
int Panel::hit(int attack)
{
	//����������Ч��ʽΪ�ٷֱȼ���
	int hitPoint = static_cast<int>(attack * (1.0f - _defence / PANEL_MAX_DEFENCE));
	_healthPoint -= hitPoint;
	if (_healthPoint <= 0) 
	{//�˺�������ɱ
		_healthPoint = 0;
		_survive = false;
	}
	return hitPoint;//�����˺���� Ҳֱ�ӷ�����ɵ��˺�
}

/****************************
* Name ��Panel::treat
* Summary ��������
* return ����������
****************************/
int Panel::treat(int healthPoint)
{
	_healthPoint += healthPoint;
	if (_healthPoint > _maxHealthPoint)
	{
		_healthPoint = _maxHealthPoint;//�������
	}
	return healthPoint;//����������
}

/****************************
* Name ��Panel::restoreMagic
* Summary ���ָ�����
* return ���ָ�������
****************************/
int Panel::restoreMagic(int magic)
{
	_magicPoint += magic;
	if (_magicPoint >= _maxMagicPoint)
	{
		_magicPoint = _maxMagicPoint;
	}
	return magic;
}

/****************************
* Name ��Panel::getPlayerState
* Summary �����player��״̬�������֣�
* return ��״̬��Ӧ��ö����
*         ����״̬��ö������Panel.h
****************************/
int Panel::getPlayerState()const
{
	return _playerstase;
}

/****************************
* Name ��Panel::setPlayerState
* Summary ������player��״̬�������֣�
           ����״̬��ö������Panel.h
* return ��
****************************/
void Panel::setPlayerState(int state)
{
	switch (state)
	{
		case NORMAL:
			_playerstase = NORMAL;
			break;
		case MOVING:
			_playerstase = MOVING;
			break;
		case ATTACK:
			_playerstase = ATTACK;
			break;
		case HURT:
			_playerstase = HURT;
			break;
		case SKILL:
			_playerstase = SKILL;
			break;
		case DEAD:
			_playerstase = DEAD;
			break;
	}
}

/****************************
* Name ��Panel::getIfPlayAttackAnimation
* Summary ����õ�ǰ�Ƿ񲥷�attack����
* return �� _ifPlayAttackAnimation
****************************/
bool Panel::getIfPlayAttackAnimation()const
{
	return _ifPlayAttackAnimation;
}

/****************************
* Name ��Panel::setIfPlayAttackAnimation
* Summary : ���õ�ǰ�Ƿ񲥷Ź�������
* return ��
****************************/
void Panel::setIfPlayAttackAnimation(bool ifplay)
{
	_ifPlayAttackAnimation = ifplay;
}

/****************************
* Name ��Panel::getIfPlayNormalAnimationInUpdate2
* Summary ����õ�ǰ�Ƿ���update2�в���normal����
* return ��_ifPlayNormalAnimationInUpdate2
****************************/
bool Panel::getIfPlayNormalAnimationInUpdate2()const
{
	return _ifPlayNormalAnimationInUpdate2;
}

/****************************
* Name ��Panel::getIfPlayNormalAnimationInUpdate2
* Summary : ���õ�ǰ�Ƿ���update2�в���normal����
* return ��
****************************/
void Panel::setIfPlayNormalAnimationInUpdate2(bool ifplay)
{
	_ifPlayNormalAnimationInUpdate2 = ifplay;

}

/****************************
* Name ��Panel::addHitnum
* Summary : ���ӻ�ɱ��
* return ��
****************************/
void Panel::addHitnum()
{
	_hitnum++;
}

/****************************
* Name ��Panel::getHitnum
* Summary : ��ȡ��ɱ��
* return ��
****************************/
int Panel::getHitnum()
{
	return _hitnum;
}