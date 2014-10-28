#include "Brick.h"
#include "StaticData.h"

USING_NS_CC;

void Brick::initBrick()
{
	this->getBody()->SetType(b2_staticBody);
	//��������
	this->setType(TYPE_BRICK);
	//���˭������ײ
	this->setMask(
		TYPE_HERO |
		TYPE_ANIMAL |
		TYPE_COIN | 
		TYPE_MONSTER |
		TYPE_ARTICLE |
		TYPE_WEAPON);
	//��������-һ�㲻��
	//this->setTexture(SD_STRING("brick_path_texture"));
}

bool Brick::init(float x, float y, float width, float height)
{
	if(!GameObject::init(x, y, width, height))
	{
		return false;
	}
	initBrick();
	return true;
}

bool Brick::init(float x, float y, b2Vec2* points, int count)
{
	if(!GameObject::init(x, y, points, count))
	{
		return false;
	}
	initBrick();
	return true;
}

void Brick::PreSolve(GameObject* other, b2Contact* contact, const b2Manifold* oldManifold)
{
	if(other->getType() == TYPE_HERO || other->getType() == TYPE_MONSTER)
	{
		//�����ש���·�����ô��͸��Ҳ����ʵ���˵ذ�ĵ�����ײ
		float otherHeight = other->getBodyBoundingBoxHeight();
		float otherY = other->getPositionY() - otherHeight/2.0f;
		float y = this->getPositionY() + height/2.0f;
		if(otherY < y)
			contact->SetEnabled(false);
	}
}
