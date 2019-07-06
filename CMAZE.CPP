#include "CMaze.h"

CMaze::CMaze()
{
	for (int i = 0; i < MAX_Y; i++)
		for (int j = 0; j < MAX_X; j++) {
			m[i][j].cx = START_X + j * 2  * HALF + j + HALF;
			m[i][j].cy = START_Y + i * 2  * HALF + i + HALF;
			if (i == 0 || i == MAX_Y - 1 || j == 0 || j == MAX_X - 1)
				setStatus(Wall, i, j);
			else
				setStatus(Path, i, j);
		}
}

CMaze::~CMaze()
{
}

void CMaze::show()
{
	for (int i = 0; i < MAX_X; i++)
		for (int j = 0; j < MAX_Y; j++)
			m[i][j].show();
}

int CMaze::fromFile(const char *fn)
{
	FILE *fp;
	fp = fopen(fn, "rb");
	if (fp != NULL) {
		fread(m, sizeof (CCell), MAX_X * MAX_Y, fp);
		fread(&hero.x, sizeof (int), 1, fp);
		fread(&hero.y, sizeof (int), 1, fp);
		fread(&nGuards, sizeof (int), 1, fp);
		for (int i = 0; i < MAX_GUARDS; i++) {
			fread(&guard[i].x, sizeof (int), 1, fp);
			fread(&guard[i].y, sizeof (int), 1, fp);
			fread(&guard[i].dead, sizeof (int), 1, fp);
		}
		fread(&nMoney, sizeof (int), 1, fp);
		fclose(fp);
		return 1;
	}
	return 0;
}
void CMaze::toFile(char *fn)
{
	FILE *fp;
	fp = fopen(fn, "wb");
	fwrite(m, sizeof (CCell), MAX_X * MAX_Y, fp);
	fwrite(&hero.x, sizeof (int), 1, fp);
	fwrite(&hero.y, sizeof (int), 1, fp);
	fwrite(&nGuards, sizeof (int), 1, fp);
	for (int i = 0; i < MAX_GUARDS; i++) {
		fwrite(&guard[i].x, sizeof (int), 1, fp);
		fwrite(&guard[i].y, sizeof (int), 1, fp);
		fwrite(&guard[i].dead, sizeof (int), 1, fp);
	}
	fwrite(&nMoney, sizeof (int), 1, fp);
	fclose(fp);
}
