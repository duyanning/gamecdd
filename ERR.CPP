#include <stdio.h>
#include <stdarg.h>
#include <conio.h>
#include "err.h"
#include "gui.h"


void error(const char *fmt, ...)
{
	char msg[100];
	va_list args;
	va_start(args, fmt);
	vsprintf(msg, fmt, args);
	/*
	setfillstyle(SOLID_FILL, WHITE);
	bar(MSG_X - 2, MSG_Y - 2,
		MSG_X + textwidth(msg), MSG_Y + textheight(msg)
		);
	setcolor(RED);
	outtextxy(MSG_X, MSG_Y, msg);
	*/

	set_gui_font_color(RGB(255, 0, 0));
	set_gui_font_height(18);
	draw_text(MSG_X, MSG_Y, msg);
	va_end(args);
}
void clrline(const char *fmt, ...)
{
	char msg[100];
	va_list args;
	va_start(args, fmt);
	vsprintf(msg, fmt, args);
	/*
	setfillstyle(SOLID_FILL, getbkcolor());
	bar(MSG_X - 2, MSG_Y - 2,
		MSG_X + textwidth(msg), MSG_Y + textheight(msg)
		);
	*/
	va_end(args);
}

void Ggets(char *buf)
{
	/*
	int x, y;
	x = MSG_X;
	y = MSG_Y + textheight("") + 5;
	setfillstyle(SOLID_FILL, getbkcolor());
	bar(x - 2, y - 2,
		x + textwidth("                   "), y + textheight("")
		);
	char c;
	int i = 0;
	while ((c = getch()) != '\r') {
		buf[i] = c;
		buf[i + 1] = '\0';
		setfillstyle(SOLID_FILL, WHITE);
		bar(x - 2, y - 2,
			x + textwidth(buf), y + textheight(buf)
			);
		setcolor(RED);
		outtextxy(x, y, buf);
		i++;
	}
	*/
}
