#include "CCell.h"
#include "extern.h"
#include "gui.h"

COLORREF wall_color = RGB(111, 65, 49);
COLORREF path_color = RGB(0, 0, 0);
COLORREF money_color = RGB(255, 255, 0);


void CCell::show()
{
	switch (s) {
	case Wall:
		showWall();
		break;
	case Path:
		showPath();
		break;
	case Hero:
		showFace(hero.face, h);
		break;
	case Guard:
		showFace(Right, g);
		break;
	case Money:
		showMoney();
		break;
	}
}

void CCell::showWall()
{
	set_pen_color(wall_color);
	set_fill_color(wall_color);
	turn_on_fill();
	draw_rectangle(cx - HALF, cy - HALF, cx + HALF + 1, cy + HALF + 1);
}

void CCell::showPath()
{
	set_pen_color(path_color);
	set_fill_color(path_color);
	turn_on_fill();
	draw_rectangle(cx - HALF, cy - HALF, cx + HALF + 1, cy + HALF + 1);
}

void CCell::showMoney()
{
	showPath();
	set_pen_color(money_color);
	set_fill_color(money_color);
	turn_on_fill();
	draw_circle(cx, cy, MR);
}
void CCell::showBullet()
{
	showPath();
	set_pen_color(RGB(255, 0, 0));
	set_fill_color(RGB(255, 0, 0));
	turn_on_fill();
	draw_circle(cx, cy, BR);
}

void CCell::showFace(direction di, who w)
{
	showPath();
	if (w == h) { // hero's face
		set_pen_color(RGB(0, 255, 0));
		set_fill_color(RGB(0, 255, 0));
	}
	else { // guard's face
		set_pen_color(RGB(153, 145, 162));
		set_fill_color(RGB(153, 145, 162));
	}

	turn_on_fill();

	switch (di) {
	case Up:
		draw_pie(cx, cy, 135, 45, FR);
		break;
	case Down:
		draw_pie(cx, cy, -45, 225, FR);
		break;
	case Left:
		draw_pie(cx, cy, 225, 135, FR);
		break;
	case Right:
		draw_pie(cx, cy, 45, 315, FR);
		break;
	}
}

void CCell::focus(int erase)
{
	if (erase == 0) {
		//setcolor(GREEN);
		//rectangle(cx - HALF, cy - HALF, cx + HALF, cy + HALF);
		set_pen_color(RGB(0, 255, 0));
		turn_off_fill();
		draw_rectangle(cx - HALF, cy - HALF, cx + HALF + 1, cy + HALF + 1);
	}
	else {
		if (s == Wall) {
			set_pen_color(wall_color);
			turn_off_fill();
			draw_rectangle(cx - HALF, cy - HALF, cx + HALF + 1, cy + HALF + 1);
		}
		else {
			set_pen_color(path_color);
			turn_off_fill();
			draw_rectangle(cx - HALF, cy - HALF, cx + HALF + 1, cy + HALF + 1);
		}
	}
}