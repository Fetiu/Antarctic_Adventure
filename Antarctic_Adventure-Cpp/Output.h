
#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include"control.h"	//setColor, goto선언 되어있음.Entity도 제어되야하므로.
#include<string>
//#include"Game.h"
//class Game;

class Output {	//시각화 객체
public:
	void printStartMenu();
	void printBorder();
	void fixOnBoard(const Entity * object);
	void CircleFade(const int(*nextScreen)[38]);
	void drawScreen();
	int (*getBoard())[38]{ return board; }	//이차원 배열 리턴하는 함수
	void resetBoard() { memset(board, -1, sizeof(int) * 22 * 38); }
	//게임 점수, 거리, 시간 저장하는 변수 만들기. 밑에 출력하는 함수도 만들고.
private:
	int board[22][38];// 프라이빗 하려그랬는데... 레이아웃은 쉽게 접근해야하니깐..?
};

#endif //!__OUTPUT_H__