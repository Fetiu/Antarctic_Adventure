#pragma once

#ifndef __GROUND_H__
#define __GROUND_H__

class Ground {
public:
	Ground(int(*board)[38]);
	void updateGround(int(*board)[38]);
	int stage;//퍼블릭? 나중에 이스터에그로 다른스테이지가게?

	const static int landscape[3][22][38];
private:
	int shape = 0;
};

#endif// !__GROUND_H__
