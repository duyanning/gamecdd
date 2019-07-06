#include <stdio.h>
#include <string.h>
#include "gui.h"
#include "CMaze.h"
//#include "key.h"
#include "figure.h"
#include "err.h"
CMaze m;
CHero hero;
int nGuards;
CGuard guard[MAX_GUARDS];
int nMoney = 0;
int okhero = 0; // have not set hero
int capture; // no use, only to avoid link time error
CBullet bullet[MAX_BULLETS]; // no use, only to avoid link time error
char copyright[] = "Du Yan Ning 2001.02.16; 2014.03.22";
const char *mn[] =
{
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9"
};




int x; int y; // focus's position

void on_input(const char *s)
{
	if (strcmp(s, "g") == 0 || strcmp(s, "G") == 0) {
		if (m.xyStatus(y, x) == Path && nGuards < MAX_GUARDS) {
			m.setStatus(Guard, y, x);
			m.m[y][x].showFace(Right, g);
			int i;
			for (i = 0; i < MAX_GUARDS; i++)
				if (guard[i].dead == 1)
					break;
			guard[i].x = x;
			guard[i].y = y;
			guard[i].dead = 0;
			nGuards++;
			m.focusAt(y, x, 0);
		}
		else if (m.xyStatus(y, x) == Guard) {
			m.setStatus(Path, y, x);
			m.m[y][x].showPath();
			int i;
			for (i = 0; i < MAX_GUARDS; i++)
				if (guard[i].x == x && guard[i].y == y)
					break;
			guard[i].dead = 1;
			nGuards--;
			m.focusAt(y, x, 0);
		}
	}
	else if (strcmp(s, "h") == 0 || strcmp(s, "H") == 0) {
		if (m.xyStatus(y, x) == Path) {
			if (okhero) {
				m.setStatus(Path, hero.y, hero.x);
				m.m[hero.y][hero.x].showPath();
			}
			m.setStatus(Hero, y, x);
			m.m[y][x].showFace(Left, h);
			hero.x = x;	hero.y = y;
			okhero = 1;
			m.focusAt(y, x, 0);
		}
	}
	else if (strcmp(s, "m") == 0 || strcmp(s, "M") == 0) {
		if (m.xyStatus(y, x) == Money) {
			m.setStatus(Path, y, x);
			m.m[y][x].showPath();
			nMoney--;
		}
		else if (m.xyStatus(y, x) == Path) {
			m.setStatus(Money, y, x);
			m.m[y][x].showMoney();
			nMoney++;
		}
		m.focusAt(y, x, 0);
	}
	else if (strcmp(s, " ") == 0) {
		if (m.xyStatus(y, x) == Wall) {
			m.setStatus(Path, y, x);
			m.m[y][x].showPath();
		}
		else if (m.xyStatus(y, x) == Path) {
			m.setStatus(Wall, y, x);
			m.m[y][x].showWall();
		}
		m.focusAt(y, x, 0);
	}
	else {
	}
}

void on_refresh(void)
{
	m.show();
	m.focusAt(x, y, 0);
}

void on_esc(void)
{
	if (nMoney == 0) {
		const char *msg =
			"you should at least set a money!"
			"press any key to continue.";
		error(msg);
		//waitKey();
		clrline(msg);

		return;
	}

	if (okhero == 0) {
		const char *msg =
			"you have not set hero! press any key to continue.";
		error(msg);
		//waitKey();
		clrline(msg);

		return;
	}

	quit_gui();
}

void on_arrow(enum ArrowDirection d)
{
	switch (d) {
	case AD_UP:
		m.focusAt(y, x, 1); // erase
		m.focusAt((y - 1 + MAX_Y) % MAX_Y, x, 0);
		x =  x;
		y = (y - 1 + MAX_Y) % MAX_Y;
		break;
	case AD_DOWN:
		m.focusAt(y, x, 1); // erase
		m.focusAt((y + 1) % MAX_Y, x, 0);
		x = x;
		y = (y + 1) % MAX_Y;
		break;
	case AD_LEFT:
		m.focusAt(y, x, 1); // erase
		m.focusAt(y, (x - 1 + MAX_X) % MAX_X, 0);
		x = (x - 1 + MAX_X) % MAX_X;
		y = y;
		break;
	case AD_RIGHT:
		m.focusAt(y, x, 1); // erase
		m.focusAt(y, (x + 1) % MAX_X, 0);
		x = (x + 1) % MAX_X;
		y = y;
		break;
	}

}


int main(int argc, char *argv[])
{

	puts("which map do you want to edit?");
	char fn[130];
	//gets(fn);
	scanf("%s", fn);

	FILE *fp;
	fp = fopen(fn, "rb");
	if (fp) {
		fclose(fp);

		hero.x = MAX_X - 2;	hero.y = MAX_Y - 2;
		nGuards = 0;
		nMoney = 0;
		if (m.fromFile(fn)) { // maze with specified name exists
			hero.x = m.hero.x; hero.y = m.hero.y;
			okhero = 1;
			// because this is a old maze, so hero has already exist
			nGuards = m.nGuards;
			int i;
			for (i = 0; i < MAX_GUARDS; i++) {
				guard[i].x = m.guard[i].x; guard[i].y = m.guard[i].y;
				guard[i].dead = m.guard[i].dead;
			}
			nMoney = m.nMoney;
		}
	}
	else {
		for (int i = 0; i < MAX_GUARDS; i++)
			guard[i].dead = 1;
		hero.x = MAX_X - 2; hero.y = MAX_Y - 2; //
		nGuards = 0;
		nMoney = 0;

	}

	hero.face = Left;
	x = MAX_X - 1; y = MAX_Y - 1; // focus's begin position

	please_call_this_function_when_refresh(on_refresh);
	please_call_this_function_when_keyboard_input(on_input);
	please_call_this_function_when_arrow_key_pressed(on_arrow);
	please_call_this_function_when_esc_key_pressed(on_esc);

	play_gui();

	m.hero.x = hero.x; m.hero.y = hero.y;
	int i;
	for (i = 0; i < MAX_GUARDS; i++) {
		m.guard[i].x = guard[i].x; m.guard[i].y = guard[i].y;
		m.guard[i].dead = guard[i].dead;
	}
	m.nGuards = nGuards;
	m.nMoney = nMoney;

	printf("save %s? [Y/N]", fn);
	char answer[10];
	//gets(answer);
	scanf("%s", answer);
	if (strcmp(answer, "Y") == 0 || strcmp(answer, "y") == 0)
		m.toFile(fn); // save
	

	return 0;
}