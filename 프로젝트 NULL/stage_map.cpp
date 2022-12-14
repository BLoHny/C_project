#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
void gotoxy(float x, int y);

void stage_map_main()
{
	gotoxy(0, 0);
	int map_x = 0, map_y = 8;
	for (int i = 0; i < 96; i++) {
		gotoxy(map_x, 7);
		if (i != 6)
			printf("收收");
		else
			printf("有有");
		map_x++;
	}
	for (int i = 0; i < 37; i++) {
		gotoxy(6, map_y); printf("朱朱"); map_y++;
	}
	map_x = 0;
	for (int i = 0; i < 96; i++) {
		gotoxy(map_x, map_y);
		if (i != 6)
			printf("收收");
		else
			printf("朴朴");
		map_x++;
	}
}
