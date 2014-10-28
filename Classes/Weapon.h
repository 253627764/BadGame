#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "LifeObject.h"
class Aware;

class Weapon : public LifeObject
{
protected:
	Aware* object;	//��������
	DIR dir;		//�ӵ�����
	int speed;		//�ٶ�
	float startY;		//��ʼY
	bool startTag;	//��ʼ��ʶ
public:
	virtual bool init(Aware* object);
	CREATE_FUNC_1(Weapon, Aware*);
	/*�����ӵ��ٶ�*/
	virtual void setSpeed(float speed);
	/*��ȡ�ӵ��ٶ�*/
	virtual int getSpeed();

	virtual void update(float ft);
	virtual void dead();
	virtual void ended();
	
	virtual void PreSolve(GameObject* othera, b2Contact* contact, const b2Manifold* oldManifold);

};

#endif