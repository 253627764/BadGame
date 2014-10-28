#ifndef _SLIME_H_
#define _SLIME_H_

#include "Aware.h"
/*ʷ��ķ*/
class Slime : public Aware
{
protected:
	CC_SYNTHESIZE(float, speed, Speed);
public:
	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(Slime, float, float, float, float);

	virtual void update(float ft);

	virtual void dead();

	virtual void ended();
/*
	virtual void BeginContact(GameObject* other, b2Contact* contact);
*/
	virtual void PreSolve(GameObject* other, b2Contact* contact, const b2Manifold* oldManifold);
	/*�����ƶ�*/
	virtual void moveLeft();
	/*�����ƶ�*/
	virtual void moveRight();
};

#endif
