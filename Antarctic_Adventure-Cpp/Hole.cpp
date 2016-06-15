#include"Hole.h"
#include<cmath>
#include<stdlib.h>
#include<ctime>

Hole::Hole(const int start_x) :Entity(start_x, 0)//10,12,14
{
	shape = 0;
	init_x = x - 13.5;	//�ʱ⿡�� �ѹ� �����Ǿ����.
}

void Hole::movePos(Output* graphic){
	static int cnt = 0;
	static int num_cnt = 0;

	switch (cnt) {	//�⺻ ��� ��ĭ�� �����°� ���ֱ�...�װͶ����� ������ϴ� ��찡 �� ����°� ����..
	case 0: 
		shape = 0;
		y = 0;
		break;
	case 1:
		y = 1;
		break;
	case 2:
		shape = 1;
		y = 2;
		break;
	case 3:
		shape = 2;
		y = 3;
		break;
	case 4:
		shape = 2;
		y = 4;
		break;
	case 5:
		shape = 3;
		y = 6;
		break;
	case 6:
		shape = 3;
		y = 8;
		break;
	case 7:
		shape = 4;
		y = 10;
		break;
	case 8:	
		shape = 4;
		y = 13;
		break;
	case 9:
		shape = 4;	//��ó�� ���¸� ��������� ��������� ������ 0�� ������� ��µǴ� ��찡 �߻���..�����Ф�
		y = 16;
		break;
	case 10:
		shape = 4;
		y = 18;
		cnt = 0;
		break;
	}
	if (num_cnt % 2)
		cnt++;
	num_cnt++;

	setPosX();	//x��ǥ ��ġ ����.

	//memcpy(presentForm, form[shape%5], sizeof(int) * 9 * 11);//������ ������ ���� ���¿� ����
	presentForm = form[shape % 5];

	graphic->fixOnBoard(this);	//��� ���忡 ���� ��ü ��ġ. ��ǥ�� ���� ��� �ʿ�.
}

void Hole::setPosX() {
	float perspect_x;	//,perspect_y;
	float slope = 8 / init_x;
	
	perspect_x = (float)(y + 3) / slope;//3��ŭ �����̵��� �Լ��� ��������� ��.
	x = (int)floor(perspect_x) + 14;	//�ݿø��ѵ� ������������ ��ǥ�� ������

}