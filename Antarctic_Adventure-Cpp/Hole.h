
#ifndef __HOLE_H__
#define __HOLE_H__

#include"Entity.h"
#include"Output.h"

class Hole : public Entity //Entity���. Entity�� ����� �⺻���� ������.
{
public:
	Hole(const int start_x);
	//int x, y;
	void movePos(Output* graphic);
	void setForm(Output* graphic);
private:
	const static int form[5][9][11];
	void setPosX();

};

#endif //!__HOLE_H__
