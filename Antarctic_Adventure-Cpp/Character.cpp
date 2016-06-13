#include"Character.h"
#include<string>
const int Character::form[5][9][11] =
{
	{//left
		{ 0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,1,1,0,0,0,0 },
		{ 0,0,0,1,3,1,1,1,0,0,0 },
		{ 0,1,1,1,1,1,1,1,0,0,0 },
		{ 0,0,0,1,1,1,1,1,1,0,0 },
		{ 0,0,0,1,1,1,1,1,0,1,0 },
		{ 0,0,0,2,2,2,2,2,0,0,0 },
		{ 0,0,0,2,2,2,2,2,3,0,0 },
		{ 0,0,2,2,3,0,0,0,0,0,0 }
	},
	{//stand
		{ 0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,1,1,0,0,0,0 },
		{ 0,0,0,1,3,1,1,1,0,0,0 },
		{ 0,0,0,1,1,1,1,1,0,0,0 },
		{ 0,1,1,1,1,1,1,1,1,1,0 },
		{ 0,0,0,1,1,1,1,1,0,0,0 },
		{ 0,0,0,2,2,2,2,2,0,0,0 },
		{ 0,0,0,2,2,2,2,2,0,0,0 },
		{ 0,0,2,2,0,0,0,2,2,0,0 }
	},
	{//right
		{ 0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,1,1,0,0,0,0 },
		{ 0,0,0,1,3,1,1,1,0,0,0 },
		{ 0,0,0,1,1,1,1,1,1,1,0 },
		{ 0,0,1,1,1,1,1,1,0,0,0 },
		{ 0,1,0,1,1,1,1,1,0,0,0 },
		{ 0,0,0,2,2,2,2,2,0,0,0 },
		{ 0,0,3,2,2,2,2,2,0,0,0 },
		{ 0,0,0,0,0,0,3,2,2,0,0 }
	},
	{//ready
		{ 0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,1,1,0,0,0,0 },
		{ 0,0,0,1,3,1,1,1,0,0,0 },
		{ 0,0,0,1,1,1,1,1,0,0,0 },
		{ 0,1,1,1,1,1,1,1,1,1,0 },
		{ 0,0,0,1,1,1,1,1,0,0,0 },
		{ 0,0,0,1,1,1,1,1,0,0,0 },
		{ 0,0,2,2,0,0,0,2,2,0,0 }
	},
	{//jump
		{ 0,0,0,0,1,1,1,0,0,0,0 },//헬리콥터 달면 이모양 유지.
		{ 0,0,0,1,3,1,1,1,0,0,0 },
		{ 0,0,0,1,1,1,1,1,0,0,0 },
		{ 0,0,0,1,1,1,1,1,0,0,0 },
		{ 0,0,1,1,1,1,1,1,1,0,0 },
		{ 0,3,0,1,1,1,1,1,0,3,0 },
		{ 0,0,0,1,1,1,1,1,0,0,0 },
		{ 0,0,0,1,1,3,1,1,0,0,0 },
		{ 0,0,0,1,0,0,0,1,0,0,0 }
	},
};


Character::Character():Entity(14,11) {
	presentForm = form[1];
}

void Character::setPosture(Output* graphic){

	if (collision(this, graphic->getBoard()) || state_stumble) { //지금 충돌이거나, 충돌 동작 상태일때. 제일 우선.
		stumblePosture();	//충돌 동작 animation?
	}
	else if (state_jump)
		jumpPosture();	//점프 동작
	else if (state_crouch)
		crouchPosture();
	else
		idlePosture();	//평상시 캐릭터 동작. 제일 마지막에 안하며 이전 상태를 우선적으로 수행할 수 없을지도.

	presentForm = form[shape % 5];	//결정된 현재 동작을 현재형태에 참조.
	graphic->fixOnBoard(this);	//출력 보드에 현재 객체 배치. 좌표와 형태 모두 필요.
}



void Character::idlePosture() {
	static int shapeCnt = 0;

	if ((shapeCnt % 4) < 2)	//0,1
		shape++;
	else	//2,3
		shape--;

	// 위와 동일 ((shapeCnt % 4) < 2) ? shape++ : shape--;

	tmp_shape = shape;	//끝났을때의 상태를 임시로 저장해둠.
						//다른 동작이 끝나고 왔을때 이 상태로 다시옴.
	shapeCnt++; //0,1,2,3,4,5,6,7,8....	
	//카운트를 '나중에' 올려줘야 현재 상태에 대한 다음 상태를 제대로 지정해줄수 있음.
}



void Character::stumblePosture() {
	static int stumbleCnt = 0;

	if (stumbleCnt == 0) {
		state_stumble = true;
		shape = (action==MOVE_RIGHT) ? 0 : 2; //이전에 오른쪽으로 이동 중이였다면 모양에 0(왼쪽)대입.
	}
	else {
		tmp_act = (shape == 0) ? MOVE_LEFT : MOVE_RIGHT;
		//벽과 충돌하는 경우를 배제하기 위해 직접적으로 좌표를 바꿔주지 않았다.
		//좌표로 판단할 시 중앙에서 좌우로 왔다갔다하는 버그가 생김.
		if (stumbleCnt == 7) {
			state_stumble = false;
			shape = tmp_shape;	//형태를 이전 동작으로 복구시킴
			stumbleCnt = 0;
			return;		// 초기화 이후에 cnt가 다시 일어나지 않도록 중단 시켜야함.
		}
		else
			(stumbleCnt % 2) ? y-- : y++;	//홀수 일때는 위로, 짝수일땐 아래로.
	}
	
	stumbleCnt++;
}

void Character::jumpPosture() {	//점프 동작과 높이를 정해주는 함수.
	static int jumpCnt = 0;

	if (jumpCnt == 0) {	//점프를 시작할때 형태를 3으로.
		shape = 3;
	}
	else if (jumpCnt == 9) {//7
		//y++;
		state_jump = false;
		shape = tmp_shape;	//형태를 이전에 하던 동작으로 복구시킴
		jumpCnt = 0;
		return;
	}
	else {
		(jumpCnt < 5) ? y-- : y++;	//4
		if (jumpCnt == 4) y++;
		if (jumpCnt == 5) y--;
		//if (jumpCnt == 6) y--;
		shape = (jumpCnt < 8) ? 4 : 3;	//마지막 카운트되기전까진 형태에 4대입.
	}

	jumpCnt++;
}

void Character::crouchPosture() {

	if (action != CROUCH)	// 우선적으로 해야 shape=3 대입 전에 해줄수 있음..
	{
		shape = tmp_shape;
		state_crouch = false;
		return;
	}
	else 
		shape = 3;

	//tmp_act = CROUCH;
}


void Character::movePos(Output* graphic) {
	if (state_stumble) action = tmp_act; //헛디딤 상태일때 어떤 키도 받지 못하게.

	switch (action)
	{
	case MOVE_LEFT:
		if (x >= 0)	x--;
		break;
	case MOVE_RIGHT:
		if (x < 28)	x++;
		break;
	case IDLE:
		break;
	case CROUCH:
		state_crouch = true;
		break;
	case JUMP:
		state_jump = true;	//점프가 눌리면 점프상태로 전환.
		//중도에 좌우 키가 눌려도 인식 할 수 있다.
		//action이 하나이기에 case외부에 하는건 의미가 없다.
		break;
	case STAGE_CLEAR:
		/*차차 와이좌표 감소하며 기지에 가까이.*/
	case GAME_QUIT:
		break;
	default:
		break;
	}

	setPosture(graphic);
}