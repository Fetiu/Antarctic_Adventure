#include"Hole.h"
#include<cmath>
#include<stdlib.h>
#include<ctime>

Hole::Hole(const int start_x) :Entity(start_x, 0)//10,12,14
{
	shape = 0;
	init_x = x - 13.5;	//초기에만 한번 지정되어야함.
}

void Hole::movePos(Output* graphic){
	static int cnt = 0;
	static int num_cnt = 0;

	switch (cnt) {	//기본 모양 한칸씩 내리는거 없애기...그것때문에 제어못하는 경우가 좀 생기는거 같아..
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
		shape = 4;	//이처럼 형태를 계속적으로 명시해주지 않으면 0의 모양으로 출력되는 경우가 발생됨..왜지ㅠㅠ
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

	setPosX();	//x좌표 위치 결정.

	//memcpy(presentForm, form[shape%5], sizeof(int) * 9 * 11);//결정된 동작을 현재 형태에 복사
	presentForm = form[shape % 5];

	graphic->fixOnBoard(this);	//출력 보드에 현재 객체 배치. 좌표와 형태 모두 필요.
}

void Hole::setPosX() {
	float perspect_x;	//,perspect_y;
	float slope = 8 / init_x;
	
	perspect_x = (float)(y + 3) / slope;//3만큼 평행이동된 함수로 생각해줘야 함.
	x = (int)floor(perspect_x) + 14;	//반올림한뒤 시작점부터의 좌표를 더해줌

}