#include"Game.h"

#include<time.h>
#include<stdlib.h>
#include<iomanip>

void Game::startMenu() {
	graphic.printBorder();

	PlaySound(TEXT("Opening.wav"), NULL, SND_FILENAME | SND_ASYNC);

	graphic.printStartMenu();
}

void Game::selectAvatar() {//캐릭터 선택 메뉴 구현..
	avatar = new Character();
	//14, 11
	// makePenguin();
}

void Game::playStage() {
	static int speed_cnt = 0;
	speed = 20;
	wipeInfo();

	PlaySound(TEXT("Main_Bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	land = new Ground(graphic.getBoard());

	destination = rand() % 1000 + 1000;	///목적지 랜덤

	while (action != STAGE_CLEAR) {

		printCurrentInfo();	//현재 게임정보 출력

		makeHoles();

		moveCloser();	//장애물 이동


		action = getKey();//제어명령 결정

		avatar->setAction(action);// 게임 제어 명령 객체에 넣어줌
		//제어명령 바탕으로 캐릭터 좌표이동. 점프를 눌렀을시엔 펭귄이 모두 1로 변하므로 충돌이 일어나지 않음.
		
		avatar->movePos(&graphic);//제어명령 바탕으로 출력될 모양 결정후, 보드에 저장시킨다


		update(); //게임 화면 업데이트
		Sleep(speed);

		//if (speed_cnt==speed) {
//		if (avatar->getCollide()) {
//			speed++;	//스피드 감소
//		}
//		if(speed>0)speed--;	//스피드 증가
//		speed_cnt = 0;
//	}
		speed_cnt++;
		distance++;
		if(speed_cnt%10==9&&speed>15)speed-=2;
		if (distance == 50/*destination*/) action = STAGE_CLEAR;

	}
	PlaySound(NULL, 0, 0);
	clearedStage++;
}

void Game::makeHoles() {
	static int holeTime = timer + rand() % 5;	//현재 시각에 랜덤으로 지정된 시간만큼 이후에 나타나게.

	//시간으로하면 그 시간을 실수로 지나칠경우 영원히 생성되지 않는 오류가 발생함..카운트로?

	if (pit != nullptr) {	//hole이 만들어 졌었다면.
		if (pit->getY() == 18) {	//바닥에 닿았는지 판단.
			delete[] pit;	//delete시킨다고 nullptr이 되지는 않는다!
			pit = nullptr;

			holeTime = timer + rand() % 5 + 3;
		}
	}

	if (timer == holeTime) {	//구덩이가 만들어져야하는 타이밍이라면 랜덤 위치에 지정.
		pit = new Hole(2 * (rand() % 4 + 5));
	}

}


void Game::moveCloser(){

	if (pit != nullptr)
		pit->movePos(&graphic);
	//이곳에 아이템들도 같은 방식으로 추가.
	
}

void Game::printCurrentInfo() {
	static int start_time = (int)time(NULL);

	timer = (unsigned int)time(NULL) - start_time;
	setColor(0x0F);
	gotoxy(3, 24); 
	cout <<"시간 - "<<setw(5) <<timer;

	gotoxy(3, 28);
	cout << "속도                             ";
	gotoxy(9, 28);
	for (int i = 0; i < (30 - speed) / 2; i++)
		cout << "■";

	gotoxy(3, 26);
	cout << "목적지 - " << setw(5) << destination<<"m";

	rest = destination - distance;

	gotoxy(33, 26);
	cout << "남은거리 - " << setw(5) << rest<<"m";

	
}


void Game::update() {
	graphic.drawScreen();
	land->updateGround(graphic.getBoard());//출력이 완료된 뒤엔 다시 초기화를 시켜줌.
}


void Game::setNextStage() {
	switch (clearedStage) {
	case 0:
		nextStage = 1;
		break;
	case 1:
		nextStage = 2;
		break;
	}
}

void Game::printMapInfo() {
	setColor(0x0F);

	gotoxy(35, 24); cout << "ANTARCTICA";

	if (clearedStage != 0) {
		for (int cnt = 0; cnt < 10; cnt++) {
			gotoxy(30, 28); 
			cout << " 스테이지 " << clearedStage << " 클리어!";
			Sleep(100);
			gotoxy(30, 28);
			cout << "                                    ";
			Sleep(50);
		}
		gotoxy(22, 28);
		cout << " 스테이지 " << nextStage << "(이)가 활성화 되었습니다.";
		Sleep(5000);
		gotoxy(22, 28);
		cout << "                                         ";
	}
}

void Game::mapMenu() {
	PlaySound(TEXT("Menu_Bgm.wav"), NULL, SND_FILENAME | SND_ASYNC );
	antarctica->updateMap(graphic.getBoard());

	wipeInfo();

	while (action != SELECT&&action != JUMP) {
		action = getKey();//제어명령 결정
		graphic.drawScreen();
		printMapInfo();
	}
	

	wipeInfo();
	readyScreen();
	graphic.CircleFade(Ground::landscape[0]);
};

void Game::wipeInfo() {
	setColor(0x0F);
	for (int y = 24; y < 29; y++) {
		gotoxy(2, y); cout << "                                                                            ";
	}
}
void Game::readyScreen() {
	graphic.resetBoard();
	graphic.drawScreen();

	gotoxy(38, 24);
	cout << "STAGE " << nextStage;
	gotoxy(38, 27);
	cout << "LOADING";
	Sleep(700);
	gotoxy(37, 27);
	cout << ".LOADING.";
	Sleep(700);
	gotoxy(36, 27);
	cout << "..LOADING..";
	Sleep(700);
	gotoxy(35, 27);
	cout << "...LOADING...";
	Sleep(700);

	gotoxy(35, 27);
	cout << "   START !    ";
}

