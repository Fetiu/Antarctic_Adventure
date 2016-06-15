#pragma once

#ifndef __ENTITY_H__

#define __ENTITY_H__

class Output;

class Entity 
{	//������ ��Ҹ� �����ϴ� �߻� Ŭ����. �浹,���� �Լ��� ��ü ������ �����Ҷ� ���!!
public:
	Entity(int _X, int _Y) :x(_X), y(_Y) { shape = 0; };
	virtual ~Entity() { /*delete[] presentForm; presentForm = nullptr;*/ }
	virtual void movePos(Output* graphic) = 0; //��ӽ�Ű�� �������̵� �ɺκ�.�߿���������.
	const int(*presentForm)[11] = { 0, };	// ���ø� �迭���κ��� ���� ���¸� �����ؿ��� ���� ������
	int getX() const { return x; }
	int getY() const { return y; }
protected:
	int shape;//�迭�� �������� �ܺ��Լ��� ��絵 �˷���߰ڳ�?...
	int x, y;	//������ ����� ��ǥ�� �����ϴ� �Լ��� ����Լ�. ���� Ŭ���� ������ ��������ֱ�!
				//int previousForm[9][11] = { 0 };
	int action;// ��� ���� ����� ����Ǵ� ����. ĳ���ʹ� Ű������ ����ϰŰ�, ����̳� ������ �Ÿ��� ���� ����� ���̴�.
};
//visualizer, conceptualizer

#endif // !__ENTITY_H__
