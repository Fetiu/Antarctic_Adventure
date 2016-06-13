#include"Map.h"

#include<string.h>

Map::Map(int(*board)[38]) {
	memcpy(board, Antartica, sizeof(int) * 22 * 38);
}

void Map::updateMap(int(*board)[38]) {
	memcpy(board, Antartica, sizeof(int) * 22 * 38);
}

void Map::printCharacterPiece() {}