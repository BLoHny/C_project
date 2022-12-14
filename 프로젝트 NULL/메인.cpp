#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

void stage();
void home_start();

int main()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };//깜박거리는 커서 제거    
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	system("mode con cols=192 lines=52 | title NULL tower");

	home_start();
}