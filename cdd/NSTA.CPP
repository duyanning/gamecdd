#include "nsta.h"
CCell nStatus[MAX_BULLETS];

void initNStatus()
{
	nStatus[0].cx = START_X + 10;
	nStatus[0].cy = START_Y - 10;

	nStatus[1].cx = START_X + 10 + 30;
	nStatus[1].cy = START_Y - 10;

	nStatus[2].cx = START_X + 10 + 30 + 30;
	nStatus[2].cy = START_Y - 10;
}
void showNStatus(int n)
{
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (i < n)
			nStatus[i].showBullet();
		else
			nStatus[i].showPath();
	}
}