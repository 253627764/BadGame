#include "JumpBoard.h"
#include "GameManager.h"
#include "Hero.h"
#include "StaticData.h"

USING_NS_CC;

bool JumpBoard::init(float x, float y, float width, float height)
{
	if (!GameObject::init(x, y, width, height))
	{
		return false;
	}

	this->getBody()->SetType(b2_staticBody);
	this->setType(TYPE_BRICK);
	this->setMask(
		TYPE_COIN |
		TYPE_HERO |
		TYPE_MONSTER |
		TYPE_PRIZE |
		TYPE_ARTICLE
		);
	this->setTexture(SD_CHARS("jump_path_texture_on"));
	return true;
}

void JumpBoard::BeginContact(GameObject* other, b2Contact* contact)
{
	if (other->getType() == TYPE_HERO)
	{
		//��ȡ��ײ������ĺ�������
		float y = contact->GetManifold()->localNormal.y;
		if (y > 0)
		{
			//ʹӢ����Ծ
			Hero* hero = GameManager::getInstance()->hero;
			b2Vec2 vec = hero->getBody()->GetLinearVelocity();
			vec.y = 10;
			hero->getBody()->SetLinearVelocity(vec);
			//�Ƴ�����
			this->autoRemovePhysicsSprite();
		}
	}
}
