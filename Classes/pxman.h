#ifndef _PXMAN_H_
#define _PXMAN_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include "GameManager.h"
#include "PhysicsSprite.h"
#include "GameObject.h"

//#define GRAVITY 10

#endif //_PXMAN_H_


/*  ===============================================================
							    ѧϰ��ע
	===============================================================
	���constλ��*����࣬��const������������ָ����ָ��ı�������ָ��ָ��Ϊ������
	���constλ��*���Ҳ࣬const��������ָ�뱾����ָ�뱾���ǳ�����

	Box2D��ײ�ص�������:
	b2Contact.GetManifold()->localNormal ���Ի������body��ײ������ĺ�������
	localNormal.y ���Ϊ0-1���ʾ���Ϸ���������ײ�����Ϊ0 �C -1���ʾ���·���������ײ
*/