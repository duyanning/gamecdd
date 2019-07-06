#ifndef FIGURE_H
#define FIGURE_H
#include "direction.h"
#include "status.h"
class figure {
public:
	int x;
	int y;
	int dead;
	virtual void go(direction) = 0;
};

class CHero : public figure {
public:
	direction face;
	virtual void go(direction);
};

class  CGuard : public figure {
public:
	int prex, prey;
	status fo;
	virtual void go(direction);
};

class  CBullet: public figure {
public:
	status fo;
	direction where;
	virtual void go(direction);
};
#endif