#ifndef EXTERN_H
#define EXTERN_H
#include "CMaze.h"
#include "figure.h"
extern CMaze m;
extern CHero hero;
extern CGuard guard[MAX_GUARDS];
extern CBullet bullet[MAX_BULLETS];
extern int nMoney;
extern int capture;
extern int gCanGo[MAX_GUARDS];
extern int superman;
#endif