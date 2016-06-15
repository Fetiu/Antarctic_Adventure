#include"Game.h"

#include<time.h>
#include<stdlib.h>
#include<iomanip>

void Game::startMenu() {
	graphic.printBorder();

	PlaySound(TEXT("Opening.wav"), NULL, SND_FILENAME | SND_ASYNC);

	graphic.printStartMenu();
}

void Game::selectAvatar() {//ĳ���� ���� �޴� ����..
	avatar = new Character();
}

void Game::setStageInfo() {
	switch (clearedStage) {
	case 0:
		nextStage = 1;
		destination = 500;
		break;
	case 1:
		nextStage = 2;
		//destination = 1200;
		break;
	}
	//destination += 100;

	antarctica->updateMap(clearedStage);
}

void Game::printMapInfo() {
	setColor(0x0F);

	gotoxy(35, 24); cout << "ANTARCTICA";


}

void Game::createEntity() {
	makeHoles();
	//makeItmes(); ������ ����� �Լ��鵵 ���������.
}

void Game::deleteEntity() {
	delete pit;
	pit = nullptr;
	//�ٸ� �����۰� ��ֹ��鵵 �̷������� ����
}

void Game::makeHoles() {
	static int holeTime = distance + (rand() % 5)*7;	//���� �ð��� �������� ������ �ð���ŭ ���Ŀ� ��Ÿ����.

	//�ð������ϸ� �� �ð��� �Ǽ��� ����ĥ��� ������ �������� �ʴ� ������ �߻���..ī��Ʈ��?

	//�ð��� �ƴ϶� �����Ÿ��� �����̸� �������Ѿ�!
	
	if (pit != nullptr) {	//hole�� ����� �����ٸ�.
		if (pit->getY() == 18) {	//�ٴڿ� ��Ҵ��� �Ǵ�.
			delete pit;	//delete��Ų�ٰ� nullptr�� ������ �ʴ´�!
			pit = nullptr;

			holeTime = distance + (rand() % 5)*7;
		}
	}
	
	if (distance == holeTime) {	//�����̰� ����������ϴ� Ÿ�̹��̶�� ���� ��ġ�� ����.
		pit = new Hole(16/*2 * (rand() % 4 + 5)*/);
	}

}


void Game::moveCloser(){


	if (pit != nullptr)
		pit->movePos(&graphic);
	//�̰��� �����۵鵵 ���� ������� �߰�.
	
}

void Game::printCurrentInfo() {

	setTimer();
	setColor(0x0F);
	gotoxy(3, 24); 
	cout <<"�ð� - "<<setw(5) <<timer;

	gotoxy(3, 28);
	cout << "�ӵ�                             ";
	gotoxy(9, 28);
	for (int i = 0; i < (30 - speed) / 2; i++)
		cout << "��";

	gotoxy(3, 26);
	cout << "������ - " << setw(5) << destination<<"m";

	rest = destination - distance;

	gotoxy(32, 26);
	cout<<"�̵��Ÿ� - "<< setw(5) << distance << "m";

	gotoxy(60, 26);
	cout << "�����Ÿ� - " << setw(5) << rest<<"m";

	
}


void Game::update() {
	graphic.drawScreen();
	land->updateGround(graphic.getBoard());//����� �Ϸ�� �ڿ� �ٽ� �ʱ�ȭ�� ������.
}



void Game::mapMenu() {
	PlaySound(TEXT("Menu_Bgm.wav"), NULL, SND_FILENAME | SND_ASYNC );
	
	wipeInfo();
	printMapInfo();
	while (action != SELECT) {
		antarctica->refreshMap(graphic.getBoard());
		action = getKey();//������ ����
		antarctica->controlCharacterPiece(graphic.getBoard(), action);	//ĳ���� �� ����
		graphic.drawScreen();
	}
	
	wipeInfo();
	loadScreen();
	//graphic.CircleFade(Ground::landscape[0]);
};

void Game::wipeInfo() {
	setColor(0x0F);
	for (int y = 24; y < 29; y++) {
		gotoxy(2, y); cout << "                                                                           ";
	}
}

void Game::loadScreen() {
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

void Game::stageCompleted() {
	
	PlaySound(TEXT("Stage_Clear.wav"), NULL, SND_FILENAME | SND_ASYNC);
	clearedStage++;
	nextStage++;
	distance = 0;
	timer = 0;

	wipeInfo();
	setColor(0x0F);
	if (clearedStage != 0) {	//���������� �ϳ��� Ŭ�����ϸ�.
		for (int cnt = 0; cnt < 10; cnt++) {
			gotoxy(30, 26);
			cout << " �������� " << clearedStage << " Ŭ����!";
			Sleep(100);
			gotoxy(30, 26);
			cout << "                                    ";
			Sleep(50);
		}
		gotoxy(22, 28);
		cout << " �������� " << nextStage << "(��)�� Ȱ��ȭ �Ǿ����ϴ�.";
		Sleep(5000);
		gotoxy(22, 28);
		cout << "                                         ";
	}

	deleteEntity();
}

void Game::setTimer() {
	timer = (unsigned int)time(NULL) - start_time;
}

void Game::playStage() {
	
	start_time = (unsigned int)time(NULL);	//���۽ð� ����.
	srand((unsigned int)time(NULL));
	wipeInfo();

	PlaySound(TEXT("Main_Bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	land = new Ground(graphic.getBoard());
	speed = 0;
	//destination = rand() % 1000 + 1000;	///������ ����

	while (action != STAGE_CLEAR) {

		printCurrentInfo();	//���� �������� ���

		createEntity();

		moveCloser();	//��ֹ� �ٰ���.

		action = getKey();//������ ����

		avatar->setAction(action);// ���� ���� ��� ��ü�� �־���
								  //������ �������� ĳ���� ��ǥ�̵�. ������ �������ÿ� ����� ��� 1�� ���ϹǷ� �浹�� �Ͼ�� ����.

		avatar->movePos(&graphic);//������ �������� ��µ� ��� ������, ���忡 �����Ų��


		update(); //���� ȭ�� ������Ʈ
		Sleep(10);

		//		if (avatar->getCollide()) {
		//			speed++;	//���ǵ� ����
		//		}
		//		if(speed>0)speed--;	//���ǵ� ����
		//		speed_cnt = 0;

		//speed_cnt++;
		distance++;
		//if (speed_cnt % 10 == 9 && speed>15)speed -= 2;
		if (distance == destination) action = STAGE_CLEAR;

	}
	PlaySound(NULL, 0, 0);
	stageCompleted();
}
