#pragma once

#ifndef __STATION_H__
#define __STATION_H__

#include"Entity.h"

class Station:public Entity {
public:
	int(*presentForm)[22];
private:
	const int form[5][12][22];
};


#endif