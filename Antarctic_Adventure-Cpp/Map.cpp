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
	//�������� Ŭ���� ������ ���� �������� ������.

	//1�� ���� ��������, 5�� ������, 3�� �ȿ��� ��������,9�� �ȿ�����.

	while (1) {
		//���̰ų� �̹̱� ���������� ���
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
		//�������� ������������ 3�� ������ ����.
		if (Antarctica[road.y][road.x] == 3)break;

		else if(Antarctica[road.y][road.x] == 5)break;	//�̹� �̵��� ��ġ�� 5�� ������ ��� ���������� Ŭ���� �Ѱ�!
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