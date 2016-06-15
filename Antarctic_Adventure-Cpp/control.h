/*
	파일이름: control.h
	작성목적: 게임 요소 제어 함수 선언
	작성일자: 2016.5.10
*/
#pragma once

#include<iostream>	//콘솔 입출력제어
#include<conio.h> //kbhit, getch 선언
#include<Windows.h>	//Sleep, 콘솔 커서 제어
#include"Entity.h"
//객체를 제어해야 하니까 부모 클래스 인클루드

using namespace std;

#define ESC 27 
#define LEFT 75 
#define RIGHT 77 
#define DOWN 80 
#define UP 72
#define ENTER 13
#define SPACE 32

enum { MOVE_LEFT = 0, MOVE_RIGHT, IDLE, CROUCH,JUMP, STAGE_CLEAR, SELECT, GAME_QUIT };

#define PIT 4
#define FLAG 5
#define FISH 6

//class controller{
//public:
//};


void gotoxy(int x, int y);//좌표 이동 함수
//void playSound(string wav); 인자때매 재선언은 안되더라고
void setColor(int color_num);//색깔 변경함수. <주의> 한번 색을 사용하면 그 색이 계속 유지됨.
/* 매개변수에 따라 색이 달라짐	
0.검정색 1.남색	2.진녹색 3.청록색 4.갈색 5.자주색9.파랑 A.C.빨강 F.흰색	*/
int getKey();

bool collision(const Entity *a,int board[][38]);//엘리먼트 없이 오버로딩 하는게 답인가...ㅠㅠ

void copyArr(int(*arr1)[11], const int(*arr2)[11]);	//arr2의 내용을 arr1에 집어넣음.
//memcpy로 대체.

