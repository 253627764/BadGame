#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "PhysicsSprite.h"
#include "Config.h"

class PhysicsSprite;

class GameObject : public PhysicsSprite
{
public:
	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(GameObject, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count) override;
	CREATE_FUNC_4(GameObject, float, float, b2Vec2*, int);
	/* ����һ����Ϸ������ײ���ص��˺���
	 * GameObjectΪ��һ����Ϸ����
	 */
	virtual void BeginContact(GameObject* other, b2Contact* contact);
	virtual void EndContact(GameObject* other, b2Contact* contact);
	virtual void PreSolve(GameObject* other, b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(GameObject* other, b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif	//_GAME_OBJECT_H_