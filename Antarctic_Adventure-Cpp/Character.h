#pragma once


#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include"Entity.h"
#include"Output.h"

class Character :public Entity
{
public:
	Character();
	Character(int _X, int _Y) :Entity(_X, _Y) {}//������������ �ҷ������� ĳ����
	//int x, y;
	void setAction(int gameAction) { action = gameAction; }
	void movePos(Output* graphic);
	bool getCollide() { return state_stumble; }
private:
	const static int form[5][9][11];

	void setPosture(Output* graphic);
	void idlePosture();
	void stumblePosture();
	void jumpPosture();
	void crouchPosture();
	bool state_stumble = false;
	bool state_jump = false;
	bool state_crouch = false;
	int tmp_shape = 0;	//���� ������ �ӽ÷� �����ϴ� ��.
	int tmp_act=IDLE;	//�ӽ� �ൿ ����� ����Ǵ� ��.
	
};

#endif //!__CHARACTER_H__