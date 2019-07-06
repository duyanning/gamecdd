#include "gui.h"
#include "hint.h"

void hint(int i)
{
	set_gui_font_color(RGB(255, 0 , 0));

	set_gui_font_bk_color(RGB(255, 255, 255));
	turn_on_gui_font_bk_color();
	
	set_gui_font_height(128);

	gui_printf(HINT_X, HINT_Y, "第%d关", i);
}

void showSuperStatus(int superman)
{
	set_gui_font_bk_color(RGB(255, 255, 255));
	turn_on_gui_font_bk_color();	
	set_gui_font_height(16);

	if (superman)
		set_gui_font_color(RGB(0, 0 , 0));
	else
		set_gui_font_color(RGB(255, 255 , 255));

	draw_text(SUPER_X, SUPER_Y, "超人");
}

int bulletfull;
void showFullStatus(int bulletfull)
{
	set_gui_font_bk_color(RGB(255, 255, 255));
	turn_on_gui_font_bk_color();	
	set_gui_font_height(16);

	if (bulletfull)
		set_gui_font_color(RGB(0, 0 , 0));
	else
		set_gui_font_color(RGB(255, 255 , 255));

	draw_text(FULL_X, FULL_Y, "子弹无限");
}

int pause;
void showPauseStatus(int pause)
{
	set_gui_font_bk_color(RGB(255, 255, 255));
	turn_on_gui_font_bk_color();	
	set_gui_font_height(16);

	if (pause)
		set_gui_font_color(RGB(0, 0 , 0));
	else
		set_gui_font_color(RGB(255, 255 , 255));

	draw_text(PAUSE_X, PAUSE_Y, "pause");
}