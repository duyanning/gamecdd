#ifndef HINT_H
#define HINT_H
#include "CMaze.h"
#define HINT_X	 500
#define HINT_Y	 5
#define SUPER_X	 (START_X + 210)
#define SUPER_Y	 (START_Y - 10)
#define FULL_X	 (SUPER_X + 50)
#define FULL_Y	 (SUPER_Y)
#define PAUSE_X	 (SUPER_X + 50 + 50)
#define PAUSE_Y	 (SUPER_Y)
extern int bulletfull;
extern int pause;
void hint(int i);
void showSuperStatus(int superman);
void showFullStatus(int bulletfull);
void showPauseStatus(int pause);
#endif