#ifndef _FRAGMENT_H_
#define _FRAGMENT_H_
/*
	��Ƭ
	��ը������˺������þ������Ƭ
*/
#include "GameObject.h"

class Fragment : public GameObject
{
protected:
	int atk;
	int bombSize;	//���þ���	���ص�λ
	bool killHero;
	cocos2d::Vec2 startPosition;
public:
	virtual bool init(float x, float y, b2Vec2 speed, int size, bool killHero);
	CREATE_FUNC_5(Fragment, float, float, b2Vec2, int, bool);	//λ��X��λ��Y, �����ٶ�,��Ƭ��С,�Ƿ��Ӣ������˺�

	virtual void BeginContact(GameObject* other, b2Contact* contact);

	virtual void update(float ft) override;
};

#endif