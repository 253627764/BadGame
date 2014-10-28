#ifndef _BRICK_H_
#define _BRICK_H_
/*
	�ذ�ש��
	Ӣ�ۿ��Դ��·���Խ��
*/
#include "GameObject.h"

class Brick : public GameObject
{
private:
	/*��ʼ��Brick ֻΪ�˷����̬*/
	void initBrick();
protected:
public:
	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(Brick, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count) override;
	CREATE_FUNC_4(Brick, float, float, b2Vec2*, int);

	virtual void PreSolve(GameObject* other, b2Contact* contact, const b2Manifold* oldManifold);
};

#endif