/*
	파일이름: Output.cpp
	작성목적: 출력객체 클래스 정의
	작성일자:??
	수정일자: 2016.5.23
	수정내용:
	1. draw()->drawScreen()으로 변경. 그리는 방향을 아래에서 위로 올라가게.
	2. Entity*로 받아오던 오브젝트들을 void형 포인터로 변경해봄. 오류가능성 높음...>>다시 원상 복구


*/

#include"Output.h"//Output클래스 선언 되어있음.
#include<cmath>

enum { SKY = 0, };

void Output::printBorder() {
	system("mode con:cols=80 lines=31");//경계크기 키우기

	setColor(0x0F);
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 24; j++) {
			gotoxy(i * 2, j);
			if (j == 0) {
				if (i == 0) cout << "┏";
				else if (i == 39)cout << "┓";
				else cout << "━";
			}
			else if (j == 23) {

				if (i == 0) cout << "┣";
				else if (i == 39)cout << "┫";
				else cout << "━";
			}
			else if (i == 0 || i == 39)	cout << "┃";
		}
	}

	gotoxy(0, 23);	cout << "┣";
	gotoxy(78, 23); cout << "┫";

	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 6; j++) {
			gotoxy(i * 2, j + 24);
			if (j == 5) {
				if (i == 0) cout << "┗";
				else if (i == 39)cout << "┛";
				else cout << "━";
			}
			else if (i == 0 || i == 39)	cout << "┃";

		}
	}

}

void Output::printStartMenu() {
	for (int i = 0; i < 38; i++) {
		for (int j = 0; j < 22; j++) {
			gotoxy((i + 1) * 2, j + 1);
			if (j > 6 && j < 16) {
				setColor(0xF0);
				cout << "  ";
			}
			else {
				setColor(0x9F);
				cout << "▒";
			}
		}
		Sleep(5);
	}

	setColor(0xF1);//색상 설정후 개행 때문에 이렇게 노가다 할수밖에 없음...ㅠㅠ
	gotoxy(8, 9);
	cout << "┏┓    ┏┓  " << endl; gotoxy(8, 10);
	cout << "┃┃    ┃┗┓" << endl; gotoxy(8, 11);
	cout << "┃┗━━┫┏┛" << endl; gotoxy(8, 12);
	cout << "┗┳━━┻┫  " << endl; gotoxy(8, 13);
	cout << "  ┃┏━┓┃  " << endl; gotoxy(8, 14);
	cout << "  ┃┗━┛┃  " << endl; gotoxy(8, 15);
	cout << "  ┗━━━┛  " << endl; gotoxy(8, 16);

	gotoxy(25, 9);
	cout << "  ┏━━━┓  " << endl; gotoxy(25, 10);
	cout << "  ┗━━┓┃  " << endl; gotoxy(25, 11);
	cout << "        ┃┃  " << endl; gotoxy(25, 12);
	cout << "┏━━━┻┻┓" << endl; gotoxy(25, 13);
	cout << "┗┳━━━┳┛" << endl; gotoxy(25, 14);
	cout << "  ┗━━┓┃  " << endl; gotoxy(25, 15);
	cout << "        ┗┛  " << endl; gotoxy(25, 16);

	gotoxy(42, 9);
	cout << "┏━━━┳┓  " << endl; gotoxy(42, 10);
	cout << "┃  ━━┫┗┓" << endl; gotoxy(42, 11);
	cout << "┃  ━━┫┏┛" << endl; gotoxy(42, 12);
	cout << "┗┳━━┻┫  " << endl; gotoxy(42, 13);
	cout << "  ┃┏━┓┃  " << endl; gotoxy(42, 14);
	cout << "  ┃┗━┛┃  " << endl; gotoxy(42, 15);
	cout << "  ┗━━━┛  " << endl; gotoxy(42, 16);
	gotoxy(58, 8);
	cout << "  ┏━━┓      " << endl; gotoxy(58, 9);
	cout << "┏┻━━┻┳┓" << endl; gotoxy(58, 10);
	cout << "┗┫┏┓┣┛┃" << endl; gotoxy(58, 11);
	cout << "  ┃┗┛┣┓┃" << endl; gotoxy(58, 12);
	cout << "   ┗━┛ ┻┫" << endl; gotoxy(58, 13);
	cout << "    ┃┏━┓┃" << endl; gotoxy(58, 14);
	cout << "    ┃┗━┛┃" << endl; gotoxy(58, 15);
	cout << "    ┗━━━┛" << endl; gotoxy(58, 16);

	setColor(0x0F);


	while (!_kbhit()) {
		gotoxy(22, 26);
		cout << " 시작하려면 아무키나 누르세요...";
		Sleep(300);
		gotoxy(22, 26);
		cout << "                                ";
		Sleep(300);
	}

}


void Output::fixOnBoard(const Entity* object) {
	//객체를 받아와서 화면 배열 위에 배치시킴. 
	//고정하기 전에 만약 프린트 해야하는 그 위치에 무언가 이미 있다면, 충돌

	for (int j = 0; j < 9; j++)
		for (int i = 0; i < sizeof(object->presentForm[0]) / sizeof(int); i++) {
			if (object->presentForm[j][i])//object현재형태 배열속에 0이아닌 값이 존재한다면
				board[object->getY() + j][object->getX() + i] = object->presentForm[j][i];
		}
}
//이걸 set객체 같은데에 넣어두어도 괜찮겠지만...그렇게 되면 보드를 여기두고
//그 객체가 받아와서 출력시키면 될듯...하다! 음 근데


void Output::CircleFade(const int (*nextScreen)[38]) {
	int space;	//이전 화면이 남아있는 공간.
	int prev_printed[22][38] = { 0, };
	for (int R = 1; R < 23; R++) {

		for (int y = 11 - R; y < 11 + R; y++) {	//y가 시작하는 시점은 중심에서 위로 반지름만큼 간 지점.
			space = (int)floor(R - sqrt(R*R - (y - 10.5)*(y - 10.5)) + 0.5) + 18 - R; //세로로 왼쪽지점의 반원만으로 공간을 계산. 

			for (int x = 0; x < 38; x++) {
				if (x > space&&x < 38 - space) {
					if (y >= 0 && y < 22) {
						if (prev_printed[y][x] == 0) {
							gotoxy(x * 2, y);
							board[y][x] = nextScreen[y][x];
							prev_printed[y][x] = 1;
						}
					}
				}
			}
		}
		drawScreen();
		//Sleep(10);
	}
}


void Output::drawScreen() {
	for (int j = 21; j >= 0; j--)
		for (int i = 0; i < 38; i++) {
			gotoxy((i + 1) * 2, j + 1);
			switch (board[j][i])
			{
			case -1: setColor(0x0A); cout << "  "; break;
			case 0: setColor(0xBF); cout << "▒"; break;//하늘
			case 1: case 2:setColor(0x10); cout << "▒"; break;//펭귄 몸체
			case 3:setColor(0x18); cout << "▒"; break;//펭귄 경계
			case 4:setColor(0x90); cout << "▒"; break;//구덩이
			case 5:setColor(0x8F); cout << "▒"; break;//얼음 반사
			case 6:
			case 7: setColor(0x9F); cout << "  "; break;//바다
			case 8: setColor(0xF0); cout << "  "; break;//빙산 
			case 9: setColor(0xF3); cout << "▒"; break;//빙산경계
			}
		}
}

