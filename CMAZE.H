#ifndef CMAZE_H
#define CMAZE_H
#include <stdio.h>
#include <stdlib.h>
#include "CCell.h"
#include "figure.h"
#define START_X		50
#define START_Y		40
#define MAX_X		21
#define MAX_Y		21
#define MAX_GUARDS	8
#define MAX_BULLETS 3
#define EATFRE		60
#define EATTIME		50
#define DIEFRE		50
#define DIETIME		200
#define OKFRE		400
#define OKTIME		1000
#define BULLETFRE	300
#define BULLETTIME	30
class CMaze {
public:
	CCell m[MAX_X][MAX_Y];
	CHero hero;
	int nGuards;
	CGuard guard[MAX_GUARDS];
	int nMoney;
	CMaze();
	~CMaze();
	status xyStatus(int i, int j)
	{
		return m[i][j].s;
	}
	void setStatus(status s, int i, int j)
	{
		m[i][j].s = s;
	}
	int fromFile(const char *fn);
	void toFile(char *fn);
	void show();
	void focusAt(int y, int x, int erase)
	{
		m[y][x].focus(erase);
	}
};
#endif