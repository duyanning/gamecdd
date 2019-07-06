#ifndef CCELL_H
#define CCELL_H
#include "who.h"
#include "status.h"
#include "direction.h"
#define HALF	8
#define MR		1
#define BR		3
#define FR		6
class CCell {
public:
	int cx;
	int cy;
	status s;
	void show();
	void showWall();
	void showPath();
	void showMoney();
	void showBullet();
	void showFace(direction, who);
	void focus(int);
};
#endif