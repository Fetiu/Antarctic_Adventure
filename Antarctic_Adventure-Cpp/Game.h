
#ifndef __GAME_H__

#define __GAME_H__

#include<ctime>
#include"Output.h"
#include"control.h"
#include"Character.h"
#include"Map.h"
#include"Ground.h"
#include"Hole.h"
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")


class Game {
public:
	Character *avatar;
	int action = IDLE;
	
	void startMenu();
	void selectAvatar();
	void mapMenu();
	void setStageInfo();
	void playStage();

private:
	int nextStage;
	int clearedStage = 0;

	Output graphic;	//게임 화면 출력을 위한 객체
	Map *antarctica = new Map(graphic.getBoard());
	Ground *land;
	Hole *pit;

	void setTimer();
	void update();
	void moveCloser();
	void wipeInfo();
	void loadScreen();
	void stageCompleted();
	void printCurrentInfo();
	void printMapInfo();
	void createEntity();
	void deleteEntity();
	void makeHoles();

	int destination;
	int distance;
	int rest;
	int speed;
	int start_time;
	int timer;
	int score;
};

#endif //!__GAME_H__