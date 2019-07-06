#include "CMaze.h"
#include "go.h"
#include "extern.h"
#include "err.h"
#include "nsta.h"
#include "hint.h"
#include "gui.h"

CMaze m;
CHero hero;
CGuard guard[MAX_GUARDS];
int blti;
CBullet bullet[MAX_BULLETS];
int alldead = 1;
int nMoney;
int capture;
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


int choice;
int iMission = 1;

int loadMap(const char *fn)
{
	superman = 0;
	bulletfull = 0;
	pause = 0;
	//showSuperStatus(superman);
	//showFullStatus(bulletfull);
	//showPauseStatus(pause);
	//hint(i);
	FILE *fp = fopen(fn, "rb");
	if (fp == NULL) {
		//error("data file %d is lost!", i);
		//printf("data file %d is lost!", i);
		printf("data file %s is lost!\n", fn);
		exit(1);
		//waitKey();
		//clrline("data file %d is lost!", i);
		return 1;
	}
	fclose(fp);
	m.fromFile(fn);
	hero.x = m.hero.x; hero.y = m.hero.y;
	hero.face = Left;
	int n;
	for (n = 0; n < MAX_BULLETS; n++) {
		bullet[n].dead = 1;
	}
	blti = MAX_BULLETS;
	initNStatus();
	//showNStatus(blti);
	initCanGo();
	for (n = 0; n < MAX_GUARDS; n++) {
		guard[n].x = guard[n].prex = m.guard[n].x;
		guard[n].y = guard[n].prey = m.guard[n].y;
		guard[n].dead = m.guard[n].dead;
		guard[n].fo = Path;
	}
	nMoney = m.nMoney;
	//m.show();
	capture = 0;

	return 0;
}

int loadMission(int i)
{
	return loadMap(mn[i - 1]);
}

void showAll(void)
{
	m.show();
	showSuperStatus(superman);
	showFullStatus(bulletfull);
	showPauseStatus(pause);
	if (iMission > 0) {
		hint(iMission);
	}
	showNStatus(blti);
}

void on_refresh(void)
{
	showAll();
}

void check(void)
{
	if (capture == 1) { // 被抓住，游戏结束
		//sound(DIEFRE);
		//delay(DIETIME);
		//nosound();
		quit_gui();
		return;
	}

	if (nMoney == 0) { // 把本关的豆豆吃光了
		//sound(OKFRE);
		//delay(OKTIME);
		//nosound();
		// 如果是标准关卡，就进入下一关，否则结束
		if (choice == 1) {
			if (iMission < 9) {
				iMission++;
				loadMission(iMission);
				showAll();
			}
			else {
				quit_gui();
			}
		}
		else {
			quit_gui();
		}
		
		return;
	}

}

void on_input(const char *s)
{
	if (strcmp(s, " ") == 0) {
		if (blti) {
			//sound(BULLETFRE);
			//delay(BULLETTIME);
			//nosound();
			bullet[blti - 1].where = hero.face;
			bullet[blti - 1].fo = Hero;
			bullet[blti - 1].dead = 0;
			bullet[blti - 1].x = hero.x;
			bullet[blti - 1].y = hero.y;
			blti--;
		}
		int i;
		for (i = 0; i < MAX_BULLETS && bullet[i].dead == 1; i++)
			;
		if (i < MAX_BULLETS)
			alldead = 0;
		else
			alldead = 1;
		if (blti == 0 && bulletfull && alldead) {
			blti = MAX_BULLETS;
		}
		showNStatus(blti);
		goStop();

		check();
	}
	else {
	}
}


void on_esc(void)
{
}

void on_arrow(enum ArrowDirection d)
{
	switch (d) {
	case AD_UP:
		goUp();
		break;
	case AD_DOWN:
		goDown();
		break;
	case AD_LEFT:
		goLeft();
		break;
	case AD_RIGHT:
		goRight();
		break;
	}

	check();

}

void on_time_pass(void)
{
	goStop();
	check();
}


void on_fn(int n)
{
	switch (n) {
	case 3: {
		superman = !superman;
		showSuperStatus(superman);
		break;
	}
	case 4: {
		bulletfull = !bulletfull;
		showFullStatus(bulletfull);
		break;
	}
	case 9: {
		pause = 1;
		showPauseStatus(pause);
		break;
	}

	}
}

int main(void)
{

	puts("1.标准关卡");
	puts("2.指定关卡");
	puts("请选择:");

	scanf("%d", &choice);
	if (choice == 1) {
		loadMission(iMission);
	}
	else {
		puts("请输入关卡名字:");
		char fn[50];
		scanf("%s", fn);
		loadMap(fn);
		iMission = 0;
	}


	please_call_this_function_when_refresh(on_refresh);
	please_call_this_function_when_keyboard_input(on_input);
	please_call_this_function_when_arrow_key_pressed(on_arrow);
	please_call_this_function_when_fn_key_pressed(on_fn);
	please_call_this_function_when_esc_key_pressed(on_esc);
	please_call_this_function_every_N_milliseconds(on_time_pass, 100);

	play_gui();

	return 0;
}