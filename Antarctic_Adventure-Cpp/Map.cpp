#include"Map.h"
#include"control.h"
#include<string.h>

Map::Map(int(*board)[38]) {
	refreshMap(board);
}

void Map::refreshMap(int(*board)[38]){
	memcpy(board, Antarctica, sizeof(int) * 22 * 38);
}

void Map::updateMap(int clearedStage) {
	//스테이지 클리어 정보에 따라 맵정보를 수정함.

	//1은 열린 스테이지, 5는 열린길, 3은 안열린 스테이지,9는 안열린길.

	while (1) {
		//길이거나 이미깬 스테이지인 경우
		if (Antarctica[road.y][road.x] == 1 
			|| Antarctica[road.y][road.x] == 5) {	
			if (Antarctica[road.y - 1][road.x] == 9 || Antarctica[road.y - 1][road.x] == 3) {
				road.y--;//way up
			}
			else if (Antarctica[road.y][road.x + 1] == 9 
				|| Antarctica[road.y][road.x + 1] == 3) {
				road.x++;//way right
			}
			else if (Antarctica[road.y + 1][road.x] == 9 
				|| Antarctica[road.y + 1][road.x] == 3) {
				road.y++;//way down
			}
			else if (Antarctica[road.y][road.x - 1] == 9 
				|| Antarctica[road.y][road.x - 1] == 3) {
				road.x--;//way left
			}
		}
		//깨지않은 다음스테이지 3을 만날때 까지.
		if (Antarctica[road.y][road.x] == 3)break;

		else if(Antarctica[road.y][road.x] == 5)break;	//이미 이동한 위치에 5가 있으면 모든 스테이지를 클리어 한것!
		else Antarctica[road.y][road.x] = 5;
		//graphic.drawScreen();
	}
	Antarctica[road.y][road.x] = 1;
	tmp_avatar = road;
}

void Map::controlCharacterPiece(int(*board)[38],int action) {
	
	switch (action) {
	case MOVE_LEFT:
		tmp_avatar.x--;
		if (tmp_collide()) tmp_avatar.x++;
		break;
	case MOVE_RIGHT:
		tmp_avatar.x++;
		if (tmp_collide()) tmp_avatar.x--;
		break;
	case JUMP:
		tmp_avatar.y--;
		if (tmp_collide()) tmp_avatar.y++;
		break;
	case CROUCH:
		tmp_avatar.y++;
		if (tmp_collide()) tmp_avatar.y--;
		break;
	}

	board[tmp_avatar.y][tmp_avatar.x] = -2;

}

bool Map::tmp_collide() {
	switch(Antarctica[tmp_avatar.y][tmp_avatar.x])
	{
	case 1: case 5: return false;
	case 0: case 8: case 9: case 3: return true;
	}
}