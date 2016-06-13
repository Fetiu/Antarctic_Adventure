/*
 	파일이름: control.cpp
 	작성목적: 게임 요소 제어 함수 정의
 	작성일자: 2016.5.10
*/

#include"control.h"

void cursorInvisible()
{
	CONSOLE_CURSOR_INFO Cinfo = { 0, };
	Cinfo.dwSize = 1;
	Cinfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Cinfo);
}

void gotoxy(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	cursorInvisible();
}

void setColor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

int getKey() {
	int keyValue, act;
	act = IDLE;
	if (_kbhit() != 0) //키보드를 눌렀는지 확인함 
	{
		keyValue = _getch();
		if (keyValue == 224) //특수 키를 눌렀을 때 버퍼에 2Byte가 발생함, 첫번째 값(2바이트중 첫1바이트)은 224값을 발생하고 두번째 값(두번째 바이트)은 특수키에 따라 다름.
		{
			keyValue = _getch(); //특수 키를 확인하기 위해 2번의 _getch()함수를 호출해야 함
		}
		
		switch (keyValue)
		{
		case ENTER:
			act = SELECT;
			break;
		case ESC:
			act = GAME_QUIT;
			break;
		case LEFT:
			act = MOVE_LEFT;
			break;
		case RIGHT:
			act = MOVE_RIGHT;
			break;
		case DOWN:
			act = CROUCH;
			break;
		case UP:
			act = JUMP;
			break;
		default:
			break;
		}
	}
	return act;
}

void copyArr( int(*arr1)[11],const int(*arr2)[11])
{
	for (int j = 0; j < 9; j++)
		for (int i = 0; i < 11; i++)
			arr1[j][i] = arr2[j][i];
}

bool collision(const Entity *a, int board[][38]) {//오버로딩이 답인가...
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 11; j++) {
			if ((a->presentForm[i][j] == 2 || a->presentForm[i][j]>3) //요소 내의 값이 충돌 판단 부분이고,
				&& board[a->getY() + i][a->getX() + j] != 8)		//보드의 요소 값이 8이 아니라면(얼음 위가 아니라면)
				return true;
		}

	return false;
}
//충돌은 객체와 보드?...음 이미 있는 보드의 내용과 새로 입력하고 싶은 객체를 비교.
//만약 충돌된 요소 클래스형을 반환한다면 숫자의 활용을 줄일수 있지않을까?