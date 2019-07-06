#include <math.h>
#include <dos.h>
#include "figure.h"
#include "status.h"
#include "extern.h"
void CHero::go(direction di)
{
	face = di;
	int nextx, nexty;
	switch (di) {
	case Up:
		nextx = x;
		nexty = y - 1;
		break;
	case Down:
		nextx = x;
		nexty = y + 1;
		break;
	case Left:
		nextx = x - 1;
		nexty = y;
		break;
	case Right:
		nextx = x + 1;
		nexty = y;
		break;
	} // switch

	status s = m.xyStatus(nexty, nextx);
	switch (s) {
	case Path:
		m.setStatus(Path, y, x);
		m.m[y][x].showPath();
		m.setStatus(Hero, nexty, nextx);
		m.m[nexty][nextx].showFace(di, h);
		x = nextx; y = nexty;
		break;
	case Money:
		m.setStatus(Path, y, x);
		m.m[y][x].showPath();
		m.setStatus(Hero, nexty, nextx);
		m.m[nexty][nextx].showFace(di, h);
		x = nextx; y = nexty;
		nMoney--;
		//sound(EATFRE);
		//delay(EATTIME);
		//nosound();
		break;
	case Wall:
		m.m[y][x].showFace(di, h);
		break;
	case Guard:
		m.setStatus(Path, y, x);
		m.m[y][x].showPath();
		capture = 1;
		break;
	} // switch
}

/*      x j
 o	__________
   |
 y |
 i |
   |
*/
double distance(int x1, int y1, int x2, int y2)
{
	int xd = x2 - x1;
	int yd = y2 - y1;
	return sqrt(xd * xd + yd * yd);
}
void CGuard::go(direction di)
{
	int pass[4]; // Up, Down, Left, Right
	int i;
	// 先假设上下左右四个方向皆可通行
	for (i = 0; i < 4; i++)
		pass[i] = 1;

	int nextx, nexty;
	status s;

	// 确定不能通行的方向(墙、其他卫兵、之前所在的地方，都不能通行)
	for (i = 0; i < 4; i++) {
		switch (i) {
		case 0: // Up
			nextx = x; nexty = y - 1;
			break;
		case 1: // Down
			nextx = x; nexty = y + 1;
			break;
		case 2: // Left
			nextx = x - 1; nexty = y;
			break;
		case 3: // Right
			nextx = x + 1; nexty = y;
			break;
		} // switch
		s = m.xyStatus(nexty, nextx);
		if (s == Wall || s == Guard || nextx == prex && nexty == prey)
			pass[i] = 0;
	} // for

	// 找出一个可以通行的方向
	for (i = 0; i < 4 && pass[i] == 0; i++)
		;
	
	// 如果找不出，就降低标准（只有其他卫兵、墙不能走，自己以前呆过的地方还可以走）
	if (i == 4) {
		for (i = 0; i < 4; i++) {
			pass[i] = 1;
			switch (i) {
			case 0: // Up
				nextx = x; nexty = y - 1;
				break;
			case 1: // Down
				nextx = x; nexty = y + 1;
				break;
			case 2: // Left
				nextx = x - 1; nexty = y;
				break;
			case 3: // Right
				nextx = x + 1; nexty = y;
				break;
			} // switch
			s = m.xyStatus(nexty, nextx);
			if (s == Wall || s == Guard)
				pass[i] = 0;
		} // for
	}

	// 对于可通行的方向，如果可以我更接近英雄，就定下这个方向
	for (i = 0; i < 4; i++) {
		if (pass[i]) {
			int nextx, nexty;
			switch (i) {
			case 0: // Up
				di = Up;
				nextx = x; nexty = y - 1;
				break;
			case 1: // Down
				di = Down;
				nextx = x; nexty = y + 1;
				break;
			case 2: // Left
				di = Left;
				nextx = x - 1; nexty = y;
				break;
			case 3: // Right
				di = Right;
				nextx = x + 1; nexty = y;
				break;
			} // switch
			if (distance(nextx, nexty, hero.x, hero.y)
				<distance(x, y, hero.x, hero.y)
				)
				break;
		} // if
	} // for

	// 根据定下的方向，确定下一步的坐标
	switch (di) {
	case Up:
		nextx = x; nexty = y - 1;
		break;
	case Down:
		nextx = x; nexty = y + 1;
		break;
	case Left:
		nextx = x - 1; nexty = y;
		break;
	case Right:
		nextx = x + 1; nexty = y;
		break;
	default:
		nextx = x; nexty = y; // 原地不动
		return;
	} // switch

	// 移动卫兵（恢复卫兵当前位置原来的事物，在新位置处放上卫兵）
	m.setStatus(fo, y, x);
	m.m[y][x].show();
	switch (m.xyStatus(nexty, nextx)) {
	case Path:
		fo = Path;
		break;
	case Money:
		fo = Money;
		break;
	case Hero:
		capture = 1;
		break;
	case Bullet:
		//sound(DIEFRE);
		//delay(DIETIME);
		//nosound();
		for (int i = 0; i < MAX_BULLETS; i++)
			if (bullet[i].x == nextx && bullet[i].y == nexty
				&& bullet[i].dead == 0
				)
				break;
		bullet[i].dead = 1;
		dead = 1;
		m.setStatus(bullet[i].fo, nexty, nextx);
		m.m[nexty][nextx].show();
		return;
	} // switch
	m.setStatus(Guard, nexty, nextx);
	m.m[nexty][nextx].showFace(di, g);
	prex = x; prey = y;
	x = nextx; y = nexty;
}

void CBullet::go(direction di)
{
	int nextx, nexty;
	switch (where) {
	case Up:
		nextx = x; nexty = y - 1;
		break;
	case Down:
		nextx = x; nexty = y + 1;
		break;
	case Left:
		nextx = x - 1; nexty = y;
		break;
	case Right:
		nextx = x + 1; nexty = y;
		break;
	} // switch

	status s;
	s = m.xyStatus(nexty, nextx);
	switch (s) {
	case Wall:
		m.setStatus(fo, y, x);
		m.m[y][x].show();
		dead = 1;
		break;
	case Money:
		m.setStatus(fo, y, x);
		m.m[y][x].show();
		m.setStatus(Bullet, nexty, nextx);
		m.m[nexty][nextx].showBullet();
		x = nextx; y = nexty;
		fo = Money;
		break;
	case Path:
		m.setStatus(fo, y, x);
		m.m[y][x].show();
		m.setStatus(Bullet, nexty, nextx);
		m.m[nexty][nextx].showBullet();
		x = nextx; y = nexty;
		fo = Path;
		break;
	case Guard: {
		m.setStatus(fo, y, x);
		m.m[y][x].show();
		int i;
		for (i = 0; i < MAX_GUARDS; i++)
			if (guard[i].x == nextx && guard[i].y == nexty
				&& guard[i].dead == 0
				)
				break;
		guard[i].dead = 1;
		m.setStatus(guard[i].fo, nexty, nextx);
		m.m[nexty][nextx].show();
		dead = 1;
		//sound(DIEFRE);
		//delay(DIETIME);
		//nosound();
		break;
	}
	case Hero:
		break;
	case Bullet:
		m.setStatus(fo, y, x);
		m.m[y][x].show();
		m.setStatus(Bullet, nexty, nextx);
		m.m[nexty][nextx].showBullet();
		int i;
		for (i = 0; i < MAX_BULLETS; i++)
			if (bullet[i].x == nextx && bullet[i].y == nexty)
				break;
		fo = bullet[i].fo;
		x = nextx; y = nexty;
		break;
	} // switch
}