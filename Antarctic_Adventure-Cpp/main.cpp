/*
	파일이름: main.cpp
	작성목적: 게임 메인 함수
	작성일자: 2016.5.10
*/


#include"control.h"//콘솔 출력 제어하는 헤더도 모두 여기에 포함됨.
#include"Game.h"
//#include"Sound.h"

int main() {

	Game game;
		
	game.startMenu();
	//키 눌리면 게임 시작

	game.selectAvatar();//캐릭터 선택

	while (game.action != GAME_QUIT) {

		game.setStageInfo();

		game.mapMenu();

		game.playStage();
	}

	return 0;
}
//캐릭터 배열 박아 그리고>그위에 장애물 배열 박고> 다시 그위에 캐릭터 그리면서 장애물과 충돌했는지 판단.
//장애물을 배열에 박고 그리긴 그리지만 위에 캐릭터를 나중에 그리기에 덧씌워짐.
