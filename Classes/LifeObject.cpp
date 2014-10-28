#include "LifeObject.h"

USING_NS_CC;

bool LifeObject::init(float x, float y, float width, float height)
{
	if(!GameObject::init(x, y, width, height))
		return false;
	hp = 1;
	atk = 0;
	die = false;
	over = false;

	//������֡�ص�
	scheduleUpdate();
	return true;
}

bool LifeObject::init(float x, float y, b2Vec2* points, int count)
{
	if(!GameObject::init(x, y, points, count))
		return false;
	hp = 1;
	atk = 0;
	die = false;
	over = false;
	
	//������֡�ص�
	scheduleUpdate();
	return true;
}

void LifeObject::setDie(bool die)
{
	this->die = die;
}

bool LifeObject::isDie() const
{
	return die;
}

void LifeObject::setOver(bool over)
{
	this->over = over;
}

bool LifeObject::isOver() const
{
	return over;
}

void LifeObject::update(float ft)
{
	if(hp <= 0 && !die)
	{//Ѫ������0 ��δ����ʱ 
		dead();
	}
}

void LifeObject::dead()
{
	die = true;
	//����������ײ
	//this->setMask(0x000000);
	//�������� �����������������ended()
}

void LifeObject::ended()
{
	//���ý�����ʶ
	over = true;
	//ɾ������ Ĭ�ϲ�ɾ��
	//this->autoRemovePhysicsSprite();
}