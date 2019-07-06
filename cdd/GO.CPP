#include "extern.h"
int gCanGo[MAX_GUARDS];
void initCanGo()
{
	for (int i = 0; i < MAX_GUARDS; i++)
		gCanGo[i] = 0;
}
int superman;
void guardsGo()
{
	for (int i = 0; i < MAX_GUARDS; i++) {
		if (guard[i].dead == 0 && gCanGo[i] == 0) {
			guard[i].go(Follow);
			// 'Follow' means to be decided by guard self
		}
		gCanGo[i]++;
		int waitn;
		if (superman) {
			waitn = 15;
		}
		else {
			waitn = 3;
		}
		if (gCanGo[i] >= waitn)
			gCanGo[i] = 0;
	}
}
void bulletGo()
{
	for (int i = MAX_BULLETS - 1; i >= 0; i--) {
		if (bullet[i].dead == 0)
			bullet[i].go(Follow);
	}
}
void goUp()
{
	bulletGo();
	hero.go(Up);
	guardsGo();
}

void goDown()
{
	bulletGo();
	hero.go(Down);
	guardsGo();
}

void goLeft()
{
	bulletGo();
	hero.go(Left);
	guardsGo();
}

void goRight()
{
	bulletGo();
	hero.go(Right);
	guardsGo();
}

void goStop()
{
	bulletGo();
	guardsGo();
}